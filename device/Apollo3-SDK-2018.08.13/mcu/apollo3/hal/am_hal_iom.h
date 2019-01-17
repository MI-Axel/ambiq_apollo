//*****************************************************************************
//
//! @file am_hal_iom.h
//!
//! @brief Functions for accessing and configuring the IO Master module
//!
//! @addtogroup hal Hardware Abstraction Layer (HAL)
//! @addtogroup iom IO Master (SPI/I2C)
//! @ingroup hal
//! @{

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

#ifndef AM_HAL_IOM_H
#define AM_HAL_IOM_H

#include "am_hal_status.h"
#include "am_hal_sysctrl.h"


//*****************************************************************************
//
//! CMSIS-Style macro for handling a variable IOM module number.
//
//*****************************************************************************
#if AM_CMSIS_REGS
#define IOMn(n) ((IOM0_Type*)(IOM0_BASE + (n * (IOM1_BASE - IOM0_BASE))))
#endif // AM_CMSIS_REGS

//
// Maximum time to wait for hardware to finish a blocking transaction
// This is an escape to allow for bailing out in case of faulty peripheral
// (e.g. a device pulling the I2C clock low)
//
#define AM_HAL_IOM_MAX_BLOCKING_WAIT    500000 // 0.5 sec

//
//  AM_HAL_IOM_CQ=1 will use the Command Queue in nonblocking transfers.
//         0 uses plain DMA (w/o CQ) in nonblocking transfers.
//  This should be enabled only for A1 silicon.
//
#define AM_HAL_IOM_CQ                   1
//*****************************************************************************
//
// IOM Specific status codes
//
//*****************************************************************************
typedef enum
{
    // Error in hardware command issued or illegal access by SW
    AM_HAL_IOM_ERR_INVALID_OPER = AM_HAL_STATUS_MODULE_SPECIFIC_START,
    // Loss of I2C multi-master arbitration
    AM_HAL_IOM_ERR_I2C_ARB,
    // I2C NAK
    AM_HAL_IOM_ERR_I2C_NAK,
} am_hal_iom_err_e;

//*****************************************************************************
//
// General defines
//
//*****************************************************************************
#define AM_HAL_IOM_FIFO_SIZE_MAX        32
#define AM_HAL_IOM_MAX_OFFSETSIZE       3
#define AM_HAL_IOM_MAX_TXNSIZE_SPI      4095
#define AM_HAL_IOM_MAX_TXNSIZE_I2C      255
#define AM_HAL_IOM_MAX_CS_SPI           3

//*****************************************************************************
//
//! @brief enumeration types for the IOM.
//
//*****************************************************************************

//
// IOM mode enumerations
//
typedef enum
{
    AM_HAL_IOM_SPI_MODE,
    AM_HAL_IOM_I2C_MODE,
    AM_HAL_IOM_NUM_MODES
} am_hal_iom_mode_e;

//
// Transmit or receive enumerations.
// Make these enums consistent with the IOM CMD register values.
//
typedef enum
{
    AM_HAL_IOM_TX,
    AM_HAL_IOM_RX,
    AM_HAL_IOM_FULLDUPLEX, // Not supported currently - TODO
} am_hal_iom_dir_e;

//
// Enumerate the SPI modes.  Note that these are arranged per the ordering of
// SPHA (bit1) and SPOL (bit0) in the IOM.MSPICFG register.
//
typedef enum
{
    AM_HAL_IOM_SPI_MODE_0,                  // CPOL = 0; CPHA = 0
    AM_HAL_IOM_SPI_MODE_2,                  // CPOL = 1; CPHA = 0
    AM_HAL_IOM_SPI_MODE_1,                  // CPOL = 0; CPHA = 1
    AM_HAL_IOM_SPI_MODE_3,                  // CPOL = 1; CPHA = 1
} am_hal_iom_spi_mode_e;

