//*****************************************************************************
//
//! @file am_devices_atxp032.c
//!
//! @brief Micron Serial NOR SPI Flash driver.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2018, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision v1.2.12-830-g39ebe7dbe of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_devices_atxp032.h"
#include "am_util_stdio.h"
#include "am_bsp.h"
#include "am_util_delay.h"

//*****************************************************************************
//
// Global variables.
//
//*****************************************************************************
#define AM_DEVICES_ATXP032_TIMEOUT             1000000
#define AM_DEVICES_ATXP032_ERASE_TIMEOUT       1000000

am_hal_mspi_dev_config_t        g_psMSPISettings;

void                            *g_pMSPIHandle;

volatile bool                   g_MSPIDMAComplete;

am_hal_mspi_pio_transfer_t      g_PIOTransaction;
uint32_t                        g_PIOBuffer[16];

volatile uint32_t               g_MSPIInterruptStatus;

am_hal_mspi_dev_config_t  SerialMSPIConfig =
{
  .eSpiMode             = AM_HAL_MSPI_SPI_MODE_0,
  .eClockFreq           = AM_HAL_MSPI_CLK_24MHZ,
  .ui8TurnAround        = 8,
  .eAddrCfg             = AM_HAL_MSPI_ADDR_4_BYTE,
  .eInstrCfg            = AM_HAL_MSPI_INSTR_1_BYTE,
  .eDeviceConfig        = AM_HAL_MSPI_FLASH_SERIAL_CE0,
  .bSeparateIO          = true,
  .bSendInstr           = true,
  .bSendAddr            = true,
  .bTurnaround          = true,
  .ui8ReadInstr         = AM_DEVICES_ATXP032_READ,
  .ui8WriteInstr        = AM_DEVICES_ATXP032_PAGE_PROGRAM,
  .ui32TCBSize          = 0,
  .pTCB                 = NULL,
  .scramblingStartAddr  = 0,
  .scramblingEndAddr    = 0,
};

//*****************************************************************************
//
// Generic Command Write function.
//
//*****************************************************************************
uint32_t am_device_command_write(uint8_t ui8Instr, bool bSendAddr,
                                 uint32_t ui32Addr, uint32_t *pData,
                                 uint32_t ui32NumBytes)
{
  // Create the individual write transaction.
  g_PIOTransaction.ui32NumBytes       = ui32NumBytes;
  g_PIOTransaction.eDirection         = AM_HAL_MSPI_TX;
  g_PIOTransaction.bSendAddr          = bSendAddr;
  g_PIOTransaction.ui32DeviceAddr     = ui32Addr;
  g_PIOTransaction.bSendInstr         = true;
  g_PIOTransaction.ui16DeviceInstr    = ui8Instr;
  g_PIOTransaction.bTurnaround        = false;
  g_PIOTransaction.bContinue          = false;
  g_PIOTransaction.bQuadCmd           = false;
  g_PIOTransaction.pui32Buffer        = pData;

  // Execute the transction over MSPI.
  return am_hal_mspi_blocking_transfer(g_pMSPIHandle, &g_PIOTransaction,
                                       AM_DEVICES_ATXP032_TIMEOUT);
}

uint32_t am_device_command_read(uint8_t ui8Instr, bool bSendAddr,
                                uint32_t ui32Addr, uint32_t *pData,
                                uint32_t ui32NumBytes)
{
  // Create the individual write transaction.
  g_PIOTransaction.eDirection         = AM_HAL_MSPI_RX;
  g_PIOTransaction.bSendAddr          = bSendAddr;
  g_PIOTransaction.ui32DeviceAddr     = ui32Addr;
  g_PIOTransaction.bSendInstr         = true;
  g_PIOTransaction.ui16DeviceInstr    = ui8Instr;
  g_PIOTransaction.bTurnaround        = false;
  g_PIOTransaction.bContinue          = false;
  g_PIOTransaction.ui32NumBytes       = ui32NumBytes;
  g_PIOTransaction.bQuadCmd           = false;
  g_PIOTransaction.pui32Buffer        = pData;

  // Execute the transction over MSPI.
  return am_hal_mspi_blocking_transfer(g_pMSPIHandle, &g_PIOTransaction,
                                       AM_DEVICES_ATXP032_TIMEOUT);

}

