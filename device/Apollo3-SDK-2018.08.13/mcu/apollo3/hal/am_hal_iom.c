//*****************************************************************************
//
//  am_hal_iom.c
//! @file
//!
//! @brief Functions for interfacing with IO Master serial (SPI/I2C) modules.
//!
//! @addtogroup IOM3
//! @ingroup apollo3hal
//! @{
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

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

#ifdef __IAR_SYSTEMS_ICC__
#define AM_INSTR_CLZ(n)                     __CLZ(n)
#else
#define AM_INSTR_CLZ(n)                     __builtin_clz(n)
#endif

#define MANUAL_POP  0

#define AM_HAL_MAGIC_IOM            0x123456
#define AM_HAL_IOM_CHK_HANDLE(h)    ((h) && ((am_hal_handle_prefix_t *)(h))->s.bInit && (((am_hal_handle_prefix_t *)(h))->s.magic == AM_HAL_MAGIC_IOM))


//*****************************************************************************
//
// IOM interface clock selections
//
//*****************************************************************************
#define AM_REG_IOM_CLKCFG_FSEL_MIN_PWR               0x00000000
#define AM_REG_IOM_CLKCFG_FSEL_HFRC                  0x00000100
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV2             0x00000200
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV4             0x00000300
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV8             0x00000400
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV16            0x00000500
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV32            0x00000600
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV64            0x00000700

//*****************************************************************************
//
// Private Types.
//
//*****************************************************************************

//
// Command Queue entry structure.
//
typedef struct
{
#if (AM_HAL_IOM_CQ == 1)
    uint32_t    ui32PAUSENAddr;
    uint32_t    ui32PAUSEENVal;
#endif
    uint32_t    ui32OFFSETHIAddr;
    uint32_t    ui32OFFSETHIVal;
    uint32_t    ui32DEVCFGAddr;
    uint32_t    ui32DEVCFGVal;
    uint32_t    ui32DMACFGdis1Addr;
    uint32_t    ui32DMACFGdis1Val;
    uint32_t    ui32DMATOTCOUNTAddr;
    uint32_t    ui32DMATOTCOUNTVal;
    uint32_t    ui32DMATARGADDRAddr;
    uint32_t    ui32DMATARGADDRVal;
    uint32_t    ui32DMACFGAddr;
    uint32_t    ui32DMACFGVal;
    uint32_t    ui32CMDRPTAddr;
    uint32_t    ui32CMDRPTVal;
    uint32_t    ui32CMDAddr;
    uint32_t    ui32CMDVal;
#if (AM_HAL_IOM_CQ == 1)
    uint32_t    ui32PAUSEN2Addr;
    uint32_t    ui32PAUSEEN2Val;
    uint32_t    ui32SETCLRAddr;
    uint32_t    ui32SETCLRVal;
#endif
} am_hal_iom_txn_cmdlist_t;

#define AM_HAL_IOM_MAX_PENDING_TRANSACTIONS      256 // Must be power of 2 for the implementation below
#define AM_HAL_IOM_CQUPD_INT_FLAG                (0x00000001)

typedef struct
{
    bool        bValid;
    uint32_t    regFIFOTHR;
    uint32_t    regDMATRIGEN;
    uint32_t    regCLKCFG;
    uint32_t    regSUBMODCTRL;
    uint32_t    regCQCFG;
    uint32_t    regCQADDR;
    uint32_t    regCQFLAGS;
    uint32_t    regCQPAUSEEN;
    uint32_t    regCQCURIDX;
    uint32_t    regCQENDIDX;
    uint32_t    regMSPICFG;
    uint32_t    regMI2CCFG;
    uint32_t    regINTEN;
} am_hal_iom_register_state_t;

typedef struct
{
    am_hal_handle_prefix_t  prefix;
    //
    // Physical module number.
    //
    uint32_t                ui32Module;

    //
    // Interface mode (SPI or I2C).
    //
    am_hal_iom_mode_e       eInterfaceMode;
    uint32_t                *pNBTxnBuf;
    uint32_t                ui32NBTxnBufLength;

    uint32_t                ui32UserIntCfg;
    uint32_t                ui32TxnInt;

    uint32_t                ui32LastIdxProcessed;
    uint32_t                ui32MaxTransactions;
    volatile uint32_t       ui32NumPendTransactions;
    //
    // Stores the CQ callbacks.
    //
    am_hal_iom_callback_t   pfnCallback[AM_HAL_IOM_MAX_PENDING_TRANSACTIONS];
    void                    *pCallbackCtxt[AM_HAL_IOM_MAX_PENDING_TRANSACTIONS];
#if (AM_HAL_IOM_CQ == 1)
    void                    *pCmdQHdl;
#else
    uint32_t                ui32NextIdx;
    am_hal_iom_txn_cmdlist_t   *pTransactions;
#endif
    //
    // Delay timeout value.
    //
    uint32_t                waitTimeout;
    // Configured clock time
    uint32_t                ui32BitTimeTicks;

    am_hal_iom_register_state_t registerState;

} am_hal_iom_state_t;

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
am_hal_iom_state_t          g_IOMhandles[AM_REG_IOM_NUM_MODULES];

//*****************************************************************************
//
// Function to build the CMD value.
// Returns the CMD value, but does not set the CMD register.
//
// The OFFSETHI register must still be handled by the caller, e.g.
//      AM_REGn(IOM, ui32Module, OFFSETHI) = (uint16_t)(ui32Offset >> 8);
//
//*****************************************************************************
static uint32_t
build_cmd(uint32_t ui32CS,     uint32_t ui32Dir, uint32_t ui32Cont,
          uint32_t ui32Offset, uint32_t ui32OffsetCnt,
          uint32_t ui32nBytes)
{
    //
    // Initialize the CMD variable
    //
    uint32_t ui32Cmd = 0;

    //
    // If SPI, we'll need the chip select
    //
#if AM_CMSIS_REGS
    ui32Cmd |= _VAL2FLD(IOM0_CMD_CMDSEL, ui32CS);

    //
    // Build the CMD with number of bytes and direction.
    //
    ui32Cmd |= _VAL2FLD(IOM0_CMD_TSIZE, ui32nBytes);

    if (ui32Dir == AM_HAL_IOM_RX)
    {
        ui32Cmd |= _VAL2FLD(IOM0_CMD_CMD, IOM0_CMD_CMD_READ);
    }
    else
    {
        ui32Cmd |= _VAL2FLD(IOM0_CMD_CMD, IOM0_CMD_CMD_WRITE);
    }

    ui32Cmd |= _VAL2FLD(IOM0_CMD_CONT, ui32Cont);

    //
    // Now add the OFFSETLO and OFFSETCNT information.
    //
    ui32Cmd |= _VAL2FLD(IOM0_CMD_OFFSETLO, (uint8_t)ui32Offset);
    ui32Cmd |= _VAL2FLD(IOM0_CMD_OFFSETCNT, ui32OffsetCnt);
#else // AM_CMSIS_REGS
    ui32Cmd |= AM_BFV(IOM, CMD, CMDSEL, ui32CS);

    //
    // Build the CMD with number of bytes and direction.
    //
    ui32Cmd |= AM_BFV(IOM, CMD, TSIZE, ui32nBytes);
    if (ui32Dir == AM_HAL_IOM_RX)
    {
        ui32Cmd |= AM_BFV(IOM, CMD, CMD, AM_REG_IOM_CMD_CMD_READ);
    }
    else
    {
        ui32Cmd |= AM_BFV(IOM, CMD, CMD, AM_REG_IOM_CMD_CMD_WRITE);
    }
    ui32Cmd |= AM_BFV(IOM, CMD, CONT, ui32Cont);

    //
    // Now add the OFFSETLO and OFFSETCNT information.
    //
    ui32Cmd |= AM_BFV(IOM, CMD, OFFSETLO, (uint8_t)ui32Offset);
    ui32Cmd |= AM_BFV(IOM, CMD, OFFSETCNT, ui32OffsetCnt);
#endif // AM_CMSIS_REGS

    return ui32Cmd;
} // build_cmd()

//*****************************************************************************
//
// Function to build CMD lists.
//
//*****************************************************************************
static void
build_txn_cmdlist(am_hal_iom_state_t       *pIOMState,
                  am_hal_iom_txn_cmdlist_t *pCQEntry,
                  am_hal_iom_transfer_t    *psTransaction)
{
    uint32_t                ui32Cmd;
    uint32_t                ui32Module = pIOMState->ui32Module;
    uint32_t                ui32Dir = psTransaction->eDirection;
    uint32_t                ui32SRAMAddress;

    //
    // Command for OFFSETHI
    //
#if AM_CMSIS_REGS
    pCQEntry->ui32OFFSETHIAddr  = (uint32_t)&IOMn(ui32Module)->OFFSETHI;

    pCQEntry->ui32OFFSETHIVal   = (uint16_t)(psTransaction->ui32Instr >> 8);

    //
    // Command for I2C DEVADDR field in DEVCFG
    //
    pCQEntry->ui32DEVCFGAddr    = (uint32_t)&IOMn(ui32Module)->DEVCFG;
    pCQEntry->ui32DEVCFGVal     = _VAL2FLD(IOM0_DEVCFG_DEVADDR, psTransaction->uPeerInfo.ui32I2CDevAddr);

    //
    // Command to disable DMA before writing TOTCOUNT.
    //
    pCQEntry->ui32DMACFGdis1Addr   = (uint32_t)&IOMn(ui32Module)->DMACFG;
    pCQEntry->ui32DMACFGdis1Val    = 0x0;

    //
    // Command to set DMATOTALCOUNT
    //
    pCQEntry->ui32DMATOTCOUNTAddr = (uint32_t)&IOMn(ui32Module)->DMATOTCOUNT;
    pCQEntry->ui32DMATOTCOUNTVal  = (1 + psTransaction->ui8RepeatCount) * psTransaction->ui32NumBytes;

    //
    // Command to set DMATARGADDR
    //
    pCQEntry->ui32DMATARGADDRAddr = (uint32_t)&IOMn(ui32Module)->DMATARGADDR;
    ui32SRAMAddress = (ui32Dir == AM_HAL_IOM_TX) ? (uint32_t)psTransaction->pui32TxBuffer : (uint32_t)psTransaction->pui32RxBuffer;
    pCQEntry->ui32DMATARGADDRVal  = ui32SRAMAddress;

    //
    // Command to set DMACFG to start the DMA operation
    //
    pCQEntry->ui32DMACFGAddr    = (uint32_t)&IOMn(ui32Module)->DMACFG;
    pCQEntry->ui32DMACFGVal     =
        _VAL2FLD(IOM0_DMACFG_DMAPRI, psTransaction->ui8Priority)     |
        _VAL2FLD(IOM0_DMACFG_DMADIR, ui32Dir == AM_HAL_IOM_TX ? 1 : 0);

    if (psTransaction->ui32NumBytes)
    {
        pCQEntry->ui32DMACFGVal |= IOM0_DMACFG_DMAEN_Msk;
    }

    pCQEntry->ui32CMDRPTAddr = (uint32_t)&IOMn(ui32Module)->CMDRPT;

    pCQEntry->ui32CMDRPTVal = psTransaction->ui8RepeatCount;

    //
    // Command to start the transfer.
    //
    ui32Cmd = pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE  ?
              psTransaction->uPeerInfo.ui32SpiChipSelect : 0;
    ui32Cmd = build_cmd(ui32Cmd,                            // ChipSelect
                        ui32Dir,          // ui32Dir
                        psTransaction->bContinue,           // ui32Cont
                        psTransaction->ui32Instr,           // ui32Offset
                        psTransaction->ui32InstrLen,        // ui32OffsetCnt
                        psTransaction->ui32NumBytes);  // ui32Bytes

    pCQEntry->ui32CMDAddr  = (uint32_t)&IOMn(ui32Module)->CMD;
    pCQEntry->ui32CMDVal   = ui32Cmd;

#else // AM_CMSIS_REGS
    pCQEntry->ui32OFFSETHIAddr  = AM_REGADDRn(IOM, ui32Module, OFFSETHI);
    pCQEntry->ui32OFFSETHIVal   = (uint16_t)(psTransaction->ui32Instr >> 8);

    //
    // Command for I2C DEVADDR field in DEVCFG
    //
    pCQEntry->ui32DEVCFGAddr    = AM_REGADDRn(IOM, ui32Module, DEVCFG);
    pCQEntry->ui32DEVCFGVal     = AM_REG_IOM_DEVCFG_DEVADDR(psTransaction->uPeerInfo.ui32I2CDevAddr);

    //
    // Command to disable DMA before writing TOTCOUNT.
    //
    pCQEntry->ui32DMACFGdis1Addr   = AM_REGADDRn(IOM, ui32Module, DMACFG);
    pCQEntry->ui32DMACFGdis1Val    = 0x0;

    //
    // Command to set DMATOTALCOUNT
    //
    pCQEntry->ui32DMATOTCOUNTAddr = AM_REGADDRn(IOM, ui32Module, DMATOTCOUNT);
    pCQEntry->ui32DMATOTCOUNTVal  = (1 + psTransaction->ui8RepeatCount) * psTransaction->ui32NumBytes;

    //
    // Command to set DMATARGADDR
    //
    pCQEntry->ui32DMATARGADDRAddr = AM_REGADDRn(IOM, ui32Module, DMATARGADDR);
    ui32SRAMAddress = (ui32Dir == AM_HAL_IOM_TX) ? (uint32_t)psTransaction->pui32TxBuffer : (uint32_t)psTransaction->pui32RxBuffer;
    pCQEntry->ui32DMATARGADDRVal  = ui32SRAMAddress;

    //
    // Command to set DMACFG to start the DMA operation
    //
    pCQEntry->ui32DMACFGAddr    = AM_REGADDRn(IOM, ui32Module, DMACFG);
    pCQEntry->ui32DMACFGVal     =
        AM_REG_IOM_DMACFG_DMAPRI(psTransaction->ui8Priority)     |
        AM_REG_IOM_DMACFG_DMADIR(ui32Dir == AM_HAL_IOM_TX ? 1 : 0);
    if (psTransaction->ui32NumBytes)
    {
        pCQEntry->ui32DMACFGVal |= AM_REG_IOM_DMACFG_DMAEN_M;
    }

    pCQEntry->ui32CMDRPTAddr = AM_REGADDRn(IOM, ui32Module, CMDRPT);
    pCQEntry->ui32CMDRPTVal = psTransaction->ui8RepeatCount;
    //
    // Command to start the transfer.
    //
    ui32Cmd = pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE  ?
              psTransaction->uPeerInfo.ui32SpiChipSelect : 0;
    ui32Cmd = build_cmd(ui32Cmd,                            // ChipSelect
                        ui32Dir,          // ui32Dir
                        psTransaction->bContinue,           // ui32Cont
                        psTransaction->ui32Instr,           // ui32Offset
                        psTransaction->ui32InstrLen,        // ui32OffsetCnt
                        psTransaction->ui32NumBytes);  // ui32Bytes

    pCQEntry->ui32CMDAddr  = AM_REGADDRn(IOM, ui32Module, CMD);
    pCQEntry->ui32CMDVal   = ui32Cmd;
#if (AM_HAL_IOM_CQ == 1)
    pCQEntry->ui32PAUSENAddr = pCQEntry->ui32PAUSEN2Addr = AM_REGADDRn(IOM, ui32Module, CQPAUSEEN);
    pCQEntry->ui32PAUSEEN2Val = AM_REG_IOM_CQPAUSEEN_CQPEN_IDXEQ;
    pCQEntry->ui32PAUSEENVal = psTransaction->ui32PauseCondition | AM_REG_IOM_CQPAUSEEN_CQPEN_IDXEQ;
    pCQEntry->ui32SETCLRVal = psTransaction->ui32StatusSetClr;
    pCQEntry->ui32SETCLRAddr = AM_REGADDRn(IOM, ui32Module, CQSETCLEAR);
#endif
#endif // AM_CMSIS_REGS
} // build_txn_cmdlist()