//*****************************************************************************
//
//! @brief Configuration structure for the IOM.
//
//*****************************************************************************
typedef struct
{
    //
    //! Select the interface mode, SPI or I2C
    //
    am_hal_iom_mode_e eInterfaceMode;

    //
    //! Select the interface clock frequency
    //
    uint32_t ui32ClockFreq;

    //
    //! Select the SPI clock mode (polarity/phase). Ignored for I2C operation.
    //
    am_hal_iom_spi_mode_e eSpiMode;

    //
    // Non-Blocking transaction memory configuration
    // Set length and pointer to Transfer Control Buffer.
    // Length is in 4 byte multiples
    //
    uint32_t *pNBTxnBuf;
    uint32_t ui32NBTxnBufLength;
}
am_hal_iom_config_t;

//*****************************************************************************
//
//! @brief Status structure for the IOM.
//
//*****************************************************************************
typedef struct
{
    //
    // IOM status.
    //
    bool     bStatIdle;
    bool     bStatCmdAct;
    bool     bStatErr;

    //!
    //! DMA status
    //! One of:
    //!     AM_HAL_IOM_STATUS_DMA_IN_PROGRESS
    //!     AM_HAL_IOM_STATUS_XFER_COMPLETE
    //!     AM_HAL_IOM_STATUS_DMAERR
    //!
    uint32_t ui32DmaStat;

    uint32_t ui32MaxTransactions;
    uint32_t ui32NumPendTransactions;
}
am_hal_iom_status_t;

//
// transfer structure
//
typedef struct
{
    union
    {
        //
        //! Chip enable (chip select) for this transaction on this device.
        //
        uint32_t ui32SpiChipSelect;
        uint32_t ui32I2CDevAddr;
    } uPeerInfo;

    //
    //! Instruction length (0,1,2, or 3).
    //
    uint32_t ui32InstrLen;

    //
    //! Device Instruction (aka Command). Often used as the offset.
    //
    uint32_t ui32Instr;

    //
    //! Number of bytes to transfer
    //
    uint32_t ui32NumBytes;

    //
    //! Transfer Direction (Transmit/Receive)
    //
    am_hal_iom_dir_e eDirection;

    //
    //! Buffer
    //
    uint32_t *pui32TxBuffer;
    uint32_t *pui32RxBuffer;

    //
    // Continue - holds the SPI or I2C bus for multiple transactions.
    //
    bool     bContinue;

    //
    // Repeat Count
    //
    uint8_t  ui8RepeatCount;

    //
    //! DMA: Priority 0 = Low (best effort); 1 = High (service immediately)
    //
    uint8_t  ui8Priority;

    //! Command Queue Advanced control on gating conditions for transaction to start
    //
    uint32_t              ui32PauseCondition;
    //! Command Queue Advanced Post-Transaction status setting
    uint32_t              ui32StatusSetClr;

} am_hal_iom_transfer_t;

typedef enum
{
    AM_HAL_IOM_REQ_FLAG_SETCLR = 0,
    AM_HAL_IOM_REQ_SPI_LSB,
    AM_HAL_IOM_REQ_SPI_FULLDUPLEX,
    AM_HAL_IOM_REQ_SPI_RDTHRESH,
    AM_HAL_IOM_REQ_SPI_WRTHRESH,
    AM_HAL_IOM_REQ_MAX
} am_hal_iom_request_e;

//
// Transfer callback function prototype
//
typedef void (*am_hal_iom_callback_t)(void *pCallbackCtxt, uint32_t transactionStatus);

#define am_hal_iom_buffer(A)            \
union                                   \
{                                       \
    uint32_t words[(A + 3) >> 2];       \
    uint8_t bytes[A];                   \
}

//*****************************************************************************
//
//! @name IOM Clock Frequencies
//! @brief Macro definitions for common SPI and I2C clock frequencies.
//!
//! These macros may be used with the ui32ClockFrequency member of the
//! am_hal_iom_config_t structure to set the clock frequency of the serial
//! interfaces.
//!
//! This list of frequencies is not exhaustive by any means. If your desired
//! frequency is not in this list, simply set ui32ClockFrequency to the
//! desired frequency (in Hz) when calling am_hal_iom_config().
//
//*****************************************************************************
#define AM_HAL_IOM_48MHZ    48000000
#define AM_HAL_IOM_24MHZ    24000000
#define AM_HAL_IOM_16MHZ    16000000
#define AM_HAL_IOM_12MHZ    12000000
#define AM_HAL_IOM_8MHZ      8000000
#define AM_HAL_IOM_6MHZ      6000000
#define AM_HAL_IOM_4MHZ      4000000
#define AM_HAL_IOM_3MHZ      3000000
#define AM_HAL_IOM_2MHZ      2000000
#define AM_HAL_IOM_1_5MHZ    1500000
#define AM_HAL_IOM_1MHZ      1000000
#define AM_HAL_IOM_750KHZ     750000
#define AM_HAL_IOM_500KHZ     500000
#define AM_HAL_IOM_400KHZ     400000
#define AM_HAL_IOM_375KHZ     375000
#define AM_HAL_IOM_250KHZ     250000
#define AM_HAL_IOM_125KHZ     125000
#define AM_HAL_IOM_100KHZ     100000
#define AM_HAL_IOM_50KHZ       50000
#define AM_HAL_IOM_10KHZ       10000

