//*****************************************************************************
//
//! @file am_devices_em9304.c
//!
//! @brief Support functions for the EM Micro EM9304 BTLE radio.
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
// This is part of revision 1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "am_bsp.h"
#include "am_devices_em9304.h"
#include "am_util_debug.h"
#include "am_util_stdio.h"
#include "am_util_delay.h"


//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************
#ifndef HCI_APOLLO_USE_CHIPID_FOR_MAC
#define HCI_APOLLO_USE_CHIPID_FOR_MAC   true
#endif

#define USE_IOM_NONBLOCKING

// SPI header byte
#define EM9304_SPI_HEADER_TX                    0x42
#define EM9304_SPI_HEADER_RX                    0x81
#define EM9304_STS1_READY_VALUE                 0xC0

// Length of RX buffer
#define EM9304_BUFFER_SIZE                      256

#if AM_APOLLO3_GPIO
// Select the EM9304 -> Set the CSN to low level
#define EM9304_SPISLAVESELECT()                 am_hal_gpio_state_write(AM_BSP_GPIO_EM9304_CS, AM_HAL_GPIO_OUTPUT_CLEAR);

// Deselect the EM9304 -> Set the CSN to high level
#define EM9304_SPISLAVEDESELECT()               am_hal_gpio_state_write(AM_BSP_GPIO_EM9304_CS, AM_HAL_GPIO_OUTPUT_SET);

// Indicates the EM9304 RDY pin state
#define EM9304_RDY_INT()                        (am_hal_gpio_input_read(AM_BSP_GPIO_EM9304_INT))
#else
// Select the EM9304 -> Set the CSN to low level
#define EM9304_SPISLAVESELECT()                 am_hal_gpio_out_bit_clear(AM_BSP_GPIO_EM9304_CS)

// Deselect the EM9304 -> Set the CSN to high level
#define EM9304_SPISLAVEDESELECT()               am_hal_gpio_out_bit_set(AM_BSP_GPIO_EM9304_CS)

// Indicates the EM9304 RDY pin state
#define EM9304_RDY_INT()                        (am_hal_gpio_input_read() & AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT))
#endif // AM_APOLLO3_GPIO

#if defined(AM_PART_APOLLO) || defined(AM_PART_APOLLO2)

// SPI lock when a transmission is in progress
static uint8_t spiTxInProgress;

uint8_t hciTrSerialRxIncoming(uint8_t *pBuf, uint8_t len);

static volatile bool gIomDone = false;

//*****************************************************************************
//
// BLE MAC address for the EM radio.
//
//*****************************************************************************
uint8_t g_BLEMacAddress[6] =
{0x01, 0x00, 0x00, 0xCA, 0xEA, 0x80};

//*****************************************************************************
//
// IOM SPI Configuration for EM9304
//
//*****************************************************************************
const am_hal_iom_config_t g_sEm9304IOMConfigSPI =
{
    .ui32ClockFrequency = AM_HAL_IOM_8MHZ,
    .ui32InterfaceMode = AM_HAL_IOM_SPIMODE,
    .ui8WriteThreshold = 20,
    .ui8ReadThreshold = 20,
    .bSPHA = 0,
    .bSPOL = 0,
};

//*****************************************************************************
//
// EM9304 Device Configuration
//
//*****************************************************************************
const am_devices_em9304_t g_sEm9304 =
{
    .ui32IOMModule      = AM_BSP_EM9304_IOM,
    .ui32IOMChipSelect  = AM_BSP_GPIO_EM9304_CS,
    .ui32DREADY         = AM_BSP_GPIO_EM9304_INT
};

#if defined(USE_IOM_NONBLOCKING)
//*****************************************************************************
//
// IOM write complete callback
//
//*****************************************************************************
static void
iom_write_complete(void)
{
    gIomDone = true;
}
#endif
//*****************************************************************************
//
// Interrupt handler for IOM0
//
//*****************************************************************************
#if (0 == AM_BSP_EM9304_IOM)
void
am_iomaster0_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(0, false);
    am_hal_iom_int_clear(0, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(0, ui32IntStatus);
}
#endif