//*****************************************************************************
//
// enable_submodule() - Utilizes the built-in fields that indicate whether which
//                      submodule is supported, then enables that submodule.
//
//  Input: ui32Type = 0, set for SPI.
//         ui32Type = 1, set for I2C.
//
//*****************************************************************************
static void
enable_submodule(uint32_t ui32Module, uint32_t ui32Type)
{
#if AM_CMSIS_REGS
    if ( IOMn(ui32Module)->SUBMODCTRL_b.SMOD0TYPE == ui32Type )
    {
        IOMn(ui32Module)->SUBMODCTRL =
             _VAL2FLD(IOM0_SUBMODCTRL_SMOD1EN, 0) |
             _VAL2FLD(IOM0_SUBMODCTRL_SMOD0EN, 1);
    }
    else
    {
        IOMn(ui32Module)->SUBMODCTRL =
             _VAL2FLD(IOM0_SUBMODCTRL_SMOD1EN, 1) |
             _VAL2FLD(IOM0_SUBMODCTRL_SMOD0EN, 0);
    }
#else // AM_CMSIS_REGS
    if ( AM_BFRn(IOM, ui32Module, SUBMODCTRL, SMOD0TYPE) == ui32Type )
    {
        AM_REGn(IOM, ui32Module, SUBMODCTRL) =
            AM_REG_IOM_SUBMODCTRL_SMOD1EN(0) |
            AM_REG_IOM_SUBMODCTRL_SMOD0EN(1);
    }
    else
    {
        AM_REGn(IOM, ui32Module, SUBMODCTRL) =
            AM_REG_IOM_SUBMODCTRL_SMOD1EN(1) |
            AM_REG_IOM_SUBMODCTRL_SMOD0EN(0);
    }
#endif // AM_CMSIS_REGS
} // enable_submodule()

//*****************************************************************************
//
// Error handling.
//
//*****************************************************************************
uint32_t
internal_iom_get_int_err(uint32_t ui32Module, uint32_t ui32IntStatus)
{
    //
    // Map the INTSTAT bits for transaction status
    //
    uint32_t ui32Status = AM_HAL_STATUS_SUCCESS;

    //
    // Let's accumulate the errors
    //
#if AM_CMSIS_REGS
    ui32IntStatus |= IOMn(ui32Module)->INTSTAT;
#else // AM_CMSIS_REGS
    ui32IntStatus |= AM_REGn(IOM, ui32Module, INTSTAT);
#endif // AM_CMSIS_REGS

    if (ui32IntStatus & AM_HAL_IOM_INT_SWERR)
    {
        // Error in hardware command issued or illegal access by SW
        ui32Status = AM_HAL_IOM_ERR_INVALID_OPER;
    }
    else if (ui32IntStatus & AM_HAL_IOM_INT_I2CARBERR)
    {
        // Loss of I2C multi-master arbitration
        ui32Status = AM_HAL_IOM_ERR_I2C_ARB;
    }
    else if (ui32IntStatus & AM_HAL_IOM_INT_NAK)
    {
        // I2C NAK
        ui32Status = AM_HAL_IOM_ERR_I2C_NAK;
    }
    else if (ui32IntStatus & AM_HAL_IOM_INT_INTERR)
    {
        // Other Error
        ui32Status = AM_HAL_STATUS_FAIL;
    }

    return ui32Status;

} // internal_iom_get_int_err()