//*****************************************************************************
//
// IOM Interrupts
//
//*****************************************************************************
#if AM_CMSIS_REGS
#define AM_HAL_IOM_INT_CQERR            IOM0_INTEN_CQERR_Msk        // Error during command queue operations
#define AM_HAL_IOM_INT_CQUPD            IOM0_INTEN_CQUPD_Msk        // Command queue operation  performed a register write with the register address bit 0 set to 1.
#define AM_HAL_IOM_INT_CQPAUSED         IOM0_INTEN_CQPAUSED_Msk     // Command queue operation paused
#define AM_HAL_IOM_INT_DERR             IOM0_INTEN_DERR_Msk         // DMA error received
#define AM_HAL_IOM_INT_DCMP             IOM0_INTEN_DCMP_Msk         // DMA transfer complete
#define AM_HAL_IOM_INT_ARB              IOM0_INTEN_ARB_Msk          // Arbitration loss
#define AM_HAL_IOM_INT_STOP             IOM0_INTEN_STOP_Msk         // STOP command
#define AM_HAL_IOM_INT_START            IOM0_INTEN_START_Msk        // START command
#define AM_HAL_IOM_INT_ICMD             IOM0_INTEN_ICMD_Msk         // ILLEGAL command
#define AM_HAL_IOM_INT_IACC             IOM0_INTEN_IACC_Msk         // Illegal FIFO access
#define AM_HAL_IOM_INT_NAK              IOM0_INTEN_NAK_Msk          // I2C NAK
#define AM_HAL_IOM_INT_FOVFL            IOM0_INTEN_FOVFL_Msk        // Write FIFO overflow
#define AM_HAL_IOM_INT_FUNDFL           IOM0_INTEN_FUNDFL_Msk       // Read FIFO underflow
#define AM_HAL_IOM_INT_THR              IOM0_INTEN_THR_Msk          // FIFO threshold interrupt
#define AM_HAL_IOM_INT_CMDCMP           IOM0_INTEN_CMDCMP_Msk       // Command complete
#else // AM_CMSIS_REGS
#define AM_HAL_IOM_INT_CQERR            AM_REG_IOM_INTEN_CQERR_M      // Error during command queue operations
#define AM_HAL_IOM_INT_CQUPD            AM_REG_IOM_INTEN_CQUPD_M      // Command queue operation  performed a register write with the register address bit 0 set to 1.
#define AM_HAL_IOM_INT_CQPAUSED         AM_REG_IOM_INTEN_CQPAUSED_M   // Command queue operation paused
#define AM_HAL_IOM_INT_DERR             AM_REG_IOM_INTEN_DERR_M       // DMA error received
#define AM_HAL_IOM_INT_DCMP             AM_REG_IOM_INTEN_DCMP_M       // DMA transfer complete
#define AM_HAL_IOM_INT_ARB              AM_REG_IOM_INTEN_ARB_M        // Arbitration loss
#define AM_HAL_IOM_INT_STOP             AM_REG_IOM_INTEN_STOP_M       // STOP command
#define AM_HAL_IOM_INT_START            AM_REG_IOM_INTEN_START_M      // START command
#define AM_HAL_IOM_INT_ICMD             AM_REG_IOM_INTEN_ICMD_M         // ILLEGAL command
#define AM_HAL_IOM_INT_IACC             AM_REG_IOM_INTEN_IACC_M       // Illegal FIFO access
#define AM_HAL_IOM_INT_NAK              AM_REG_IOM_INTEN_NAK_M        // I2C NAK
#define AM_HAL_IOM_INT_FOVFL            AM_REG_IOM_INTEN_FOVFL_M      // Write FIFO overflow
#define AM_HAL_IOM_INT_FUNDFL           AM_REG_IOM_INTEN_FUNDFL_M     // Read FIFO underflow
#define AM_HAL_IOM_INT_THR              AM_REG_IOM_INTEN_THR_M        // FIFO threshold interrupt
#define AM_HAL_IOM_INT_CMDCMP           AM_REG_IOM_INTEN_CMDCMP_M     // Command complete
#endif // AM_CMSIS_REGS