void pfnATXP032_Callback(void *pCallbackCtxt, uint32_t status)
{
  // Set the DMA complete flag.
  g_MSPIDMAComplete = true;
}

//*****************************************************************************
//
//  MSPI Interrupt Service Routine.
//
//*****************************************************************************
void
am_mspi_isr(void)
{
    uint32_t      ui32Status;

    am_hal_mspi_interrupt_status_get(g_pMSPIHandle, &ui32Status, false);

    am_hal_mspi_interrupt_clear(g_pMSPIHandle, ui32Status);

    am_hal_mspi_interrupt_service(g_pMSPIHandle, ui32Status);

    g_MSPIInterruptStatus &= ~ui32Status;
}

//*****************************************************************************
//
//! @brief Initialize the atxp032 driver.
//!
//! @param psIOMSettings - IOM device structure describing the target spiflash.
//! @param pfnWriteFunc - Function to use for spi writes.
//! @param pfnReadFunc - Function to use for spi reads.
//!
//! This function should be called before any other am_devices_spiflash
//! functions. It is used to set tell the other functions how to communicate
//! with the external spiflash hardware.
//!
//! The \e pfnWriteFunc and \e pfnReadFunc variables may be used to provide
//! alternate implementations of SPI write and read functions respectively. If
//! they are left set to 0, the default functions am_hal_iom_spi_write() and
//! am_hal_iom_spi_read() will be used.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_devices_atxp032_init(am_hal_mspi_dev_config_t *psMSPISettings,
                        uint32_t ui32DMACtrlBufferSize,
                        uint32_t *pDMACtrlBuffer)
{
  uint32_t            ui32Command;
  uint32_t            ui32Status;

  //
  // Enable fault detection.
  //
#if AM_APOLLO3_MCUCTRL
  am_hal_mcuctrl_control(AM_HAL_MCUCTRL_CONTROL_FAULT_CAPTURE_ENABLE, 0);
#else
  am_hal_mcuctrl_fault_capture_enable();
#endif

  //
  // Configure the MSPI for Serial or Quad-Paired Serial operation during initialization.
  //
    switch ( psMSPISettings->eDeviceConfig )
    {
        case AM_HAL_MSPI_FLASH_SERIAL_CE0:
        case AM_HAL_MSPI_FLASH_SERIAL_CE1:
        case AM_HAL_MSPI_FLASH_QUAD_CE0:
        case AM_HAL_MSPI_FLASH_QUAD_CE1:
        case AM_HAL_MSPI_FLASH_OCTAL_CE0:
        case AM_HAL_MSPI_FLASH_OCTAL_CE1:
            g_psMSPISettings = SerialMSPIConfig;
            if (AM_HAL_STATUS_SUCCESS != am_hal_mspi_initialize(AM_DEVICES_ATXP032_MSPI_INSTANCE, &g_pMSPIHandle))
            {
                am_util_stdio_printf("Error - Failed to initialize MSPI.\n");
                return AM_DEVICES_ATXP032_STATUS_ERROR;
            }
            if (AM_HAL_STATUS_SUCCESS != am_hal_mspi_power_control(g_pMSPIHandle, AM_HAL_SYSCTRL_WAKE, false))
            {
                am_util_stdio_printf("Error - Failed to power on MSPI.\n");
                return AM_DEVICES_ATXP032_STATUS_ERROR;
            }

            if (AM_HAL_STATUS_SUCCESS != am_hal_mspi_device_configure(g_pMSPIHandle, &SerialMSPIConfig))
            {
                am_util_stdio_printf("Error - Failed to configure MSPI.\n");
                return AM_DEVICES_ATXP032_STATUS_ERROR;
            }
            if (AM_HAL_STATUS_SUCCESS != am_hal_mspi_enable(g_pMSPIHandle))
            {
                am_util_stdio_printf("Error - Failed to enable MSPI.\n");
                return AM_DEVICES_ATXP032_STATUS_ERROR;
            }
            am_bsp_mspi_pins_enable(SerialMSPIConfig.eDeviceConfig);
            break;
        case AM_HAL_MSPI_FLASH_DUAL_CE1:
        case AM_HAL_MSPI_FLASH_QUADPAIRED:
        case AM_HAL_MSPI_FLASH_DUAL_CE0:
        case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
            return AM_DEVICES_ATXP032_STATUS_ERROR;
            //break;
    }

  if (AM_HAL_STATUS_SUCCESS != am_devices_atxp032_reset())
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Set the Dummy Cycles in Status/Control register 3 to 8.
  //
  am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
  g_PIOBuffer[0] = 0x00000003;
  am_device_command_write(AM_DEVICES_ATXP032_WRITE_STATUS_CTRL, false, 0, g_PIOBuffer, 2);

  //
  // Configure the ATXP032 mode based on the MSPI configuration.
  //
  am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);

    switch ( psMSPISettings->eDeviceConfig )
    {
        case AM_HAL_MSPI_FLASH_SERIAL_CE0:
        case AM_HAL_MSPI_FLASH_SERIAL_CE1:
            ui32Command = AM_DEVICES_ATXP032_RETURN_TO_SPI_MODE;
            break;
        case AM_HAL_MSPI_FLASH_DUAL_CE0:
        case AM_HAL_MSPI_FLASH_DUAL_CE1:
        case AM_HAL_MSPI_FLASH_QUADPAIRED:
        case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
            return AM_DEVICES_ATXP032_STATUS_ERROR;
            break;
        case AM_HAL_MSPI_FLASH_QUAD_CE0:
        case AM_HAL_MSPI_FLASH_QUAD_CE1:
            ui32Command = AM_DEVICES_ATXP032_ENTER_QUAD_MODE;
            break;
        case AM_HAL_MSPI_FLASH_OCTAL_CE0:
        case AM_HAL_MSPI_FLASH_OCTAL_CE1:
            ui32Command = AM_DEVICES_ATXP032_ENTER_OCTAL_MODE;
            break;
    }

  am_device_command_write(ui32Command, false, 0, g_PIOBuffer, 0);


  //
  // Initialize the MSPI settings for the MSPI_FLASH.
  //
  g_psMSPISettings = *psMSPISettings;

  // Disable MSPI defore re-configuring it
  ui32Status = am_hal_mspi_disable(g_pMSPIHandle);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
  //
  // Re-Configure the MSPI for the requested operation mode.
  //
  ui32Status = am_hal_mspi_device_configure(g_pMSPIHandle, psMSPISettings);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
  // Re-Enable MSPI
  ui32Status = am_hal_mspi_enable(g_pMSPIHandle);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Configure the MSPI pins.
  //
  am_bsp_mspi_pins_enable(g_psMSPISettings.eDeviceConfig);

  //
  // Enable MSPI interrupts.
  //