static void
internal_iom_reset_on_error(am_hal_iom_state_t  *pIOMState, uint32_t ui32IntMask)
{
    uint32_t iterationsToWait = 2 * pIOMState->ui32BitTimeTicks; // effectively > 6 clocks
    uint32_t ui32Module = pIOMState->ui32Module;
#if AM_CMSIS_REGS
    uint32_t curIntCfg = IOMn(ui32Module)->INTEN;
    IOMn(ui32Module)->INTEN = 0;

    // Disable interrupts temporarily
    if (ui32IntMask & AM_HAL_IOM_INT_DERR)
    {
        if ((IOMn(ui32Module)->DMACFG & IOM0_DMACFG_DMADIR_Msk) == _VAL2FLD(IOM0_DMACFG_DMADIR, IOM0_DMACFG_DMADIR_M2P))
        {
            // Write
            uint32_t dummy = 0xDEADBEEF;
            uint32_t numBytesRemaining = IOMn(ui32Module)->DMATOTCOUNT;

            while (numBytesRemaining)
            {
                if (IOMn(ui32Module)->FIFOPTR_b.FIFO0REM >= 4)
                {
                    // Write one 4-byte word to FIFO
                    IOMn(ui32Module)->FIFOPUSH = dummy;
                    if (numBytesRemaining > 4)
                    {
                        numBytesRemaining -= 4;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // Now wait for command to finish
            while ((IOMn(ui32Module)->STATUS & (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk)) != IOM0_STATUS_IDLEST_Msk);
        }
        else
        {
            // Read
            // Let command finish
            while (IOMn(ui32Module)->STATUS_b.CMDACT)
            {
                while (IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ >= 4)
                {
                    // Read one 4-byte word from FIFO
                    IOMn(ui32Module)->FIFOPOP;
#if MANUAL_POP
                    IOMn(ui32Module)->FIFOPOP = 0x11111111;
#endif
                }
            }
            // Now wait for command to finish
            while ((IOMn(ui32Module)->STATUS & (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk)) != IOM0_STATUS_IDLEST_Msk);
            // Flush any remaining data from FIFO
            while  (IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ)
            {
                while (IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ >= 4)
                {
                    // Read one 4-byte word from FIFO
                    IOMn(ui32Module)->FIFOPOP;
#if MANUAL_POP
                    IOMn(ui32Module)->FIFOPOP = 0x11111111;
#endif
                }
            }
        }
    }
    if (ui32IntMask & AM_HAL_IOM_INT_NAK)
    {
        //
        // Wait for Idle
        //
        while ((IOMn(ui32Module)->STATUS & (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk)) != IOM0_STATUS_IDLEST_Msk);

        //
        // Reset Submodule & FIFO
        //
        // Disable the submodules
        //
        IOMn(ui32Module)->SUBMODCTRL_b.SMOD1EN = 0;
        // Reset Fifo
        IOMn(ui32Module)->FIFOCTRL_b.FIFORSTN = 0;

        // Wait for few IO clock cycles
        am_hal_flash_delay(iterationsToWait);

        IOMn(ui32Module)->FIFOCTRL_b.FIFORSTN = 1;

        // Enable submodule
        IOMn(ui32Module)->SUBMODCTRL_b.SMOD1EN = 1;
    }

    IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;

    // Restore interrupts
    IOMn(ui32Module)->INTEN = curIntCfg;
#else // AM_CMSIS_REGS
    uint32_t curIntCfg = AM_REGn(IOM, ui32Module, INTEN);

    // Disable interrupts temporarily
    AM_REGn(IOM, ui32Module, INTEN) = 0;
    if (ui32IntMask & AM_HAL_IOM_INT_DERR)
    {
        if ((AM_REGn(IOM, ui32Module, DMACFG) & AM_REG_IOM_DMACFG_DMADIR_M) == AM_REG_IOM_DMACFG_DMADIR_M2P)
        {
            // Write
            uint32_t dummy = 0xDEADBEEF;
            uint32_t numBytesRemaining = AM_REGn(IOM, ui32Module, DMATOTCOUNT);
            while (numBytesRemaining)
            {
                if (AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO0REM) >= 4)
                {
                    // Write one 4-byte word to FIFO
                    AM_REGn(IOM, ui32Module, FIFOPUSH) = dummy;
                    if (numBytesRemaining > 4)
                    {
                        numBytesRemaining -= 4;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // Now wait for command to finish
            while ((AM_REGn(IOM, ui32Module, STATUS) & (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M)) != AM_REG_IOM_STATUS_IDLEST_M);
        }
        else
        {
            // Read
            // Let command finish
            while (AM_BFRn(IOM, ui32Module, STATUS, CMDACT))
            {
                while  (AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ) >= 4)
                {
                    // Read one 4-byte word from FIFO
                    AM_REGn(IOM, ui32Module, FIFOPOP);
#if MANUAL_POP
                    AM_REGn(IOM, ui32Module, FIFOPOP) = 0x11111111;
#endif
                }
            }
            // Now wait for command to finish
            while ((AM_REGn(IOM, ui32Module, STATUS) & (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M)) != AM_REG_IOM_STATUS_IDLEST_M);
            // Flush any remaining data from FIFO
            while  (AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ))
            {
                while  (AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ) >= 4)
                {
                    // Read one 4-byte word from FIFO
                    AM_REGn(IOM, ui32Module, FIFOPOP);
#if MANUAL_POP
                    AM_REGn(IOM, ui32Module, FIFOPOP) = 0x11111111;
#endif
                }
            }
        }
    }
    if (ui32IntMask & AM_HAL_IOM_INT_NAK)
    {
        //
        // Wait for Idle
        //
        while ((AM_REGn(IOM, ui32Module, STATUS) & (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M)) != AM_REG_IOM_STATUS_IDLEST_M);

        // Reset Submodule & FIFO
        //
        // Disable the submodules
        //
        AM_BFWn(IOM, ui32Module, SUBMODCTRL, SMOD1EN, 0);
        // Reset Fifo
        AM_BFWn(IOM, ui32Module, FIFOCTRL, FIFORSTN, 0);

        // Wait for few IO clock cycles
        am_hal_flash_delay(iterationsToWait);

        AM_BFWn(IOM, ui32Module, FIFOCTRL, FIFORSTN, 1);
        // Enable submodule
        AM_BFWn(IOM, ui32Module, SUBMODCTRL, SMOD1EN, 1);

    }
    AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    // Restore interrupts
    AM_REGn(IOM, ui32Module, INTEN) = curIntCfg;
#endif // AM_CMSIS_REGS
}

//*****************************************************************************
// compute_freq()
//*****************************************************************************
//
// Compute the interface frequency based on the given parameters
//
static uint32_t
compute_freq(uint32_t ui32HFRCfreqHz,
             uint32_t ui32Fsel, uint32_t ui32Div3,
             uint32_t ui32DivEn, uint32_t ui32TotPer)
{
    uint32_t ui32Denomfinal, ui32ClkFreq;

    ui32Denomfinal = ((1 << (ui32Fsel - 1)) * (1 + ui32Div3 * 2) * (1 + ui32DivEn * (ui32TotPer)));
    ui32ClkFreq = (ui32HFRCfreqHz) / ui32Denomfinal;                           // Compute the set frequency value
    ui32ClkFreq +=  (((ui32HFRCfreqHz) % ui32Denomfinal) > (ui32Denomfinal / 2)) ? 1 : 0;

    return ui32ClkFreq;
} // compute_freq()

//*****************************************************************************
// onebit()
//*****************************************************************************
//
// A power of 2?
// Return true if ui32Value has exactly 1 bit set, otherwise false.
//
static bool
onebit(uint32_t ui32Value)
{
    return ui32Value  &&  !(ui32Value & (ui32Value - 1));
} // onebit()

//*****************************************************************************
//
// iom_get_interface_clock_cfg()
//
// Returns the proper settings for the CLKCFG register.
//
// ui32FreqHz - The desired interface frequency in Hz.
//
// Given a desired serial interface clock frequency, this function computes
// the appropriate settings for the various fields in the CLKCFG register
// and returns the 32-bit value that should be written to that register.
// The actual interface frequency may be slightly lower than the specified
// frequency, but the actual frequency is also returned.
//
// Note A couple of criteria that this algorithm follow are:
//  1. For power savings, choose the highest FSEL possible.
//  2. Use DIV3 when possible rather than DIVEN.
//
// Return An unsigned 64-bit value.
// The lower 32-bits represent the value to use to set CLKCFG.
// The upper 32-bits represent the actual frequency (in Hz) that will result
// from setting CLKCFG with the lower 32-bits.
//
// 0 (64 bits) = error. Note that the caller must check the entire 64 bits.
// It is not an error if only the low 32-bits are 0 (this is a valid value).
// But the entire 64 bits returning 0 is an error.
//!
//*****************************************************************************
static
uint64_t iom_get_interface_clock_cfg(uint32_t ui32FreqHz, uint32_t ui32Phase )
{
    uint32_t ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer, ui32LowPer;
    uint32_t ui32Denom, ui32v1, ui32Denomfinal, ui32ClkFreq, ui32ClkCfg;
    uint32_t ui32HFRCfreqHz;
    int32_t i32Div, i32N;

    if ( ui32FreqHz == 0 )
    {
        return 0;
    }

    //
    // Set the HFRC clock frequency.
    //
    ui32HFRCfreqHz = AM_HAL_CLKGEN_FREQ_MAX_HZ;

    //
    // Compute various parameters used for computing the optimal CLKCFG setting.
    //
    i32Div = (ui32HFRCfreqHz / ui32FreqHz) + ((ui32HFRCfreqHz % ui32FreqHz) ? 1 : 0);    // Round up (ceiling)

    //
    // Compute N (count the number of LS zeros of Div) = ctz(Div) = log2(Div & (-Div))
    //
    i32N = 31 - AM_INSTR_CLZ((i32Div & (-i32Div)));

    if ( i32N > 6 )
    {
        i32N = 6;
    }

    ui32Div3 = ( (ui32FreqHz < (ui32HFRCfreqHz / 16384))            ||
                 ( ((ui32FreqHz >= (ui32HFRCfreqHz / 3))    &&
                    (ui32FreqHz <= ((ui32HFRCfreqHz / 2) - 1)) ) ) ) ? 1 : 0;
    ui32Denom = ( 1 << i32N ) * ( 1 + (ui32Div3 * 2) );
    ui32TotPer = i32Div / ui32Denom;
    ui32TotPer += (i32Div % ui32Denom) ? 1 : 0;
    ui32v1 = 31 - AM_INSTR_CLZ(ui32TotPer);     // v1 = log2(TotPer)
    ui32Fsel = (ui32v1 > 7) ? ui32v1 + i32N - 7 : i32N;
    ui32Fsel++;

    if ( ui32Fsel > 7 )
    {
        //
        // This is an error, can't go that low.
        //
        return 0;
    }

    if ( ui32v1 > 7 )
    {
        ui32DivEn = ui32TotPer;     // Save TotPer for the round up calculation
        ui32TotPer = ui32TotPer>>(ui32v1-7);
        ui32TotPer += ((ui32DivEn) % (1 << (ui32v1 - 7))) ? 1 : 0;
    }

    ui32DivEn = ( (ui32FreqHz >= (ui32HFRCfreqHz / 4)) ||
                  ((1 << (ui32Fsel - 1)) == i32Div) ) ? 0 : 1;

    if (ui32Phase == 1)
    {
        ui32LowPer = (ui32TotPer - 2) / 2;          // Longer high phase
    }
    else
    {
        ui32LowPer = (ui32TotPer - 1) / 2;          // Longer low phase
    }

#if AM_CMSIS_REGS
    ui32ClkCfg = _VAL2FLD(IOM0_CLKCFG_FSEL,   ui32Fsel)     |
                 _VAL2FLD(IOM0_CLKCFG_DIV3,   ui32Div3)     |
                 _VAL2FLD(IOM0_CLKCFG_DIVEN,  ui32DivEn)    |
                 _VAL2FLD(IOM0_CLKCFG_LOWPER, ui32LowPer)   |
                 _VAL2FLD(IOM0_CLKCFG_TOTPER, ui32TotPer - 1);
#else // AM_CMSIS_REGS
    ui32ClkCfg = AM_REG_IOM_CLKCFG_FSEL(ui32Fsel)           |
                 AM_REG_IOM_CLKCFG_DIV3(ui32Div3)           |
                 AM_REG_IOM_CLKCFG_DIVEN(ui32DivEn)         |
                 AM_REG_IOM_CLKCFG_LOWPER(ui32LowPer)       |
                 AM_REG_IOM_CLKCFG_TOTPER(ui32TotPer - 1);
#endif // AM_CMSIS_REGS

    //
    // Now, compute the actual frequency, which will be returned.
    //
    ui32ClkFreq = compute_freq(ui32HFRCfreqHz, ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer - 1);

    //
    // Determine if the actual frequency is a power of 2 (MHz).
    //
    if ( (ui32ClkFreq % 250000) == 0 )
    {
        //
        // If the actual clock frequency is a power of 2 ranging from 250KHz up,
        // we can simplify the CLKCFG value using DIV3 (which also results in a
        // better duty cycle).
        //
        ui32Denomfinal = ui32ClkFreq / (uint32_t)250000;

        if ( onebit(ui32Denomfinal) )
        {
            //
            // These configurations can be simplified by using DIV3.  Configs
            // using DIV3 have a 50% duty cycle, while those from DIVEN will
            // have a 66/33 duty cycle.
            //
            ui32TotPer = ui32LowPer = ui32DivEn = 0;
            ui32Div3 = 1;

            //
            // Now, compute the return values.
            //
            ui32ClkFreq = compute_freq(ui32HFRCfreqHz, ui32Fsel, ui32Div3, ui32DivEn, ui32TotPer);

#if AM_CMSIS_REGS
    ui32ClkCfg = _VAL2FLD(IOM0_CLKCFG_FSEL,   ui32Fsel)     |
                 _VAL2FLD(IOM0_CLKCFG_DIV3,   1)            |
                 _VAL2FLD(IOM0_CLKCFG_DIVEN,  0)            |
                 _VAL2FLD(IOM0_CLKCFG_LOWPER, 0)            |
                 _VAL2FLD(IOM0_CLKCFG_TOTPER, 0);
#else // AM_CMSIS_REGS
            ui32ClkCfg = AM_REG_IOM_CLKCFG_FSEL(ui32Fsel)   |
                         AM_REG_IOM_CLKCFG_DIV3(1)          |
                         AM_REG_IOM_CLKCFG_DIVEN(0)         |
                         AM_REG_IOM_CLKCFG_LOWPER(0)        |
                         AM_REG_IOM_CLKCFG_TOTPER(0);
#endif // AM_CMSIS_REGS
        }
    }

    return ( ((uint64_t)ui32ClkFreq) << 32) | (uint64_t)ui32ClkCfg;

} //iom_get_interface_clock_cfg()

#if (AM_HAL_IOM_CQ == 1)
//*****************************************************************************
//
//! @brief Initializes the IOM Command Queue.
//!
//! @param handle       - handle for the interface.
//! @param ui32Length   - length of the SRAM Command Queue buffer in words.
//! @param pTCB         - pointer to the SRAM to use for the Command Queue.
//!
//! This function initializes the global command queue structure.
//!
//! @return HAL status of the operation.
//
//*****************************************************************************
uint32_t
am_hal_iom_CQInit(void *pHandle, uint32_t ui32Length,
                  uint32_t *pTCB)
{
    am_hal_cmdq_cfg_t cqCfg;
    am_hal_iom_state_t  *pIOMState = (am_hal_iom_state_t *)pHandle;
    uint32_t            ui32Module = pIOMState->ui32Module;
    uint32_t            ui32Status = AM_HAL_STATUS_SUCCESS;

    pIOMState->pCmdQHdl = NULL;
    pIOMState->ui32MaxTransactions = 0;

    cqCfg.pCmdQBuf = pTCB;
    cqCfg.cmdQSize = ui32Length / 2;
    cqCfg.priority = AM_HAL_CMDQ_PRIO_HI;
    ui32Status = am_hal_cmdq_init((am_hal_cmdq_if_e)(AM_HAL_CMDQ_IF_IOM0 + ui32Module),
                      &cqCfg, &pIOMState->pCmdQHdl);
    if (ui32Status == AM_HAL_STATUS_SUCCESS)
    {
        pIOMState->ui32MaxTransactions = AM_HAL_IOM_MAX_PENDING_TRANSACTIONS;
    }
    return ui32Status;
} // am_hal_iom_CQInit()

//*****************************************************************************
//
//! @brief Resets the IOM Command Queue.
//!
//! @param ui32Module   - IOM instance.
//!
//! This function resets the global command queue structure.
//!
//! @return HAL status of the operation.
//
//
//*****************************************************************************
uint32_t
am_hal_IOM_CQReset(void *pHandle)
{
    am_hal_iom_state_t  *pIOMState = (am_hal_iom_state_t *)pHandle;

    if (pIOMState->pCmdQHdl)
    {
        am_hal_cmdq_term(pIOMState->pCmdQHdl, true);
        pIOMState->pCmdQHdl = NULL;
    }

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;
} // am_hal_IOM_CQReset()

//*****************************************************************************
//
//! @brief Adds a transaction the IOM Command Queue.
//!
//! @param handle       - handle for the interface.
//! @param pTransaction - transaction to add to the CQ
//! @param pfnCallback  - pointer the callback function to be executed when
//!                       transaction is complete.
//!
//! This function copies data from the IOM FIFO into the array \e pui32Data.
//! This is how input data from SPI or I2C transactions may be retrieved.
//!
//!
//! @return HAL status of the operation.
//
//
//*****************************************************************************
uint32_t
am_hal_iom_CQAddTransaction(void *pHandle,
                            am_hal_iom_transfer_t *psTransaction,
                            am_hal_iom_callback_t pfnCallback,
                            void *pCallbackCtxt)
{
    am_hal_iom_state_t      *pIOMState = (am_hal_iom_state_t *)pHandle;
    am_hal_iom_txn_cmdlist_t   *pCQEntry;
    am_hal_cmdq_entry_t     *pCQBlock;
    uint32_t                index;

    //
    // Check to see if there is enough room in the CQ
    //
    if ((pIOMState->ui32NumPendTransactions == AM_HAL_IOM_MAX_PENDING_TRANSACTIONS) ||
        (am_hal_cmdq_alloc_block(pIOMState->pCmdQHdl, sizeof(am_hal_iom_txn_cmdlist_t) / 8, &pCQBlock, &index)))
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    pCQEntry = (am_hal_iom_txn_cmdlist_t *)pCQBlock;


    build_txn_cmdlist(pIOMState, pCQEntry, psTransaction);

    //
    // Will resume here after DMA completes.
    //

    //
    // Because we set AM_HAL_IOM_CQUPD_INT_FLAG, an interrupt will occur once
    // we reach this point in the Command Queue.  In the service routine, we'll
    // look for the appropriate callback.
    //
    // If ENDIDX has been reached, the CQ will pause here. Otherwise will
    // continue with the next CQ entry.
    //

    //
    // Store the callback function pointer.
    //
    pIOMState->pfnCallback[index & (AM_HAL_IOM_MAX_PENDING_TRANSACTIONS - 1)] = pfnCallback;
    pIOMState->pCallbackCtxt[index & (AM_HAL_IOM_MAX_PENDING_TRANSACTIONS - 1)] = pCallbackCtxt;

    return AM_HAL_STATUS_SUCCESS;
} // am_hal_iom_CQAddTransaction()

//*****************************************************************************
//
//! @brief Enable the Command Queue operation.
//!
//! @param handle       - handle for the interface.
//!
//! This function enables Command Queue operation.
//!
//!
//! @return HAL status of the operation.
//
//
//*****************************************************************************
uint32_t
am_hal_iom_CQEnable(void *pHandle)
{
    am_hal_iom_state_t  *pIOMState = (am_hal_iom_state_t *)pHandle;

    //
    // Enable the Command Queue operation
    //
    return am_hal_cmdq_enable(pIOMState->pCmdQHdl);

} // am_hal_iom_CQEnable()

//*****************************************************************************
//
//! @brief Disable the Command Queue operation.
//!
//! @param handle       - handle for the interface.
//!
//! This function disables the Command Queue operation.
//!
//!
//! @return HAL status of the operation.
//
//
//*****************************************************************************
uint32_t
am_hal_iom_CQDisable(void *pHandle)
{
    am_hal_iom_state_t  *pIOMState = (am_hal_iom_state_t *)pHandle;

    //
    // Disable the Command Queue operation
    //
    return am_hal_cmdq_disable(pIOMState->pCmdQHdl);
} // am_hal_iom_CQDisable()

#else   // AM_HAL_IOM_CQ != 1
static void
run_txn_cmdlist(void *pCQEntry, uint32_t numEntries)
{
    uint32_t ix;
    am_hal_cmdq_entry_t *pCmd = (am_hal_cmdq_entry_t *)pCQEntry;

    for ( ix = 0; ix < numEntries; ix++, pCmd++ )
    {
        *((uint32_t *)pCmd->address) = pCmd->value;
    }

} // run_txn_cmdlist()

//*****************************************************************************
//
//! @brief Adds a transaction the IOM Command Queue.
//!
//! @param handle       - handle for the interface.
//! @param pTransaction - transaction to add to the CQ
//! @param pfnCallback  - pointer the callback function to be executed when
//!                       transaction is complete.
//!
//! This function copies data from the IOM FIFO into the array \e pui32Data.
//! This is how input data from SPI or I2C transactions may be retrieved.
//!
//!
//! @return HAL status of the operation.
//
//
//*****************************************************************************
uint32_t
am_hal_iom_DmaAddTransaction(void *pHandle,
                             am_hal_iom_transfer_t *psTransaction,
                             am_hal_iom_callback_t pfnCallback,
                             void *pCallbackCtxt)
{
    am_hal_iom_state_t      *pIOMState = (am_hal_iom_state_t *)pHandle;
    am_hal_iom_txn_cmdlist_t   *pCQEntry;
    uint32_t                index = pIOMState->ui32NextIdx % pIOMState->ui32MaxTransactions;

    //
    // Check to see if there is enough room in the queue
    //
    if ( pIOMState->ui32NumPendTransactions == pIOMState->ui32MaxTransactions )
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    pCQEntry = &pIOMState->pTransactions[index];


    build_txn_cmdlist(pIOMState, pCQEntry, psTransaction);

    //
    // Store the callback function pointer.
    //
    pIOMState->pfnCallback[index] = pfnCallback;
    pIOMState->pCallbackCtxt[index] = pCallbackCtxt;
    pIOMState->ui32NextIdx++;

    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_DmaAddTransaction()
#endif  // AM_HAL_IOM_CQ == 1

//*****************************************************************************
//
// validate_transaction()
//
//*****************************************************************************
uint32_t
validate_transaction(am_hal_iom_state_t *pIOMState,
                     am_hal_iom_transfer_t *psTransaction,
                     bool bBlocking)
{
    uint32_t ui32Offset, ui32OffsetCnt, ui32Dir, ui32Bytes;

    if (!psTransaction)
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    ui32Offset = psTransaction->ui32Instr;
    ui32OffsetCnt = psTransaction->ui32InstrLen;
    ui32Dir = psTransaction->eDirection;
    ui32Bytes = psTransaction->ui32NumBytes;
    //
    // Validate parameters
    //
    if ( (ui32OffsetCnt > AM_HAL_IOM_MAX_OFFSETSIZE)                            ||
         (ui32Offset & (0xFFFFFFFF << (ui32OffsetCnt*8)))                       ||
         (ui32Bytes && (ui32Dir != AM_HAL_IOM_TX) && (psTransaction->pui32RxBuffer == NULL)) ||
         (ui32Bytes && (ui32Dir != AM_HAL_IOM_RX) && (psTransaction->pui32TxBuffer == NULL)) ||
         ((pIOMState->eInterfaceMode == AM_HAL_IOM_I2C_MODE) &&
          (psTransaction->ui32NumBytes > AM_HAL_IOM_MAX_TXNSIZE_I2C))           ||
         ((pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE) &&
          ((psTransaction->uPeerInfo.ui32SpiChipSelect > AM_HAL_IOM_MAX_CS_SPI) ||
           (psTransaction->ui32NumBytes > AM_HAL_IOM_MAX_TXNSIZE_SPI))) )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
    if (!bBlocking)
    {
#if (AM_HAL_IOM_CQ != 1)
        if (psTransaction->ui32PauseCondition != 0)
        {
            return AM_HAL_STATUS_INVALID_ARG;
        }
        if (psTransaction->ui32StatusSetClr != 0)
        {
            return AM_HAL_STATUS_INVALID_ARG;
        }
#endif
    }

    return AM_HAL_STATUS_SUCCESS;

} // validate_transaction()

//*****************************************************************************
//
// IOM uninitialize function
//
//*****************************************************************************
uint32_t
am_hal_iom_uninitialize(void *pHandle)
{
    uint32_t status = AM_HAL_STATUS_SUCCESS;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    if (pIOMState->prefix.s.bEnable)
    {
        am_hal_iom_disable(pHandle);
    }

    pIOMState->prefix.s.bInit = false;

    //
    // Return the status.
    //
    return status;

} // am_hal_iom_uninitialize()

//*****************************************************************************
//
// IOM initialization function
//
//*****************************************************************************
uint32_t
am_hal_iom_initialize(uint32_t ui32Module, void **ppHandle)
{
#ifndef AM_HAL_DISABLE_API_VALIDATION
    //
    // Validate the module number
    //
    if ( ui32Module >= AM_REG_IOM_NUM_MODULES )
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    if (ppHandle == NULL)
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

    if (g_IOMhandles[ui32Module].prefix.s.bInit)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    g_IOMhandles[ui32Module].prefix.s.bInit = true;
    g_IOMhandles[ui32Module].prefix.s.bEnable = false;
    g_IOMhandles[ui32Module].prefix.s.magic = AM_HAL_MAGIC_IOM;

    //
    // Initialize the handle.
    //
    g_IOMhandles[ui32Module].ui32Module = ui32Module;

    //
    // Return the handle.
    //
    *ppHandle = (void *)&g_IOMhandles[ui32Module];

    //
    // Return the status
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_initialize()

//*****************************************************************************
//
// IOM enable function
//
//*****************************************************************************
uint32_t
am_hal_iom_enable(void *pHandle)
{
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t status = AM_HAL_STATUS_SUCCESS;
#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    if (pIOMState->prefix.s.bEnable)
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#endif

    // Enable submodule
#if 1
    enable_submodule(pIOMState->ui32Module, ((pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE) ? 0 : 1));
#endif

#if MANUAL_POP
#if AM_CMSIS_REGS
    IOMn(pIOMState->ui32Module)->FIFOCTRL_b.POPWR = 1;
#else // AM_CMSIS_REGS
    AM_BFWn(IOM, pIOMState->ui32Module, FIFOCTRL, POPWR, 1);
#endif // AM_CMSIS_REGS
#endif

    //
    // If Enable the Command Queue
    //
    if ( pIOMState->pNBTxnBuf )
    {
        pIOMState->ui32NumPendTransactions = 0;
        pIOMState->ui32LastIdxProcessed = 0;
#if (AM_HAL_IOM_CQ == 1)
        status = am_hal_iom_CQInit(pIOMState,
                                   pIOMState->ui32NBTxnBufLength,
                                   pIOMState->pNBTxnBuf);
#else
        // Determine the maximum number of transactions based on the memory provided
        pIOMState->ui32MaxTransactions = pIOMState->ui32NBTxnBufLength * 4 / sizeof(am_hal_iom_txn_cmdlist_t);
        if (pIOMState->ui32MaxTransactions > 0)
        {
            if (pIOMState->ui32MaxTransactions > AM_HAL_IOM_MAX_PENDING_TRANSACTIONS)
            {
                pIOMState->ui32MaxTransactions = AM_HAL_IOM_MAX_PENDING_TRANSACTIONS;
            }
            pIOMState->ui32NextIdx = pIOMState->ui32LastIdxProcessed + 1;
            pIOMState->pTransactions = (am_hal_iom_txn_cmdlist_t *)pIOMState->pNBTxnBuf;
        }
#endif
        // Initialize the DMA Trigger Setting
        //
        // DMATRIG, set DTHREN and/or DCMDCMPEN.
        // Note - it is recommended that DTHREN always be set.
        //
#if AM_CMSIS_REGS
#if 1
        IOMn(pIOMState->ui32Module)->DMATRIGEN = _VAL2FLD(IOM0_DMATRIGEN_DTHREN, 1);
#endif
#else // AM_CMSIS_REGS
        AM_REGn(IOM, pIOMState->ui32Module, DMATRIGEN) = AM_REG_IOM_DMATRIGEN_DTHREN(1);
#endif // AM_CMSIS_REGS
    }

    if (status == AM_HAL_STATUS_SUCCESS)
    {
        pIOMState->prefix.s.bEnable = true;
    }

    //
    // We're done, return the status.
    //
    return status;

} // am_hal_iom_enable()

//*****************************************************************************
//
// IOM disable function
//
//*****************************************************************************
uint32_t
am_hal_iom_disable(void *pHandle)
{
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    if (!pIOMState->prefix.s.bEnable)
    {
        return AM_HAL_STATUS_SUCCESS;
    }

    //
    // Disable the submodules
    //
#if AM_CMSIS_REGS
    IOMn(pIOMState->ui32Module)->SUBMODCTRL_b.SMOD0EN = 0;
    IOMn(pIOMState->ui32Module)->SUBMODCTRL_b.SMOD1EN = 0;
#else // AM_CMSIS_REGS
    AM_BFWn(IOM, pIOMState->ui32Module, SUBMODCTRL, SMOD0EN, 0);
    AM_BFWn(IOM, pIOMState->ui32Module, SUBMODCTRL, SMOD1EN, 0);
#endif // AM_CMSIS_REGS

#if (AM_HAL_IOM_CQ == 1)
    am_hal_IOM_CQReset(pHandle);
#endif

    pIOMState->prefix.s.bEnable = false;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_disable()

//*****************************************************************************
//
// IOM get status function
//
//*****************************************************************************
uint32_t
am_hal_iom_status_get(void *pHandle, am_hal_iom_status_t *psStatus)
{
    uint32_t ui32Module, ui32IomStat;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
    if (!psStatus)
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#endif

    ui32Module = pIOMState->ui32Module;

    //
    // Begin critical section while we gather status information.
    //
#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN

    ui32IomStat = IOMn(ui32Module)->STATUS;
    psStatus->bStatIdle   = _FLD2VAL(IOM0_STATUS_IDLEST, ui32IomStat);
    psStatus->bStatErr    = _FLD2VAL(IOM0_STATUS_ERR,    ui32IomStat);
    psStatus->bStatCmdAct = _FLD2VAL(IOM0_STATUS_CMDACT, ui32IomStat);


    //
    // Return all the bitfields of DMASTAT.
    //
    psStatus->ui32DmaStat = IOMn(ui32Module)->DMASTAT;

    psStatus->ui32MaxTransactions = pIOMState->ui32MaxTransactions;
    psStatus->ui32NumPendTransactions = pIOMState->ui32NumPendTransactions;

    //
    // End the critical section.
    //
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    uint32_t ui32Critical = 0;
    //
    // Start a critical section.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    ui32IomStat = AM_REGn(IOM, ui32Module, STATUS);
    psStatus->bStatIdle   = AM_READ_SM(AM_REG_IOM_STATUS_IDLEST, ui32IomStat);
    psStatus->bStatErr    = AM_READ_SM(AM_REG_IOM_STATUS_ERR,    ui32IomStat);
    psStatus->bStatCmdAct = AM_READ_SM(AM_REG_IOM_STATUS_CMDACT, ui32IomStat);


    //
    // Return all the bitfields of DMASTAT.
    //
    psStatus->ui32DmaStat = AM_REGn(IOM, ui32Module, DMASTAT);

    psStatus->ui32MaxTransactions = pIOMState->ui32MaxTransactions;
    psStatus->ui32NumPendTransactions = pIOMState->ui32NumPendTransactions;

    //
    // End the critical section.
    //
    am_hal_interrupt_master_set(ui32Critical);
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_status_get()

//*****************************************************************************
//
// IOM enable interrupts function
//
//*****************************************************************************
uint32_t
am_hal_iom_interrupt_enable(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    ui32Module = ((am_hal_iom_state_t*)pHandle)->ui32Module;

    //
    // Set the interrupt enables according to the mask.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->INTEN |= ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, INTEN) |= ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_interrupt_enable()

//*****************************************************************************
//
// IOM disable interrupts function
//
//*****************************************************************************
uint32_t
am_hal_iom_interrupt_disable(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    ui32Module = ((am_hal_iom_state_t*)pHandle)->ui32Module;

    //
    // Clear the interrupt enables according to the mask.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->INTEN &= ~ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, INTEN) &= ~ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_interrupt_disable()

//*****************************************************************************
//
// IOM get interrupt status
//
//*****************************************************************************
uint32_t
am_hal_iom_interrupt_status_get(void *pHandle, bool bEnabledOnly,
                                uint32_t *pui32IntStatus)
{
    uint32_t ui32IntStatus;
    uint32_t ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if ( !AM_HAL_IOM_CHK_HANDLE(pHandle) )
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    if ( !pui32IntStatus )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#endif

    ui32Module = ((am_hal_iom_state_t*)pHandle)->ui32Module;

#if AM_CMSIS_REGS
    ui32IntStatus = IOMn(ui32Module)->INTSTAT;

    if ( bEnabledOnly )
    {
        ui32IntStatus &= IOMn(ui32Module)->INTEN;
    }
#else // AM_CMSIS_REGS
    ui32IntStatus = AM_REGn(IOM, ui32Module, INTSTAT);

    if ( bEnabledOnly )
    {
        ui32IntStatus &= AM_REGn(IOM, ui32Module, INTEN);
    }
#endif // AM_CMSIS_REGS

    *pui32IntStatus = ui32IntStatus;

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_interrupt_status_get()

//*****************************************************************************
//
// IOM interrupt clear
//
//*****************************************************************************
uint32_t
am_hal_iom_interrupt_clear(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif
    ui32Module = ((am_hal_iom_state_t*)pHandle)->ui32Module;

    //
    // Clear the requested interrupts.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->INTCLR = ui32IntMask;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, INTCLR) = ui32IntMask;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_interrupt_clear()

//*****************************************************************************
//
// IOM interrupt service routine
//
//*****************************************************************************
uint32_t am_hal_iom_interrupt_service(void *pHandle, uint32_t ui32IntMask)
{
    uint32_t ui32Module;
    uint32_t ui32Status = AM_HAL_STATUS_SUCCESS;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t index;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    ui32Module = pIOMState->ui32Module;

    if (pIOMState->ui32NumPendTransactions)
    {
#if (AM_HAL_IOM_CQ == 1)
        am_hal_cmdq_status_t status;

        //
        // Get the current and last indexes.
        //
        if (pIOMState->pCmdQHdl && ((ui32Status = am_hal_cmdq_get_status(pIOMState->pCmdQHdl, &status)) == AM_HAL_STATUS_SUCCESS))
        {
            //
            // Figure out which callbacks need to be handled.
            //
            while (pIOMState->ui32LastIdxProcessed != status.lastIdxProcessed)
            {
                pIOMState->ui32LastIdxProcessed++;
                pIOMState->ui32NumPendTransactions--;
                index = pIOMState->ui32LastIdxProcessed & (AM_HAL_IOM_MAX_PENDING_TRANSACTIONS - 1);
                if ( pIOMState->pfnCallback[index] != NULL )
                {
                    pIOMState->pfnCallback[index](pIOMState->pCallbackCtxt[index], AM_HAL_STATUS_SUCCESS);
                    pIOMState->pfnCallback[index] = NULL;
                }
            }

            //
            // Check the CQError - If set it indicates that the current transaction encountered an error
            //
            if (ui32IntMask & AM_HAL_IOM_INT_ERR)
            {
                // Need to determine the error, call the callback with proper status
                pIOMState->ui32LastIdxProcessed++;
                pIOMState->ui32NumPendTransactions--;
                index = pIOMState->ui32LastIdxProcessed & (AM_HAL_IOM_MAX_PENDING_TRANSACTIONS - 1);
                if ( pIOMState->pfnCallback[index] != NULL )
                {
                    pIOMState->pfnCallback[index](pIOMState->pCallbackCtxt[index], internal_iom_get_int_err(ui32Module, ui32IntMask));
                    pIOMState->pfnCallback[index] = NULL;
                }

#if AM_CMSIS_REGS
                //
                // Do Error recovery
                // Disable CQ
                //
                IOMn(ui32Module)->CQCFG_b.CQEN = 0;

                //
                // Disable DMA
                //
                IOMn(ui32Module)->DMACFG_b.DMAEN = 0;

                //
                // Clear DMAERR in DMASTAT
                //
                IOMn(ui32Module)->DMASTAT = 0;

                //
                // Reset Submodule & FIFO
                //
                internal_iom_reset_on_error(pIOMState, ui32IntMask & AM_HAL_IOM_INT_ERR);

                //
                // Resume the command queue
                //
                am_hal_cmdq_error_resume(pIOMState->pCmdQHdl);
#else // AM_CMSIS_REGS
                // Do Error recovery
                // Disable CQ
                AM_BFWn(IOM, ui32Module, CQCFG, CQEN, 0);
                // Disable DMA
                AM_BFWn(IOM, ui32Module, DMACFG, DMAEN, 0);
                // Clear DMAERR in DMASTAT
                AM_REGn(IOM, ui32Module, DMASTAT) = 0;
                // Reset Submodule & FIFO
                internal_iom_reset_on_error(pIOMState, ui32IntMask & AM_HAL_IOM_INT_ERR);
                // Resume the command queue
                am_hal_cmdq_error_resume(pIOMState->pCmdQHdl);
#endif // AM_CMSIS_REGS
            }

            if (pIOMState->ui32NumPendTransactions == 0)
            {
                //
                // Disable the Command Queue
                //
                am_hal_iom_CQDisable(pHandle);
            }
        }
#else // !AM_HAL_IOM_CQ
        //
        // Accumulate the INTSTAT for this transaction
        //
        pIOMState->ui32TxnInt |= ui32IntMask;

        //
        // Check for the command completion
        //
        if (pIOMState->ui32TxnInt & (AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_DERR))
        {
            //
            // We need to wait for the DMA complete as well
            // Special case for 0 length DMA - by checking the DMAEN register
            //
#if AM_CMSIS_REGS
            if ((IOMn(ui32Module)->DMACFG_b.DMAEN == 0) || (pIOMState->ui32TxnInt & (AM_HAL_IOM_INT_DCMP | AM_HAL_IOM_INT_ERR)))
            {
                // Call the callback
                // Need to determine the error, call the callback with proper status
                pIOMState->ui32LastIdxProcessed++;
                pIOMState->ui32NumPendTransactions--;
                index = pIOMState->ui32LastIdxProcessed % pIOMState->ui32MaxTransactions;
                if ( pIOMState->pfnCallback[index] != NULL )
                {
                    pIOMState->pfnCallback[index](pIOMState->pCallbackCtxt[index], internal_iom_get_int_err(ui32Module, pIOMState->ui32TxnInt));
                    pIOMState->pfnCallback[index] = NULL;
                }

                if (pIOMState->ui32TxnInt & AM_HAL_IOM_INT_ERR)
                {
                    //
                    // Do Error recovery
                    // Disable DMA
                    //
                    IOMn(ui32Module)->DMACFG_b.DMAEN = 0;

                    //
                    // Clear DMAERR in DMASTAT
                    //
                    IOMn(ui32Module)->DMASTAT = 0;

                    //
                    // Reset Submodule & FIFO
                    //
                    internal_iom_reset_on_error(pIOMState, pIOMState->ui32TxnInt & AM_HAL_IOM_INT_ERR);
                }
                //
                // Post next transaction if queue is not empty
                //
                if (pIOMState->ui32NumPendTransactions)
                {
                    index = (pIOMState->ui32LastIdxProcessed + 1) % pIOMState->ui32MaxTransactions;

                    //
                    // Initialize the DMA state machine (clear the DMACPL flag).
                    //
                    IOMn(ui32Module)->DMASTAT = 0;
                    //AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
                    pIOMState->ui32TxnInt = 0;
                    run_txn_cmdlist(&pIOMState->pTransactions[index], sizeof(am_hal_iom_txn_cmdlist_t) / sizeof(am_hal_cmdq_entry_t));
                }
            }
#else // AM_CMSIS_REGS
            if ((AM_BFRn(IOM, ui32Module, DMACFG, DMAEN) == 0) || (pIOMState->ui32TxnInt & (AM_HAL_IOM_INT_DCMP | AM_HAL_IOM_INT_ERR)))
            {
                // Call the callback
                // Need to determine the error, call the callback with proper status
                pIOMState->ui32LastIdxProcessed++;
                pIOMState->ui32NumPendTransactions--;
                index = pIOMState->ui32LastIdxProcessed % pIOMState->ui32MaxTransactions;
                if ( pIOMState->pfnCallback[index] != NULL )
                {
                    pIOMState->pfnCallback[index](pIOMState->pCallbackCtxt[index], internal_iom_get_int_err(ui32Module, pIOMState->ui32TxnInt));
                    pIOMState->pfnCallback[index] = NULL;
                }

                if (pIOMState->ui32TxnInt & AM_HAL_IOM_INT_ERR)
                {
                    // Do Error recovery
                    // Disable DMA
                    AM_BFWn(IOM, ui32Module, DMACFG, DMAEN, 0);
                    // Clear DMAERR in DMASTAT
                    AM_REGn(IOM, ui32Module, DMASTAT) = 0;
                    // Reset Submodule & FIFO
                    internal_iom_reset_on_error(pIOMState, pIOMState->ui32TxnInt & AM_HAL_IOM_INT_ERR);
                }
                //
                // Post next transaction if queue is not empty
                //
                if (pIOMState->ui32NumPendTransactions)
                {
                    index = (pIOMState->ui32LastIdxProcessed + 1) % pIOMState->ui32MaxTransactions;

                    //
                    // Initialize the DMA state machine (clear the DMACPL flag).
                    //
                    AM_REGn(IOM, ui32Module, DMASTAT) = 0;
                    //AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
                    pIOMState->ui32TxnInt = 0;
                    run_txn_cmdlist(&pIOMState->pTransactions[index], sizeof(am_hal_iom_txn_cmdlist_t) / sizeof(am_hal_cmdq_entry_t));
                }
            }
#endif // AM_CMSIS_REGS
        }
#endif // !AM_HAL_IOM_CQ

        if (pIOMState->ui32NumPendTransactions == 0)
        {
#if AM_CMSIS_REGS
            //
            // Disable DMA
            //
            IOMn(ui32Module)->DMACFG_b.DMAEN = 0;

            //
            // Clear interrupts
            // Restore IOM interrupts.
            //
            IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;
            IOMn(ui32Module)->INTEN  = pIOMState->ui32UserIntCfg;
#else // AM_CMSIS_REGS
            // Disable DMA
            AM_BFWn(IOM, ui32Module, DMACFG, DMAEN, 0);
            // Clear interrupts
            // Restore IOM interrupts.
            //
            AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
            AM_REGn(IOM, ui32Module, INTEN) = pIOMState->ui32UserIntCfg;
#endif // AM_CMSIS_REGS
        }
    }

    //
    // Return the status.
    //
    return ui32Status;

} // am_hal_iom_interrupt_service()

//*****************************************************************************
//
// IOM power control function
//
//*****************************************************************************
uint32_t
am_hal_iom_power_ctrl(void *pHandle,
                      am_hal_sysctrl_power_state_e ePowerState,
                      bool bRetainState)
{
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }
#endif

    //
    // Decode the requested power state and update IOM operation accordingly.
    //
    switch (ePowerState)
    {
        case AM_HAL_SYSCTRL_WAKE:
            if (bRetainState && !pIOMState->registerState.bValid)
            {
                return AM_HAL_STATUS_INVALID_OPERATION;
            }

            //
            // Enable power control.
            //
            am_hal_pwrctrl_periph_enable((am_hal_pwrctrl_periph_e)(AM_HAL_PWRCTRL_PERIPH_IOM0 + pIOMState->ui32Module));

            if (bRetainState)
            {
                //
                // Restore IOM registers
#if AM_CMSIS_REGS
                IOMn(pIOMState->ui32Module)->FIFOTHR    = pIOMState->registerState.regFIFOTHR;
                IOMn(pIOMState->ui32Module)->CLKCFG     = pIOMState->registerState.regCLKCFG;
                IOMn(pIOMState->ui32Module)->SUBMODCTRL = pIOMState->registerState.regSUBMODCTRL;
                IOMn(pIOMState->ui32Module)->CQADDR     = pIOMState->registerState.regCQADDR;
                IOMn(pIOMState->ui32Module)->CQFLAGS    = pIOMState->registerState.regCQFLAGS;
                IOMn(pIOMState->ui32Module)->CQPAUSEEN  = pIOMState->registerState.regCQPAUSEEN;
                IOMn(pIOMState->ui32Module)->CQCURIDX   = pIOMState->registerState.regCQCURIDX;
                IOMn(pIOMState->ui32Module)->CQENDIDX   = pIOMState->registerState.regCQENDIDX;
                IOMn(pIOMState->ui32Module)->MSPICFG    = pIOMState->registerState.regMSPICFG;
                IOMn(pIOMState->ui32Module)->MI2CCFG    = pIOMState->registerState.regMI2CCFG;
                IOMn(pIOMState->ui32Module)->INTEN      = pIOMState->registerState.regINTEN;
                IOMn(pIOMState->ui32Module)->DMATRIGEN  = pIOMState->registerState.regDMATRIGEN;

                //
                // Set CQCFG last
                //
                IOMn(pIOMState->ui32Module)->CQCFG      = pIOMState->registerState.regCQCFG;
#else // AM_CMSIS_REGS
                AM_REGn(IOM, pIOMState->ui32Module, FIFOTHR) = pIOMState->registerState.regFIFOTHR;
                AM_REGn(IOM, pIOMState->ui32Module, CLKCFG) = pIOMState->registerState.regCLKCFG;
                AM_REGn(IOM, pIOMState->ui32Module, SUBMODCTRL) = pIOMState->registerState.regSUBMODCTRL;
                AM_REGn(IOM, pIOMState->ui32Module, CQADDR) = pIOMState->registerState.regCQADDR;
                AM_REGn(IOM, pIOMState->ui32Module, CQFLAGS) = pIOMState->registerState.regCQFLAGS;
                AM_REGn(IOM, pIOMState->ui32Module, CQPAUSEEN) = pIOMState->registerState.regCQPAUSEEN;
                AM_REGn(IOM, pIOMState->ui32Module, CQCURIDX) = pIOMState->registerState.regCQCURIDX;
                AM_REGn(IOM, pIOMState->ui32Module, CQENDIDX) = pIOMState->registerState.regCQENDIDX;
                AM_REGn(IOM, pIOMState->ui32Module, MSPICFG) = pIOMState->registerState.regMSPICFG;
                AM_REGn(IOM, pIOMState->ui32Module, MI2CCFG) = pIOMState->registerState.regMI2CCFG;
                AM_REGn(IOM, pIOMState->ui32Module, INTEN) = pIOMState->registerState.regINTEN;
                AM_REGn(IOM, pIOMState->ui32Module, DMATRIGEN) = pIOMState->registerState.regDMATRIGEN;
                // Set CQCFG last
                AM_REGn(IOM, pIOMState->ui32Module, CQCFG) = pIOMState->registerState.regCQCFG;
#endif // AM_CMSIS_REGS
                pIOMState->registerState.bValid = false;
            }
            break;

        case AM_HAL_SYSCTRL_NORMALSLEEP:
        case AM_HAL_SYSCTRL_DEEPSLEEP:
            // Make sure IOM is not active currently
#if AM_CMSIS_REGS
            if (((IOMn(pIOMState->ui32Module)->STATUS & (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk)) != IOM0_STATUS_IDLEST_Msk) ||
                pIOMState->ui32NumPendTransactions)
            {
                return AM_HAL_STATUS_IN_USE;
            }
            if (bRetainState)
            {
                // Save IOM Registers
                pIOMState->registerState.regFIFOTHR    = IOMn(pIOMState->ui32Module)->FIFOTHR;
                pIOMState->registerState.regCLKCFG     = IOMn(pIOMState->ui32Module)->CLKCFG;
                pIOMState->registerState.regSUBMODCTRL = IOMn(pIOMState->ui32Module)->SUBMODCTRL;
                pIOMState->registerState.regCQCFG      = IOMn(pIOMState->ui32Module)->CQCFG;
                pIOMState->registerState.regCQADDR     = IOMn(pIOMState->ui32Module)->CQADDR;
                pIOMState->registerState.regCQFLAGS    = IOMn(pIOMState->ui32Module)->CQFLAGS;
                pIOMState->registerState.regCQPAUSEEN  = IOMn(pIOMState->ui32Module)->CQPAUSEEN;
                pIOMState->registerState.regCQCURIDX   = IOMn(pIOMState->ui32Module)->CQCURIDX;
                pIOMState->registerState.regCQENDIDX   = IOMn(pIOMState->ui32Module)->CQENDIDX;
                pIOMState->registerState.regMSPICFG    = IOMn(pIOMState->ui32Module)->MSPICFG;
                pIOMState->registerState.regMI2CCFG    = IOMn(pIOMState->ui32Module)->MI2CCFG;
                pIOMState->registerState.regINTEN      = IOMn(pIOMState->ui32Module)->INTEN;
                pIOMState->registerState.regDMATRIGEN  = IOMn(pIOMState->ui32Module)->DMATRIGEN;
#else // AM_CMSIS_REGS
            if (((AM_REGn(IOM, pIOMState->ui32Module, STATUS) & (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M)) != AM_REG_IOM_STATUS_IDLEST_M) ||
                pIOMState->ui32NumPendTransactions)
            {
                return AM_HAL_STATUS_IN_USE;
            }
            if (bRetainState)
            {
                // Save IOM Registers
                pIOMState->registerState.regFIFOTHR = AM_REGn(IOM, pIOMState->ui32Module, FIFOTHR);
                pIOMState->registerState.regCLKCFG = AM_REGn(IOM, pIOMState->ui32Module, CLKCFG);
                pIOMState->registerState.regSUBMODCTRL = AM_REGn(IOM, pIOMState->ui32Module, SUBMODCTRL);
                pIOMState->registerState.regCQCFG = AM_REGn(IOM, pIOMState->ui32Module, CQCFG);
                pIOMState->registerState.regCQADDR = AM_REGn(IOM, pIOMState->ui32Module, CQADDR);
                pIOMState->registerState.regCQFLAGS = AM_REGn(IOM, pIOMState->ui32Module, CQFLAGS);
                pIOMState->registerState.regCQPAUSEEN = AM_REGn(IOM, pIOMState->ui32Module, CQPAUSEEN);
                pIOMState->registerState.regCQCURIDX = AM_REGn(IOM, pIOMState->ui32Module, CQCURIDX);
                pIOMState->registerState.regCQENDIDX = AM_REGn(IOM, pIOMState->ui32Module, CQENDIDX);
                pIOMState->registerState.regMSPICFG = AM_REGn(IOM, pIOMState->ui32Module, MSPICFG);
                pIOMState->registerState.regMI2CCFG = AM_REGn(IOM, pIOMState->ui32Module, MI2CCFG);
                pIOMState->registerState.regINTEN = AM_REGn(IOM, pIOMState->ui32Module, INTEN);
                pIOMState->registerState.regDMATRIGEN = AM_REGn(IOM, pIOMState->ui32Module, DMATRIGEN);
#endif // AM_CMSIS_REGS
                pIOMState->registerState.bValid = true;
            }

            //
            // Disable power control.
            //
            am_hal_pwrctrl_periph_disable((am_hal_pwrctrl_periph_e)(AM_HAL_PWRCTRL_PERIPH_IOM0 + pIOMState->ui32Module));
            break;

        default:
            return AM_HAL_STATUS_INVALID_ARG;
    }

    //
    // Return the status.
    //
    return AM_HAL_STATUS_SUCCESS;

} // am_hal_iom_power_ctrl()

//*****************************************************************************
//
// IOM configuration function.
//
//*****************************************************************************
uint32_t
am_hal_iom_configure(void *pHandle, am_hal_iom_config_t *psConfig)
{
    uint32_t ui32ClkCfg;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t status = AM_HAL_STATUS_SUCCESS;
    uint32_t ui32Module;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Validate the parameters
    //
    if ( (pHandle == NULL)      ||
         (psConfig == NULL)     ||
         (pIOMState->ui32Module >= AM_REG_IOM_NUM_MODULES) )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
    // Configure not allowed in Enabled state
    if (pIOMState->prefix.s.bEnable)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    ui32Module = pIOMState->ui32Module;
    //
    // Save the interface mode and chip select in the global handle.
    //
    pIOMState->eInterfaceMode = psConfig->eInterfaceMode;

    //
    // Set the IOM read/write FIFO thresholds to default values.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->FIFOTHR =
        _VAL2FLD(IOM0_FIFOTHR_FIFORTHR, 16) |
        _VAL2FLD(IOM0_FIFOTHR_FIFOWTHR, 16);
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, FIFOTHR) =
                AM_BFV(IOM, FIFOTHR, FIFORTHR, 16)   |
                AM_BFV(IOM, FIFOTHR, FIFOWTHR, 16);
#endif // AM_CMSIS_REGS

    if ( psConfig->eInterfaceMode == AM_HAL_IOM_SPI_MODE )
    {
#ifndef AM_HAL_DISABLE_API_VALIDATION
        //
        // Validate the SPI mode
        //
        if ( psConfig->eSpiMode > AM_HAL_IOM_SPI_MODE_3 )
        {
            return AM_HAL_STATUS_INVALID_ARG;
        }
#endif

        //
        // Determine the CLKCFG value for SPI.
        //
        ui32ClkCfg = iom_get_interface_clock_cfg(psConfig->ui32ClockFreq, (psConfig->eSpiMode & 2) >> 1);

        //
        // Set the SPI configuration.
        //
#if AM_CMSIS_REGS
        IOMn(ui32Module)->MSPICFG =
            ( ((psConfig->eSpiMode << IOM0_MSPICFG_SPOL_Pos) & (IOM0_MSPICFG_SPHA_Msk | IOM0_MSPICFG_SPOL_Msk))  |
             _VAL2FLD(IOM0_MSPICFG_FULLDUP, 0)                              |
             _VAL2FLD(IOM0_MSPICFG_WTFC,    IOM0_MSPICFG_WTFC_DIS)          |
             _VAL2FLD(IOM0_MSPICFG_RDFC,    IOM0_MSPICFG_RDFC_DIS)          |
             _VAL2FLD(IOM0_MSPICFG_MOSIINV, IOM0_MSPICFG_MOSIINV_NORMAL)    |
             _VAL2FLD(IOM0_MSPICFG_WTFCIRQ, IOM0_MSPICFG_WTFCIRQ_MISO)      |
             _VAL2FLD(IOM0_MSPICFG_WTFCPOL, IOM0_MSPICFG_WTFCPOL_HIGH)      |
             _VAL2FLD(IOM0_MSPICFG_RDFCPOL, IOM0_MSPICFG_RDFCPOL_HIGH)      |
             _VAL2FLD(IOM0_MSPICFG_SPILSB,  IOM0_MSPICFG_SPILSB_MSB)        |
             _VAL2FLD(IOM0_MSPICFG_DINDLY,  0)                              |
             _VAL2FLD(IOM0_MSPICFG_DOUTDLY, 0)                              |
             _VAL2FLD(IOM0_MSPICFG_MSPIRST, 0) );
#else // AM_CMSIS_REGS
        AM_REGn(IOM, ui32Module, MSPICFG) =
                ( ((psConfig->eSpiMode << AM_REG_IOM_MSPICFG_SPOL_S) & (AM_REG_IOM_MSPICFG_SPHA_M | AM_REG_IOM_MSPICFG_SPOL_M))  |
                 AM_REG_IOM_MSPICFG_FULLDUP(0)                      |
                 AM_REG_IOM_MSPICFG_WTFC_DIS                        |
                 AM_REG_IOM_MSPICFG_RDFC_DIS                        |
                 AM_REG_IOM_MSPICFG_MOSIINV_NORMAL                  |
                 AM_REG_IOM_MSPICFG_WTFCIRQ_MISO                    |
                 AM_REG_IOM_MSPICFG_WTFCPOL_HIGH                    |
                 AM_REG_IOM_MSPICFG_RDFCPOL_HIGH                    |
                 AM_REG_IOM_MSPICFG_SPILSB_MSB                      |
                 AM_REG_IOM_MSPICFG_DINDLY(0)                       |
                 AM_REG_IOM_MSPICFG_DOUTDLY(0)                      |
                 AM_REG_IOM_MSPICFG_MSPIRST(0) );
#endif // AM_CMSIS_REGS
    }
    else if ( psConfig->eInterfaceMode == AM_HAL_IOM_I2C_MODE )
    {

        switch (psConfig->ui32ClockFreq)
        {
            case AM_HAL_IOM_100KHZ:
                //
                // settings below should give ~100 kHz
                //
#if AM_CMSIS_REGS
                ui32ClkCfg = _VAL2FLD(IOM0_CLKCFG_TOTPER, 0x77)                     |
                             _VAL2FLD(IOM0_CLKCFG_LOWPER, 0x3B)                     |
                             _VAL2FLD(IOM0_CLKCFG_DIVEN, IOM0_CLKCFG_DIVEN_EN)      |
                             _VAL2FLD(IOM0_CLKCFG_DIV3, IOM0_CLKCFG_DIV3_DIS)       |
                             _VAL2FLD(IOM0_CLKCFG_FSEL, IOM0_CLKCFG_FSEL_HFRC_DIV2) |
                             _VAL2FLD(IOM0_CLKCFG_IOCLKEN, 1);
                IOMn(ui32Module)->MI2CCFG = _VAL2FLD(IOM0_MI2CCFG_STRDIS, 0)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_SMPCNT, 3)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_SDAENDLY, 15)                         |
                                            _VAL2FLD(IOM0_MI2CCFG_SCLENDLY, 0)                          |
                                            _VAL2FLD(IOM0_MI2CCFG_MI2CRST, 1)                           |
                                            _VAL2FLD(IOM0_MI2CCFG_SDADLY, 3)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_ARBEN, IOM0_MI2CCFG_ARBEN_ARBDIS)     |
                                            _VAL2FLD(IOM0_MI2CCFG_I2CLSB, IOM0_MI2CCFG_I2CLSB_MSBFIRST) |
                                            _VAL2FLD(IOM0_MI2CCFG_ADDRSZ, IOM0_MI2CCFG_ADDRSZ_ADDRSZ7);
#else // !AM_CMSIS_REGS
                ui32ClkCfg = AM_REG_IOM_CLKCFG_TOTPER(0x77)                     |
                             AM_REG_IOM_CLKCFG_LOWPER(0x3B)                     |
                             AM_REG_IOM_CLKCFG_DIVEN_EN                         |
                             AM_REG_IOM_CLKCFG_DIV3_DIS                         |
                             AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV2                   |
                             AM_REG_IOM_CLKCFG_IOCLKEN(1);
                AM_REGn(IOM, ui32Module, MI2CCFG) = AM_REG_IOM_MI2CCFG_STRDIS(0)                            |
                                                    AM_REG_IOM_MI2CCFG_SMPCNT(3)                            |
                                                    AM_REG_IOM_MI2CCFG_SDAENDLY(0xF)                        |
                                                    AM_REG_IOM_MI2CCFG_SCLENDLY(0)                          |
                                                    AM_REG_IOM_MI2CCFG_MI2CRST(1)                           |
                                                    AM_REG_IOM_MI2CCFG_SDADLY(3)                            |
                                                    AM_REG_IOM_MI2CCFG_ARBEN_ARBDIS                         |
                                                    AM_REG_IOM_MI2CCFG_I2CLSB_MSBFIRST                      |
                                                    AM_REG_IOM_MI2CCFG_ADDRSZ_ADDRSZ7;

//                ui32ClkCfg = 0x773B1201;
//                AM_REGn(IOM, ui32Module, MI2CCFG) = 0x0003F070;
#endif // AM_CMSIS_REGS
                break;
            case AM_HAL_IOM_400KHZ:
                //
                // settings below should give ~400 kHz
                //
#if AM_CMSIS_REGS
                ui32ClkCfg = _VAL2FLD(IOM0_CLKCFG_TOTPER, 0x1D)                     |
                             _VAL2FLD(IOM0_CLKCFG_LOWPER, 0x0E)                     |
                             _VAL2FLD(IOM0_CLKCFG_DIVEN, IOM0_CLKCFG_DIVEN_EN)      |
                             _VAL2FLD(IOM0_CLKCFG_DIV3, IOM0_CLKCFG_DIV3_DIS)       |
                             _VAL2FLD(IOM0_CLKCFG_FSEL, IOM0_CLKCFG_FSEL_HFRC_DIV2) |
                             _VAL2FLD(IOM0_CLKCFG_IOCLKEN, 1);
                IOMn(ui32Module)->MI2CCFG = _VAL2FLD(IOM0_MI2CCFG_STRDIS, 0)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_SMPCNT, 3)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_SDAENDLY, 15)                         |
                                            _VAL2FLD(IOM0_MI2CCFG_SCLENDLY, 2)                          |
                                            _VAL2FLD(IOM0_MI2CCFG_MI2CRST, 1)                           |
                                            _VAL2FLD(IOM0_MI2CCFG_SDADLY, 3)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_ARBEN, IOM0_MI2CCFG_ARBEN_ARBDIS)     |
                                            _VAL2FLD(IOM0_MI2CCFG_I2CLSB, IOM0_MI2CCFG_I2CLSB_MSBFIRST) |
                                            _VAL2FLD(IOM0_MI2CCFG_ADDRSZ, IOM0_MI2CCFG_ADDRSZ_ADDRSZ7);
#else // !AM_CMSIS_REGS
                ui32ClkCfg = AM_REG_IOM_CLKCFG_TOTPER(0x1D)                     |
                             AM_REG_IOM_CLKCFG_LOWPER(0x0E)                     |
                             AM_REG_IOM_CLKCFG_DIVEN_EN                         |
                             AM_REG_IOM_CLKCFG_DIV3_DIS                         |
                             AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV2                   |
                             AM_REG_IOM_CLKCFG_IOCLKEN(1);
                AM_REGn(IOM, ui32Module, MI2CCFG) = AM_REG_IOM_MI2CCFG_STRDIS(0)                            |
                                                    AM_REG_IOM_MI2CCFG_SMPCNT(3)                            |
                                                    AM_REG_IOM_MI2CCFG_SDAENDLY(0xF)                        |
                                                    AM_REG_IOM_MI2CCFG_SCLENDLY(2)                          |
                                                    AM_REG_IOM_MI2CCFG_MI2CRST(1)                           |
                                                    AM_REG_IOM_MI2CCFG_SDADLY(3)                            |
                                                    AM_REG_IOM_MI2CCFG_ARBEN_ARBDIS                         |
                                                    AM_REG_IOM_MI2CCFG_I2CLSB_MSBFIRST                      |
                                                    AM_REG_IOM_MI2CCFG_ADDRSZ_ADDRSZ7;

//                ui32ClkCfg = 0x1D0E1201;
//                AM_REGn(IOM, ui32Module, MI2CCFG) = 0x0003F270;
#endif // AM_CMSIS_REGS
                break;
            case AM_HAL_IOM_1MHZ:
                //
                // settings below should give ~860 kHz
                //
#if AM_CMSIS_REGS
                ui32ClkCfg = _VAL2FLD(IOM0_CLKCFG_TOTPER, 0x06)                     |
                             _VAL2FLD(IOM0_CLKCFG_LOWPER, 0x03)                     |
                             _VAL2FLD(IOM0_CLKCFG_DIVEN, IOM0_CLKCFG_DIVEN_EN)      |
                             _VAL2FLD(IOM0_CLKCFG_DIV3, IOM0_CLKCFG_DIV3_DIS)       |
                             _VAL2FLD(IOM0_CLKCFG_FSEL, IOM0_CLKCFG_FSEL_HFRC_DIV4) |
                             _VAL2FLD(IOM0_CLKCFG_IOCLKEN, 1);
                IOMn(ui32Module)->MI2CCFG = _VAL2FLD(IOM0_MI2CCFG_STRDIS, 0)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_SMPCNT, 0x21)                         |
                                            _VAL2FLD(IOM0_MI2CCFG_SDAENDLY, 3)                          |
                                            _VAL2FLD(IOM0_MI2CCFG_SCLENDLY, 0)                          |
                                            _VAL2FLD(IOM0_MI2CCFG_MI2CRST, 1)                           |
                                            _VAL2FLD(IOM0_MI2CCFG_SDADLY, 0)                            |
                                            _VAL2FLD(IOM0_MI2CCFG_ARBEN, IOM0_MI2CCFG_ARBEN_ARBDIS)     |
                                            _VAL2FLD(IOM0_MI2CCFG_I2CLSB, IOM0_MI2CCFG_I2CLSB_MSBFIRST) |
                                            _VAL2FLD(IOM0_MI2CCFG_ADDRSZ, IOM0_MI2CCFG_ADDRSZ_ADDRSZ7);
#else // AM_CMSIS_REGS
                ui32ClkCfg = AM_REG_IOM_CLKCFG_TOTPER(0x06)                     |
                             AM_REG_IOM_CLKCFG_LOWPER(0x03)                     |
                             AM_REG_IOM_CLKCFG_DIVEN_EN                         |
                             AM_REG_IOM_CLKCFG_DIV3_DIS                         |
                             AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV4                   |
                             AM_REG_IOM_CLKCFG_IOCLKEN(1);
                AM_REGn(IOM, ui32Module, MI2CCFG) = AM_REG_IOM_MI2CCFG_STRDIS(0)                            |
                                                    AM_REG_IOM_MI2CCFG_SMPCNT(0x21)                         |
                                                    AM_REG_IOM_MI2CCFG_SDAENDLY(3)                          |
                                                    AM_REG_IOM_MI2CCFG_SCLENDLY(0)                          |
                                                    AM_REG_IOM_MI2CCFG_MI2CRST(1)                           |
                                                    AM_REG_IOM_MI2CCFG_SDADLY(0)                            |
                                                    AM_REG_IOM_MI2CCFG_ARBEN_ARBDIS                         |
                                                    AM_REG_IOM_MI2CCFG_I2CLSB_MSBFIRST                      |
                                                    AM_REG_IOM_MI2CCFG_ADDRSZ_ADDRSZ7;


//                ui32ClkCfg = 0x6031301;
//                AM_REGn(IOM, ui32Module, MI2CCFG) = 0x213040;
#endif // AM_CMSIS_REGS
                break;
            default:
                return AM_HAL_STATUS_INVALID_ARG;
        }

    }
    else
    {
        return AM_HAL_STATUS_OUT_OF_RANGE;
    }

    //
    // Enable and set the clock configuration.
    //
#if AM_CMSIS_REGS
    ui32ClkCfg |= _VAL2FLD(IOM0_CLKCFG_IOCLKEN, 1);
    IOMn(ui32Module)->CLKCFG = ui32ClkCfg;
#else // AM_CMSIS_REGS
    ui32ClkCfg |= AM_BFV(IOM, CLKCFG, IOCLKEN, 1);
    AM_REGn(IOM, ui32Module, CLKCFG) = ui32ClkCfg;
#endif // AM_CMSIS_REGS

    pIOMState->ui32BitTimeTicks = AM_HAL_CLKGEN_FREQ_MAX_HZ / psConfig->ui32ClockFreq;

    //
    // Set the delay timeout value to the default maximum value.
    //
    pIOMState->waitTimeout = 1000;

    pIOMState->pNBTxnBuf = psConfig->pNBTxnBuf;
    pIOMState->ui32NBTxnBufLength = psConfig->ui32NBTxnBufLength;

    //
    // Return the status.
    //
    return status;

} // am_hal_iom_configure()

//*****************************************************************************
//
// IOM blocking transfer function
//
//*****************************************************************************
uint32_t
am_hal_iom_blocking_transfer(void *pHandle,
                             am_hal_iom_transfer_t *psTransaction)
{
    uint32_t ui32Cmd, ui32Offset, ui32OffsetCnt, ui32Dir, ui32Cont;
    uint32_t ui32FifoRem, ui32FifoSiz;
    uint32_t ui32Bytes;
    uint32_t ui32IntConfig;
    uint32_t *pui32Buffer;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t ui32Module;
    uint32_t ui32Status = AM_HAL_STATUS_SUCCESS;
    bool     bCmdCmp = false;
    uint32_t numWait = 0;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Validate parameters
    //
    ui32Status = validate_transaction(pIOMState, psTransaction, true);

    if (ui32Status != AM_HAL_STATUS_SUCCESS)
    {
        return ui32Status;
    }
    if (psTransaction->eDirection > AM_HAL_IOM_RX)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    ui32Module = pIOMState->ui32Module;
    ui32Offset = psTransaction->ui32Instr;
    ui32OffsetCnt = psTransaction->ui32InstrLen;
    ui32Bytes = psTransaction->ui32NumBytes;
    ui32Dir = psTransaction->eDirection;
    ui32Cont = psTransaction->bContinue ? 1 : 0;
    pui32Buffer = (ui32Dir == AM_HAL_IOM_TX) ? psTransaction->pui32TxBuffer : psTransaction->pui32RxBuffer;

    //
    // Make sure any previous non-blocking transfers have completed.
    //
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                                                 (uint32_t)&pIOMState->ui32NumPendTransactions,
                                                 0xFFFFFFFF,
                                                 0,
                                                 true);
    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        return ui32Status;
    }

    //
    // Make sure any previous blocking transfer has been completed.
    // This check is required to make sure previous transaction has cleared if the blocking call
    // finished with a timeout
    //
#if AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                            (uint32_t)&IOMn(ui32Module)->STATUS,
                            (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk),
                            IOM0_STATUS_IDLEST_Msk,
                            true);