//*****************************************************************************
//
// Interrupt handler for IOM0
//
//*****************************************************************************
#if (1 == AM_BSP_EM9304_IOM)
void
am_iomaster1_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(1, false);
    am_hal_iom_int_clear(1, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(1, ui32IntStatus);
}
#endif

#if defined(AM_PART_APOLLO2)
//*****************************************************************************
//
// Interrupt handler for IOM5
//
//*****************************************************************************
#if (2 == AM_BSP_EM9304_IOM)
void
am_iomaster2_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(2, false);
    am_hal_iom_int_clear(2, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(2, ui32IntStatus);
}
#endif

//*****************************************************************************
//
// Interrupt handler for IOM5
//
//*****************************************************************************
#if (3 == AM_BSP_EM9304_IOM)
void
am_iomaster3_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(3, false);
    am_hal_iom_int_clear(3, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(3, ui32IntStatus);
}
#endif

//*****************************************************************************
//
// Interrupt handler for IOM5
//
//*****************************************************************************
#if (4 == AM_BSP_EM9304_IOM)
void
am_iomaster4_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(4, false);
    am_hal_iom_int_clear(4, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(4, ui32IntStatus);
}
#endif

//*****************************************************************************
//
// Interrupt handler for IOM5
//
//*****************************************************************************
#if (5 == AM_BSP_EM9304_IOM)
void
am_iomaster5_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(5, false);
    am_hal_iom_int_clear(5, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(5, ui32IntStatus);
}
#endif