#if MSPI_USE_CQ

  ui32Status = am_hal_mspi_interrupt_clear(g_pMSPIHandle, AM_HAL_MSPI_INT_CQUPD | AM_HAL_MSPI_INT_ERR );
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  ui32Status = am_hal_mspi_interrupt_enable(g_pMSPIHandle, AM_HAL_MSPI_INT_CQUPD | AM_HAL_MSPI_INT_ERR );
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

#else
  ui32Status = am_hal_mspi_interrupt_clear(g_pMSPIHandle, AM_HAL_MSPI_INT_ERR | AM_HAL_MSPI_INT_DMACMP );
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  ui32Status = am_hal_mspi_interrupt_enable(g_pMSPIHandle, AM_HAL_MSPI_INT_ERR | AM_HAL_MSPI_INT_DMACMP );
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
#endif

#if AM_CMSIS_REGS
    NVIC_EnableIRQ(MSPI_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_MSPI);
#endif // AM_CMSIS_REGS

  am_hal_interrupt_master_enable();

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief De-Initialization the atxp032 driver.
//!
//! @param psIOMSettings - IOM device structure describing the target spiflash.
//! @param pfnWriteFunc - Function to use for spi writes.
//! @param pfnReadFunc - Function to use for spi reads.
//!
//! This function should be called before any other am_devices_spiflash
//! functions. It is used to set tell the other functions how to communicate
//! with the external spiflash hardware.
//!
//! The \e pfnWriteFunc and \e pfnReadFunc variables may be used to provide
//! alternate implementations of SPI write and read functions respectively. If
//! they are left set to 0, the default functions am_hal_iom_spi_write() and
//! am_hal_iom_spi_read() will be used.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_devices_atxp032_deinit(am_hal_mspi_dev_config_t *psMSPISettings)
{
  uint32_t      ui32Status;

  if (AM_HAL_STATUS_SUCCESS != am_devices_atxp032_reset())
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Disable the master interrupt on NVIC
  //
  am_hal_interrupt_master_disable();

  //
  // Disable and clear the interrupts to start with.
  //
  ui32Status = am_hal_mspi_interrupt_disable(g_pMSPIHandle, 0xFFFFFFFF);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
  ui32Status = am_hal_mspi_interrupt_clear(g_pMSPIHandle, 0xFFFFFFFF);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Disable the MSPI interrupts.
  //
#if AM_CMSIS_REGS
    NVIC_DisableIRQ(MSPI_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_MSPI);
#endif // AM_CMSIS_REGS

  //
  // Disable the MSPI instance.
  //
  ui32Status = am_hal_mspi_disable(g_pMSPIHandle);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  if (AM_HAL_STATUS_SUCCESS != am_hal_mspi_power_control(g_pMSPIHandle, AM_HAL_SYSCTRL_DEEPSLEEP, false))
  {
    am_util_stdio_printf("Error - Failed to power on MSPI.\n");
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Deinitialize the MSPI instance.
  //
  ui32Status = am_hal_mspi_deinitialize(g_pMSPIHandle);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Clear the Flash Caching.
  //
#if AM_CMSIS_REGS
    CACHECTRL->CACHECFG = 0;
#else // AM_CMSIS_REGS
    AM_REG(CACHECTRL, CACHECFG) = 0;
#endif // AM_CMSIS_REGS

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}
//*****************************************************************************
//
//! @brief Reads the current status of the external flash
//!
//! @param ui32DeviceNumber - Device number of the external flash
//!
//! This function reads the device ID register of the external flash, and returns
//! the result as an 32-bit unsigned integer value.
//!
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_reset(void)
{
  //
  // Return the device to SPI mode.
  //
  if (AM_HAL_STATUS_SUCCESS != am_device_command_write(AM_DEVICES_ATXP032_RETURN_TO_SPI_MODE, false, 0, g_PIOBuffer, 0))
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Reads the ID of the external flash and returns the value.
//!
//! @param pDeviceID - Pointer to the return buffer for the Device ID.
//!
//! This function reads the device ID register of the external flash, and returns
//! the result as an 32-bit unsigned integer value.
//!
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_id(uint32_t *pDeviceID)
{
  uint32_t      ui32Status;
  uint32_t      ui32DeviceID;
  uint8_t       ui8Response[11];

  //
  // Send the command sequence to read the Device ID and return status.
  //
  ui32Status = am_device_command_read(AM_DEVICES_ATXP032_READ_ID, false, 0, (uint32_t *)&ui8Response[0], 11);
  ui32DeviceID = (ui8Response[7] << 16) | (ui8Response[8] << 8) | ui8Response[9];
  am_util_stdio_printf("Flash ID is %8.8X\n", ui32DeviceID);
  if ((ui32DeviceID == AM_DEVICES_ATXP032_ID) && (AM_HAL_STATUS_SUCCESS == ui32Status))
  {
    return AM_DEVICES_ATXP032_STATUS_SUCCESS;
  }
  else
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
}

//*****************************************************************************
//
//! @brief Reads the current status of the external flash
//!
//! This function reads the status register of the external flash, and returns
//! the result as an 8-bit unsigned integer value. The processor will block
//! during the data transfer process, but will return as soon as the status
//! register had been read.
//!
//! Macro definitions for interpreting the contents of the status register are
//! included in the header file.
//!
//! @return 8-bit status register contents
//
//*****************************************************************************
uint32_t
am_devices_atxp032_status(uint32_t *pStatus)
{
  uint32_t      ui32Status;

  //
  // Send the command sequence to read the Device status.
  //
  //
  // ATXP032 has different number of bytes for each speed of status read.
    switch ( g_psMSPISettings.eDeviceConfig )
    {
        case AM_HAL_MSPI_FLASH_SERIAL_CE0:
        case AM_HAL_MSPI_FLASH_SERIAL_CE1:
            ui32Status = am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 2);
            *pStatus = (g_PIOBuffer[0] & 0x000000FF);
            break;
        case AM_HAL_MSPI_FLASH_QUAD_CE0:
        case AM_HAL_MSPI_FLASH_QUAD_CE1:
            ui32Status = am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 4);
            *pStatus = ((g_PIOBuffer[0] >> 16) & 0x000000FF);
            break;
        case AM_HAL_MSPI_FLASH_OCTAL_CE0:
        case AM_HAL_MSPI_FLASH_OCTAL_CE1:
            ui32Status = am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 6);
            *pStatus = (g_PIOBuffer[1] & 0x000000FF);
            break;
        case AM_HAL_MSPI_FLASH_DUAL_CE0:
        case AM_HAL_MSPI_FLASH_DUAL_CE1:
        case AM_HAL_MSPI_FLASH_QUADPAIRED:
        case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
            return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

  if (AM_HAL_STATUS_SUCCESS == ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_SUCCESS;
  }
  else
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
}