#else // AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                            AM_REG_IOMn(ui32Module) + AM_REG_IOM_STATUS_O,
                            (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M),
                            AM_REG_IOM_STATUS_IDLEST_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        return ui32Status;
    }

    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntConfig = IOMn(ui32Module)->INTEN;
    //
    // Disable IOM interrupts as we'll be polling
    //
    IOMn(ui32Module)->INTEN = 0;

    //
    // Clear interrupts
    //
    IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;

    //
    // Set the dev addr (either 7 or 10 bit as configured in MI2CCFG).
    //
    IOMn(ui32Module)->DEVCFG = psTransaction->uPeerInfo.ui32I2CDevAddr;

    //
    // Set the Repeat Count
    //
    IOMn(ui32Module)->CMDRPT = psTransaction->ui8RepeatCount;

    //
    // Build the CMD value
    //

    ui32Cmd = pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE ?
              psTransaction->uPeerInfo.ui32SpiChipSelect : 0;
    ui32Cmd = build_cmd(ui32Cmd, ui32Dir,  ui32Cont, ui32Offset, ui32OffsetCnt, ui32Bytes);

    //
    // Set the OFFSETHI register.
    //
    IOMn(ui32Module)->OFFSETHI = (uint16_t)(ui32Offset >> 8);

    //
    // Start the transfer
    //
    IOMn(ui32Module)->CMD = ui32Cmd;