#define AM_HAL_IOM_INT_SWERR            (AM_HAL_IOM_INT_ICMD | AM_HAL_IOM_INT_IACC | AM_HAL_IOM_INT_FOVFL | AM_HAL_IOM_INT_FUNDFL)
#define AM_HAL_IOM_INT_I2CARBERR        (AM_HAL_IOM_INT_ARB)
#define AM_HAL_IOM_INT_INTERR           (AM_HAL_IOM_INT_CQERR | AM_HAL_IOM_INT_DERR)
#define AM_HAL_IOM_INT_ALL              0xFFFFFFFF
//
// Unsuccessful end of a transaction results in one more more of the following
//
#define AM_HAL_IOM_INT_ERR          (AM_HAL_IOM_INT_SWERR | AM_HAL_IOM_INT_I2CARBERR | AM_HAL_IOM_INT_INTERR | AM_HAL_IOM_INT_NAK)

//*****************************************************************************
//
//! @brief IOM initialization function
//!
//! @param ui32Module   - module instance.
//! @param handle       - returns the handle for the module instance.
//!
//! This function accepts a module instance, allocates the interface and then
//! returns a handle to be used by the remaining interface functions.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_initialize(uint32_t ui32Module, void **ppHandle);

//*****************************************************************************
//
//! @brief IOM configuration function
//!
//! @param handle       - handle for the IOM.
//! @param pConfig      - pointer to the IOM specific configuration.
//!
//! This function configures the interface settings for the IO Master.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_configure(void *pHandle, am_hal_iom_config_t *psConfig);

//*****************************************************************************
//
//! @brief IOM enable function
//!
//! @param handle       - handle for the interface.
//!
//! This function enables the IOM for operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_enable(void *pHandle);

//*****************************************************************************
//
//! @brief IOM disable function
//!
//! @param handle       - handle for the interface.
//!
//! This function disables the IOMaster from operation.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_disable(void *pHandle);

//*****************************************************************************
//
//! @brief IOM control function
//!
//! @param handle       - handle for the IOM.
//! @param eReq         - device specific special request code.
//! @param pArgs        - pointer to the request specific arguments.
//!
//! This function allows advanced settings
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_control(void *pHandle, am_hal_iom_request_e eReq, void *pArgs);

//*****************************************************************************
//
//! @brief IOM status function
//!
//! @param handle       - handle for the interface.
//! @param psStatus     - pointer to an interface specific structure used to
//!                       return the status of the interface.
//!
//! This function returns the current status of the interface.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_status_get(void *pHandle, am_hal_iom_status_t *psStatus);

//*****************************************************************************
//
//! @brief IOM enable interrupts function
//!
//! @param handle       - handle for the interface.
//! @param ui32IntMask  - interface specific interrupt mask.
//!
//! This function enables the specific indicated interrupts.
//!
//! The following are valid enable bits, any of which can be ORed together.
//!   AM_REG_IOM_INTEN_CQERR_M      // Error during command queue operations
//!   AM_REG_IOM_INTEN_CQCMP_M      // Command queue operation complete
//!   AM_REG_IOM_INTEN_DERR_M       // DMA error received
//!   AM_REG_IOM_INTEN_DCMP_M       // DMA transfer complete
//!   AM_REG_IOM_INTEN_ARB_M        // Arbitration loss
//!   AM_REG_IOM_INTEN_STOP_M       // STOP command
//!   AM_REG_IOM_INTEN_START_M      // START command
//!   AM_REG_IOM_INTEN_ICMD         // ILLEGAL command
//!   AM_REG_IOM_INTEN_IACC_M       // Illegal FIFO access
//!   AM_REG_IOM_INTEN_NAK_M        // I2C NAK
//!   AM_REG_IOM_INTEN_FOVFL_M      // Write FIFO overflow
//!   AM_REG_IOM_INTEN_FUNDFL_M     // Read FIFO underflow
//!   AM_REG_IOM_INTEN_THR_M        // FIFO threshold interrupt
//!   AM_REG_IOM_INTEN_CMDCMP_M     // Command complete
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_interrupt_enable(void *pHandle, uint32_t ui32IntMask);