//*****************************************************************************
//
// Checks to see if this processor is a Rev B2 device.
//
//*****************************************************************************
static bool
isRevB2(void)
{
    //
    // Check to make sure the major rev is B and the minor rev is zero.
    //
    if ( (AM_REG(MCUCTRL, CHIPREV) & 0xFF) ==
         (AM_REG_MCUCTRL_CHIPREV_REVMAJ_B | AM_REG_MCUCTRL_CHIPREV_REVMIN_REV2) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif

//*****************************************************************************
//
//! @brief Start a transmit transaction to the EM9304.
//!
//! @param psDevice is a pointer to a device structure describing the EM9304.
//!
//! This function handles the initial handshake of asserting the SPI CE and
//! then waiting for the RDY signal from the EM.  It then executes a transmit
//! command to the EM9304 and receives the number of bytes that can be accepted.
//!
//! @return Number of bytes that can be written to EM9304.
//
//*****************************************************************************
uint8_t
am_devices_em9304_tx_starts(const am_devices_em9304_t *psDevice)
{
  // Indicates that a SPI transfer is in progress
  spiTxInProgress = 1;

  am_hal_iom_buffer(2) sCommand;
  am_hal_iom_buffer(2) sStas;
  sCommand.bytes[0] = EM9304_SPI_HEADER_TX;
  sCommand.bytes[1] = 0x0;

  // Select the EM9304
  EM9304_SPISLAVESELECT();

  // Wait EM9304 RDY signal
  while ( !EM9304_RDY_INT() );

#if defined(AM_PART_APOLLO2)
  //
  // Full-Duplex operation is only supported for Apollo2 B2 Silicon.
  //
  if (isRevB2())
  {
    //
    // Write to the IOM.
    //
    am_hal_iom_spi_fullduplex(psDevice->ui32IOMModule,
                              0, sCommand.words, sStas.words, 2,
                              AM_HAL_IOM_RAW);

    //
    // Check that the EM9304 is ready.
    //
    if (sStas.bytes[0] != EM9304_STS1_READY_VALUE)
    {
      // Error
      EM9304_SPISLAVEDESELECT();
      am_util_debug_printf("HCI TX Failed to starts\n");
      am_util_debug_printf("%d, %d\n", sStas.bytes[0], sStas.bytes[1]);
      return 0;
    }

    return sStas.bytes[1];
  }
  else
#endif
  {
    //
    // Write to the IOM.
    //
    am_hal_iom_spi_write(psDevice->ui32IOMModule,
                         0, sCommand.words, 1,
                         AM_HAL_IOM_RAW);

    //
    // Read from the IOM.
    //
    am_hal_iom_spi_read(psDevice->ui32IOMModule,
                        0, sStas.words, 1,
                        AM_HAL_IOM_RAW);

    return sStas.bytes[0];
  }
}

//*****************************************************************************
//
//! @brief End a transmit transaction to the EM9304.
//!
//! @param None.
//!
//! This function handles the completion of a transmit to the EM9304.  After
//! the IOM has completed the transaction, the CE is deasserted and the RDY
//! interrupt is renabled.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_tx_ends(void)
{
    am_hal_iom_poll_complete(g_sEm9304.ui32IOMModule);
    // Deselect the EM9304
    EM9304_SPISLAVEDESELECT();

    // Indicates that the SPI transfer is finished
    spiTxInProgress = 0;
}

//*****************************************************************************
//
//! @brief EM9304 write function.
//!
//! @param psDevice is a pointer to a device structure describing the EM9304.
//! @param type is the HCI command.
//! @param pui8Values is the HCI packet to send.
//! @param ui32NumBytes is the number of bytes to send (including HCI command).
//!
//! This function perform a write transaction to the EM9304.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_block_write(const am_devices_em9304_t *psDevice,
                              uint8_t type,
                              uint8_t *pui8Values,
                              uint32_t ui32NumBytes)
{
  am_hal_iom_buffer(EM9304_BUFFER_SIZE) sData;
  uint8_t em9304BufSize = 0;
  uint8_t hci_type_sent = 0;

  // Check that we are not going to overwrite buffer.
  if ((ui32NumBytes + 1) > EM9304_BUFFER_SIZE)
  {
    am_util_debug_printf("HCI TX Error (STATUS ERROR) Packet Too Large\n");
    return;
  }

  for ( uint32_t i = 0; i < ui32NumBytes; )
  {
    if ( i < ui32NumBytes )
    {
      em9304BufSize = am_devices_em9304_tx_starts(psDevice);
    }

    uint32_t len = (em9304BufSize < (ui32NumBytes - i)) ? em9304BufSize : (ui32NumBytes - i);

    if (len > 0)  // check again if there is room to send more data
    {
      if (hci_type_sent == 0)
      {
        sData.bytes[0] = type;
        memcpy(&(sData.bytes[1]), pui8Values, len - 1);
        i += len -1;
        hci_type_sent = 1;
      }
      else
      {
        memcpy(&(sData.bytes[0]), pui8Values + i, len);
        i += len;
      }

      while ( !EM9304_RDY_INT() );

#if defined(USE_IOM_NONBLOCKING)
      gIomDone = false;
      am_hal_iom_spi_write_nb(psDevice->ui32IOMModule,
                              0, sData.words, len,
                              AM_HAL_IOM_RAW,
                              iom_write_complete);
      while(1)
      {
        //
        // Disable interrupt while we decide whether we're going to sleep.
        //
        uint32_t ui32IntStatus = am_hal_interrupt_master_disable();

        if (!gIomDone)
        {
          //
          // Sleep while waiting for the IOM transaction to finish.
          //
          am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
          //
          // Enable interrupts
          //
          am_hal_interrupt_master_set(ui32IntStatus);
        }
        else
        {
          //
          // Enable interrupts
          //
          am_hal_interrupt_master_set(ui32IntStatus);
          break;
        }
      }
#else
      am_hal_iom_spi_write(psDevice->ui32IOMModule,
                           0, sData.words, len,
                           AM_HAL_IOM_RAW);
#endif
    }

    am_devices_em9304_tx_ends();

  }
}

//*****************************************************************************
//
//! @brief EM9304 read function.
//!
//! @param psDevice is a pointer to a device structure describing the EM9304.
//! @param pui8Values is the buffer to receive the HCI packet.
//! @param ui32NumBytes is the number of bytes to send (including HCI command).
//!
//! This function a read transaction from the EM9304.
//!
//! @return Number of bytes read.
//
//*****************************************************************************
uint32_t
am_devices_em9304_block_read(const am_devices_em9304_t *psDevice,
                             uint32_t *pui32Values,
                             uint32_t ui32NumBytes)
{
  am_hal_iom_buffer(2) sCommand;
  am_hal_iom_buffer(2) sStas;
  uint8_t ui8RxBytes;
  uint8_t spiRxTotalBytesCount = 0;


  sCommand.bytes[0] = EM9304_SPI_HEADER_RX;
  sCommand.bytes[1] = 0x0;

  //
  // Check if the SPI is free
  //
  if ( spiTxInProgress )
  {
    //
    // TX in progress -> Ignore RDY interrupt
    //
    am_util_debug_printf("HCI TX in progress\n");
    return 0;
  }

  //
  // Check if they are still data to read
  //
  if ( !EM9304_RDY_INT() )
  {
    // No data
    //am_util_debug_printf("HCI No data\n");
    return 0;
  }

  //
  // Select the EM9304
  //
  EM9304_SPISLAVESELECT();

#if defined(AM_PART_APOLLO2)
  //
  // Full-Duplex operation is only supported for Apollo2 B2 Silicon.
  //
  if (isRevB2())
  {
    //
    // Write to the IOM.
    //
    am_hal_iom_spi_fullduplex(psDevice->ui32IOMModule,
                              0, sCommand.words, sStas.words, 2,
                              AM_HAL_IOM_RAW);

    //
    // Check that the EM9304 is ready.
    //
    if ( sStas.bytes[0] != EM9304_STS1_READY_VALUE )
    {
      // Error
      EM9304_SPISLAVEDESELECT();
      am_util_debug_printf("HCI RX Error (STATUS ERROR) EM9304 Not Ready\n");
      am_util_debug_printf("%d, %d\n", sStas.bytes[0], sStas.bytes[1]);
      return 0;
    }

    //
    // Set the number of bytes to receive.
    //
    ui8RxBytes = sStas.bytes[1];
  }
  else
#endif
  {
    //
    // Write to the IOM.
    //
    am_hal_iom_spi_write(psDevice->ui32IOMModule,
                         0, sCommand.words, 1,
                         AM_HAL_IOM_RAW);

    //
    // Read from the IOM.
    //
    am_hal_iom_spi_read(psDevice->ui32IOMModule,
                        0, sStas.words, 1,
                        AM_HAL_IOM_RAW);

    //
    // Set the number of bytes to receive.
    //
    ui8RxBytes = sStas.bytes[0];
  }

  while ( EM9304_RDY_INT() && (spiRxTotalBytesCount < ui8RxBytes) && (ui8RxBytes != 0))
  {
    uint32_t len = 1;

    if ( (ui8RxBytes - spiRxTotalBytesCount) >= EM9304_BUFFER_SIZE )
    {
      //
      // Error. Packet too large.
      //
      am_util_debug_printf("HCI RX Error (STATUS ERROR) Packet Too Large\n");
      am_util_debug_printf("%d, %d\n", sStas.bytes[0], sStas.bytes[1]);
      return 0;
    }
    else
    {
      len = ui8RxBytes;
    }

#if defined(USE_IOM_NONBLOCKING)
    gIomDone = false;
    am_hal_iom_spi_read_nb(psDevice->ui32IOMModule,
                           0, pui32Values, len,
                           AM_HAL_IOM_RAW,
                           iom_write_complete);
    while(1)
    {
      //
      // Disable interrupt while we decide whether we're going to sleep.
      //
      uint32_t ui32IntStatus = am_hal_interrupt_master_disable();

      if (!gIomDone)
      {
        //
        // Sleep while waiting for the IOM transaction to finish.
        //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
        //
        // Enable interrupts
        //
        am_hal_interrupt_master_set(ui32IntStatus);
      }
      else
      {
        //
        // Enable interrupts
        //
        am_hal_interrupt_master_set(ui32IntStatus);
        break;
      }
    }
#else
    am_hal_iom_spi_read(psDevice->ui32IOMModule,
                        0, pui32Values,
                        len, AM_HAL_IOM_RAW);
#endif

    spiRxTotalBytesCount = len;
  }

  // Deselect the EM9304
  EM9304_SPISLAVEDESELECT();

  return spiRxTotalBytesCount;
}

//*****************************************************************************
//
//! @brief EM9304 SPI/IOM initialization function.
//!
//! @param ui32Module is the IOM module to be used for EM9304.
//! @param psIomConfig is the configuration information for the IOM.
//!
//! This function initializes the IOM for operation with the EM9304.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_spi_init(uint32_t ui32Module, const am_hal_iom_config_t *psIomConfig)
{
    if ( AM_REGn(IOMSTR, ui32Module, CFG) & AM_REG_IOMSTR_CFG_IFCEN_M )
    {
        return;
    }

#if defined(AM_PART_APOLLO2)
    am_hal_iom_pwrctrl_enable(ui32Module);
#endif
    //
    // Setup the pins for SPI mode.
    //
    am_bsp_iom_spi_pins_enable(ui32Module);

    //
    // Set the required configuration settings for the IOM.
    //
    am_hal_iom_config(ui32Module, psIomConfig);

    // Enable spi
    am_hal_iom_enable(ui32Module);

#if defined(USE_IOM_NONBLOCKING)
    //
    // Enable interrupts.
    //
    am_hal_iom_int_clear(ui32Module, AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_THR);
    am_hal_iom_int_enable(ui32Module, AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_THR);

#if (0 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER0);
#elif (1 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER1);
#elif (2 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER2);
#elif (3 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER3);
#elif (4 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER4);
#elif (5 == AM_BSP_EM9304_IOM)
      am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER5);
#endif

    //
    // Reset the IOM Done flag.
    //
    gIomDone = false;
#endif

}