#else // AM_CMSIS_REGS
    ui32IntConfig = AM_REGn(IOM, ui32Module, INTEN);

    //
    // Disable IOM interrupts as we'll be polling
    //
    AM_REGn(IOM, ui32Module, INTEN) = 0;

    //
    // Clear interrupts
    //
    AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Set the dev addr (either 7 or 10 bit as configured in MI2CCFG).
    //
    AM_REGn(IOM, ui32Module, DEVCFG) = psTransaction->uPeerInfo.ui32I2CDevAddr;

    //
    // Set the Repeat Count
    //
    AM_REGn(IOM, ui32Module, CMDRPT) = psTransaction->ui8RepeatCount;

    //
    // Build the CMD value
    //

    ui32Cmd = pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE ?
              psTransaction->uPeerInfo.ui32SpiChipSelect : 0;
    ui32Cmd = build_cmd(ui32Cmd, ui32Dir,  ui32Cont, ui32Offset, ui32OffsetCnt, ui32Bytes);

    //
    // Set the OFFSETHI register.
    //
    AM_REGn(IOM, ui32Module, OFFSETHI) = (uint16_t)(ui32Offset >> 8);


    //
    // Start the transfer
    //
    AM_REGn(IOM, ui32Module, CMD) = ui32Cmd;