//*****************************************************************************
//
//! @brief IOM disable interrupts function
//!
//! @param handle       - handle for the interface.
//! @param ui32IntMask  - interface specific interrupt mask.
//!
//! This function disables the specified interrupts.
//!
//! @return status      - generic or interface specific status.
//!
//! The following are valid disable bits, any of which can be ORed together.
//!   AM_REG_IOM_INTEN_CQERR_M      // Error during command queue operations
//!   AM_REG_IOM_INTEN_CQCMP_M      // Command queue operation complete
//!   AM_REG_IOM_INTEN_DERR_M       // DMA error received
//!   AM_REG_IOM_INTEN_DCMP_M       // DMA transfer complete
//!   AM_REG_IOM_INTEN_ARB_M        // Arbitration loss
//!   AM_REG_IOM_INTEN_STOP_M       // STOP command
//!   AM_REG_IOM_INTEN_START_M      // START command
//!   AM_REG_IOM_INTEN_ICMD         // ILLEGAL command
//!   AM_REG_IOM_INTEN_IACC_M       // Illegal FIFO access
//!   AM_REG_IOM_INTEN_NAK_M        // I2C NAK
//!   AM_REG_IOM_INTEN_FOVFL_M      // Write FIFO overflow
//!   AM_REG_IOM_INTEN_FUNDFL_M     // Read FIFO underflow
//!   AM_REG_IOM_INTEN_THR_M        // FIFO threshold interrupt
//!   AM_REG_IOM_INTEN_CMDCMP_M     // Command complete
//
//*****************************************************************************
extern uint32_t am_hal_iom_interrupt_disable(void *pHandle, uint32_t ui32IntMask);

//*****************************************************************************
//
//! @brief IOM get interrupt status
//!
//! @param handle         - handle for the interface.
//! @param pui32IntStatus - pointer to a uint32_t to return the interrupt status
//!
//! This function returns the interrupt status for the given peripheral.
//!
//! The following are valid status bits.
//!   AM_REG_IOM_INTSTAT_CQERR_M    // Error during command queue operations
//!   AM_REG_IOM_INTSTAT_CQCMP_M    // Command queue operation complete
//!   AM_REG_IOM_INTSTAT_DERR_M     // DMA error received
//!   AM_REG_IOM_INTSTAT_DCMP_M     // DMA transfer complete
//!   AM_REG_IOM_INTSTAT_ARB_M      // Arbitration loss
//!   AM_REG_IOM_INTSTAT_STOP_M     // STOP command
//!   AM_REG_IOM_INTSTAT_START_M    // START command
//!   AM_REG_IOM_INTSTAT_ICMD       // ILLEGAL command
//!   AM_REG_IOM_INTSTAT_IACC_M     // Illegal FIFO access
//!   AM_REG_IOM_INTSTAT_NAK_M      // I2C NAK
//!   AM_REG_IOM_INTSTAT_FOVFL_M    // Write FIFO overflow
//!   AM_REG_IOM_INTSTAT_FUNDFL_M   // Read FIFO underflow
//!   AM_REG_IOM_INTSTAT_THR_M      // FIFO threshold interrupt
//!   AM_REG_IOM_INTSTAT_CMDCMP_M   // Command complete
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_interrupt_status_get(void *pHandle, bool bEnabledOnly,
                                                uint32_t *pui32IntStatus);