//*****************************************************************************
//
//! @brief EM9304 SPI/IOM wakeup function.
//!
//! @param ui32Module is the IOM module to be used for EM9304.
//!
//! This function restores the IOM operation after sleep.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_spi_awake(uint32_t ui32Module)
{

    if ( AM_REGn(IOMSTR, ui32Module, CFG) & AM_REG_IOMSTR_CFG_IFCEN_M )
    {
        return;
    }

#if defined(AM_PART_APOLLO2)
    am_hal_iom_power_on_restore(ui32Module);
#endif

    //
    // Setup the pins for SPI mode.
    //
    am_bsp_iom_spi_pins_enable(ui32Module);

    // Enable spi
    am_hal_iom_enable(ui32Module);
}

void
am_devices_em9304_configure_spi_sleep(void)
{
  //
  // Re-configure SPI pins during sleep
  //
#if AM_APOLLO3_GPIO
#if (0 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM0_SCK,  g_AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM0_MISO, g_AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM0_MOSI, g_AM_HAL_PIN_OUTPUT);

  am_hal_gpio_state_write(AM_BSP_GPIO_IOM0_SCK,  AM_HAL_GPIO_OUTPUT_CLEAR);
  am_hal_gpio_state_write(AM_BSP_GPIO_IOM0_MISO, AM_HAL_GPIO_OUTPUT_CLEAR);
  am_hal_gpio_state_write(AM_BSP_GPIO_IOM0_MOSI, AM_HAL_GPIO_OUTPUT_CLEAR);
#elif (5 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_SCK,  g_AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_MISO, g_AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM5_MOSI, g_AM_HAL_PIN_OUTPUT);

  am_hal_gpio_state_write(AM_BSP_GPIO_IOM5_SCK,  AM_HAL_GPIO_OUTPUT_CLEAR);
  am_hal_gpio_state_write(AM_BSP_GPIO_IOM5_MISO, AM_HAL_GPIO_OUTPUT_CLEAR);
  am_hal_gpio_state_write(AM_BSP_GPIO_IOM5_MOSI, AM_HAL_GPIO_OUTPUT_CLEAR);
#endif
#else
#if (0 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM0_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM0_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM0_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM0_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM0_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM0_MOSI);
#elif (1 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM1_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM1_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM1_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM1_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM1_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM1_MOSI);
#elif (2 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM2_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM2_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM2_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM2_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM2_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM2_MOSI);
#elif (3 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM3_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM3_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM3_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM3_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM3_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM3_MOSI);
#elif (4 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM4_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM4_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM4_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM4_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM4_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM4_MOSI);
#elif (5 == AM_BSP_EM9304_IOM)
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM5_SCK, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM5_MISO, AM_HAL_PIN_OUTPUT);
  am_hal_gpio_pin_config(AM_BSP_GPIO_IOM5_MOSI, AM_HAL_PIN_OUTPUT);

  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM5_SCK);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM5_MISO);
  am_hal_gpio_out_bit_clear(AM_BSP_GPIO_IOM5_MOSI);