#endif // AM_CMSIS_REGS

    // Adjust the byte count to be sent/received for repeat count
    ui32Bytes = (1 + psTransaction->ui8RepeatCount) * psTransaction->ui32NumBytes;

    if ( ui32Dir == AM_HAL_IOM_RX )
    {

        //
        // Start a loop to catch the Rx data.
        //
        while ( ui32Bytes )
        {
            //
            // Limit the wait to reasonable limit - instead of blocking forever
            //
            numWait = 0;
#if AM_CMSIS_REGS
            while ((ui32FifoSiz = IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ) < 4)
            {
#else // AM_CMSIS_REGS
            while ((ui32FifoSiz = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ)) < 4)
            {
#endif // AM_CMSIS_REGS
                if (numWait++ < AM_HAL_IOM_MAX_BLOCKING_WAIT)
                {
                    if (bCmdCmp && (ui32Bytes > ui32FifoSiz))
                    {
                        //
                        // No more data expected. Get out of the loop
                        //
                        break;
                    }
                    am_hal_flash_delay( FLASH_CYCLES_US(1) );
                }
                else
                {
                    //
                    // We've waited long enough - get out!
                    //
                    break;
                }
#if AM_CMSIS_REGS
                bCmdCmp = IOMn(ui32Module)->INTSTAT_b.CMDCMP;
#else // AM_CMSIS_REGS
                bCmdCmp = AM_BFRn(IOM, ui32Module, INTSTAT, CMDCMP);
#endif // AM_CMSIS_REGS
            }
            if (ui32FifoSiz < 4)
            {
                //
                // Something went wrong - get out and report failure
                //
                break;
            }

            while ((ui32FifoSiz >= 4) && ui32Bytes)
            {
                //
                // Safe to read the FIFO, read 4 bytes
                //
                uint32_t ui32Read;
#if AM_CMSIS_REGS
                ui32Read = IOMn(ui32Module)->FIFOPOP;
#if MANUAL_POP
                IOMn(ui32Module)->FIFOPOP = 0x11111111;
#endif
#else // AM_CMSIS_REGS
                ui32Read = AM_REGn(IOM, ui32Module, FIFOPOP);
#if MANUAL_POP
                AM_REGn(IOM, ui32Module, FIFOPOP) = 0x11111111;
#endif
#endif // AM_CMSIS_REGS
                ui32FifoSiz -= 4;
                if (ui32Bytes >= 4)
                {
                    *pui32Buffer++ = ui32Read;
                    ui32Bytes -= 4;
                }
                else
                {
                    // Copy byte by byte - so as to not corrupt the rest of the buffer
                    uint8_t *pui8Buffer = (uint8_t *)pui32Buffer;
                    do
                    {
                        *pui8Buffer++ = ui32Read & 0xFF;
                        ui32Read >>= 8;
                    } while (--ui32Bytes);

                }
            }
        }
    }
    else if ( ui32Dir == AM_HAL_IOM_TX )
    {
        //
        // Keep looping until we're out of bytes to send or command complete (error).
        //
        while (ui32Bytes)
        {
            //
            // Limit the wait to reasonable limit - instead of blocking forever
            //
            numWait = 0;
#if AM_CMSIS_REGS
            while ((ui32FifoRem = IOMn(ui32Module)->FIFOPTR_b.FIFO0REM) < 4)
            {
                bCmdCmp = IOMn(ui32Module)->INTSTAT_b.CMDCMP;
#else // AM_CMSIS_REGS
            while ((ui32FifoRem = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO0REM)) < 4)
            {
                bCmdCmp = AM_BFRn(IOM, ui32Module, INTSTAT, CMDCMP);
#endif // AM_CMSIS_REGS
                if (bCmdCmp || (numWait++ >= AM_HAL_IOM_MAX_BLOCKING_WAIT))
                {
                    //
                    // FIFO not expected to change any more - get out
                    //
                    break;
                }
                else
                {
                    am_hal_flash_delay( FLASH_CYCLES_US(1) );
                }
            }
            if (bCmdCmp || (ui32FifoRem < 4))
            {
                //
                // Something went wrong - bail out
                //
                break;
            }

            while ((ui32FifoRem >= 4) && ui32Bytes)
            {
#if AM_CMSIS_REGS
                IOMn(ui32Module)->FIFOPUSH = *pui32Buffer++;
#else // AM_CMSIS_REGS
                AM_REGn(IOM, ui32Module, FIFOPUSH) = *pui32Buffer++;
#endif // AM_CMSIS_REGS
                ui32FifoRem -= 4;
                if (ui32Bytes >= 4)
                {
                    ui32Bytes -= 4;
                }
                else
                {
                    ui32Bytes = 0;
                }
            }
        }
    }

    //
    // Make sure transfer is completed.
    //
