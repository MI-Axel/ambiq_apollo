//*****************************************************************************
//
//  am_reg_mspi.h
//! @file
//!
//! @brief Register macros for the MSPI module
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
#ifndef AM_REG_MSPI_H
#define AM_REG_MSPI_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_MSPI_NUM_MODULES                      1
#define AM_REG_MSPIn(n) \
    (REG_MSPI_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_MSPI_CTRL_O                           0x00000000
#define AM_REG_MSPI_CFG_O                            0x00000004
#define AM_REG_MSPI_ADDR_O                           0x00000008
#define AM_REG_MSPI_INSTR_O                          0x0000000C
#define AM_REG_MSPI_TXFIFO_O                         0x00000010
#define AM_REG_MSPI_RXFIFO_O                         0x00000014
#define AM_REG_MSPI_TXENTRIES_O                      0x00000018
#define AM_REG_MSPI_RXENTRIES_O                      0x0000001C
#define AM_REG_MSPI_THRESHOLD_O                      0x00000020
#define AM_REG_MSPI_MSPICFG_O                        0x00000100
#define AM_REG_MSPI_PADCFG_O                         0x00000104
#define AM_REG_MSPI_PADOUTEN_O                       0x00000108
#define AM_REG_MSPI_FLASH_O                          0x0000010C
#define AM_REG_MSPI_SCRAMBLING_O                     0x00000120
#define AM_REG_MSPI_DMACFG_O                         0x00000250
#define AM_REG_MSPI_DMASTAT_O                        0x00000254
#define AM_REG_MSPI_DMATARGADDR_O                    0x00000258
#define AM_REG_MSPI_DMADEVADDR_O                     0x0000025C
#define AM_REG_MSPI_DMATOTCOUNT_O                    0x00000260
#define AM_REG_MSPI_DMABCOUNT_O                      0x00000264
#define AM_REG_MSPI_DMATHRESH_O                      0x00000278
#define AM_REG_MSPI_CQCFG_O                          0x000002A0
#define AM_REG_MSPI_CQADDR_O                         0x000002A8
#define AM_REG_MSPI_CQSTAT_O                         0x000002AC
#define AM_REG_MSPI_CQFLAGS_O                        0x000002B0
#define AM_REG_MSPI_CQSETCLEAR_O                     0x000002B4
#define AM_REG_MSPI_CQPAUSE_O                        0x000002B8
#define AM_REG_MSPI_CQCURIDX_O                       0x000002C0
#define AM_REG_MSPI_CQENDIDX_O                       0x000002C4
#define AM_REG_MSPI_INTEN_O                          0x00000200
#define AM_REG_MSPI_INTSTAT_O                        0x00000204
#define AM_REG_MSPI_INTCLR_O                         0x00000208
#define AM_REG_MSPI_INTSET_O                         0x0000020C

//*****************************************************************************
//
// MSPI_INTEN - MSPI Master Interrupts: Enable
//
//*****************************************************************************
// Scrambling Alignment Error.  Scrambling operations must be aligned to word
// (4-byte) start address.
#define AM_REG_MSPI_INTEN_SCRERR_S                   12
#define AM_REG_MSPI_INTEN_SCRERR_M                   0x00001000
#define AM_REG_MSPI_INTEN_SCRERR(n)                  (((uint32_t)(n) << 12) & 0x00001000)

// Command Queue Error Interrupt
#define AM_REG_MSPI_INTEN_CQERR_S                    11
#define AM_REG_MSPI_INTEN_CQERR_M                    0x00000800
#define AM_REG_MSPI_INTEN_CQERR(n)                   (((uint32_t)(n) << 11) & 0x00000800)

// Command Queue is Paused.
#define AM_REG_MSPI_INTEN_CQPAUSED_S                 10
#define AM_REG_MSPI_INTEN_CQPAUSED_M                 0x00000400
#define AM_REG_MSPI_INTEN_CQPAUSED(n)                (((uint32_t)(n) << 10) & 0x00000400)

// Command Queue Update Interrupt.  Issued whenever the CQ performs an operation
// where address bit[0] is set.  Useful for triggering CURIDX interrupts.
#define AM_REG_MSPI_INTEN_CQUPD_S                    9
#define AM_REG_MSPI_INTEN_CQUPD_M                    0x00000200
#define AM_REG_MSPI_INTEN_CQUPD(n)                   (((uint32_t)(n) << 9) & 0x00000200)

// Command Queue Complete Interrupt
#define AM_REG_MSPI_INTEN_CQCMP_S                    8
#define AM_REG_MSPI_INTEN_CQCMP_M                    0x00000100
#define AM_REG_MSPI_INTEN_CQCMP(n)                   (((uint32_t)(n) << 8) & 0x00000100)

// DMA Error Interrupt
#define AM_REG_MSPI_INTEN_DERR_S                     7
#define AM_REG_MSPI_INTEN_DERR_M                     0x00000080
#define AM_REG_MSPI_INTEN_DERR(n)                    (((uint32_t)(n) << 7) & 0x00000080)

// DMA Complete Interrupt
#define AM_REG_MSPI_INTEN_DCMP_S                     6
#define AM_REG_MSPI_INTEN_DCMP_M                     0x00000040
#define AM_REG_MSPI_INTEN_DCMP(n)                    (((uint32_t)(n) << 6) & 0x00000040)

// Receive FIFO full
#define AM_REG_MSPI_INTEN_RXF_S                      5
#define AM_REG_MSPI_INTEN_RXF_M                      0x00000020
#define AM_REG_MSPI_INTEN_RXF(n)                     (((uint32_t)(n) << 5) & 0x00000020)

// Receive FIFO overflow (cannot happen in MSPI design -- MSPI bus pins will
// stall)
#define AM_REG_MSPI_INTEN_RXO_S                      4
#define AM_REG_MSPI_INTEN_RXO_M                      0x00000010
#define AM_REG_MSPI_INTEN_RXO(n)                     (((uint32_t)(n) << 4) & 0x00000010)

// Receive FIFO underflow (only occurs when SW reads from an empty FIFO)
#define AM_REG_MSPI_INTEN_RXU_S                      3
#define AM_REG_MSPI_INTEN_RXU_M                      0x00000008
#define AM_REG_MSPI_INTEN_RXU(n)                     (((uint32_t)(n) << 3) & 0x00000008)

// Transmit FIFO Overflow (only occurs when SW writes to a full FIFO).
#define AM_REG_MSPI_INTEN_TXO_S                      2
#define AM_REG_MSPI_INTEN_TXO_M                      0x00000004
#define AM_REG_MSPI_INTEN_TXO(n)                     (((uint32_t)(n) << 2) & 0x00000004)

// Transmit FIFO empty.
#define AM_REG_MSPI_INTEN_TXE_S                      1
#define AM_REG_MSPI_INTEN_TXE_M                      0x00000002
#define AM_REG_MSPI_INTEN_TXE(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// Transfer complete.  Note that DMA and CQ operations are layered, so CMDCMP,
// DCMP, and CQ* can all be signalled simultaneously
#define AM_REG_MSPI_INTEN_CMDCMP_S                   0
#define AM_REG_MSPI_INTEN_CMDCMP_M                   0x00000001
#define AM_REG_MSPI_INTEN_CMDCMP(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_INTSTAT - MSPI Master Interrupts: Status
//
//*****************************************************************************
// Scrambling Alignment Error.  Scrambling operations must be aligned to word
// (4-byte) start address.
#define AM_REG_MSPI_INTSTAT_SCRERR_S                 12
#define AM_REG_MSPI_INTSTAT_SCRERR_M                 0x00001000
#define AM_REG_MSPI_INTSTAT_SCRERR(n)                (((uint32_t)(n) << 12) & 0x00001000)

// Command Queue Error Interrupt
#define AM_REG_MSPI_INTSTAT_CQERR_S                  11
#define AM_REG_MSPI_INTSTAT_CQERR_M                  0x00000800
#define AM_REG_MSPI_INTSTAT_CQERR(n)                 (((uint32_t)(n) << 11) & 0x00000800)

// Command Queue is Paused.
#define AM_REG_MSPI_INTSTAT_CQPAUSED_S               10
#define AM_REG_MSPI_INTSTAT_CQPAUSED_M               0x00000400
#define AM_REG_MSPI_INTSTAT_CQPAUSED(n)              (((uint32_t)(n) << 10) & 0x00000400)

// Command Queue Update Interrupt.  Issued whenever the CQ performs an operation
// where address bit[0] is set.  Useful for triggering CURIDX interrupts.
#define AM_REG_MSPI_INTSTAT_CQUPD_S                  9
#define AM_REG_MSPI_INTSTAT_CQUPD_M                  0x00000200
#define AM_REG_MSPI_INTSTAT_CQUPD(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// Command Queue Complete Interrupt
#define AM_REG_MSPI_INTSTAT_CQCMP_S                  8
#define AM_REG_MSPI_INTSTAT_CQCMP_M                  0x00000100
#define AM_REG_MSPI_INTSTAT_CQCMP(n)                 (((uint32_t)(n) << 8) & 0x00000100)

// DMA Error Interrupt
#define AM_REG_MSPI_INTSTAT_DERR_S                   7
#define AM_REG_MSPI_INTSTAT_DERR_M                   0x00000080
#define AM_REG_MSPI_INTSTAT_DERR(n)                  (((uint32_t)(n) << 7) & 0x00000080)

// DMA Complete Interrupt
#define AM_REG_MSPI_INTSTAT_DCMP_S                   6
#define AM_REG_MSPI_INTSTAT_DCMP_M                   0x00000040
#define AM_REG_MSPI_INTSTAT_DCMP(n)                  (((uint32_t)(n) << 6) & 0x00000040)

// Receive FIFO full
#define AM_REG_MSPI_INTSTAT_RXF_S                    5
#define AM_REG_MSPI_INTSTAT_RXF_M                    0x00000020
#define AM_REG_MSPI_INTSTAT_RXF(n)                   (((uint32_t)(n) << 5) & 0x00000020)

// Receive FIFO overflow (cannot happen in MSPI design -- MSPI bus pins will
// stall)
#define AM_REG_MSPI_INTSTAT_RXO_S                    4
#define AM_REG_MSPI_INTSTAT_RXO_M                    0x00000010
#define AM_REG_MSPI_INTSTAT_RXO(n)                   (((uint32_t)(n) << 4) & 0x00000010)

// Receive FIFO underflow (only occurs when SW reads from an empty FIFO)
#define AM_REG_MSPI_INTSTAT_RXU_S                    3
#define AM_REG_MSPI_INTSTAT_RXU_M                    0x00000008
#define AM_REG_MSPI_INTSTAT_RXU(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// Transmit FIFO Overflow (only occurs when SW writes to a full FIFO).
#define AM_REG_MSPI_INTSTAT_TXO_S                    2
#define AM_REG_MSPI_INTSTAT_TXO_M                    0x00000004
#define AM_REG_MSPI_INTSTAT_TXO(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// Transmit FIFO empty.
#define AM_REG_MSPI_INTSTAT_TXE_S                    1
#define AM_REG_MSPI_INTSTAT_TXE_M                    0x00000002
#define AM_REG_MSPI_INTSTAT_TXE(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// Transfer complete.  Note that DMA and CQ operations are layered, so CMDCMP,
// DCMP, and CQ* can all be signalled simultaneously
#define AM_REG_MSPI_INTSTAT_CMDCMP_S                 0
#define AM_REG_MSPI_INTSTAT_CMDCMP_M                 0x00000001
#define AM_REG_MSPI_INTSTAT_CMDCMP(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_INTCLR - MSPI Master Interrupts: Clear
//
//*****************************************************************************
// Scrambling Alignment Error.  Scrambling operations must be aligned to word
// (4-byte) start address.
#define AM_REG_MSPI_INTCLR_SCRERR_S                  12
#define AM_REG_MSPI_INTCLR_SCRERR_M                  0x00001000
#define AM_REG_MSPI_INTCLR_SCRERR(n)                 (((uint32_t)(n) << 12) & 0x00001000)

// Command Queue Error Interrupt
#define AM_REG_MSPI_INTCLR_CQERR_S                   11
#define AM_REG_MSPI_INTCLR_CQERR_M                   0x00000800
#define AM_REG_MSPI_INTCLR_CQERR(n)                  (((uint32_t)(n) << 11) & 0x00000800)

// Command Queue is Paused.
#define AM_REG_MSPI_INTCLR_CQPAUSED_S                10
#define AM_REG_MSPI_INTCLR_CQPAUSED_M                0x00000400
#define AM_REG_MSPI_INTCLR_CQPAUSED(n)               (((uint32_t)(n) << 10) & 0x00000400)

// Command Queue Update Interrupt.  Issued whenever the CQ performs an operation
// where address bit[0] is set.  Useful for triggering CURIDX interrupts.
#define AM_REG_MSPI_INTCLR_CQUPD_S                   9
#define AM_REG_MSPI_INTCLR_CQUPD_M                   0x00000200
#define AM_REG_MSPI_INTCLR_CQUPD(n)                  (((uint32_t)(n) << 9) & 0x00000200)

// Command Queue Complete Interrupt
#define AM_REG_MSPI_INTCLR_CQCMP_S                   8
#define AM_REG_MSPI_INTCLR_CQCMP_M                   0x00000100
#define AM_REG_MSPI_INTCLR_CQCMP(n)                  (((uint32_t)(n) << 8) & 0x00000100)

// DMA Error Interrupt
#define AM_REG_MSPI_INTCLR_DERR_S                    7
#define AM_REG_MSPI_INTCLR_DERR_M                    0x00000080
#define AM_REG_MSPI_INTCLR_DERR(n)                   (((uint32_t)(n) << 7) & 0x00000080)

// DMA Complete Interrupt
#define AM_REG_MSPI_INTCLR_DCMP_S                    6
#define AM_REG_MSPI_INTCLR_DCMP_M                    0x00000040
#define AM_REG_MSPI_INTCLR_DCMP(n)                   (((uint32_t)(n) << 6) & 0x00000040)

// Receive FIFO full
#define AM_REG_MSPI_INTCLR_RXF_S                     5
#define AM_REG_MSPI_INTCLR_RXF_M                     0x00000020
#define AM_REG_MSPI_INTCLR_RXF(n)                    (((uint32_t)(n) << 5) & 0x00000020)

// Receive FIFO overflow (cannot happen in MSPI design -- MSPI bus pins will
// stall)
#define AM_REG_MSPI_INTCLR_RXO_S                     4
#define AM_REG_MSPI_INTCLR_RXO_M                     0x00000010
#define AM_REG_MSPI_INTCLR_RXO(n)                    (((uint32_t)(n) << 4) & 0x00000010)

// Receive FIFO underflow (only occurs when SW reads from an empty FIFO)
#define AM_REG_MSPI_INTCLR_RXU_S                     3
#define AM_REG_MSPI_INTCLR_RXU_M                     0x00000008
#define AM_REG_MSPI_INTCLR_RXU(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// Transmit FIFO Overflow (only occurs when SW writes to a full FIFO).
#define AM_REG_MSPI_INTCLR_TXO_S                     2
#define AM_REG_MSPI_INTCLR_TXO_M                     0x00000004
#define AM_REG_MSPI_INTCLR_TXO(n)                    (((uint32_t)(n) << 2) & 0x00000004)

// Transmit FIFO empty.
#define AM_REG_MSPI_INTCLR_TXE_S                     1
#define AM_REG_MSPI_INTCLR_TXE_M                     0x00000002
#define AM_REG_MSPI_INTCLR_TXE(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// Transfer complete.  Note that DMA and CQ operations are layered, so CMDCMP,
// DCMP, and CQ* can all be signalled simultaneously
#define AM_REG_MSPI_INTCLR_CMDCMP_S                  0
#define AM_REG_MSPI_INTCLR_CMDCMP_M                  0x00000001
#define AM_REG_MSPI_INTCLR_CMDCMP(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_INTSET - MSPI Master Interrupts: Set
//
//*****************************************************************************
// Scrambling Alignment Error.  Scrambling operations must be aligned to word
// (4-byte) start address.
#define AM_REG_MSPI_INTSET_SCRERR_S                  12
#define AM_REG_MSPI_INTSET_SCRERR_M                  0x00001000
#define AM_REG_MSPI_INTSET_SCRERR(n)                 (((uint32_t)(n) << 12) & 0x00001000)

// Command Queue Error Interrupt
#define AM_REG_MSPI_INTSET_CQERR_S                   11
#define AM_REG_MSPI_INTSET_CQERR_M                   0x00000800
#define AM_REG_MSPI_INTSET_CQERR(n)                  (((uint32_t)(n) << 11) & 0x00000800)

// Command Queue is Paused.
#define AM_REG_MSPI_INTSET_CQPAUSED_S                10
#define AM_REG_MSPI_INTSET_CQPAUSED_M                0x00000400
#define AM_REG_MSPI_INTSET_CQPAUSED(n)               (((uint32_t)(n) << 10) & 0x00000400)

// Command Queue Update Interrupt.  Issued whenever the CQ performs an operation
// where address bit[0] is set.  Useful for triggering CURIDX interrupts.
#define AM_REG_MSPI_INTSET_CQUPD_S                   9
#define AM_REG_MSPI_INTSET_CQUPD_M                   0x00000200
#define AM_REG_MSPI_INTSET_CQUPD(n)                  (((uint32_t)(n) << 9) & 0x00000200)

// Command Queue Complete Interrupt
#define AM_REG_MSPI_INTSET_CQCMP_S                   8
#define AM_REG_MSPI_INTSET_CQCMP_M                   0x00000100
#define AM_REG_MSPI_INTSET_CQCMP(n)                  (((uint32_t)(n) << 8) & 0x00000100)

// DMA Error Interrupt
#define AM_REG_MSPI_INTSET_DERR_S                    7
#define AM_REG_MSPI_INTSET_DERR_M                    0x00000080
#define AM_REG_MSPI_INTSET_DERR(n)                   (((uint32_t)(n) << 7) & 0x00000080)

// DMA Complete Interrupt
#define AM_REG_MSPI_INTSET_DCMP_S                    6
#define AM_REG_MSPI_INTSET_DCMP_M                    0x00000040
#define AM_REG_MSPI_INTSET_DCMP(n)                   (((uint32_t)(n) << 6) & 0x00000040)

// Receive FIFO full
#define AM_REG_MSPI_INTSET_RXF_S                     5
#define AM_REG_MSPI_INTSET_RXF_M                     0x00000020
#define AM_REG_MSPI_INTSET_RXF(n)                    (((uint32_t)(n) << 5) & 0x00000020)

// Receive FIFO overflow (cannot happen in MSPI design -- MSPI bus pins will
// stall)
#define AM_REG_MSPI_INTSET_RXO_S                     4
#define AM_REG_MSPI_INTSET_RXO_M                     0x00000010
#define AM_REG_MSPI_INTSET_RXO(n)                    (((uint32_t)(n) << 4) & 0x00000010)

// Receive FIFO underflow (only occurs when SW reads from an empty FIFO)
#define AM_REG_MSPI_INTSET_RXU_S                     3
#define AM_REG_MSPI_INTSET_RXU_M                     0x00000008
#define AM_REG_MSPI_INTSET_RXU(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// Transmit FIFO Overflow (only occurs when SW writes to a full FIFO).
#define AM_REG_MSPI_INTSET_TXO_S                     2
#define AM_REG_MSPI_INTSET_TXO_M                     0x00000004
#define AM_REG_MSPI_INTSET_TXO(n)                    (((uint32_t)(n) << 2) & 0x00000004)

// Transmit FIFO empty.
#define AM_REG_MSPI_INTSET_TXE_S                     1
#define AM_REG_MSPI_INTSET_TXE_M                     0x00000002
#define AM_REG_MSPI_INTSET_TXE(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// Transfer complete.  Note that DMA and CQ operations are layered, so CMDCMP,
// DCMP, and CQ* can all be signalled simultaneously
#define AM_REG_MSPI_INTSET_CMDCMP_S                  0
#define AM_REG_MSPI_INTSET_CMDCMP_M                  0x00000001
#define AM_REG_MSPI_INTSET_CMDCMP(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_CTRL - MSPI PIO Transfer Control/Status Register
//
//*****************************************************************************
// Number of bytes to transmit or receive (based on TXRX bit)
#define AM_REG_MSPI_CTRL_XFERBYTES_S                 16
#define AM_REG_MSPI_CTRL_XFERBYTES_M                 0xFFFF0000
#define AM_REG_MSPI_CTRL_XFERBYTES(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Enables data scrambling for PIO opertions.  This should only be used for data
// operations and never for commands to a device.
#define AM_REG_MSPI_CTRL_PIOSCRAMBLE_S               11
#define AM_REG_MSPI_CTRL_PIOSCRAMBLE_M               0x00000800
#define AM_REG_MSPI_CTRL_PIOSCRAMBLE(n)              (((uint32_t)(n) << 11) & 0x00000800)

// 1 Indicates a TX operation, 0 indicates an RX operation of XFERBYTES
#define AM_REG_MSPI_CTRL_TXRX_S                      10
#define AM_REG_MSPI_CTRL_TXRX_M                      0x00000400
#define AM_REG_MSPI_CTRL_TXRX(n)                     (((uint32_t)(n) << 10) & 0x00000400)

// Indicates whether an instruction phase should be sent (see INSTR field and
// ISIZE field in CFG register)
#define AM_REG_MSPI_CTRL_SENDI_S                     9
#define AM_REG_MSPI_CTRL_SENDI_M                     0x00000200
#define AM_REG_MSPI_CTRL_SENDI(n)                    (((uint32_t)(n) << 9) & 0x00000200)

// Indicates whether an address phase should be sent (see ADDR register and
// ASIZE field in CFG register)
#define AM_REG_MSPI_CTRL_SENDA_S                     8
#define AM_REG_MSPI_CTRL_SENDA_M                     0x00000100
#define AM_REG_MSPI_CTRL_SENDA(n)                    (((uint32_t)(n) << 8) & 0x00000100)

// Indicates whether TX->RX turnaround cycles should be enabled for this
// operation (see TURNAROUND field in CFG register).
#define AM_REG_MSPI_CTRL_ENTURN_S                    7
#define AM_REG_MSPI_CTRL_ENTURN_M                    0x00000080
#define AM_REG_MSPI_CTRL_ENTURN(n)                   (((uint32_t)(n) << 7) & 0x00000080)

// 1 indicates data in FIFO is in big endian format (MSB first); 0 indicates
// little endian data (default, LSB first).
#define AM_REG_MSPI_CTRL_BIGENDIAN_S                 6
#define AM_REG_MSPI_CTRL_BIGENDIAN_M                 0x00000040
#define AM_REG_MSPI_CTRL_BIGENDIAN(n)                (((uint32_t)(n) << 6) & 0x00000040)

// Continuation transfer.  When 1, indicates that the MSPI will hold CE low
// after the transaction completes.  This is included for compatibility with IOM
// module since the MSPI transfer module can handle most cases in a single
// transfer.  NOTE:  CONT functionality only works with CLKDIV=2 (24 MHz).
#define AM_REG_MSPI_CTRL_CONT_S                      5
#define AM_REG_MSPI_CTRL_CONT_M                      0x00000020
#define AM_REG_MSPI_CTRL_CONT(n)                     (((uint32_t)(n) << 5) & 0x00000020)

// Flag indicating that the operation is a command that should be replicated to
// both devices in paired QUAD mode.  This is typically only used when
// reading/writing configuration registers in paired flash devices (do not set
// for memory transfers).
#define AM_REG_MSPI_CTRL_QUADCMD_S                   3
#define AM_REG_MSPI_CTRL_QUADCMD_M                   0x00000008
#define AM_REG_MSPI_CTRL_QUADCMD(n)                  (((uint32_t)(n) << 3) & 0x00000008)

// Command status:  1 indicates controller is busy (command in progress)
#define AM_REG_MSPI_CTRL_BUSY_S                      2
#define AM_REG_MSPI_CTRL_BUSY_M                      0x00000004
#define AM_REG_MSPI_CTRL_BUSY(n)                     (((uint32_t)(n) << 2) & 0x00000004)

// Command status:  1 indicates command has completed.  Cleared by writing 1 to
// this bit or starting a new transfer.
#define AM_REG_MSPI_CTRL_STATUS_S                    1
#define AM_REG_MSPI_CTRL_STATUS_M                    0x00000002
#define AM_REG_MSPI_CTRL_STATUS(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// Write to 1 to initiate a PIO transaction on the bus (typically the entire
// register should be written at once with this bit set).
#define AM_REG_MSPI_CTRL_START_S                     0
#define AM_REG_MSPI_CTRL_START_M                     0x00000001
#define AM_REG_MSPI_CTRL_START(n)                    (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_CFG - MSPI Transfer Configuration Register
//
//*****************************************************************************
// Serial clock polarity.
#define AM_REG_MSPI_CFG_CPOL_S                       17
#define AM_REG_MSPI_CFG_CPOL_M                       0x00020000
#define AM_REG_MSPI_CFG_CPOL(n)                      (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_MSPI_CFG_CPOL_LOW                     0x00000000
#define AM_REG_MSPI_CFG_CPOL_HIGH                    0x00020000

// Serial clock phase.
#define AM_REG_MSPI_CFG_CPHA_S                       16
#define AM_REG_MSPI_CFG_CPHA_M                       0x00010000
#define AM_REG_MSPI_CFG_CPHA(n)                      (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_MSPI_CFG_CPHA_MIDDLE                  0x00000000
#define AM_REG_MSPI_CFG_CPHA_START                   0x00010000

// Number of turnaound cycles (for TX->RX transitions).  Qualified by ENTURN or
// XIPENTURN bit field.
#define AM_REG_MSPI_CFG_TURNAROUND_S                 8
#define AM_REG_MSPI_CFG_TURNAROUND_M                 0x00003F00
#define AM_REG_MSPI_CFG_TURNAROUND(n)                (((uint32_t)(n) << 8) & 0x00003F00)

// Separate IO configuration.  This bit should be set when the target device has
// separate MOSI and MISO pins.  Respective IN/OUT bits below should be set to
// map pins.
#define AM_REG_MSPI_CFG_SEPIO_S                      7
#define AM_REG_MSPI_CFG_SEPIO_M                      0x00000080
#define AM_REG_MSPI_CFG_SEPIO(n)                     (((uint32_t)(n) << 7) & 0x00000080)

// Instruction Size enum   name    =   I8   value   =   0x0   desc    =
// Instruction is 1 byte enum   name    =   I16   value   =   0x1   desc    =
// Instruction is 2 bytes
#define AM_REG_MSPI_CFG_ISIZE_S                      6
#define AM_REG_MSPI_CFG_ISIZE_M                      0x00000040
#define AM_REG_MSPI_CFG_ISIZE(n)                     (((uint32_t)(n) << 6) & 0x00000040)

// Address Size.  Address bytes to send from ADDR register   name    =   A1
// value   =   0x0   desc    =   Send one address byte enum   name    =   A2
// value   =   0x1   desc    =   Send two address bytes enum   name    =   A3
// value   =   0x2   desc    =   Send three address bytes enum   name    =   A4
// value   =   0x3   desc    =   Send four address bytes
#define AM_REG_MSPI_CFG_ASIZE_S                      4
#define AM_REG_MSPI_CFG_ASIZE_M                      0x00000030
#define AM_REG_MSPI_CFG_ASIZE(n)                     (((uint32_t)(n) << 4) & 0x00000030)

// Flash configuration for XIP and AUTO DMA operations. Controls value for SER
// (Slave Enable) for XIP operations and address generation for DMA/XIP modes.
// Also used to configure SPIFRF (frame format).
#define AM_REG_MSPI_CFG_DEVCFG_S                     0
#define AM_REG_MSPI_CFG_DEVCFG_M                     0x0000000F
#define AM_REG_MSPI_CFG_DEVCFG(n)                    (((uint32_t)(n) << 0) & 0x0000000F)
#define AM_REG_MSPI_CFG_DEVCFG_SERIAL0               0x00000001
#define AM_REG_MSPI_CFG_DEVCFG_SERIAL1               0x00000002
#define AM_REG_MSPI_CFG_DEVCFG_DUAL0                 0x00000005
#define AM_REG_MSPI_CFG_DEVCFG_DUAL1                 0x00000006
#define AM_REG_MSPI_CFG_DEVCFG_QUAD0                 0x00000009
#define AM_REG_MSPI_CFG_DEVCFG_QUAD1                 0x0000000A
#define AM_REG_MSPI_CFG_DEVCFG_OCTAL0                0x0000000D
#define AM_REG_MSPI_CFG_DEVCFG_OCTAL1                0x0000000E
#define AM_REG_MSPI_CFG_DEVCFG_QUADPAIRED            0x0000000F
#define AM_REG_MSPI_CFG_DEVCFG_QUADPAIRED_SERIAL     0x00000003

//*****************************************************************************
//
// MSPI_ADDR - MSPI Transfer Address Register
//
//*****************************************************************************
// Optional Address field to send (after optional instruction field) - qualified
// by ASIZE in CMD register.  NOTE:  This register is aliased to DMADEVADDR.
#define AM_REG_MSPI_ADDR_ADDR_S                      0
#define AM_REG_MSPI_ADDR_ADDR_M                      0xFFFFFFFF
#define AM_REG_MSPI_ADDR_ADDR(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MSPI_INSTR - MSPI Transfer Instruction
//
//*****************************************************************************
// Optional Instruction field to send (1st byte) - qualified by ISEND/ISIZE
#define AM_REG_MSPI_INSTR_INSTR_S                    0
#define AM_REG_MSPI_INSTR_INSTR_M                    0x0000FFFF
#define AM_REG_MSPI_INSTR_INSTR(n)                   (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// MSPI_TXFIFO - TX Data FIFO
//
//*****************************************************************************
// Data to be transmitted.  Data should normall be aligned to the LSB (pad the
// upper bits with zeros) unless BIGENDIAN is set.
#define AM_REG_MSPI_TXFIFO_TXFIFO_S                  0
#define AM_REG_MSPI_TXFIFO_TXFIFO_M                  0xFFFFFFFF
#define AM_REG_MSPI_TXFIFO_TXFIFO(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MSPI_RXFIFO - RX Data FIFO
//
//*****************************************************************************
// Receive data.  Data is aligned to the LSB (padded zeros on upper bits) unless
// BIGENDIAN is set.
#define AM_REG_MSPI_RXFIFO_RXFIFO_S                  0
#define AM_REG_MSPI_RXFIFO_RXFIFO_M                  0xFFFFFFFF
#define AM_REG_MSPI_RXFIFO_RXFIFO(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MSPI_TXENTRIES - TX FIFO Entries
//
//*****************************************************************************
// Number of 32-bit words/entries in TX FIFO
#define AM_REG_MSPI_TXENTRIES_TXENTRIES_S            0
#define AM_REG_MSPI_TXENTRIES_TXENTRIES_M            0x0000001F
#define AM_REG_MSPI_TXENTRIES_TXENTRIES(n)           (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// MSPI_RXENTRIES - RX FIFO Entries
//
//*****************************************************************************
// Number of 32-bit words/entries in RX FIFO
#define AM_REG_MSPI_RXENTRIES_RXENTRIES_S            0
#define AM_REG_MSPI_RXENTRIES_RXENTRIES_M            0x0000001F
#define AM_REG_MSPI_RXENTRIES_RXENTRIES(n)           (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// MSPI_THRESHOLD - TX/RX FIFO Threshhold Levels
//
//*****************************************************************************
// Number of entries in TX FIFO that cause RXE interrupt
#define AM_REG_MSPI_THRESHOLD_RXTHRESH_S             8
#define AM_REG_MSPI_THRESHOLD_RXTHRESH_M             0x00001F00
#define AM_REG_MSPI_THRESHOLD_RXTHRESH(n)            (((uint32_t)(n) << 8) & 0x00001F00)

// Number of entries in TX FIFO that cause TXF interrupt
#define AM_REG_MSPI_THRESHOLD_TXTHRESH_S             0
#define AM_REG_MSPI_THRESHOLD_TXTHRESH_M             0x0000001F
#define AM_REG_MSPI_THRESHOLD_TXTHRESH(n)            (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// MSPI_MSPICFG - MSPI Module Configuration
//
//*****************************************************************************
// Peripheral reset.  Master reset to the entire MSPI module (DMA, XIP, and
// transfer state machines).  1=normal operation, 0=in reset.
#define AM_REG_MSPI_MSPICFG_PRSTN_S                  31
#define AM_REG_MSPI_MSPICFG_PRSTN_M                  0x80000000
#define AM_REG_MSPI_MSPICFG_PRSTN(n)                 (((uint32_t)(n) << 31) & 0x80000000)

// IP block reset. Write to 0 to put the transfer module in reset or 1 for
// normal operation.  This may be required after error conditions to clear the
// transfer on the bus.
#define AM_REG_MSPI_MSPICFG_IPRSTN_S                 30
#define AM_REG_MSPI_MSPICFG_IPRSTN_M                 0x40000000
#define AM_REG_MSPI_MSPICFG_IPRSTN(n)                (((uint32_t)(n) << 30) & 0x40000000)

// Reset MSPI FIFO (active high).  1=reset FIFO, 0=normal operation.   May be
// used to manually flush the FIFO in error handling.
#define AM_REG_MSPI_MSPICFG_FIFORESET_S              29
#define AM_REG_MSPI_MSPICFG_FIFORESET_M              0x20000000
#define AM_REG_MSPI_MSPICFG_FIFORESET(n)             (((uint32_t)(n) << 29) & 0x20000000)

// Clock Divider.  Allows dividing 48 MHz base clock by integer multiples.
// Enumerations are provided for common frequency, but any integer divide from
// 48 MHz is allowed.  Odd divide ratios will result in a 33/66 percent duty
// cycle with a long low clock pulse (to allow longer round-trip for read data).
#define AM_REG_MSPI_MSPICFG_CLKDIV_S                 8
#define AM_REG_MSPI_MSPICFG_CLKDIV_M                 0x00003F00
#define AM_REG_MSPI_MSPICFG_CLKDIV(n)                (((uint32_t)(n) << 8) & 0x00003F00)
#define AM_REG_MSPI_MSPICFG_CLKDIV_CLK24             0x00000200
#define AM_REG_MSPI_MSPICFG_CLKDIV_CLK12             0x00000400
#define AM_REG_MSPI_MSPICFG_CLKDIV_CLK6              0x00000800
#define AM_REG_MSPI_MSPICFG_CLKDIV_CLK3              0x00001000
#define AM_REG_MSPI_MSPICFG_CLKDIV_CLK1_5            0x00002000

// Selects which IOM is selected for CQ handshake status.
#define AM_REG_MSPI_MSPICFG_IOMSEL_S                 4
#define AM_REG_MSPI_MSPICFG_IOMSEL_M                 0x00000070
#define AM_REG_MSPI_MSPICFG_IOMSEL(n)                (((uint32_t)(n) << 4) & 0x00000070)
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM0              0x00000000
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM1              0x00000010
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM2              0x00000020
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM3              0x00000030
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM4              0x00000040
#define AM_REG_MSPI_MSPICFG_IOMSEL_IOM5              0x00000050
#define AM_REG_MSPI_MSPICFG_IOMSEL_DISABLED          0x00000070

// Launches TX data a half clock cycle (~10ns) early.  This should normally be
// programmed to zero (NORMAL).
#define AM_REG_MSPI_MSPICFG_TXNEG_S                  3
#define AM_REG_MSPI_MSPICFG_TXNEG_M                  0x00000008
#define AM_REG_MSPI_MSPICFG_TXNEG(n)                 (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_MSPI_MSPICFG_TXNEG_NORMAL             0x00000000
#define AM_REG_MSPI_MSPICFG_TXNEG_NEGEDGE            0x00000008

// Adjusts the RX capture phase to the negedge of the 48MHz internal clock
// (~10ns early).  For normal operation, it is expected that RXNEG will be set
// to 0.
#define AM_REG_MSPI_MSPICFG_RXNEG_S                  2
#define AM_REG_MSPI_MSPICFG_RXNEG_M                  0x00000004
#define AM_REG_MSPI_MSPICFG_RXNEG(n)                 (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MSPI_MSPICFG_RXNEG_NORMAL             0x00000000
#define AM_REG_MSPI_MSPICFG_RXNEG_NEGEDGE            0x00000004

// Controls RX data capture phase.  A setting of 0 (NORMAL) captures read data
// at the normal capture point relative to the internal clock launch point.
// However, to accomodate chip/pad/board delays, a setting of RXCAP of 1 is
// expected to be used to align the capture point with the return data window.
// This bit is used in conjunction with RXNEG to provide 4 unique capture
// points, all about 10ns apart.
#define AM_REG_MSPI_MSPICFG_RXCAP_S                  1
#define AM_REG_MSPI_MSPICFG_RXCAP_M                  0x00000002
#define AM_REG_MSPI_MSPICFG_RXCAP(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MSPI_MSPICFG_RXCAP_NORMAL             0x00000000
#define AM_REG_MSPI_MSPICFG_RXCAP_DELAY              0x00000002

// Enable continuous APB clock.  For power-efficient operation, APBCLK should be
// set to 0.
#define AM_REG_MSPI_MSPICFG_APBCLK_S                 0
#define AM_REG_MSPI_MSPICFG_APBCLK_M                 0x00000001
#define AM_REG_MSPI_MSPICFG_APBCLK(n)                (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MSPI_MSPICFG_APBCLK_DIS               0x00000000
#define AM_REG_MSPI_MSPICFG_APBCLK_EN                0x00000001

//*****************************************************************************
//
// MSPI_PADCFG - MSPI Output Pad Configuration
//
//*****************************************************************************
// Reverse CS connections.  Allows CS1 to be associated with lower data lanes
// and CS0 to be associated with upper data lines
#define AM_REG_MSPI_PADCFG_REVCS_S                   21
#define AM_REG_MSPI_PADCFG_REVCS_M                   0x00200000
#define AM_REG_MSPI_PADCFG_REVCS(n)                  (((uint32_t)(n) << 21) & 0x00200000)

// Data Input pad 3 pin muxing: 0=pad[3] 1=pad[7]
#define AM_REG_MSPI_PADCFG_IN3_S                     20
#define AM_REG_MSPI_PADCFG_IN3_M                     0x00100000
#define AM_REG_MSPI_PADCFG_IN3(n)                    (((uint32_t)(n) << 20) & 0x00100000)

// Data Input pad 2 pin muxing: 0=pad[2] 1=pad[6]
#define AM_REG_MSPI_PADCFG_IN2_S                     19
#define AM_REG_MSPI_PADCFG_IN2_M                     0x00080000
#define AM_REG_MSPI_PADCFG_IN2(n)                    (((uint32_t)(n) << 19) & 0x00080000)

// Data Input pad 1 pin muxing: 0=pad[1] 1=pad[5]
#define AM_REG_MSPI_PADCFG_IN1_S                     18
#define AM_REG_MSPI_PADCFG_IN1_M                     0x00040000
#define AM_REG_MSPI_PADCFG_IN1(n)                    (((uint32_t)(n) << 18) & 0x00040000)

// Data Input pad 0 pin muxing:  0=pad[0] 1=pad[4] 2=pad[1] 3=pad[5]
#define AM_REG_MSPI_PADCFG_IN0_S                     16
#define AM_REG_MSPI_PADCFG_IN0_M                     0x00030000
#define AM_REG_MSPI_PADCFG_IN0(n)                    (((uint32_t)(n) << 16) & 0x00030000)

// Output pad 7 configuration.  0=data[7] 1=data[3]
#define AM_REG_MSPI_PADCFG_OUT7_S                    4
#define AM_REG_MSPI_PADCFG_OUT7_M                    0x00000010
#define AM_REG_MSPI_PADCFG_OUT7(n)                   (((uint32_t)(n) << 4) & 0x00000010)

// Output pad 6 configuration.  0=data[6] 1=data[2]
#define AM_REG_MSPI_PADCFG_OUT6_S                    3
#define AM_REG_MSPI_PADCFG_OUT6_M                    0x00000008
#define AM_REG_MSPI_PADCFG_OUT6(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// Output pad 5 configuration.  0=data[5] 1=data[1]
#define AM_REG_MSPI_PADCFG_OUT5_S                    2
#define AM_REG_MSPI_PADCFG_OUT5_M                    0x00000004
#define AM_REG_MSPI_PADCFG_OUT5(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// Output pad 4 configuration.  0=data[4] 1=data[0]
#define AM_REG_MSPI_PADCFG_OUT4_S                    1
#define AM_REG_MSPI_PADCFG_OUT4_M                    0x00000002
#define AM_REG_MSPI_PADCFG_OUT4(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// Output pad 3 configuration.  0=data[3] 1=CLK
#define AM_REG_MSPI_PADCFG_OUT3_S                    0
#define AM_REG_MSPI_PADCFG_OUT3_M                    0x00000001
#define AM_REG_MSPI_PADCFG_OUT3(n)                   (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_PADOUTEN - MSPI Output Enable Pad Configuration
//
//*****************************************************************************
// Output pad enable configuration.  Indicates which pads should be driven.
// Bits [3:0] are Quad0 data, [7:4] are Quad1 data, and [8] is clock.
#define AM_REG_MSPI_PADOUTEN_OUTEN_S                 0
#define AM_REG_MSPI_PADOUTEN_OUTEN_M                 0x000001FF
#define AM_REG_MSPI_PADOUTEN_OUTEN(n)                (((uint32_t)(n) << 0) & 0x000001FF)
#define AM_REG_MSPI_PADOUTEN_OUTEN_QUAD0             0x0000010F
#define AM_REG_MSPI_PADOUTEN_OUTEN_QUAD1             0x000001F0
#define AM_REG_MSPI_PADOUTEN_OUTEN_OCTAL             0x000001FF
#define AM_REG_MSPI_PADOUTEN_OUTEN_SERIAL0           0x00000103

//*****************************************************************************
//
// MSPI_FLASH - Configuration for XIP/DMA support of SPI flash modules.
//
//*****************************************************************************
// Read command sent to flash for DMA/XIP operations
#define AM_REG_MSPI_FLASH_READINSTR_S                24
#define AM_REG_MSPI_FLASH_READINSTR_M                0xFF000000
#define AM_REG_MSPI_FLASH_READINSTR(n)               (((uint32_t)(n) << 24) & 0xFF000000)

// Write command sent for DMA operations
#define AM_REG_MSPI_FLASH_WRITEINSTR_S               16
#define AM_REG_MSPI_FLASH_WRITEINSTR_M               0x00FF0000
#define AM_REG_MSPI_FLASH_WRITEINSTR(n)              (((uint32_t)(n) << 16) & 0x00FF0000)

// Reserved.  Set to 0x0
#define AM_REG_MSPI_FLASH_XIPMIXED_S                 8
#define AM_REG_MSPI_FLASH_XIPMIXED_M                 0x00000700
#define AM_REG_MSPI_FLASH_XIPMIXED(n)                (((uint32_t)(n) << 8) & 0x00000700)

// Indicates whether XIP/AUTO DMA operations should send an instruction (see
// READINSTR field and ISIZE field in CFG)
#define AM_REG_MSPI_FLASH_XIPSENDI_S                 7
#define AM_REG_MSPI_FLASH_XIPSENDI_M                 0x00000080
#define AM_REG_MSPI_FLASH_XIPSENDI(n)                (((uint32_t)(n) << 7) & 0x00000080)

// Indicates whether XIP/AUTO DMA operations should send an an address phase
// (see DMADEVADDR register and ASIZE field in CFG)
#define AM_REG_MSPI_FLASH_XIPSENDA_S                 6
#define AM_REG_MSPI_FLASH_XIPSENDA_M                 0x00000040
#define AM_REG_MSPI_FLASH_XIPSENDA(n)                (((uint32_t)(n) << 6) & 0x00000040)

// Indicates whether XIP/AUTO DMA operations should enable TX->RX turnaround
// cycles
#define AM_REG_MSPI_FLASH_XIPENTURN_S                5
#define AM_REG_MSPI_FLASH_XIPENTURN_M                0x00000020
#define AM_REG_MSPI_FLASH_XIPENTURN(n)               (((uint32_t)(n) << 5) & 0x00000020)

// Indicates whether XIP/AUTO DMA data transfers are in big or little endian
// format
#define AM_REG_MSPI_FLASH_XIPBIGENDIAN_S             4
#define AM_REG_MSPI_FLASH_XIPBIGENDIAN_M             0x00000010
#define AM_REG_MSPI_FLASH_XIPBIGENDIAN(n)            (((uint32_t)(n) << 4) & 0x00000010)

// Controls transmission of Micron XIP acknowledge cycles (Micron Flash devices
// only)
#define AM_REG_MSPI_FLASH_XIPACK_S                   2
#define AM_REG_MSPI_FLASH_XIPACK_M                   0x0000000C
#define AM_REG_MSPI_FLASH_XIPACK(n)                  (((uint32_t)(n) << 2) & 0x0000000C)
#define AM_REG_MSPI_FLASH_XIPACK_NOACK               0x00000000
#define AM_REG_MSPI_FLASH_XIPACK_ACK                 0x00000008
#define AM_REG_MSPI_FLASH_XIPACK_TERMINATE           0x0000000C

// Enable the XIP (eXecute In Place) function which effectively enables the
// address decoding of the MSPI device in the flash/cache address space at
// address 0x04000000-0x07FFFFFF.
#define AM_REG_MSPI_FLASH_XIPEN_S                    0
#define AM_REG_MSPI_FLASH_XIPEN_M                    0x00000001
#define AM_REG_MSPI_FLASH_XIPEN(n)                   (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_SCRAMBLING - External Flash Scrambling Controls
//
//*****************************************************************************
// Enables Data Scrambling Region.  When 1 reads and writes to the range will be
// scrambled.  When 0, data will be read/written unmodified.  Address range is
// specified in 64K granularity and the START/END ranges are included within the
// range.
#define AM_REG_MSPI_SCRAMBLING_SCRENABLE_S           31
#define AM_REG_MSPI_SCRAMBLING_SCRENABLE_M           0x80000000
#define AM_REG_MSPI_SCRAMBLING_SCRENABLE(n)          (((uint32_t)(n) << 31) & 0x80000000)

// Scrambling region end address [25:16] (64K block granularity).  The END block
// is the LAST block included in the scrambled address range.
#define AM_REG_MSPI_SCRAMBLING_SCREND_S              16
#define AM_REG_MSPI_SCRAMBLING_SCREND_M              0x03FF0000
#define AM_REG_MSPI_SCRAMBLING_SCREND(n)             (((uint32_t)(n) << 16) & 0x03FF0000)

// Scrambling region start address [25:16] (64K block granularity).  The START
// block is the FIRST block included in the scrambled address range.
#define AM_REG_MSPI_SCRAMBLING_SCRSTART_S            0
#define AM_REG_MSPI_SCRAMBLING_SCRSTART_M            0x000003FF
#define AM_REG_MSPI_SCRAMBLING_SCRSTART(n)           (((uint32_t)(n) << 0) & 0x000003FF)

//*****************************************************************************
//
// MSPI_DMACFG - DMA Configuration Register
//
//*****************************************************************************
// Power off MSPI domain upon completion of DMA operation.
#define AM_REG_MSPI_DMACFG_DMAPWROFF_S               18
#define AM_REG_MSPI_DMACFG_DMAPWROFF_M               0x00040000
#define AM_REG_MSPI_DMACFG_DMAPWROFF(n)              (((uint32_t)(n) << 18) & 0x00040000)

// Sets the Priority of the DMA request
#define AM_REG_MSPI_DMACFG_DMAPRI_S                  3
#define AM_REG_MSPI_DMACFG_DMAPRI_M                  0x00000018
#define AM_REG_MSPI_DMACFG_DMAPRI(n)                 (((uint32_t)(n) << 3) & 0x00000018)
#define AM_REG_MSPI_DMACFG_DMAPRI_LOW                0x00000000
#define AM_REG_MSPI_DMACFG_DMAPRI_HIGH               0x00000008
#define AM_REG_MSPI_DMACFG_DMAPRI_AUTO               0x00000010

// Direction
#define AM_REG_MSPI_DMACFG_DMADIR_S                  2
#define AM_REG_MSPI_DMACFG_DMADIR_M                  0x00000004
#define AM_REG_MSPI_DMACFG_DMADIR(n)                 (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MSPI_DMACFG_DMADIR_P2M                0x00000000
#define AM_REG_MSPI_DMACFG_DMADIR_M2P                0x00000004

// DMA Enable. Setting this bit to EN will start the DMA operation
#define AM_REG_MSPI_DMACFG_DMAEN_S                   0
#define AM_REG_MSPI_DMACFG_DMAEN_M                   0x00000003
#define AM_REG_MSPI_DMACFG_DMAEN(n)                  (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_MSPI_DMACFG_DMAEN_DIS                 0x00000000
#define AM_REG_MSPI_DMACFG_DMAEN_EN                  0x00000003

//*****************************************************************************
//
// MSPI_DMASTAT - DMA Status Register
//
//*****************************************************************************
// Scrambling Access Alignment Error. This active high bit signals that a
// scrambling operation was specified for a non-word aligned DEVADDR.
#define AM_REG_MSPI_DMASTAT_SCRERR_S                 3
#define AM_REG_MSPI_DMASTAT_SCRERR_M                 0x00000008
#define AM_REG_MSPI_DMASTAT_SCRERR(n)                (((uint32_t)(n) << 3) & 0x00000008)

// DMA Error. This active high bit signals that an error was encountered during
// the DMA operation.
#define AM_REG_MSPI_DMASTAT_DMAERR_S                 2
#define AM_REG_MSPI_DMASTAT_DMAERR_M                 0x00000004
#define AM_REG_MSPI_DMASTAT_DMAERR(n)                (((uint32_t)(n) << 2) & 0x00000004)

// DMA Transfer Complete. This signals the end of the DMA operation.
#define AM_REG_MSPI_DMASTAT_DMACPL_S                 1
#define AM_REG_MSPI_DMASTAT_DMACPL_M                 0x00000002
#define AM_REG_MSPI_DMASTAT_DMACPL(n)                (((uint32_t)(n) << 1) & 0x00000002)

// DMA Transfer In Progress indicator.  1 will indicate that a DMA transfer is
// active.  The DMA transfer may be waiting on data, transferring data, or
// waiting for priority.  All of these will be indicated with a 1.  A 0 will
// indicate that the DMA is fully complete and no further transactions will be
// done.
#define AM_REG_MSPI_DMASTAT_DMATIP_S                 0
#define AM_REG_MSPI_DMASTAT_DMATIP_M                 0x00000001
#define AM_REG_MSPI_DMASTAT_DMATIP(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_DMATARGADDR - DMA Target Address Register
//
//*****************************************************************************
// Target byte address for source of DMA (either read or write). In cases of
// non-word aligned addresses, the DMA logic will take care for ensuring only
// the target bytes are read/written.
#define AM_REG_MSPI_DMATARGADDR_TARGADDR_S           0
#define AM_REG_MSPI_DMATARGADDR_TARGADDR_M           0xFFFFFFFF
#define AM_REG_MSPI_DMATARGADDR_TARGADDR(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MSPI_DMADEVADDR - DMA Device Address Register
//
//*****************************************************************************
// SPI Device address for automated DMA transactions (both read and write).
#define AM_REG_MSPI_DMADEVADDR_DEVADDR_S             0
#define AM_REG_MSPI_DMADEVADDR_DEVADDR_M             0xFFFFFFFF
#define AM_REG_MSPI_DMADEVADDR_DEVADDR(n)            (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MSPI_DMATOTCOUNT - DMA Total Transfer Count
//
//*****************************************************************************
// Total Transfer Count in bytes.
#define AM_REG_MSPI_DMATOTCOUNT_TOTCOUNT_S           0
#define AM_REG_MSPI_DMATOTCOUNT_TOTCOUNT_M           0x0000FFFF
#define AM_REG_MSPI_DMATOTCOUNT_TOTCOUNT(n)          (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// MSPI_DMABCOUNT - DMA BYTE Transfer Count
//
//*****************************************************************************
// Burst transfer size in bytes. This is the number of bytes transferred when a
// FIFO trigger event occurs.  Recommended values are 16 or 32.
#define AM_REG_MSPI_DMABCOUNT_BCOUNT_S               0
#define AM_REG_MSPI_DMABCOUNT_BCOUNT_M               0x000000FF
#define AM_REG_MSPI_DMABCOUNT_BCOUNT(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// MSPI_DMATHRESH - DMA Transmit Trigger Threshhold
//
//*****************************************************************************
// DMA transfer FIFO level trigger.  For read operations, DMA is triggered when
// the FIFO level is greater than this value.  For write operations, DMA is
// triggered when the FIFO level is less than this level.  Each DMA operation
// will consist of BCOUNT bytes.
#define AM_REG_MSPI_DMATHRESH_DMATHRESH_S            0
#define AM_REG_MSPI_DMATHRESH_DMATHRESH_M            0x0000000F
#define AM_REG_MSPI_DMATHRESH_DMATHRESH(n)           (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// MSPI_CQCFG - Command Queue Configuration Register
//
//*****************************************************************************
// Eanble clear of CQMASK after each pause operation.  This may be useful when
// using software flags to pause CQ.
#define AM_REG_MSPI_CQCFG_CQAUTOCLEARMASK_S          3
#define AM_REG_MSPI_CQCFG_CQAUTOCLEARMASK_M          0x00000008
#define AM_REG_MSPI_CQCFG_CQAUTOCLEARMASK(n)         (((uint32_t)(n) << 3) & 0x00000008)

// Power off MSPI domain upon completion of DMA operation.
#define AM_REG_MSPI_CQCFG_CQPWROFF_S                 2
#define AM_REG_MSPI_CQCFG_CQPWROFF_M                 0x00000004
#define AM_REG_MSPI_CQCFG_CQPWROFF(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Sets the Priority of the command queue dma request
#define AM_REG_MSPI_CQCFG_CQPRI_S                    1
#define AM_REG_MSPI_CQCFG_CQPRI_M                    0x00000002
#define AM_REG_MSPI_CQCFG_CQPRI(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MSPI_CQCFG_CQPRI_LOW                  0x00000000
#define AM_REG_MSPI_CQCFG_CQPRI_HIGH                 0x00000002

// Command queue enable. When set, will enable the processing of the command
// queue
#define AM_REG_MSPI_CQCFG_CQEN_S                     0
#define AM_REG_MSPI_CQCFG_CQEN_M                     0x00000001
#define AM_REG_MSPI_CQCFG_CQEN(n)                    (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MSPI_CQCFG_CQEN_DIS                   0x00000000
#define AM_REG_MSPI_CQCFG_CQEN_EN                    0x00000001

//*****************************************************************************
//
// MSPI_CQADDR - CQ Target Read Address Register
//
//*****************************************************************************
// Address of command queue buffer in SRAM or flash.  The buffer address must be
// aligned to a word boundary.
#define AM_REG_MSPI_CQADDR_CQADDR_S                  0
#define AM_REG_MSPI_CQADDR_CQADDR_M                  0x1FFFFFFF
#define AM_REG_MSPI_CQADDR_CQADDR(n)                 (((uint32_t)(n) << 0) & 0x1FFFFFFF)

//*****************************************************************************
//
// MSPI_CQSTAT - Command Queue Status Register
//
//*****************************************************************************
// Command queue is currently paused status.
#define AM_REG_MSPI_CQSTAT_CQPAUSED_S                3
#define AM_REG_MSPI_CQSTAT_CQPAUSED_M                0x00000008
#define AM_REG_MSPI_CQSTAT_CQPAUSED(n)               (((uint32_t)(n) << 3) & 0x00000008)

// Command queue processing  Error. This active high bit signals that an error
// was encountered during the CQ  operation.
#define AM_REG_MSPI_CQSTAT_CQERR_S                   2
#define AM_REG_MSPI_CQSTAT_CQERR_M                   0x00000004
#define AM_REG_MSPI_CQSTAT_CQERR(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// Command queue operation Complete. This signals the end of the command queue
// operation.
#define AM_REG_MSPI_CQSTAT_CQCPL_S                   1
#define AM_REG_MSPI_CQSTAT_CQCPL_M                   0x00000002
#define AM_REG_MSPI_CQSTAT_CQCPL(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// Command queue Transfer In Progress indicator.  1 will indicate that a CQ
// transfer is active and this will remain active even when paused waiting for
// external event.
#define AM_REG_MSPI_CQSTAT_CQTIP_S                   0
#define AM_REG_MSPI_CQSTAT_CQTIP_M                   0x00000001
#define AM_REG_MSPI_CQSTAT_CQTIP(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MSPI_CQFLAGS - Command Queue Flag Register
//
//*****************************************************************************
// Current flag status (read-only).  Bits [7:0] are software controllable and
// bits [15:8] are hardware status.
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_S                0
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_M                0x0000FFFF
#define AM_REG_MSPI_CQFLAGS_CQFLAGS(n)               (((uint32_t)(n) << 0) & 0x0000FFFF)
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_STOP             0x00008000
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_CQIDX            0x00004000
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_DMACPL           0x00000800
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_CMDCPL           0x00000400
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM1READY        0x00000200
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM0READY        0x00000100
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG7          0x00000080
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG6          0x00000040
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG5          0x00000020
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG4          0x00000010
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG3          0x00000008
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG2          0x00000004
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG1          0x00000002
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_SWFLAG0          0x00000001
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM1START        0x00000002
#define AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM0START        0x00000001

//*****************************************************************************
//
// MSPI_CQSETCLEAR - Command Queue Flag Set/Clear Register
//
//*****************************************************************************
// Clear CQFlag status bits.
#define AM_REG_MSPI_CQSETCLEAR_CQFCLR_S              16
#define AM_REG_MSPI_CQSETCLEAR_CQFCLR_M              0x00FF0000
#define AM_REG_MSPI_CQSETCLEAR_CQFCLR(n)             (((uint32_t)(n) << 16) & 0x00FF0000)

// Toggle CQFlag status bits
#define AM_REG_MSPI_CQSETCLEAR_CQFTOGGLE_S           8
#define AM_REG_MSPI_CQSETCLEAR_CQFTOGGLE_M           0x0000FF00
#define AM_REG_MSPI_CQSETCLEAR_CQFTOGGLE(n)          (((uint32_t)(n) << 8) & 0x0000FF00)

// Set CQFlag status bits.  Set has priority over clear if both are high.
#define AM_REG_MSPI_CQSETCLEAR_CQFSET_S              0
#define AM_REG_MSPI_CQSETCLEAR_CQFSET_M              0x000000FF
#define AM_REG_MSPI_CQSETCLEAR_CQFSET(n)             (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// MSPI_CQPAUSE - Command Queue Pause Mask Register
//
//*****************************************************************************
// CQ will pause processing until all specified events are satisfied.
#define AM_REG_MSPI_CQPAUSE_CQMASK_S                 0
#define AM_REG_MSPI_CQPAUSE_CQMASK_M                 0x0000FFFF
#define AM_REG_MSPI_CQPAUSE_CQMASK(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)
#define AM_REG_MSPI_CQPAUSE_CQMASK_STOP              0x00008000
#define AM_REG_MSPI_CQPAUSE_CQMASK_CQIDX             0x00004000
#define AM_REG_MSPI_CQPAUSE_CQMASK_DMACPL            0x00000800
#define AM_REG_MSPI_CQPAUSE_CQMASK_CMDCPL            0x00000400
#define AM_REG_MSPI_CQPAUSE_CQMASK_IOM1READY         0x00000200
#define AM_REG_MSPI_CQPAUSE_CQMASK_IOM0READY         0x00000100
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG7           0x00000080
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG6           0x00000040
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG5           0x00000020
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG4           0x00000010
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG3           0x00000008
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG2           0x00000004
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG1           0x00000002
#define AM_REG_MSPI_CQPAUSE_CQMASK_SWFLAG0           0x00000001
#define AM_REG_MSPI_CQPAUSE_CQMASK_IOM1START         0x00000002
#define AM_REG_MSPI_CQPAUSE_CQMASK_IOM0START         0x00000001

//*****************************************************************************
//
// MSPI_CQCURIDX - Command Queue Current Index
//
//*****************************************************************************
// Can be used to indicate the current position of the command  queue by having
// CQ operations write this field.  A CQ hardware status flag indicates when
// CURIDX and ENDIDX are not equal, allowing SW to pause the CQ processing until
// the end index is updated.
#define AM_REG_MSPI_CQCURIDX_CQCURIDX_S              0
#define AM_REG_MSPI_CQCURIDX_CQCURIDX_M              0x000000FF
#define AM_REG_MSPI_CQCURIDX_CQCURIDX(n)             (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// MSPI_CQENDIDX - Command Queue End Index
//
//*****************************************************************************
// Can be used to indicate the end position of the command queue.  A CQ hardware
// status bit indices when CURIDX != ENDIDX so that the CQ can be paused when it
// reaches the end pointer.
#define AM_REG_MSPI_CQENDIDX_CQENDIDX_S              0
#define AM_REG_MSPI_CQENDIDX_CQENDIDX_M              0x000000FF
#define AM_REG_MSPI_CQENDIDX_CQENDIDX(n)             (((uint32_t)(n) << 0) & 0x000000FF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_MSPI_H