#endif
#endif // AM_APOLLO3_GPIO

}

//*****************************************************************************
//
//! @brief EM9304 SPI/IOM sleep function.
//!
//! @param ui32Module is the IOM module to be used for EM9304.
//!
//! This function prepares the IOM for sleep.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_spi_sleep(uint32_t ui32Module)
{
    if ( !(AM_REGn(IOMSTR, ui32Module, CFG) & AM_REG_IOMSTR_CFG_IFCEN_M) )
    {
        return;
    }

    am_hal_iom_disable(ui32Module);

#if defined(AM_PART_APOLLO)
    am_bsp_iom_spi_pins_disable(ui32Module);
#else
    am_hal_iom_power_off_save(ui32Module);
    am_devices_em9304_configure_spi_sleep();
#endif
}

//*****************************************************************************
//
//! @brief Configure EM9304 pins.
//!
//! @param None.
//!
//! This function initializes the GPIOs for communication with the EM9304.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_config_pins(void)
{
#if AM_APOLLO3_GPIO
    am_hal_gpio_pinconfig(AM_BSP_GPIO_EM9304_CS,   g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_EM9304_INT,  g_AM_HAL_GPIO_INPUT);
    am_hal_gpio_state_write(AM_BSP_GPIO_EM9304_CS, AM_HAL_GPIO_OUTPUT_SET);

    // Note - interrupt polarity is handled by the pin configuration.
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#else
    am_bsp_pin_enable(EM9304_CS);
    am_bsp_pin_enable(EM9304_INT);

    am_hal_gpio_out_bit_set(AM_BSP_GPIO_EM9304_CS);

    am_hal_gpio_int_polarity_bit_set(AM_BSP_GPIO_EM9304_INT, AM_HAL_GPIO_RISING);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#endif // AM_APOLLO3_GPIO
}