#if AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(AM_HAL_IOM_MAX_BLOCKING_WAIT,
                            (uint32_t)&IOMn(ui32Module)->STATUS,
                            (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk),
                            IOM0_STATUS_IDLEST_Msk,
                            true);
#else // AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(AM_HAL_IOM_MAX_BLOCKING_WAIT,
                            AM_REG_IOMn(ui32Module) + AM_REG_IOM_STATUS_O,
                            (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M),
                            AM_REG_IOM_STATUS_IDLEST_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status == AM_HAL_STATUS_SUCCESS )
    {
        ui32Status = internal_iom_get_int_err(ui32Module, 0);

        if (ui32Status == AM_HAL_STATUS_SUCCESS)
        {
            if (ui32Bytes)
            {
                // Indicates transaction did not finish for some reason
                ui32Status = AM_HAL_STATUS_FAIL;
            }
        }
    }

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        // Do Error recovery
        // Reset Submodule & FIFO
#if AM_CMSIS_REGS
        internal_iom_reset_on_error(pIOMState, IOMn(ui32Module)->INTSTAT);
#else // AM_CMSIS_REGS
        internal_iom_reset_on_error(pIOMState, AM_REGn(IOM, ui32Module, INTSTAT));
#endif
    }

    //
    // Clear interrupts
    // Re-enable IOM interrupts.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;
    IOMn(ui32Module)->INTEN = ui32IntConfig;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOM, ui32Module, INTEN) = ui32IntConfig;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return ui32Status;

} // am_hal_iom_blocking_transfer()


//*****************************************************************************
//
// IOM non-blocking transfer function
//
//*****************************************************************************
uint32_t
am_hal_iom_nonblocking_transfer(void *pHandle,
                                am_hal_iom_transfer_t *psTransaction,
                                am_hal_iom_callback_t pfnCallback,
                                void *pCallbackCtxt)
{
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t ui32Module;
    uint32_t ui32Status = AM_HAL_STATUS_SUCCESS;
    uint32_t ui32NumPend;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Validate parameters
    //
    ui32Status = validate_transaction(pIOMState, psTransaction, false);

    if (ui32Status != AM_HAL_STATUS_SUCCESS)
    {
        return ui32Status;
    }
    if (psTransaction->eDirection > AM_HAL_IOM_RX)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    ui32Module = pIOMState->ui32Module;

#if (AM_HAL_IOM_CQ == 1)
    if (!pIOMState->pCmdQHdl)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
    //
    // DMA defaults to using the Command Queue
    //
    ui32Status = am_hal_iom_CQAddTransaction(pHandle, psTransaction, pfnCallback, pCallbackCtxt);

    if (ui32Status == AM_HAL_STATUS_SUCCESS)
    {
        uint32_t ui32Critical = 0;

        //
        // Need to protect access of ui32NumPendTransactions as it is accessed
        // from ISR as well
        //
        // Start a critical section.
        //
        ui32Critical = am_hal_interrupt_master_disable();

        //
        // Register for interrupt only if there is a callback
        //
        ui32Status = am_hal_cmdq_post_block(pIOMState->pCmdQHdl, pfnCallback);
        if (ui32Status == AM_HAL_STATUS_SUCCESS)
        {
            ui32NumPend = pIOMState->ui32NumPendTransactions++;
            //
            // End the critical section.
            //
            am_hal_interrupt_master_set(ui32Critical);

            if (0 == ui32NumPend)
            {
                //
                // Set the interrupts
                // Disable interrupts so that we don't get any undesired interrupts.
                //
#if AM_CMSIS_REGS
                pIOMState->ui32UserIntCfg = IOMn(ui32Module)->INTEN;

                //
                // Clear interrupts
                //
                IOMn(ui32Module)->INTEN = 0;
                IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;

                //
                // Only keep IOM interrupts we're intereseted in
                // We should not need CMDCMP/DCMP - as CQUPD should suffice for transactions which need callback
                //
                IOMn(ui32Module)->INTEN =
                    (AM_HAL_IOM_INT_CQUPD | AM_HAL_IOM_INT_ERR);
#else // AM_CMSIS_REGS
                pIOMState->ui32UserIntCfg = AM_REGn(IOM, ui32Module, INTEN);

                //
                // Clear interrupts
                //
                AM_REGn(IOM, ui32Module, INTEN) = 0;
                AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

                //
                // Only keep IOM interrupts we're intereseted in
                // We should not need CMDCMP/DCMP - as CQUPD should suffice for transactions which need callback
                //
                AM_REGn(IOM, ui32Module, INTEN) =
                    (AM_HAL_IOM_INT_CQUPD | AM_HAL_IOM_INT_ERR);
#endif // AM_CMSIS_REGS

                //
                // Enable the Command Queue
                //
                am_hal_iom_CQEnable(pHandle);
            }
        }
        else
        {
            //
            // End the critical section.
            //
            am_hal_interrupt_master_set(ui32Critical);
            am_hal_cmdq_release_block(pIOMState->pCmdQHdl);
        }
    }
#else // !AM_HAL_IOM_CQ
    if (pIOMState->ui32MaxTransactions == 0)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
    ui32Status = am_hal_iom_DmaAddTransaction(pHandle, psTransaction, pfnCallback, pCallbackCtxt);

    if (ui32Status == AM_HAL_STATUS_SUCCESS)
    {
#if AM_CMSIS_REGS
        //
        // Start a critical section.
        //
        AM_CRITICAL_BEGIN

        ui32NumPend = pIOMState->ui32NumPendTransactions++;

        //
        // End the critical section.
        //
        AM_CRITICAL_END
#else // AM_CMSIS_REGS
        uint32_t ui32Critical = 0;

        //
        // Start a critical section.
        //
        ui32Critical = am_hal_interrupt_master_disable();

        ui32NumPend = pIOMState->ui32NumPendTransactions++;

        //
        // End the critical section.
        //
        am_hal_interrupt_master_set(ui32Critical);
#endif // AM_CMSIS_REGS

        if (0 == ui32NumPend)
        {
            uint32_t index = (pIOMState->ui32LastIdxProcessed + 1) % pIOMState->ui32MaxTransactions;

            //
            // Disable interrupts so that we don't get any undesired interrupts.
            //
#if AM_CMSIS_REGS
            pIOMState->ui32UserIntCfg = IOMn(ui32Module)->INTEN;

            //
            // Clear interrupts
            //
            IOMn(ui32Module)->INTEN = 0;
            IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;

            //
            // Only keep IOM interrupts we're interested in
            // Need both CMDCMP & DCMP, as for Read we need to wait for DCMP after CMDCMP
            //
            IOMn(ui32Module)->INTEN =
                (AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_DCMP | AM_HAL_IOM_INT_ERR);

            //
            // Initialize the DMA state machine (clear the DMACPL flag).
            //
            IOMn(ui32Module)->DMASTAT = 0;
#else // AM_CMSIS_REGS
            pIOMState->ui32UserIntCfg = AM_REGn(IOM, ui32Module, INTEN);

            //
            // Clear interrupts
            //
            AM_REGn(IOM, ui32Module, INTEN) = 0;
            AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

            //
            // Only keep IOM interrupts we're interested in
            // Need both CMDCMP & DCMP, as for Read we need to wait for DCMP after CMDCMP
            //
            AM_REGn(IOM, ui32Module, INTEN) =
                (AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_DCMP | AM_HAL_IOM_INT_ERR);

            //
            // Initialize the DMA state machine (clear the DMACPL flag).
            //
            AM_REGn(IOM, ui32Module, DMASTAT) = 0;
#endif // AM_CMSIS_REGS
            pIOMState->ui32TxnInt = 0;

            //
            // Run the command list
            //
            run_txn_cmdlist(&pIOMState->pTransactions[index], sizeof(am_hal_iom_txn_cmdlist_t) / sizeof(am_hal_cmdq_entry_t));
        }
    }
#endif // !AM_HAL_IOM_CQ

    //
    // Return the status.
    //
    return ui32Status;

} // am_hal_iom_nonblocking_transfer()