uint32_t
am_devices_atxp032_read_adv(uint8_t *pui8RxBuffer,
                            uint32_t ui32ReadAddress,
                            uint32_t ui32NumBytes,
                            uint32_t ui32PauseCondition,
                            uint32_t ui32StatusSetClr,
                            am_hal_mspi_callback_t pfnCallback,
                            void *pCallbackCtxt)
{
  am_hal_mspi_dma_transfer_t    Transaction;
  uint32_t                      ui32Status;

  // Not trying to save power for now.
  // TODO: Figure out how to to use this correctly in this device driver.
  Transaction.bPowerOff = false;

  // Set the DMA priority
  Transaction.ui8Priority = 1;

  // Set the address configuration for the read
  Transaction.eAddrCfg = AM_HAL_MSPI_ADDR_4_BYTE;

  // Set the transfer direction to RX (Read)
  Transaction.eDirection = AM_HAL_MSPI_RX;

  // Set the transfer count in bytes.
  Transaction.ui32TransferCount = ui32NumBytes;

  // Set the address to read data from.
  Transaction.ui32DeviceAddress = ui32ReadAddress;

  // Set the target SRAM buffer address.
  Transaction.ui32SRAMAddress = (uint32_t)pui8RxBuffer;

  // Clear the CQ stimulus.
  Transaction.ui32PauseCondition = ui32PauseCondition;
  // Clear the post-processing
  Transaction.ui32StatusSetClr = ui32StatusSetClr;

  // Check the transaction status.
  ui32Status = am_hal_mspi_nonblocking_transfer(g_pMSPIHandle, &Transaction,
                                                AM_HAL_MSPI_TRANS_DMA, pfnCallback, pCallbackCtxt);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Reads the contents of the external flash into a buffer.
//!
//! @param pui8RxBuffer - Buffer to store the received data from the flash
//! @param ui32ReadAddress - Address of desired data in external flash
//! @param ui32NumBytes - Number of bytes to read from external flash
//!
//! This function reads the external flash at the provided address and stores
//! the received data into the provided buffer location. This function will
//! only store ui32NumBytes worth of data.
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_read(uint8_t *pui8RxBuffer,
                        uint32_t ui32ReadAddress,
                        uint32_t ui32NumBytes,
                        bool bWaitForCompletion)
{
  am_hal_mspi_dma_transfer_t    Transaction;
  uint32_t                      ui32Status;

  // Not trying to save power for now.
  // TODO: Figure out how to to use this correctly in this device driver.
  Transaction.bPowerOff = false;

  // Set the DMA priority
  Transaction.ui8Priority = 1;

  // Set the address configuration for the read
  Transaction.eAddrCfg = AM_HAL_MSPI_ADDR_4_BYTE;

  // Set the transfer direction to RX (Read)
  Transaction.eDirection = AM_HAL_MSPI_RX;

  // Set the transfer count in bytes.
  Transaction.ui32TransferCount = ui32NumBytes;

  // Set the address to read data from.
  Transaction.ui32DeviceAddress = ui32ReadAddress;

  // Set the target SRAM buffer address.
  Transaction.ui32SRAMAddress = (uint32_t)pui8RxBuffer;

  // Clear the CQ stimulus.
  Transaction.ui32PauseCondition = 0;
  // Clear the post-processing
  Transaction.ui32StatusSetClr = 0;

  if (bWaitForCompletion)
  {
    // Start the transaction.
    g_MSPIDMAComplete = false;
    ui32Status = am_hal_mspi_nonblocking_transfer(g_pMSPIHandle, &Transaction, AM_HAL_MSPI_TRANS_DMA, pfnATXP032_Callback, NULL);

    // Check the transaction status.
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    // Wait for DMA Complete or Timeout
    for (uint32_t i = 0; i < AM_DEVICES_ATXP032_TIMEOUT; i++)
    {
      if (g_MSPIDMAComplete)
      {
        break;
      }
      //
      // Call the BOOTROM cycle function to delay for about 1 microsecond.
      //
      am_hal_flash_delay( FLASH_CYCLES_US(1) );
    }

    // Check the status.
    if (!g_MSPIDMAComplete)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }
  else
  {
    // Check the transaction status.
    ui32Status = am_hal_mspi_nonblocking_transfer(g_pMSPIHandle, &Transaction,
                                                  AM_HAL_MSPI_TRANS_DMA, NULL, NULL);
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}


//*****************************************************************************
//
//! @brief Programs the given range of flash addresses.
//!
//! @param ui32DeviceNumber - Device number of the external flash
//! @param pui8TxBuffer - Buffer to write the external flash data from
//! @param ui32WriteAddress - Address to write to in the external flash
//! @param ui32NumBytes - Number of bytes to write to the external flash
//!
//! This function uses the data in the provided pui8TxBuffer and copies it to
//! the external flash at the address given by ui32WriteAddress. It will copy
//! exactly ui32NumBytes of data from the original pui8TxBuffer pointer. The
//! user is responsible for ensuring that they do not overflow the target flash
//! memory or underflow the pui8TxBuffer array
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_write(uint8_t *pui8TxBuffer,
                         uint32_t ui32WriteAddress,
                         uint32_t ui32NumBytes)
{
  am_hal_mspi_dma_transfer_t    Transaction;
  bool                          bWriteComplete = false;
  uint32_t                      ui32BytesLeft = ui32NumBytes;
  uint32_t                      ui32PageAddress = ui32WriteAddress;
  uint32_t                      ui32BufferAddress = (uint32_t)pui8TxBuffer;
  uint32_t                      ui32Status;

  while (ui32BytesLeft > 0)
  {
    //
    // Send the command sequence to enable writing.
    //
    ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    // Not trying to save power for now.
    // TODO: Need to implement end of transaction power-off feature.
    Transaction.bPowerOff = false;

    // Set the DMA priority
    Transaction.ui8Priority = 1;

    // Set the transfer direction to TX (Write)
    Transaction.eDirection = AM_HAL_MSPI_TX;

    if (ui32BytesLeft > AM_DEVICES_ATXP032_PAGE_SIZE)
    {
      // Set the transfer count in bytes.
      Transaction.ui32TransferCount = AM_DEVICES_ATXP032_PAGE_SIZE;
      ui32BytesLeft -= AM_DEVICES_ATXP032_PAGE_SIZE;
    }
    else
    {
      // Set the transfer count in bytes.
      Transaction.ui32TransferCount = ui32BytesLeft;
      ui32BytesLeft = 0;
    }

    // Set the address configuration for the read
    //    Transaction.eAddrCfg = AM_HAL_MSPI_ADDR_3_BYTE;

    //    Transaction.eAddrExtSize = AM_HAL_MSPI_ADDR_EXT_0_BYTE;
    //    Transaction.ui8AddrExtValue = 0;

    // Set the address to read data to.
    Transaction.ui32DeviceAddress = ui32PageAddress;
    ui32PageAddress += AM_DEVICES_ATXP032_PAGE_SIZE;

    // Set the source SRAM buffer address.
    Transaction.ui32SRAMAddress = ui32BufferAddress;
    ui32BufferAddress += AM_DEVICES_ATXP032_PAGE_SIZE;

    // Clear the CQ stimulus.
    Transaction.ui32PauseCondition = 0;
    // Clear the post-processing
    Transaction.ui32StatusSetClr = 0;

    // Start the transaction.
    g_MSPIDMAComplete = false;
    ui32Status = am_hal_mspi_nonblocking_transfer(g_pMSPIHandle, &Transaction, AM_HAL_MSPI_TRANS_DMA, pfnATXP032_Callback, NULL);

    // Check the transaction status.
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    // Wait for DMA Complete or Timeout
    for (uint32_t i = 0; i < AM_DEVICES_ATXP032_TIMEOUT; i++)
    {
      if (g_MSPIDMAComplete)
      {
        break;
      }
      //
      // Call the BOOTROM cycle function to delay for about 1 microsecond.
      //
      am_hal_flash_delay( FLASH_CYCLES_US(1) );
    }

    // Check the status.
    if (!g_MSPIDMAComplete)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    //
    // Wait for the Write In Progress to indicate the erase is complete.
    //
    for (uint32_t i = 0; i < AM_DEVICES_ATXP032_TIMEOUT; i++)
    {
        // ATXP032 has different number of bytes for each speed of status read.
        switch ( g_psMSPISettings.eDeviceConfig )
        {
            case AM_HAL_MSPI_FLASH_SERIAL_CE0:
            case AM_HAL_MSPI_FLASH_SERIAL_CE1:
                am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 2);
                bWriteComplete = (0 == (g_PIOBuffer[0] & AM_DEVICES_ATXP032_WIP));
                break;
            case AM_HAL_MSPI_FLASH_QUAD_CE0:
            case AM_HAL_MSPI_FLASH_QUAD_CE1:
                am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 4);
                bWriteComplete = (0 == ((g_PIOBuffer[0] >> 16) & AM_DEVICES_ATXP032_WIP));
                break;
            case AM_HAL_MSPI_FLASH_OCTAL_CE0:
            case AM_HAL_MSPI_FLASH_OCTAL_CE1:
                am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 6);
                bWriteComplete = (0 == (g_PIOBuffer[1] & AM_DEVICES_ATXP032_WIP));
                break;
            case AM_HAL_MSPI_FLASH_DUAL_CE0:
            case AM_HAL_MSPI_FLASH_DUAL_CE1:
            case AM_HAL_MSPI_FLASH_QUADPAIRED:
            case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
                return AM_DEVICES_ATXP032_STATUS_ERROR;
        }

      if (bWriteComplete)
      {
        break;
      }
    }

    //
    // Send the command sequence to disable writing.
    //
    ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_DISABLE, false, 0, g_PIOBuffer, 0);
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Erases the entire contents of the external flash
//!
//! @param ui32DeviceNumber - Device number of the external flash
//!
//! This function uses the "Bulk Erase" instruction to erase the entire
//! contents of the external flash.
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_mass_erase(void)
{
  bool          bEraseComplete = false;
  uint32_t      ui32Status;

  //
  // Send the command sequence to enable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Send the command sequence to do the mass erase.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_BULK_ERASE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Wait for the Write In Progress to indicate the erase is complete.
  //
  for (uint32_t i = 0; i < AM_DEVICES_ATXP032_ERASE_TIMEOUT; i++)
  {
    // ATXP032 has different number of bytes for each speed of status read.
    switch ( g_psMSPISettings.eDeviceConfig )
    {
        case AM_HAL_MSPI_FLASH_SERIAL_CE0:
        case AM_HAL_MSPI_FLASH_SERIAL_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 2);
            bEraseComplete = (0 == (g_PIOBuffer[0] & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_QUAD_CE0:
        case AM_HAL_MSPI_FLASH_QUAD_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 4);
            bEraseComplete = (0 == ((g_PIOBuffer[0] >> 16) & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_OCTAL_CE0:
        case AM_HAL_MSPI_FLASH_OCTAL_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 6);
            bEraseComplete = (0 == (g_PIOBuffer[1] & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_DUAL_CE0:
        case AM_HAL_MSPI_FLASH_DUAL_CE1:
        case AM_HAL_MSPI_FLASH_QUADPAIRED:
        case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
            return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    if (bEraseComplete)
    {
      break;
    }
    am_util_delay_ms(10);
  }

  //
  // Send the command sequence to disable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_DISABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Erases the contents of a single sector of flash
//!
//! @param ui32DeviceNumber - Device number of the external flash
//! @param ui32SectorAddress - Address to erase in the external flash
//!
//! This function erases a single sector of the external flash as specified by
//! ui32EraseAddress. The entire sector where ui32EraseAddress will
//! be erased.
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_sector_erase(uint32_t ui32SectorAddress)
{
  bool          bEraseComplete = false;
  uint32_t      ui32Status;
  //  uint32_t      ui32EraseStatus;

  //
  // Send the command sequence to enable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Send the command to remove protection from the sector.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_UNPROTECT_SECTOR, true, ui32SectorAddress, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }


  //
  // Send the command sequence to enable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Send the command sequence to do the sector erase.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_SECTOR_ERASE, true, ui32SectorAddress, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Wait for the Write In Progress to indicate the erase is complete.
  //
  for (uint32_t i = 0; i < AM_DEVICES_ATXP032_ERASE_TIMEOUT; i++)
  {
    // ATXP032 has different number of bytes for each speed of status read.
    switch ( g_psMSPISettings.eDeviceConfig )
    {
        case AM_HAL_MSPI_FLASH_SERIAL_CE0:
        case AM_HAL_MSPI_FLASH_SERIAL_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 2);
            bEraseComplete = (0 == (g_PIOBuffer[0] & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_QUAD_CE0:
        case AM_HAL_MSPI_FLASH_QUAD_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 4);
            bEraseComplete = (0 == ((g_PIOBuffer[0] >> 16) & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_OCTAL_CE0:
        case AM_HAL_MSPI_FLASH_OCTAL_CE1:
            am_device_command_read(AM_DEVICES_ATXP032_READ_STATUS, false, 0, g_PIOBuffer, 6);
            bEraseComplete = (0 == (g_PIOBuffer[1] & AM_DEVICES_ATXP032_WIP));
            break;
        case AM_HAL_MSPI_FLASH_DUAL_CE0:
        case AM_HAL_MSPI_FLASH_DUAL_CE1:
        case AM_HAL_MSPI_FLASH_QUADPAIRED:
        case AM_HAL_MSPI_FLASH_QUADPAIRED_SERIAL:
            return AM_DEVICES_ATXP032_STATUS_ERROR;
    }

    if (bEraseComplete)
    {
      break;
    }
    am_util_delay_ms(10);
  }

  //
  // Check the status.
  //
  if (!bEraseComplete)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Send the command sequence to disable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_DISABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Sets up the MSPI and external Flash into XIP mode.
//!
//! This function sets the external flash device and the MSPI into XIP mode.
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_enable(bool bEnableXIP, bool bEnableScrambling)
{
  uint32_t      ui32Status;


  //
  // Enable XIP on the MSPI.
  //
  if (bEnableXIP)
  {
    ui32Status = am_hal_mspi_control(g_pMSPIHandle, AM_HAL_MSPI_REQ_XIP_EN, NULL);
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }

  //
  // Enable scrambling on the MSPI.
  //
  if (bEnableScrambling)
  {
    ui32Status = am_hal_mspi_control(g_pMSPIHandle, AM_HAL_MSPI_REQ_SCRAMB_EN, NULL);
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }

#if !MSPI_USE_CQ
  if (bEnableXIP)
  {
    // Disable the DMA interrupts.
    ui32Status = am_hal_mspi_interrupt_disable(g_pMSPIHandle,
                                               AM_HAL_MSPI_INT_DMAERR |
                                                 AM_HAL_MSPI_INT_DMACMP );
    if (AM_HAL_STATUS_SUCCESS != ui32Status)
    {
      return AM_DEVICES_ATXP032_STATUS_ERROR;
    }
  }
#endif

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}

//*****************************************************************************
//
//! @brief Removes the MSPI and external Flash from XIP mode.
//!
//! This function removes the external device and the MSPI from XIP mode.
//
//! @return 32-bit status
//
//*****************************************************************************
uint32_t
am_devices_atxp032_disable_xip(void)
{
  uint32_t      ui32Status;

  //
  // Send the command to enable writing.
  //
  ui32Status = am_device_command_write(AM_DEVICES_ATXP032_WRITE_ENABLE, false, 0, g_PIOBuffer, 0);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Disable XIP and Scrambling on the MSPI.
  //
  ui32Status = am_hal_mspi_control(g_pMSPIHandle, AM_HAL_MSPI_REQ_XIP_DIS, NULL);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }
  ui32Status = am_hal_mspi_control(g_pMSPIHandle, AM_HAL_MSPI_REQ_SCRAMB_DIS, NULL);
  if (AM_HAL_STATUS_SUCCESS != ui32Status)
  {
    return AM_DEVICES_ATXP032_STATUS_ERROR;
  }

  //
  // Return the status.
  //
  return AM_DEVICES_ATXP032_STATUS_SUCCESS;
}