//*****************************************************************************
//
//! @brief Configure EM9304 MAC address.
//!
//! @param pui8MacAddress - the desired BLE MAC address.
//!
//! This function configures the EM9304 BLE MAC address.
//!
//! @return Success.
//
//*****************************************************************************
bool
am_devices_em9304_mac_set(const uint8_t *pui8MacAddress)
{
    uint32_t i;

    //
    // Copy the 6-byte MAC address into our global variable.
    //
    for ( i = 0; i < 6; i++ )
    {
        g_BLEMacAddress[i] = *pui8MacAddress++;
    }

    //HciVendorSpecificCmd(0xFC02, 6, g_BLEMacAddress);

    return true;
}

void am_devices_em9304_enable_interrupt(void)
{
#if AM_APOLLO3_GPIO
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#else
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#endif
}

void am_devices_em9304_disable_interrupt(void)
{
#if AM_APOLLO3_GPIO
    am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#else
    am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#endif
}
#endif // defined(AM_PART_APOLLO) || defined(AM_PART_APOLLO2)


#if defined(AM_PART_APOLLO3)

//*****************************************************************************
//
// Global variables.
//
//*****************************************************************************
void *g_pEM9304IOMHandle;

//*****************************************************************************
//
// EM9304 Device Configuration
//
//*****************************************************************************
const am_devices_em9304_t g_sEm9304 =
{
    .ui32IOMModule      = AM_BSP_EM9304_IOM,
    .ui32IOMChipSelect  = AM_BSP_GPIO_EM9304_CS,
    .ui32DREADY         = AM_BSP_GPIO_EM9304_INT
};