//*****************************************************************************
//
//! @brief Perform a simple full-duplex transaction to the SPI interface.
//!
//! This function performs SPI full-duplex operation to a selected SPI device.
//!
//! @note The actual SPI and I2C interfaces operate in BYTES, not 32-bit words.
//! This means that you will need to byte-pack the \e pui32TxData array with the
//! data you intend to send over the interface. One easy way to do this is to
//! declare the array as a 32-bit integer array, but use an 8-bit pointer to
//! put your actual data into the array. If there are not enough bytes in your
//! desired message to completely fill the last 32-bit word, you may pad that
//! last word with bytes of any value. The IOM hardware will only read the
//! first \e ui32NumBytes in the \e pui32TxData array.
//!
//! @return returns AM_HAL_IOM_SUCCESS on successful execution.
//
//*****************************************************************************
uint32_t
am_hal_iom_spi_blocking_fullduplex(void *pHandle,
                                   am_hal_iom_transfer_t *psTransaction)
{
    uint32_t ui32Cmd, ui32Offset, ui32OffsetCnt, ui32Dir, ui32Cont;
    uint32_t ui32FifoRem, ui32FifoSiz;
    uint32_t ui32Bytes;
    uint32_t ui32RxBytes;
    uint32_t ui32IntConfig;
    uint32_t *pui32TxBuffer;
    uint32_t *pui32RxBuffer;
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t ui32Module;
    uint32_t ui32Status = AM_HAL_STATUS_SUCCESS;
    bool     bCmdCmp = false;
    uint32_t numWait = 0;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Validate parameters
    //
    ui32Status = validate_transaction(pIOMState, psTransaction, true);

    if (ui32Status != AM_HAL_STATUS_SUCCESS)
    {
        return ui32Status;
    }
    if (psTransaction->eDirection != AM_HAL_IOM_FULLDUPLEX)
    {
        return AM_HAL_STATUS_INVALID_OPERATION;
    }
#endif

    ui32Module = pIOMState->ui32Module;
    ui32Offset = psTransaction->ui32Instr;
    ui32OffsetCnt = psTransaction->ui32InstrLen;
    ui32Bytes = psTransaction->ui32NumBytes;
    ui32Dir = psTransaction->eDirection;
    ui32Cont = psTransaction->bContinue ? 1 : 0;
    pui32RxBuffer = psTransaction->pui32RxBuffer;
    pui32TxBuffer = psTransaction->pui32TxBuffer;

    //
    // Make sure any previous non-blocking transfers have completed.
    //
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                                                 (uint32_t)&pIOMState->ui32NumPendTransactions,
                                                 0xFFFFFFFF,
                                                 0,
                                                 true);
    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        return ui32Status;
    }

    //
    // Make sure any previous blocking transfer has been completed.
    // This check is required to make sure previous transaction has cleared if the blocking call
    // finished with a timeout
    //
#if AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                            (uint32_t)&IOMn(ui32Module)->STATUS,
                            (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk),
                            IOM0_STATUS_IDLEST_Msk,
                            true);
#else // AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(pIOMState->waitTimeout,
                            AM_REG_IOMn(ui32Module) + AM_REG_IOM_STATUS_O,
                            (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M),
                            AM_REG_IOM_STATUS_IDLEST_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        return ui32Status;
    }

    //
    // Disable interrupts so that we don't get any undesired interrupts.
    //
#if AM_CMSIS_REGS
    ui32IntConfig = IOMn(ui32Module)->INTEN;

    //
    // Disable IOM interrupts as we'll be polling
    //
    IOMn(ui32Module)->INTEN = 0;

    //
    // Clear interrupts
    //
    IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;

    //
    // Set the dev addr (either 7 or 10 bit as configured in MI2CCFG).
    //
    IOMn(ui32Module)->DEVCFG = psTransaction->uPeerInfo.ui32I2CDevAddr;

    //
    // Set the Repeat Count
    //
    IOMn(ui32Module)->CMDRPT = psTransaction->ui8RepeatCount;
#else // AM_CMSIS_REGS
    ui32IntConfig = AM_REGn(IOM, ui32Module, INTEN);

    //
    // Disable IOM interrupts as we'll be polling
    //
    AM_REGn(IOM, ui32Module, INTEN) = 0;

    //
    // Clear interrupts
    //
    AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;

    //
    // Set the dev addr (either 7 or 10 bit as configured in MI2CCFG).
    //
    AM_REGn(IOM, ui32Module, DEVCFG) = psTransaction->uPeerInfo.ui32I2CDevAddr;

    //
    // Set the Repeat Count
    //
    AM_REGn(IOM, ui32Module, CMDRPT) = psTransaction->ui8RepeatCount;
#endif // AM_CMSIS_REGS

    //
    // Build the CMD value
    //

    ui32Cmd = pIOMState->eInterfaceMode == AM_HAL_IOM_SPI_MODE ?
              psTransaction->uPeerInfo.ui32SpiChipSelect : 0;
    ui32Cmd = build_cmd(ui32Cmd, ui32Dir,  ui32Cont, ui32Offset, ui32OffsetCnt, ui32Bytes);

    //
    // Set the OFFSETHI register.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->OFFSETHI = (uint16_t)(ui32Offset >> 8);

    //
    // Set FULLDUPLEX mode
    //
    IOMn(ui32Module)->MSPICFG |= _VAL2FLD(IOM0_MSPICFG_FULLDUP, 1);

    //
    // Start the transfer
    //
    IOMn(ui32Module)->CMD = ui32Cmd;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, OFFSETHI) = (uint16_t)(ui32Offset >> 8);


    //
    // Set FULLDUPLEX mode
    //
    AM_REGn(IOM, ui32Module, MSPICFG) |= AM_REG_IOM_MSPICFG_FULLDUP(1);

    //
    // Start the transfer
    //
    AM_REGn(IOM, ui32Module, CMD) = ui32Cmd;
#endif // AM_CMSIS_REGS

    // Adjust the byte count to be sent/received for repeat count
    ui32Bytes = (1 + psTransaction->ui8RepeatCount) * psTransaction->ui32NumBytes;
    ui32RxBytes = ui32Bytes;

    //
    // Start a loop to catch the Rx data.
    //
    //
    // Keep looping until we're out of bytes to send or command complete (error).
    //
    while (ui32Bytes || ui32RxBytes)
    {
        //
        // Limit the wait to reasonable limit - instead of blocking forever
        //
        numWait = 0;
#if AM_CMSIS_REGS
        ui32FifoRem = IOMn(ui32Module)->FIFOPTR_b.FIFO0REM;
        ui32FifoSiz = IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ;

#else // AM_CMSIS_REGS
        ui32FifoRem = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO0REM);
        ui32FifoSiz = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ);
#endif // AM_CMSIS_REGS
        while ((ui32FifoRem < 4) &&
               (ui32FifoSiz < 4))
        {
            if (numWait++ < AM_HAL_IOM_MAX_BLOCKING_WAIT)
            {
                if (bCmdCmp && (ui32RxBytes > ui32FifoSiz))
                {
                    //
                    // No more data expected. Get out of the loop
                    //
                    break;
                }
                am_hal_flash_delay( FLASH_CYCLES_US(1) );
            }
            else
            {
                //
                // We've waited long enough - get out!
                //
                break;
            }
#if AM_CMSIS_REGS
            bCmdCmp     = IOMn(ui32Module)->INTSTAT_b.CMDCMP;
            ui32FifoRem = IOMn(ui32Module)->FIFOPTR_b.FIFO0REM;
            ui32FifoSiz = IOMn(ui32Module)->FIFOPTR_b.FIFO1SIZ;
#else // AM_CMSIS_REGS
            bCmdCmp = AM_BFRn(IOM, ui32Module, INTSTAT, CMDCMP);
            ui32FifoRem = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO0REM);
            ui32FifoSiz = AM_BFRn(IOM, ui32Module, FIFOPTR, FIFO1SIZ);
#endif // AM_CMSIS_REGS
        }
        if (bCmdCmp || ((ui32FifoRem < 4) && (ui32FifoSiz < 4)))
        {
            //
            // Something went wrong - bail out
            //
            break;
        }

        while ((ui32FifoRem >= 4) && ui32Bytes)
        {
#if AM_CMSIS_REGS
            IOMn(ui32Module)->FIFOPUSH = *pui32TxBuffer++;
#else // AM_CMSIS_REGS
            AM_REGn(IOM, ui32Module, FIFOPUSH) = *pui32TxBuffer++;
#endif // AM_CMSIS_REGS
            ui32FifoRem -= 4;
            if (ui32Bytes >= 4)
            {
                ui32Bytes -= 4;
            }
            else
            {
                ui32Bytes = 0;
            }
        }
        while ((ui32FifoSiz >= 4) && ui32RxBytes)
        {
            //
            // Safe to read the FIFO, read 4 bytes
            //
#if AM_CMSIS_REGS
            *pui32RxBuffer++ = IOMn(ui32Module)->FIFOPOP;
#if MANUAL_POP
            IOMn(ui32Module)->FIFOPOP = 0x11111111;
#endif
#else // AM_CMSIS_REGS
            *pui32RxBuffer++ = AM_REGn(IOM, ui32Module, FIFOPOP);
#if MANUAL_POP
            AM_REGn(IOM, ui32Module, FIFOPOP) = 0x11111111;
#endif
#endif // AM_CMSIS_REGS
            ui32FifoSiz -= 4;
            if (ui32RxBytes >= 4)
            {
                ui32RxBytes -= 4;
            }
            else
            {
                ui32RxBytes = 0;
            }
        }
    }

    //
    // Make sure transfer is completed.
    //
#if AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(AM_HAL_IOM_MAX_BLOCKING_WAIT,
                            (uint32_t)&IOMn(ui32Module)->STATUS,
                            (IOM0_STATUS_IDLEST_Msk | IOM0_STATUS_CMDACT_Msk),
                            IOM0_STATUS_IDLEST_Msk,
                            true);
#else // AM_CMSIS_REGS
    ui32Status = am_hal_flash_delay_status_check(AM_HAL_IOM_MAX_BLOCKING_WAIT,
                            AM_REG_IOMn(ui32Module) + AM_REG_IOM_STATUS_O,
                            (AM_REG_IOM_STATUS_IDLEST_M | AM_REG_IOM_STATUS_CMDACT_M),
                            AM_REG_IOM_STATUS_IDLEST_M,
                            true);
#endif // AM_CMSIS_REGS

    if ( ui32Status != AM_HAL_STATUS_SUCCESS )
    {
        return ui32Status;
    }

    ui32Status = internal_iom_get_int_err(ui32Module, 0);

    if (ui32Status == AM_HAL_STATUS_SUCCESS)
    {
        if (ui32Bytes)
        {
            // Indicates transaction did not finish for some reason
            ui32Status = AM_HAL_STATUS_FAIL;
        }
    }
    else
    {
        // Do Error recovery
        // Reset Submodule & FIFO
#if AM_CMSIS_REGS
        internal_iom_reset_on_error(pIOMState, IOMn(ui32Module)->INTSTAT);
#else // AM_CMSIS_REGS
        internal_iom_reset_on_error(pIOMState, AM_REGn(IOM, ui32Module, INTSTAT));
#endif // AM_CMSIS_REGS
    }

    //
    // Clear interrupts
    // Re-enable IOM interrupts.
    //
#if AM_CMSIS_REGS
    IOMn(ui32Module)->INTCLR = AM_HAL_IOM_INT_ALL;
    IOMn(ui32Module)->INTEN = ui32IntConfig;
#else // AM_CMSIS_REGS
    AM_REGn(IOM, ui32Module, INTCLR) = AM_HAL_IOM_INT_ALL;
    AM_REGn(IOM, ui32Module, INTEN) = ui32IntConfig;
#endif // AM_CMSIS_REGS

    //
    // Return the status.
    //
    return ui32Status;

}

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
uint32_t am_hal_iom_control(void *pHandle, am_hal_iom_request_e eReq, void *pArgs)
{
    am_hal_iom_state_t *pIOMState = (am_hal_iom_state_t*)pHandle;
    uint32_t status = AM_HAL_STATUS_SUCCESS;

#ifndef AM_HAL_DISABLE_API_VALIDATION
    if (!AM_HAL_IOM_CHK_HANDLE(pHandle))
    {
        return AM_HAL_STATUS_INVALID_HANDLE;
    }

    //
    // Validate the parameters
    //
    if (eReq > AM_HAL_IOM_REQ_MAX)
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }
#endif

#if AM_CMSIS_REGS
    switch (eReq)
    {
        case AM_HAL_IOM_REQ_FLAG_SETCLR:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                IOMn(ui32Module)->CQSETCLEAR = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_LSB:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                IOMn(ui32Module)->MSPICFG_b.SPILSB = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_FULLDUPLEX:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                IOMn(ui32Module)->MSPICFG_b.FULLDUP = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_RDTHRESH:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                IOMn(ui32Module)->FIFOTHR_b.FIFORTHR = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_WRTHRESH:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                IOMn(ui32Module)->FIFOTHR_b.FIFOWTHR = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        default:
            status = AM_HAL_STATUS_INVALID_ARG;
    }
#else // AM_CMSIS_REGS
    switch (eReq)
    {
        case AM_HAL_IOM_REQ_FLAG_SETCLR:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                AM_REGn(IOM, ui32Module, CQSETCLEAR) = *((uint32_t *)pArgs);
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_LSB:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                AM_BFWn(IOM, ui32Module, MSPICFG, SPILSB, *((uint32_t *)pArgs));
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_FULLDUPLEX:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                AM_BFWn(IOM, ui32Module, MSPICFG, FULLDUP, *((uint32_t *)pArgs));
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_RDTHRESH:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                AM_BFWn(IOM, ui32Module, FIFOTHR, FIFORTHR, *((uint32_t *)pArgs));
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        case AM_HAL_IOM_REQ_SPI_WRTHRESH:
            if (pArgs)
            {
                uint32_t ui32Module = pIOMState->ui32Module;
                AM_BFWn(IOM, ui32Module, FIFOTHR, FIFOWTHR, *((uint32_t *)pArgs));
            }
            else
            {
                status = AM_HAL_STATUS_INVALID_ARG;
            }
            break;
        default:
            status = AM_HAL_STATUS_INVALID_ARG;
    }
#endif // AM_CMSIS_REGS

    return status;
}


//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************