//*****************************************************************************
//
//! @brief IOM interrupt clear
//!
//! @param handle         - handle for the interface.
//! @param ui32IntMask  - interface specific interrupt mask.
//!
//! This function clears the interrupts for the given peripheral.
//!
//! The following are valid clear bits, any of which can be ORed together.
//!   AM_REG_IOM_INTCLR_CQERR_M     // Error during command queue operations
//!   AM_REG_IOM_INTCLR_CQCMP_M     // Command queue operation complete
//!   AM_REG_IOM_INTCLR_DERR_M      // DMA error received
//!   AM_REG_IOM_INTCLR_DCMP_M      // DMA transfer complete
//!   AM_REG_IOM_INTCLR_ARB_M       // Arbitration loss
//!   AM_REG_IOM_INTCLR_STOP_M      // STOP command
//!   AM_REG_IOM_INTCLR_START_M     // START command
//!   AM_REG_IOM_INTCLR_ICMD        // ILLEGAL command
//!   AM_REG_IOM_INTCLR_IACC_M      // Illegal FIFO access
//!   AM_REG_IOM_INTCLR_NAK_M       // I2C NAK
//!   AM_REG_IOM_INTCLR_FOVFL_M     // Write FIFO overflow
//!   AM_REG_IOM_INTCLR_FUNDFL_M    // Read FIFO underflow
//!   AM_REG_IOM_INTCLR_THR_M       // FIFO threshold interrupt
//!   AM_REG_IOM_INTCLR_CMDCMP_M    // Command complete
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_interrupt_clear(void *pHandle, uint32_t ui32IntMask);

//*****************************************************************************
//
//! @brief IOM interrupt service routine
//!
//! @param handle       - handle for the interface.
//! @param ui32IntMask  - interface specific interrupt mask indicating
//!                       interrupts to be serviced
//!
//! This function is designed to be called from within the user defined ISR
//! (am_iom_isr) in order to service the non-blocking, queued, or DMA processing
//! for a given module instance.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_interrupt_service(void *pHandle, uint32_t ui32IntMask);

//*****************************************************************************
//
//! @brief IOM power control function
//!
//! @param handle       - handle for the interface.
//! @param ePowerState  - the desired power state to move the peripheral to.
//! @param retainState  - flag (if true) to save/restore perhipheral state upon
//!                       power state change.
//!
//! This function updates the peripheral to a given power state.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_power_ctrl(void *pHandle,
                                      am_hal_sysctrl_power_state_e ePowerState,
                                      bool retainState);

//*****************************************************************************
//
//! @brief IOM blocking transfer function
//!
//! @param handle       - handle for the interface.
//! @param pTransaction - pointer to the transaction control structure.
//!
//! This function performs a transaction on the IOM in PIO mode.  It handles
//! half duplex transactions only (TX or RX).
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_blocking_transfer(void *pHandle,
                                             am_hal_iom_transfer_t *psTransaction);

//*****************************************************************************
//
//! @brief IOM non-blocking transfer function
//!
//! @param handle       - handle for the interface.
//! @param pTransaction - pointer to the uniform transaction control structure.
//! @param pfnCallback  - pointer the callback function to be executed when
//!                       transaction is complete can be set to NULL).
//! @param pCallbackCtxt- context registered which is passed on to the callback
//!                       function
//!
//! This function performs a transaction on the interface.  It handles both full
//! and half duplex transactions.  The callback is executed when the transaction
//! is complete.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
extern uint32_t am_hal_iom_nonblocking_transfer(void *pHandle,
                                                am_hal_iom_transfer_t *psTransaction,
                                                am_hal_iom_callback_t pfnCallback,
                                                void *pCallbackCtxt);

//*****************************************************************************
//
//! @brief IOM uninitialize function
//!
//! @param handle       - returns the handle for the module instance.
//!
//! This function accepts a handle to the initialized interface and returns
//! the peripheral instance to a known uninitialized state.
//!
//! @return status      - generic or interface specific status.
//
//*****************************************************************************
//
// Uninitialize the interface and return the handle to a known state.
//
extern uint32_t am_hal_iom_uninitialize(void *pHandle);

//*****************************************************************************
//
//! @brief Perform a Full Duplex transaction.
//!
//! @param handle       - handle for the interface.
//!
//! @return HAL status of the operation.
//
//*****************************************************************************
uint32_t
am_hal_iom_spi_blocking_fullduplex(void *pHandle,
                                   am_hal_iom_transfer_t *psTransaction);


//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
#endif // AM_HAL_IOM_H