//*****************************************************************************
//
//! @brief Configure EM9304 pins.
//!
//! @param None.
//!
//! This function initializes the GPIOs for communication with the EM9304.
//!
//! @return None.
//
//*****************************************************************************
void
am_devices_em9304_config_pins(void)
{
#if AM_APOLLO3_GPIO
    am_hal_gpio_pinconfig(AM_BSP_GPIO_EM9304_CS,   g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_EM9304_INT,  g_AM_HAL_GPIO_INPUT);
    am_hal_gpio_state_write(AM_BSP_GPIO_EM9304_CS, AM_HAL_GPIO_OUTPUT_SET);

    // Note - interrupt polarity is handled by the pin configuration.
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#else
    am_bsp_pin_enable(EM9304_CS);
    am_bsp_pin_enable(EM9304_INT);

    am_hal_gpio_out_bit_set(AM_BSP_GPIO_EM9304_CS);

    am_hal_gpio_int_polarity_bit_set(AM_BSP_GPIO_EM9304_INT, AM_HAL_GPIO_RISING);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT));
#endif // AM_APOLLO3_GPIO
}

//*****************************************************************************
//
//! @brief EM9304 SPI/IOM initialization function.
//!
//! @param ui32Module is the IOM module to be used for EM9304.
//! @param psIomConfig is the configuration information for the IOM.
//!
//! This function initializes the IOM for operation with the EM9304.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_devices_em9304_init(uint32_t ui32Module, am_hal_iom_config_t *psIomConfig, void **ppIomHandle)
{
    //
    // Configure the IOM pins.
    //
    am_bsp_iom_pins_enable(ui32Module, AM_HAL_IOM_SPI_MODE);

    //
    // Configure the EM9304 pins
    //
    am_devices_em9304_config_pins();

    //
    // Enable fault detection.
    //
#if AM_APOLLO3_MCUCTRL
    am_hal_mcuctrl_control(AM_HAL_MCUCTRL_CONTROL_FAULT_CAPTURE_ENABLE, 0);
#else
    am_hal_mcuctrl_fault_capture_enable();
#endif

    //
    // Initialize the IOM instance.
    //
    if (am_hal_iom_initialize(ui32Module, &g_pEM9304IOMHandle) ||
        am_hal_iom_power_ctrl(g_pEM9304IOMHandle, AM_HAL_SYSCTRL_WAKE, false) ||
        am_hal_iom_configure(g_pEM9304IOMHandle, psIomConfig) ||
        am_hal_iom_enable(g_pEM9304IOMHandle))
    {
        return AM_DEVICES_EM9304_STATUS_ERROR;
    }

    *ppIomHandle = g_pEM9304IOMHandle;
    //
    // Return the status.
    //
    return AM_DEVICES_EM9304_STATUS_SUCCESS;
}


//*****************************************************************************
//
//! @brief Apollo3 full duplex SPI transaction.
//!
//! @param None.
//!
//! This function handles a full duplex transaction on the EM9304.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_devices_em9304_fullduplex(uint32_t ui32WriteAddress,
                             uint8_t *pui8TxBuffer,
                             uint8_t *pui8RxBuffer,
                             uint32_t ui32TxNumBytes)
{
    am_hal_iom_transfer_t Transaction;
    uint32_t ui32Status;

    //
    // Set up the full-duplex transaction.
    //
    Transaction.uPeerInfo.ui32SpiChipSelect = g_sEm9304.ui32IOMChipSelect;
    Transaction.bContinue         = false;
    Transaction.ui32InstrLen      = 0;
    Transaction.ui32Instr      = 0;
    Transaction.ui32NumBytes       = ui32TxNumBytes;
    Transaction.pui32TxBuffer       = (uint32_t *)pui8TxBuffer;
    Transaction.pui32RxBuffer       = (uint32_t *)pui8RxBuffer;
    Transaction.eDirection       = AM_HAL_IOM_FULLDUPLEX;
    Transaction.ui8RepeatCount   = 0;

    // Select the EM9304
    EM9304_SPISLAVESELECT();

    // Wait until ready (RDY goes high)
    while ( !EM9304_RDY_INT() );

    //
    // Do the transaction.
    // Header information is assumed to be in the TX buffer.
    //
    ui32Status = am_hal_iom_spi_blocking_fullduplex(g_pEM9304IOMHandle,
                              &Transaction);

    // Deselect the EM9304
    EM9304_SPISLAVEDESELECT();
    return ui32Status;
}
#endif // defined(AM_PART_APOLLO3)

