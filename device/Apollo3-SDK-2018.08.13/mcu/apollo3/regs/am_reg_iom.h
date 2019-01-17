//*****************************************************************************
//
//  am_reg_iom.h
//! @file
//!
//! @brief Register macros for the IOM module
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
#ifndef AM_REG_IOM_H
#define AM_REG_IOM_H

//*****************************************************************************
//
// Instance finder. (6 instance(s) available)
//
//*****************************************************************************
#define AM_REG_IOM_NUM_MODULES                       6
#define AM_REG_IOMn(n) \
    (REG_IOM_BASEADDR + 0x00001000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_IOM_FIFO_O                            0x00000000
#define AM_REG_IOM_FIFOPTR_O                         0x00000100
#define AM_REG_IOM_FIFOTHR_O                         0x00000104
#define AM_REG_IOM_FIFOPOP_O                         0x00000108
#define AM_REG_IOM_FIFOPUSH_O                        0x0000010C
#define AM_REG_IOM_FIFOCTRL_O                        0x00000110
#define AM_REG_IOM_FIFOLOC_O                         0x00000114
#define AM_REG_IOM_CLKCFG_O                          0x00000210
#define AM_REG_IOM_SUBMODCTRL_O                      0x00000214
#define AM_REG_IOM_CMD_O                             0x00000218
#define AM_REG_IOM_CMDRPT_O                          0x0000021C
#define AM_REG_IOM_OFFSETHI_O                        0x00000220
#define AM_REG_IOM_CMDSTAT_O                         0x00000224
#define AM_REG_IOM_DMATRIGEN_O                       0x00000240
#define AM_REG_IOM_DMATRIGSTAT_O                     0x00000244
#define AM_REG_IOM_DMACFG_O                          0x00000280
#define AM_REG_IOM_DMATOTCOUNT_O                     0x00000288
#define AM_REG_IOM_DMATARGADDR_O                     0x0000028C
#define AM_REG_IOM_DMASTAT_O                         0x00000290
#define AM_REG_IOM_CQCFG_O                           0x00000294
#define AM_REG_IOM_CQADDR_O                          0x00000298
#define AM_REG_IOM_CQSTAT_O                          0x0000029C
#define AM_REG_IOM_CQFLAGS_O                         0x000002A0
#define AM_REG_IOM_CQSETCLEAR_O                      0x000002A4
#define AM_REG_IOM_CQPAUSEEN_O                       0x000002A8
#define AM_REG_IOM_CQCURIDX_O                        0x000002AC
#define AM_REG_IOM_CQENDIDX_O                        0x000002B0
#define AM_REG_IOM_STATUS_O                          0x000002B4
#define AM_REG_IOM_MSPICFG_O                         0x00000300
#define AM_REG_IOM_MI2CCFG_O                         0x00000400
#define AM_REG_IOM_DEVCFG_O                          0x00000404
#define AM_REG_IOM_IOMDBG_O                          0x00000410
#define AM_REG_IOM_INTEN_O                           0x00000200
#define AM_REG_IOM_INTSTAT_O                         0x00000204
#define AM_REG_IOM_INTCLR_O                          0x00000208
#define AM_REG_IOM_INTSET_O                          0x0000020C

//*****************************************************************************
//
// IOM_INTEN - IO Master Interrupts: Enable
//
//*****************************************************************************
// Error during command queue operations
#define AM_REG_IOM_INTEN_CQERR_S                     14
#define AM_REG_IOM_INTEN_CQERR_M                     0x00004000
#define AM_REG_IOM_INTEN_CQERR(n)                    (((uint32_t)(n) << 14) & 0x00004000)

// CQ write operation performed a register write with the register address bit 0
// set to 1.  The low address bits in the CQ address fields are unused and bit 0
// can be used to trigger an interrupt to indicate when this register write is
// performed by the CQ operation.
#define AM_REG_IOM_INTEN_CQUPD_S                     13
#define AM_REG_IOM_INTEN_CQUPD_M                     0x00002000
#define AM_REG_IOM_INTEN_CQUPD(n)                    (((uint32_t)(n) << 13) & 0x00002000)

// Command queue is paused due to an active event enabled in the PAUSEEN
// register.  The interrupt is posted when the event is enabled within the
// PAUSEEN register, the mask is active in the CQIRQMASK field and the event
// occurs.
#define AM_REG_IOM_INTEN_CQPAUSED_S                  12
#define AM_REG_IOM_INTEN_CQPAUSED_M                  0x00001000
#define AM_REG_IOM_INTEN_CQPAUSED(n)                 (((uint32_t)(n) << 12) & 0x00001000)

// DMA Error encountered during the processing of the DMA command.  The DMA
// error could occur when the memory access specified in the DMA operation is
// not available or incorrectly specified.
#define AM_REG_IOM_INTEN_DERR_S                      11
#define AM_REG_IOM_INTEN_DERR_M                      0x00000800
#define AM_REG_IOM_INTEN_DERR(n)                     (((uint32_t)(n) << 11) & 0x00000800)

// DMA Complete. Processing of the DMA operation has completed and the DMA
// submodule is returned into the idle state
#define AM_REG_IOM_INTEN_DCMP_S                      10
#define AM_REG_IOM_INTEN_DCMP_M                      0x00000400
#define AM_REG_IOM_INTEN_DCMP(n)                     (((uint32_t)(n) << 10) & 0x00000400)

// Arbitration loss interrupt. Asserted when arbitration is enabled and has been
// lost to another master on the bus.
#define AM_REG_IOM_INTEN_ARB_S                       9
#define AM_REG_IOM_INTEN_ARB_M                       0x00000200
#define AM_REG_IOM_INTEN_ARB(n)                      (((uint32_t)(n) << 9) & 0x00000200)

// STOP command interrupt. Asserted when another master on the bus has signaled
// a STOP command.
#define AM_REG_IOM_INTEN_STOP_S                      8
#define AM_REG_IOM_INTEN_STOP_M                      0x00000100
#define AM_REG_IOM_INTEN_STOP(n)                     (((uint32_t)(n) << 8) & 0x00000100)

// START command interrupt. Asserted when another master on the bus has signaled
// a START command.
#define AM_REG_IOM_INTEN_START_S                     7
#define AM_REG_IOM_INTEN_START_M                     0x00000080
#define AM_REG_IOM_INTEN_START(n)                    (((uint32_t)(n) << 7) & 0x00000080)

// illegal command interrupt. Asserted when a command is written when an active
// command is in progress.
#define AM_REG_IOM_INTEN_ICMD_S                      6
#define AM_REG_IOM_INTEN_ICMD_M                      0x00000040
#define AM_REG_IOM_INTEN_ICMD(n)                     (((uint32_t)(n) << 6) & 0x00000040)

// illegal FIFO access interrupt. Asserted when there is a overflow or underflow
// event
#define AM_REG_IOM_INTEN_IACC_S                      5
#define AM_REG_IOM_INTEN_IACC_M                      0x00000020
#define AM_REG_IOM_INTEN_IACC(n)                     (((uint32_t)(n) << 5) & 0x00000020)

// I2C NAK interrupt. Asserted when an unexpected NAK has been received on the
// I2C bus.
#define AM_REG_IOM_INTEN_NAK_S                       4
#define AM_REG_IOM_INTEN_NAK_M                       0x00000010
#define AM_REG_IOM_INTEN_NAK(n)                      (((uint32_t)(n) << 4) & 0x00000010)

// Write FIFO Overflow interrupt. This occurs when software tries to write to a
// full fifo.  The current operation does not stop.
#define AM_REG_IOM_INTEN_FOVFL_S                     3
#define AM_REG_IOM_INTEN_FOVFL_M                     0x00000008
#define AM_REG_IOM_INTEN_FOVFL(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// Read FIFO Underflow interrupt. This occurs when software tries to pop from an
// empty fifo.
#define AM_REG_IOM_INTEN_FUNDFL_S                    2
#define AM_REG_IOM_INTEN_FUNDFL_M                    0x00000004
#define AM_REG_IOM_INTEN_FUNDFL(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// FIFO Threshold interrupt. For write operations, asserted when the number of
// free bytes in the write FIFO equals or exceeds the WTHR field. For read
// operations, asserted when the number of valid bytes in the read FIFO equals
// of exceeds the value set in the RTHR field.
#define AM_REG_IOM_INTEN_THR_S                       1
#define AM_REG_IOM_INTEN_THR_M                       0x00000002
#define AM_REG_IOM_INTEN_THR(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// Command Complete interrupt. Asserted when the current operation has
// completed.   For repeated commands, this will only be asserted when the final
// repeated command is completed.
#define AM_REG_IOM_INTEN_CMDCMP_S                    0
#define AM_REG_IOM_INTEN_CMDCMP_M                    0x00000001
#define AM_REG_IOM_INTEN_CMDCMP(n)                   (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_INTSTAT - IO Master Interrupts: Status
//
//*****************************************************************************
// Error during command queue operations
#define AM_REG_IOM_INTSTAT_CQERR_S                   14
#define AM_REG_IOM_INTSTAT_CQERR_M                   0x00004000
#define AM_REG_IOM_INTSTAT_CQERR(n)                  (((uint32_t)(n) << 14) & 0x00004000)

// CQ write operation performed a register write with the register address bit 0
// set to 1.  The low address bits in the CQ address fields are unused and bit 0
// can be used to trigger an interrupt to indicate when this register write is
// performed by the CQ operation.
#define AM_REG_IOM_INTSTAT_CQUPD_S                   13
#define AM_REG_IOM_INTSTAT_CQUPD_M                   0x00002000
#define AM_REG_IOM_INTSTAT_CQUPD(n)                  (((uint32_t)(n) << 13) & 0x00002000)

// Command queue is paused due to an active event enabled in the PAUSEEN
// register.  The interrupt is posted when the event is enabled within the
// PAUSEEN register, the mask is active in the CQIRQMASK field and the event
// occurs.
#define AM_REG_IOM_INTSTAT_CQPAUSED_S                12
#define AM_REG_IOM_INTSTAT_CQPAUSED_M                0x00001000
#define AM_REG_IOM_INTSTAT_CQPAUSED(n)               (((uint32_t)(n) << 12) & 0x00001000)

// DMA Error encountered during the processing of the DMA command.  The DMA
// error could occur when the memory access specified in the DMA operation is
// not available or incorrectly specified.
#define AM_REG_IOM_INTSTAT_DERR_S                    11
#define AM_REG_IOM_INTSTAT_DERR_M                    0x00000800
#define AM_REG_IOM_INTSTAT_DERR(n)                   (((uint32_t)(n) << 11) & 0x00000800)

// DMA Complete. Processing of the DMA operation has completed and the DMA
// submodule is returned into the idle state
#define AM_REG_IOM_INTSTAT_DCMP_S                    10
#define AM_REG_IOM_INTSTAT_DCMP_M                    0x00000400
#define AM_REG_IOM_INTSTAT_DCMP(n)                   (((uint32_t)(n) << 10) & 0x00000400)

// Arbitration loss interrupt. Asserted when arbitration is enabled and has been
// lost to another master on the bus.
#define AM_REG_IOM_INTSTAT_ARB_S                     9
#define AM_REG_IOM_INTSTAT_ARB_M                     0x00000200
#define AM_REG_IOM_INTSTAT_ARB(n)                    (((uint32_t)(n) << 9) & 0x00000200)

// STOP command interrupt. Asserted when another master on the bus has signaled
// a STOP command.
#define AM_REG_IOM_INTSTAT_STOP_S                    8
#define AM_REG_IOM_INTSTAT_STOP_M                    0x00000100
#define AM_REG_IOM_INTSTAT_STOP(n)                   (((uint32_t)(n) << 8) & 0x00000100)

// START command interrupt. Asserted when another master on the bus has signaled
// a START command.
#define AM_REG_IOM_INTSTAT_START_S                   7
#define AM_REG_IOM_INTSTAT_START_M                   0x00000080
#define AM_REG_IOM_INTSTAT_START(n)                  (((uint32_t)(n) << 7) & 0x00000080)

// illegal command interrupt. Asserted when a command is written when an active
// command is in progress.
#define AM_REG_IOM_INTSTAT_ICMD_S                    6
#define AM_REG_IOM_INTSTAT_ICMD_M                    0x00000040
#define AM_REG_IOM_INTSTAT_ICMD(n)                   (((uint32_t)(n) << 6) & 0x00000040)

// illegal FIFO access interrupt. Asserted when there is a overflow or underflow
// event
#define AM_REG_IOM_INTSTAT_IACC_S                    5
#define AM_REG_IOM_INTSTAT_IACC_M                    0x00000020
#define AM_REG_IOM_INTSTAT_IACC(n)                   (((uint32_t)(n) << 5) & 0x00000020)

// I2C NAK interrupt. Asserted when an unexpected NAK has been received on the
// I2C bus.
#define AM_REG_IOM_INTSTAT_NAK_S                     4
#define AM_REG_IOM_INTSTAT_NAK_M                     0x00000010
#define AM_REG_IOM_INTSTAT_NAK(n)                    (((uint32_t)(n) << 4) & 0x00000010)

// Write FIFO Overflow interrupt. This occurs when software tries to write to a
// full fifo.  The current operation does not stop.
#define AM_REG_IOM_INTSTAT_FOVFL_S                   3
#define AM_REG_IOM_INTSTAT_FOVFL_M                   0x00000008
#define AM_REG_IOM_INTSTAT_FOVFL(n)                  (((uint32_t)(n) << 3) & 0x00000008)

// Read FIFO Underflow interrupt. This occurs when software tries to pop from an
// empty fifo.
#define AM_REG_IOM_INTSTAT_FUNDFL_S                  2
#define AM_REG_IOM_INTSTAT_FUNDFL_M                  0x00000004
#define AM_REG_IOM_INTSTAT_FUNDFL(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// FIFO Threshold interrupt. For write operations, asserted when the number of
// free bytes in the write FIFO equals or exceeds the WTHR field. For read
// operations, asserted when the number of valid bytes in the read FIFO equals
// of exceeds the value set in the RTHR field.
#define AM_REG_IOM_INTSTAT_THR_S                     1
#define AM_REG_IOM_INTSTAT_THR_M                     0x00000002
#define AM_REG_IOM_INTSTAT_THR(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// Command Complete interrupt. Asserted when the current operation has
// completed.   For repeated commands, this will only be asserted when the final
// repeated command is completed.
#define AM_REG_IOM_INTSTAT_CMDCMP_S                  0
#define AM_REG_IOM_INTSTAT_CMDCMP_M                  0x00000001
#define AM_REG_IOM_INTSTAT_CMDCMP(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_INTCLR - IO Master Interrupts: Clear
//
//*****************************************************************************
// Error during command queue operations
#define AM_REG_IOM_INTCLR_CQERR_S                    14
#define AM_REG_IOM_INTCLR_CQERR_M                    0x00004000
#define AM_REG_IOM_INTCLR_CQERR(n)                   (((uint32_t)(n) << 14) & 0x00004000)

// CQ write operation performed a register write with the register address bit 0
// set to 1.  The low address bits in the CQ address fields are unused and bit 0
// can be used to trigger an interrupt to indicate when this register write is
// performed by the CQ operation.
#define AM_REG_IOM_INTCLR_CQUPD_S                    13
#define AM_REG_IOM_INTCLR_CQUPD_M                    0x00002000
#define AM_REG_IOM_INTCLR_CQUPD(n)                   (((uint32_t)(n) << 13) & 0x00002000)

// Command queue is paused due to an active event enabled in the PAUSEEN
// register.  The interrupt is posted when the event is enabled within the
// PAUSEEN register, the mask is active in the CQIRQMASK field and the event
// occurs.
#define AM_REG_IOM_INTCLR_CQPAUSED_S                 12
#define AM_REG_IOM_INTCLR_CQPAUSED_M                 0x00001000
#define AM_REG_IOM_INTCLR_CQPAUSED(n)                (((uint32_t)(n) << 12) & 0x00001000)

// DMA Error encountered during the processing of the DMA command.  The DMA
// error could occur when the memory access specified in the DMA operation is
// not available or incorrectly specified.
#define AM_REG_IOM_INTCLR_DERR_S                     11
#define AM_REG_IOM_INTCLR_DERR_M                     0x00000800
#define AM_REG_IOM_INTCLR_DERR(n)                    (((uint32_t)(n) << 11) & 0x00000800)

// DMA Complete. Processing of the DMA operation has completed and the DMA
// submodule is returned into the idle state
#define AM_REG_IOM_INTCLR_DCMP_S                     10
#define AM_REG_IOM_INTCLR_DCMP_M                     0x00000400
#define AM_REG_IOM_INTCLR_DCMP(n)                    (((uint32_t)(n) << 10) & 0x00000400)

// Arbitration loss interrupt. Asserted when arbitration is enabled and has been
// lost to another master on the bus.
#define AM_REG_IOM_INTCLR_ARB_S                      9
#define AM_REG_IOM_INTCLR_ARB_M                      0x00000200
#define AM_REG_IOM_INTCLR_ARB(n)                     (((uint32_t)(n) << 9) & 0x00000200)

// STOP command interrupt. Asserted when another master on the bus has signaled
// a STOP command.
#define AM_REG_IOM_INTCLR_STOP_S                     8
#define AM_REG_IOM_INTCLR_STOP_M                     0x00000100
#define AM_REG_IOM_INTCLR_STOP(n)                    (((uint32_t)(n) << 8) & 0x00000100)

// START command interrupt. Asserted when another master on the bus has signaled
// a START command.
#define AM_REG_IOM_INTCLR_START_S                    7
#define AM_REG_IOM_INTCLR_START_M                    0x00000080
#define AM_REG_IOM_INTCLR_START(n)                   (((uint32_t)(n) << 7) & 0x00000080)

// illegal command interrupt. Asserted when a command is written when an active
// command is in progress.
#define AM_REG_IOM_INTCLR_ICMD_S                     6
#define AM_REG_IOM_INTCLR_ICMD_M                     0x00000040
#define AM_REG_IOM_INTCLR_ICMD(n)                    (((uint32_t)(n) << 6) & 0x00000040)

// illegal FIFO access interrupt. Asserted when there is a overflow or underflow
// event
#define AM_REG_IOM_INTCLR_IACC_S                     5
#define AM_REG_IOM_INTCLR_IACC_M                     0x00000020
#define AM_REG_IOM_INTCLR_IACC(n)                    (((uint32_t)(n) << 5) & 0x00000020)

// I2C NAK interrupt. Asserted when an unexpected NAK has been received on the
// I2C bus.
#define AM_REG_IOM_INTCLR_NAK_S                      4
#define AM_REG_IOM_INTCLR_NAK_M                      0x00000010
#define AM_REG_IOM_INTCLR_NAK(n)                     (((uint32_t)(n) << 4) & 0x00000010)

// Write FIFO Overflow interrupt. This occurs when software tries to write to a
// full fifo.  The current operation does not stop.
#define AM_REG_IOM_INTCLR_FOVFL_S                    3
#define AM_REG_IOM_INTCLR_FOVFL_M                    0x00000008
#define AM_REG_IOM_INTCLR_FOVFL(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// Read FIFO Underflow interrupt. This occurs when software tries to pop from an
// empty fifo.
#define AM_REG_IOM_INTCLR_FUNDFL_S                   2
#define AM_REG_IOM_INTCLR_FUNDFL_M                   0x00000004
#define AM_REG_IOM_INTCLR_FUNDFL(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// FIFO Threshold interrupt. For write operations, asserted when the number of
// free bytes in the write FIFO equals or exceeds the WTHR field. For read
// operations, asserted when the number of valid bytes in the read FIFO equals
// of exceeds the value set in the RTHR field.
#define AM_REG_IOM_INTCLR_THR_S                      1
#define AM_REG_IOM_INTCLR_THR_M                      0x00000002
#define AM_REG_IOM_INTCLR_THR(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// Command Complete interrupt. Asserted when the current operation has
// completed.   For repeated commands, this will only be asserted when the final
// repeated command is completed.
#define AM_REG_IOM_INTCLR_CMDCMP_S                   0
#define AM_REG_IOM_INTCLR_CMDCMP_M                   0x00000001
#define AM_REG_IOM_INTCLR_CMDCMP(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_INTSET - IO Master Interrupts: Set
//
//*****************************************************************************
// Error during command queue operations
#define AM_REG_IOM_INTSET_CQERR_S                    14
#define AM_REG_IOM_INTSET_CQERR_M                    0x00004000
#define AM_REG_IOM_INTSET_CQERR(n)                   (((uint32_t)(n) << 14) & 0x00004000)

// CQ write operation performed a register write with the register address bit 0
// set to 1.  The low address bits in the CQ address fields are unused and bit 0
// can be used to trigger an interrupt to indicate when this register write is
// performed by the CQ operation.
#define AM_REG_IOM_INTSET_CQUPD_S                    13
#define AM_REG_IOM_INTSET_CQUPD_M                    0x00002000
#define AM_REG_IOM_INTSET_CQUPD(n)                   (((uint32_t)(n) << 13) & 0x00002000)

// Command queue is paused due to an active event enabled in the PAUSEEN
// register.  The interrupt is posted when the event is enabled within the
// PAUSEEN register, the mask is active in the CQIRQMASK field and the event
// occurs.
#define AM_REG_IOM_INTSET_CQPAUSED_S                 12
#define AM_REG_IOM_INTSET_CQPAUSED_M                 0x00001000
#define AM_REG_IOM_INTSET_CQPAUSED(n)                (((uint32_t)(n) << 12) & 0x00001000)

// DMA Error encountered during the processing of the DMA command.  The DMA
// error could occur when the memory access specified in the DMA operation is
// not available or incorrectly specified.
#define AM_REG_IOM_INTSET_DERR_S                     11
#define AM_REG_IOM_INTSET_DERR_M                     0x00000800
#define AM_REG_IOM_INTSET_DERR(n)                    (((uint32_t)(n) << 11) & 0x00000800)

// DMA Complete. Processing of the DMA operation has completed and the DMA
// submodule is returned into the idle state
#define AM_REG_IOM_INTSET_DCMP_S                     10
#define AM_REG_IOM_INTSET_DCMP_M                     0x00000400
#define AM_REG_IOM_INTSET_DCMP(n)                    (((uint32_t)(n) << 10) & 0x00000400)

// Arbitration loss interrupt. Asserted when arbitration is enabled and has been
// lost to another master on the bus.
#define AM_REG_IOM_INTSET_ARB_S                      9
#define AM_REG_IOM_INTSET_ARB_M                      0x00000200
#define AM_REG_IOM_INTSET_ARB(n)                     (((uint32_t)(n) << 9) & 0x00000200)

// STOP command interrupt. Asserted when another master on the bus has signaled
// a STOP command.
#define AM_REG_IOM_INTSET_STOP_S                     8
#define AM_REG_IOM_INTSET_STOP_M                     0x00000100
#define AM_REG_IOM_INTSET_STOP(n)                    (((uint32_t)(n) << 8) & 0x00000100)

// START command interrupt. Asserted when another master on the bus has signaled
// a START command.
#define AM_REG_IOM_INTSET_START_S                    7
#define AM_REG_IOM_INTSET_START_M                    0x00000080
#define AM_REG_IOM_INTSET_START(n)                   (((uint32_t)(n) << 7) & 0x00000080)

// illegal command interrupt. Asserted when a command is written when an active
// command is in progress.
#define AM_REG_IOM_INTSET_ICMD_S                     6
#define AM_REG_IOM_INTSET_ICMD_M                     0x00000040
#define AM_REG_IOM_INTSET_ICMD(n)                    (((uint32_t)(n) << 6) & 0x00000040)

// illegal FIFO access interrupt. Asserted when there is a overflow or underflow
// event
#define AM_REG_IOM_INTSET_IACC_S                     5
#define AM_REG_IOM_INTSET_IACC_M                     0x00000020
#define AM_REG_IOM_INTSET_IACC(n)                    (((uint32_t)(n) << 5) & 0x00000020)

// I2C NAK interrupt. Asserted when an unexpected NAK has been received on the
// I2C bus.
#define AM_REG_IOM_INTSET_NAK_S                      4
#define AM_REG_IOM_INTSET_NAK_M                      0x00000010
#define AM_REG_IOM_INTSET_NAK(n)                     (((uint32_t)(n) << 4) & 0x00000010)

// Write FIFO Overflow interrupt. This occurs when software tries to write to a
// full fifo.  The current operation does not stop.
#define AM_REG_IOM_INTSET_FOVFL_S                    3
#define AM_REG_IOM_INTSET_FOVFL_M                    0x00000008
#define AM_REG_IOM_INTSET_FOVFL(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// Read FIFO Underflow interrupt. This occurs when software tries to pop from an
// empty fifo.
#define AM_REG_IOM_INTSET_FUNDFL_S                   2
#define AM_REG_IOM_INTSET_FUNDFL_M                   0x00000004
#define AM_REG_IOM_INTSET_FUNDFL(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// FIFO Threshold interrupt. For write operations, asserted when the number of
// free bytes in the write FIFO equals or exceeds the WTHR field. For read
// operations, asserted when the number of valid bytes in the read FIFO equals
// of exceeds the value set in the RTHR field.
#define AM_REG_IOM_INTSET_THR_S                      1
#define AM_REG_IOM_INTSET_THR_M                      0x00000002
#define AM_REG_IOM_INTSET_THR(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// Command Complete interrupt. Asserted when the current operation has
// completed.   For repeated commands, this will only be asserted when the final
// repeated command is completed.
#define AM_REG_IOM_INTSET_CMDCMP_S                   0
#define AM_REG_IOM_INTSET_CMDCMP_M                   0x00000001
#define AM_REG_IOM_INTSET_CMDCMP(n)                  (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_FIFO - FIFO Access Port
//
//*****************************************************************************
// FIFO direct access. Only locations 0 - 3F will return valid information.
#define AM_REG_IOM_FIFO_FIFO_S                       0
#define AM_REG_IOM_FIFO_FIFO_M                       0xFFFFFFFF
#define AM_REG_IOM_FIFO_FIFO(n)                      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// IOM_FIFOPTR - FIFO size and remaining slots open values
//
//*****************************************************************************
// The number of remaining data bytes slots currently in FIFO 1 (written by
// interface, read by MCU)
#define AM_REG_IOM_FIFOPTR_FIFO1REM_S                24
#define AM_REG_IOM_FIFOPTR_FIFO1REM_M                0xFF000000
#define AM_REG_IOM_FIFOPTR_FIFO1REM(n)               (((uint32_t)(n) << 24) & 0xFF000000)

// The number of valid data bytes currently in FIFO 1 (written by interface,
// read by MCU)
#define AM_REG_IOM_FIFOPTR_FIFO1SIZ_S                16
#define AM_REG_IOM_FIFOPTR_FIFO1SIZ_M                0x00FF0000
#define AM_REG_IOM_FIFOPTR_FIFO1SIZ(n)               (((uint32_t)(n) << 16) & 0x00FF0000)

// The number of remaining data bytes slots currently in FIFO 0 (written by MCU,
// read by interface)
#define AM_REG_IOM_FIFOPTR_FIFO0REM_S                8
#define AM_REG_IOM_FIFOPTR_FIFO0REM_M                0x0000FF00
#define AM_REG_IOM_FIFOPTR_FIFO0REM(n)               (((uint32_t)(n) << 8) & 0x0000FF00)

// The number of valid data bytes currently in the FIFO 0 (written by MCU, read
// by interface)
#define AM_REG_IOM_FIFOPTR_FIFO0SIZ_S                0
#define AM_REG_IOM_FIFOPTR_FIFO0SIZ_M                0x000000FF
#define AM_REG_IOM_FIFOPTR_FIFO0SIZ(n)               (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// IOM_FIFOTHR - FIFO Threshold Configuration
//
//*****************************************************************************
// FIFO write threshold in bytes.  A value of 0 will disable the write FIFO
// level from activating the threshold interrupt. If this field is non-zero, it
// will trigger a threshold interrupt when the write fifo contains FIFOWTHR free
// bytes, as indicated by the FIFO0REM field.  This is intended to signal when a
// transfer of FIFOWTHR bytes can be done from the host to the IOM write fifo to
// support large IOM write operations.
#define AM_REG_IOM_FIFOTHR_FIFOWTHR_S                8
#define AM_REG_IOM_FIFOTHR_FIFOWTHR_M                0x00003F00
#define AM_REG_IOM_FIFOTHR_FIFOWTHR(n)               (((uint32_t)(n) << 8) & 0x00003F00)

// FIFO read threshold in bytes.  A value of 0 will disable the read FIFO level
// from activating the threshold interrupt. If this field is non-zero, it will
// trigger a threshold interrupt when the read fifo contains FIFORTHR valid
// bytes of data, as indicated by the FIFO1SIZ field.  This is intended to
// signal when a data transfer of FIFORTHR bytes can be done from the IOM module
// to the host via the read fifo to support large IOM read operations.
#define AM_REG_IOM_FIFOTHR_FIFORTHR_S                0
#define AM_REG_IOM_FIFOTHR_FIFORTHR_M                0x0000003F
#define AM_REG_IOM_FIFOTHR_FIFORTHR(n)               (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// IOM_FIFOPOP - FIFO POP register
//
//*****************************************************************************
// This register will return the read data indicated by the current read pointer
// on reads. If the POPWR control bit in the FIFOCTRL register is reset (0), the
// fifo read pointer will be advanced by one word as a result of the read. If
// the POPWR bit is set (1), the fifo read pointer will only be advanced after a
// write operation to this register.  The write data is ignored for this
// register. If less than a even word multiple is available, and the command is
// completed, the module will return the word containing these bytes and
// undetermined data in the unused fields of the word.
#define AM_REG_IOM_FIFOPOP_FIFODOUT_S                0
#define AM_REG_IOM_FIFOPOP_FIFODOUT_M                0xFFFFFFFF
#define AM_REG_IOM_FIFOPOP_FIFODOUT(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// IOM_FIFOPUSH - FIFO PUSH register
//
//*****************************************************************************
// This register is used to write the FIFORAM in FIFO mode and will cause a push
// event to occur to the next open slot within the FIFORAM.  Writing to this
// register will cause the write point to increment by 1 word(4 bytes).
#define AM_REG_IOM_FIFOPUSH_FIFODIN_S                0
#define AM_REG_IOM_FIFOPUSH_FIFODIN_M                0xFFFFFFFF
#define AM_REG_IOM_FIFOPUSH_FIFODIN(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// IOM_FIFOCTRL - FIFO Control Register
//
//*****************************************************************************
// Active low manual reset of the fifo.  Write to 0 to reset fifo, and then
// write to 1 to remove the reset.
#define AM_REG_IOM_FIFOCTRL_FIFORSTN_S               1
#define AM_REG_IOM_FIFOCTRL_FIFORSTN_M               0x00000002
#define AM_REG_IOM_FIFOCTRL_FIFORSTN(n)              (((uint32_t)(n) << 1) & 0x00000002)

// Selects the mode in which 'pop' events are done for the fifo read operations.
// A value of '1' will prevent a pop event on a read operation, and will require
// a write to the FIFOPOP register to create a pop event. A value of '0' in this
// register will allow a pop event to occur on the read of the FIFOPOP register,
// and may cause inadvertant fifo pops when used in a debugging mode.
#define AM_REG_IOM_FIFOCTRL_POPWR_S                  0
#define AM_REG_IOM_FIFOCTRL_POPWR_M                  0x00000001
#define AM_REG_IOM_FIFOCTRL_POPWR(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_FIFOLOC - FIFO Pointers
//
//*****************************************************************************
// Current FIFO read pointer.  Used to index into the incoming FIFO (FIFO1),
// which is used to store read data returned from external devices during a read
// operation.
#define AM_REG_IOM_FIFOLOC_FIFORPTR_S                8
#define AM_REG_IOM_FIFOLOC_FIFORPTR_M                0x00000F00
#define AM_REG_IOM_FIFOLOC_FIFORPTR(n)               (((uint32_t)(n) << 8) & 0x00000F00)

// Current FIFO write pointer. Value is the index into the outgoing FIFO
// (FIFO0), which is used during write operations to external devices.
#define AM_REG_IOM_FIFOLOC_FIFOWPTR_S                0
#define AM_REG_IOM_FIFOLOC_FIFOWPTR_M                0x0000000F
#define AM_REG_IOM_FIFOLOC_FIFOWPTR(n)               (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// IOM_CLKCFG - I/O Clock Configuration
//
//*****************************************************************************
// Clock total clock count minus 1. This provides the total period of the
// divided clock -1 when the DIVEN is active. The source clock is selected by
// FSEL.  Only applicable when DIVEN = 1.
#define AM_REG_IOM_CLKCFG_TOTPER_S                   24
#define AM_REG_IOM_CLKCFG_TOTPER_M                   0xFF000000
#define AM_REG_IOM_CLKCFG_TOTPER(n)                  (((uint32_t)(n) << 24) & 0xFF000000)

// Clock low clock count minus 1. This provides the number of clocks the divided
// clock will be low when the DIVEN = 1. Only applicable when DIVEN = 1.
#define AM_REG_IOM_CLKCFG_LOWPER_S                   16
#define AM_REG_IOM_CLKCFG_LOWPER_M                   0x00FF0000
#define AM_REG_IOM_CLKCFG_LOWPER(n)                  (((uint32_t)(n) << 16) & 0x00FF0000)

// Enable clock division by TOTPER and LOWPER
#define AM_REG_IOM_CLKCFG_DIVEN_S                    12
#define AM_REG_IOM_CLKCFG_DIVEN_M                    0x00001000
#define AM_REG_IOM_CLKCFG_DIVEN(n)                   (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_IOM_CLKCFG_DIVEN_DIS                  0x00000000
#define AM_REG_IOM_CLKCFG_DIVEN_EN                   0x00001000

// Enable divide by 3 of the source IOCLK.  Division by 3 is done before the
// DIVEN programmable divider, and if enabled will provide the divided by 3
// clock as the source to the programmable divider.
#define AM_REG_IOM_CLKCFG_DIV3_S                     11
#define AM_REG_IOM_CLKCFG_DIV3_M                     0x00000800
#define AM_REG_IOM_CLKCFG_DIV3(n)                    (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_IOM_CLKCFG_DIV3_DIS                   0x00000000
#define AM_REG_IOM_CLKCFG_DIV3_EN                    0x00000800

// Select the input clock frequency.
#define AM_REG_IOM_CLKCFG_FSEL_S                     8
#define AM_REG_IOM_CLKCFG_FSEL_M                     0x00000700
#define AM_REG_IOM_CLKCFG_FSEL(n)                    (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_IOM_CLKCFG_FSEL_MIN_PWR               0x00000000
#define AM_REG_IOM_CLKCFG_FSEL_HFRC                  0x00000100
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV2             0x00000200
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV4             0x00000300
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV8             0x00000400
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV16            0x00000500
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV32            0x00000600
#define AM_REG_IOM_CLKCFG_FSEL_HFRC_DIV64            0x00000700

// Enable for the interface clock.  Must be enabled prior to executing any IO
// operations.
#define AM_REG_IOM_CLKCFG_IOCLKEN_S                  0
#define AM_REG_IOM_CLKCFG_IOCLKEN_M                  0x00000001
#define AM_REG_IOM_CLKCFG_IOCLKEN(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_SUBMODCTRL - Submodule control
//
//*****************************************************************************
// Submodule 0 module type.  This is the I2C Master interface
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_S            5
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_M            0x000000E0
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE(n)           (((uint32_t)(n) << 5) & 0x000000E0)
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_MSPI         0x00000000
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_I2C_MASTER   0x00000020
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_SSPI         0x00000040
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_SI2C         0x00000060
#define AM_REG_IOM_SUBMODCTRL_SMOD1TYPE_NA           0x000000E0

// Submodule 1 enable (1) or disable (0)
#define AM_REG_IOM_SUBMODCTRL_SMOD1EN_S              4
#define AM_REG_IOM_SUBMODCTRL_SMOD1EN_M              0x00000010
#define AM_REG_IOM_SUBMODCTRL_SMOD1EN(n)             (((uint32_t)(n) << 4) & 0x00000010)

// Submodule 0 module type.  This is the SPI Master interface.
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_S            1
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_M            0x0000000E
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE(n)           (((uint32_t)(n) << 1) & 0x0000000E)
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_SPI_MASTER   0x00000000
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_I2C_MASTER   0x00000002
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_SSPI         0x00000004
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_SI2C         0x00000006
#define AM_REG_IOM_SUBMODCTRL_SMOD0TYPE_NA           0x0000000E

// Submodule 0 enable (1) or disable (0)
#define AM_REG_IOM_SUBMODCTRL_SMOD0EN_S              0
#define AM_REG_IOM_SUBMODCTRL_SMOD0EN_M              0x00000001
#define AM_REG_IOM_SUBMODCTRL_SMOD0EN(n)             (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_CMD - Command and offset Register
//
//*****************************************************************************
// This register holds the low order byte of offset to be used in the
// transaction. The number of offset bytes to use is set with bits 1:0 of the
// command.
#define AM_REG_IOM_CMD_OFFSETLO_S                    24
#define AM_REG_IOM_CMD_OFFSETLO_M                    0xFF000000
#define AM_REG_IOM_CMD_OFFSETLO(n)                   (((uint32_t)(n) << 24) & 0xFF000000)

// Command Specific selection information. Not used in Master I2C.  Used as CEn
// select for Master SPI transactions
#define AM_REG_IOM_CMD_CMDSEL_S                      20
#define AM_REG_IOM_CMD_CMDSEL_M                      0x00300000
#define AM_REG_IOM_CMD_CMDSEL(n)                     (((uint32_t)(n) << 20) & 0x00300000)

// Defines the transaction size in bytes.  The offset transfer is not included
// in this size.
#define AM_REG_IOM_CMD_TSIZE_S                       8
#define AM_REG_IOM_CMD_TSIZE_M                       0x000FFF00
#define AM_REG_IOM_CMD_TSIZE(n)                      (((uint32_t)(n) << 8) & 0x000FFF00)

// Contine to hold the bus after the current transaction if set to a 1 with a
// new command issued.
#define AM_REG_IOM_CMD_CONT_S                        7
#define AM_REG_IOM_CMD_CONT_M                        0x00000080
#define AM_REG_IOM_CMD_CONT(n)                       (((uint32_t)(n) << 7) & 0x00000080)

// Number of offset bytes to use for the command - 0, 1, 2, 3 are valid
// selections. The second (byte 1) and third byte (byte 2) are read from the
// OFFSETHI register, and the low order byte is pulled from this register in the
// OFFSETLO field. Offset bytes are transmitted highest byte first.  EG if
// offsetcnt == 3, OFFSETHI[15:8] will be transmitted first, then OFFSETHI[7:0]
// then OFFSETLO. If offsetcnt == 2, OFFSETHI[7:0] will be transmitted, then
// OFFSETLO. If offsetcnt == 1, only OFFSETLO will be transmitted. Offset bytes
// are always transmitted MSB first, regardless of the value of the LSB control
// bit within the module configuration.
#define AM_REG_IOM_CMD_OFFSETCNT_S                   5
#define AM_REG_IOM_CMD_OFFSETCNT_M                   0x00000060
#define AM_REG_IOM_CMD_OFFSETCNT(n)                  (((uint32_t)(n) << 5) & 0x00000060)

// Command for submodule.
#define AM_REG_IOM_CMD_CMD_S                         0
#define AM_REG_IOM_CMD_CMD_M                         0x0000001F
#define AM_REG_IOM_CMD_CMD(n)                        (((uint32_t)(n) << 0) & 0x0000001F)
#define AM_REG_IOM_CMD_CMD_WRITE                     0x00000001
#define AM_REG_IOM_CMD_CMD_READ                      0x00000002
#define AM_REG_IOM_CMD_CMD_TMW                       0x00000003
#define AM_REG_IOM_CMD_CMD_TMR                       0x00000004

//*****************************************************************************
//
// IOM_CMDRPT - Command Repeat Register
//
//*****************************************************************************
// Count of number of times to repeat the next command.
#define AM_REG_IOM_CMDRPT_CMDRPT_S                   0
#define AM_REG_IOM_CMDRPT_CMDRPT_M                   0x0000001F
#define AM_REG_IOM_CMDRPT_CMDRPT(n)                  (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// IOM_OFFSETHI - High order 2 bytes of 3 byte offset for IO transaction
//
//*****************************************************************************
// Holds the high order 2 bytes of the 3 byte addressing/offset field to use
// with IO commands.  The number of offset bytes to use is specified in the
// command register
#define AM_REG_IOM_OFFSETHI_OFFSETHI_S               0
#define AM_REG_IOM_OFFSETHI_OFFSETHI_M               0x0000FFFF
#define AM_REG_IOM_OFFSETHI_OFFSETHI(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// IOM_CMDSTAT - Command status
//
//*****************************************************************************
// The current number of bytes still to be transferred with this command.  This
// field will count down to zero.
#define AM_REG_IOM_CMDSTAT_CTSIZE_S                  8
#define AM_REG_IOM_CMDSTAT_CTSIZE_M                  0x000FFF00
#define AM_REG_IOM_CMDSTAT_CTSIZE(n)                 (((uint32_t)(n) << 8) & 0x000FFF00)

// The current status of the command execution.
#define AM_REG_IOM_CMDSTAT_CMDSTAT_S                 5
#define AM_REG_IOM_CMDSTAT_CMDSTAT_M                 0x000000E0
#define AM_REG_IOM_CMDSTAT_CMDSTAT(n)                (((uint32_t)(n) << 5) & 0x000000E0)
#define AM_REG_IOM_CMDSTAT_CMDSTAT_ERR               0x00000020
#define AM_REG_IOM_CMDSTAT_CMDSTAT_ACTIVE            0x00000040
#define AM_REG_IOM_CMDSTAT_CMDSTAT_IDLE              0x00000080
#define AM_REG_IOM_CMDSTAT_CMDSTAT_WAIT              0x000000C0

// current command that is being executed
#define AM_REG_IOM_CMDSTAT_CCMD_S                    0
#define AM_REG_IOM_CMDSTAT_CCMD_M                    0x0000001F
#define AM_REG_IOM_CMDSTAT_CCMD(n)                   (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// IOM_DMATRIGEN - DMA Trigger Enable Register
//
//*****************************************************************************
// Trigger DMA upon THR level reached. For M2P DMA operations (IOM writes), the
// trigger will assert when the write FIFO has (WTHR/4) number of words free in
// the write FIFO, and will transfer (WTHR/4) number of words or, if the number
// of words left to transfer is less than the WTHR value, will transfer the
// remaining byte count. For P2M DMA operations, the trigger will assert when
// the read FIFO has (RTHR/4) words available in the read FIFO, and will
// transfer (RTHR/4) words to SRAM. This trigger will NOT assert when the
// transaction completes and there are less than RTHR bytes left in the fifo,
// since the RTHR has not been reached.  In this case, the CMDCMP trigger must
// also be enabled to transfer the remaining read FIFO data to SRAM.
#define AM_REG_IOM_DMATRIGEN_DTHREN_S                1
#define AM_REG_IOM_DMATRIGEN_DTHREN_M                0x00000002
#define AM_REG_IOM_DMATRIGEN_DTHREN(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Trigger DMA upon command complete.  Enables the trigger of the DMA when a
// command is completed.  When this event is triggered, the number of words
// transferred will be the lesser of the remaining TOTCOUNT bytes, or
#define AM_REG_IOM_DMATRIGEN_DCMDCMPEN_S             0
#define AM_REG_IOM_DMATRIGEN_DCMDCMPEN_M             0x00000001
#define AM_REG_IOM_DMATRIGEN_DCMDCMPEN(n)            (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_DMATRIGSTAT - DMA Trigger Status Register
//
//*****************************************************************************
// DMA triggered when DCMDCMP = 0, and the amount of data in the FIFO was enough
// to complete the DMA operation (greater than or equal to current TOTCOUNT)
// when the command completed. This trigger is default active when the DCMDCMP
// trigger is disabled and there is enough data in the FIFO to complete the DMA
// operation.
#define AM_REG_IOM_DMATRIGSTAT_DTOTCMP_S             2
#define AM_REG_IOM_DMATRIGSTAT_DTOTCMP_M             0x00000004
#define AM_REG_IOM_DMATRIGSTAT_DTOTCMP(n)            (((uint32_t)(n) << 2) & 0x00000004)

// Triggered DMA from THR event. Bit is read only and can be cleared by
// disabling the DTHR trigger enable or by disabling DMA.
#define AM_REG_IOM_DMATRIGSTAT_DTHR_S                1
#define AM_REG_IOM_DMATRIGSTAT_DTHR_M                0x00000002
#define AM_REG_IOM_DMATRIGSTAT_DTHR(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Triggered DMA from Command complete event.   Bit is read only and can be
// cleared by disabling the DCMDCMP trigger enable or by disabling DMA.
#define AM_REG_IOM_DMATRIGSTAT_DCMDCMP_S             0
#define AM_REG_IOM_DMATRIGSTAT_DCMDCMP_M             0x00000001
#define AM_REG_IOM_DMATRIGSTAT_DCMDCMP(n)            (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_DMACFG - DMA Configuration Register
//
//*****************************************************************************
// Power off module after DMA is complete.  If this bit is active, the module
// will request to power off the supply it is attached to. If there are other
// units still requiring power from the same domain, power down will not be
// performed.
#define AM_REG_IOM_DMACFG_DPWROFF_S                  9
#define AM_REG_IOM_DMACFG_DPWROFF_M                  0x00000200
#define AM_REG_IOM_DMACFG_DPWROFF(n)                 (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_IOM_DMACFG_DPWROFF_DIS                0x00000000
#define AM_REG_IOM_DMACFG_DPWROFF_EN                 0x00000200

// Sets the Priority of the DMA request
#define AM_REG_IOM_DMACFG_DMAPRI_S                   8
#define AM_REG_IOM_DMACFG_DMAPRI_M                   0x00000100
#define AM_REG_IOM_DMACFG_DMAPRI(n)                  (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_IOM_DMACFG_DMAPRI_LOW                 0x00000000
#define AM_REG_IOM_DMACFG_DMAPRI_HIGH                0x00000100

// Direction
#define AM_REG_IOM_DMACFG_DMADIR_S                   1
#define AM_REG_IOM_DMACFG_DMADIR_M                   0x00000002
#define AM_REG_IOM_DMACFG_DMADIR(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOM_DMACFG_DMADIR_P2M                 0x00000000
#define AM_REG_IOM_DMACFG_DMADIR_M2P                 0x00000002

// DMA Enable. Setting this bit to EN will start the DMA operation. This should
// be the last DMA related register set prior to issuing the command
#define AM_REG_IOM_DMACFG_DMAEN_S                    0
#define AM_REG_IOM_DMACFG_DMAEN_M                    0x00000001
#define AM_REG_IOM_DMACFG_DMAEN(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOM_DMACFG_DMAEN_DIS                  0x00000000
#define AM_REG_IOM_DMACFG_DMAEN_EN                   0x00000001

//*****************************************************************************
//
// IOM_DMATOTCOUNT - DMA Total Transfer Count
//
//*****************************************************************************
// Triggered DMA from Command complete event occured.   Bit is read only and can
// be cleared by disabling the DTHR trigger enable or by disabling DMA.
#define AM_REG_IOM_DMATOTCOUNT_TOTCOUNT_S            0
#define AM_REG_IOM_DMATOTCOUNT_TOTCOUNT_M            0x00000FFF
#define AM_REG_IOM_DMATOTCOUNT_TOTCOUNT(n)           (((uint32_t)(n) << 0) & 0x00000FFF)

//*****************************************************************************
//
// IOM_DMATARGADDR - DMA Target Address Register
//
//*****************************************************************************
// Bit 28 of the target byte address for source of DMA (either read or write).
// In cases of non-word aligned addresses, the DMA logic will take care for
// ensuring only the target bytes are read/written. Setting to '1' will select
// the SRAM.  Setting to '0' will select the flash
#define AM_REG_IOM_DMATARGADDR_TARGADDR28_S          28
#define AM_REG_IOM_DMATARGADDR_TARGADDR28_M          0x10000000
#define AM_REG_IOM_DMATARGADDR_TARGADDR28(n)         (((uint32_t)(n) << 28) & 0x10000000)

// Bits [19:0] of the target byte address for source of DMA (either read or
// write). The address can be any byte alignment, and does not have to be word
// aligned.  In cases of non-word aligned addresses, the DMA logic will take
// care for ensuring only the target bytes are read/written.
#define AM_REG_IOM_DMATARGADDR_TARGADDR_S            0
#define AM_REG_IOM_DMATARGADDR_TARGADDR_M            0x000FFFFF
#define AM_REG_IOM_DMATARGADDR_TARGADDR(n)           (((uint32_t)(n) << 0) & 0x000FFFFF)

//*****************************************************************************
//
// IOM_DMASTAT - DMA Status Register
//
//*****************************************************************************
// DMA Error. This active high bit signals an error was encountered during the
// DMA operation. The bit can be cleared by writing to 0.  Once set, this bit
// will remain set until cleared by software.
#define AM_REG_IOM_DMASTAT_DMAERR_S                  2
#define AM_REG_IOM_DMASTAT_DMAERR_M                  0x00000004
#define AM_REG_IOM_DMASTAT_DMAERR(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// DMA Transfer Complete. This signals the end of the DMA operation.  This bit
// can be cleared by writing to 0, and will also be cleared when a new DMA is
// started.
#define AM_REG_IOM_DMASTAT_DMACPL_S                  1
#define AM_REG_IOM_DMASTAT_DMACPL_M                  0x00000002
#define AM_REG_IOM_DMASTAT_DMACPL(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// DMA Transfer In Progress indicator.  1 will indicate that a DMA transfer is
// active.  The DMA transfer may be waiting on data, transferring data, or
// waiting for priority. All of these will be indicated with a 1.  A 0 will
// indicate that the DMA is fully complete and no further transactions will be
// done.  This bit is read only.
#define AM_REG_IOM_DMASTAT_DMATIP_S                  0
#define AM_REG_IOM_DMASTAT_DMATIP_M                  0x00000001
#define AM_REG_IOM_DMASTAT_DMATIP(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_CQCFG - Command Queue Configuration Register
//
//*****************************************************************************
// Sets the Priority of the command queue dma request
#define AM_REG_IOM_CQCFG_CQPRI_S                     1
#define AM_REG_IOM_CQCFG_CQPRI_M                     0x00000002
#define AM_REG_IOM_CQCFG_CQPRI(n)                    (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOM_CQCFG_CQPRI_LOW                   0x00000000
#define AM_REG_IOM_CQCFG_CQPRI_HIGH                  0x00000002

// Command queue enable. When set, will enable the processing of the command
// queue and fetches of address/data pairs will proceed from the word address
// within the CQADDR register.  Can be disabled using a CQ executed write to
// this bit as well.
#define AM_REG_IOM_CQCFG_CQEN_S                      0
#define AM_REG_IOM_CQCFG_CQEN_M                      0x00000001
#define AM_REG_IOM_CQCFG_CQEN(n)                     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOM_CQCFG_CQEN_DIS                    0x00000000
#define AM_REG_IOM_CQCFG_CQEN_EN                     0x00000001

//*****************************************************************************
//
// IOM_CQADDR - CQ Target Read Address Register
//
//*****************************************************************************
// Bit 28 of target byte address for source of CQ (read only). Used to denote
// Flash (0) or SRAM (1) access
#define AM_REG_IOM_CQADDR_CQADDR28_S                 28
#define AM_REG_IOM_CQADDR_CQADDR28_M                 0x10000000
#define AM_REG_IOM_CQADDR_CQADDR28(n)                (((uint32_t)(n) << 28) & 0x10000000)

// Bits 19:2 of target byte address for source of CQ (read only). The buffer
// must be aligned on a word boundary
#define AM_REG_IOM_CQADDR_CQADDR_S                   2
#define AM_REG_IOM_CQADDR_CQADDR_M                   0x000FFFFC
#define AM_REG_IOM_CQADDR_CQADDR(n)                  (((uint32_t)(n) << 2) & 0x000FFFFC)

//*****************************************************************************
//
// IOM_CQSTAT - Command Queue Status Register
//
//*****************************************************************************
// Command queue processing  Error. This active high bit signals that an error
// was encountered during the CQ  operation.
#define AM_REG_IOM_CQSTAT_CQERR_S                    2
#define AM_REG_IOM_CQSTAT_CQERR_M                    0x00000004
#define AM_REG_IOM_CQSTAT_CQERR(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// Command queue operation is currently paused.
#define AM_REG_IOM_CQSTAT_CQPAUSED_S                 1
#define AM_REG_IOM_CQSTAT_CQPAUSED_M                 0x00000002
#define AM_REG_IOM_CQSTAT_CQPAUSED(n)                (((uint32_t)(n) << 1) & 0x00000002)

// Command queue Transfer In Progress indicator.  1 will indicate that a CQ
// transfer is active and this will remain active even when paused waiting for
// external event.
#define AM_REG_IOM_CQSTAT_CQTIP_S                    0
#define AM_REG_IOM_CQSTAT_CQTIP_M                    0x00000001
#define AM_REG_IOM_CQSTAT_CQTIP(n)                   (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOM_CQFLAGS - Command Queue Flag Register
//
//*****************************************************************************
// Mask the bits used to generate the command queue interrupt.  A '1' in the bit
// position will enable the pause event to trigger the interrupt, if the
// CQWT_int interrupt is enabled. Bits definitions are the same as CQPAUSE
#define AM_REG_IOM_CQFLAGS_CQIRQMASK_S               16
#define AM_REG_IOM_CQFLAGS_CQIRQMASK_M               0xFFFF0000
#define AM_REG_IOM_CQFLAGS_CQIRQMASK(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Current flag status (read-only).  Bits [7:0] are software controllable and
// bits [15:8] are hardware status.
#define AM_REG_IOM_CQFLAGS_CQFLAGS_S                 0
#define AM_REG_IOM_CQFLAGS_CQFLAGS_M                 0x0000FFFF
#define AM_REG_IOM_CQFLAGS_CQFLAGS(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// IOM_CQSETCLEAR - Command Queue Flag Set/Clear Register
//
//*****************************************************************************
// Clear CQFlag status bits. Will clear to 0 any SWFLAG with a '1' in the
// corresponding bit position of this field
#define AM_REG_IOM_CQSETCLEAR_CQFCLR_S               16
#define AM_REG_IOM_CQSETCLEAR_CQFCLR_M               0x00FF0000
#define AM_REG_IOM_CQSETCLEAR_CQFCLR(n)              (((uint32_t)(n) << 16) & 0x00FF0000)

// Toggle the indicated bit. Will toggle the value of any SWFLAG with a '1' in
// the corresponding bit position of this field
#define AM_REG_IOM_CQSETCLEAR_CQFTGL_S               8
#define AM_REG_IOM_CQSETCLEAR_CQFTGL_M               0x0000FF00
#define AM_REG_IOM_CQSETCLEAR_CQFTGL(n)              (((uint32_t)(n) << 8) & 0x0000FF00)

// Set CQFlag status bits.  Will set to 1 the value of any SWFLAG with a '1' in
// the corresponding bit position of this field
#define AM_REG_IOM_CQSETCLEAR_CQFSET_S               0
#define AM_REG_IOM_CQSETCLEAR_CQFSET_M               0x000000FF
#define AM_REG_IOM_CQSETCLEAR_CQFSET(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// IOM_CQPAUSEEN - Command Queue Pause Enable Register
//
//*****************************************************************************
// Enables the specified event to pause command processing when active
#define AM_REG_IOM_CQPAUSEEN_CQPEN_S                 0
#define AM_REG_IOM_CQPAUSEEN_CQPEN_M                 0x0000FFFF
#define AM_REG_IOM_CQPAUSEEN_CQPEN(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)
#define AM_REG_IOM_CQPAUSEEN_CQPEN_IDXEQ             0x00008000
#define AM_REG_IOM_CQPAUSEEN_CQPEN_BLEXOREN          0x00004000
#define AM_REG_IOM_CQPAUSEEN_CQPEN_IOMXOREN          0x00002000
#define AM_REG_IOM_CQPAUSEEN_CQPEN_GPIOXOREN         0x00001000
#define AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI1XNOREN       0x00000800
#define AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI0XNOREN       0x00000400
#define AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI1XOREN        0x00000200
#define AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI0XOREN        0x00000100
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN7         0x00000080
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN6         0x00000040
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN5         0x00000020
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN4         0x00000010
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN3         0x00000008
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN2         0x00000004
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN1         0x00000002
#define AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN0         0x00000001

//*****************************************************************************
//
// IOM_CQCURIDX - IOM Command Queue current index value . Compared to the
// CQENDIDX reg contents to generate the IDXEQ Pause event for command queue
//
//*****************************************************************************
// Holds 8 bits of data that will be compared with the CQENDIX register field.
// If the values match, the IDXEQ pause event will be activated, which will
// cause the pausing of command quue operation if the IDXEQ bit is enabled in
// CQPAUSEEN.
#define AM_REG_IOM_CQCURIDX_CQCURIDX_S               0
#define AM_REG_IOM_CQCURIDX_CQCURIDX_M               0x000000FF
#define AM_REG_IOM_CQCURIDX_CQCURIDX(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// IOM_CQENDIDX - IOM Command Queue current index value . Compared to the
// CQCURIDX reg contents to generate the IDXEQ Pause event for command queue
//
//*****************************************************************************
// Holds 8 bits of data that will be compared with the CQCURIX register field.
// If the values match, the IDXEQ pause event will be activated, which will
// cause the pausing of command quue operation if the IDXEQ bit is enabled in
// CQPAUSEEN.
#define AM_REG_IOM_CQENDIDX_CQENDIDX_S               0
#define AM_REG_IOM_CQENDIDX_CQENDIDX_M               0x000000FF
#define AM_REG_IOM_CQENDIDX_CQENDIDX(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// IOM_STATUS - IOM Module Status Register
//
//*****************************************************************************
// indicates if the active I/O state machine is IDLE. Note - The state machine
// could be in idle state due to holdoffs from data availability, or as the
// command gets propagated into the logic from the registers.
#define AM_REG_IOM_STATUS_IDLEST_S                   2
#define AM_REG_IOM_STATUS_IDLEST_M                   0x00000004
#define AM_REG_IOM_STATUS_IDLEST(n)                  (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_IOM_STATUS_IDLEST_IDLE                0x00000004

// Indicates if the active I/O Command is currently processing a transaction, or
// command is complete, but the FIFO pointers are still syncronizing internally.
// This bit will go high at the start of the transaction, and will go low when
// the command is complete, and the data and pointers within the FIFO have been
// syncronized.
#define AM_REG_IOM_STATUS_CMDACT_S                   1
#define AM_REG_IOM_STATUS_CMDACT_M                   0x00000002
#define AM_REG_IOM_STATUS_CMDACT(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOM_STATUS_CMDACT_ACTIVE              0x00000002

// Bit has been deprecated.  Please refer to the other error indicators.  This
// will always return 0.
#define AM_REG_IOM_STATUS_ERR_S                      0
#define AM_REG_IOM_STATUS_ERR_M                      0x00000001
#define AM_REG_IOM_STATUS_ERR(n)                     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOM_STATUS_ERR_ERROR                  0x00000001

//*****************************************************************************
//
// IOM_MSPICFG - SPI module master configuration
//
//*****************************************************************************
// Not used.  To reset the module, toggle the SMOD_EN for the module
#define AM_REG_IOM_MSPICFG_MSPIRST_S                 30
#define AM_REG_IOM_MSPICFG_MSPIRST_M                 0x40000000
#define AM_REG_IOM_MSPICFG_MSPIRST(n)                (((uint32_t)(n) << 30) & 0x40000000)

// Delay tap to use for the output signal (MOSI).  This give more hold time on
// the output data
#define AM_REG_IOM_MSPICFG_DOUTDLY_S                 27
#define AM_REG_IOM_MSPICFG_DOUTDLY_M                 0x38000000
#define AM_REG_IOM_MSPICFG_DOUTDLY(n)                (((uint32_t)(n) << 27) & 0x38000000)

// Delay tap to use for the input signal (MISO).  This gives more hold time on
// the input data.
#define AM_REG_IOM_MSPICFG_DINDLY_S                  24
#define AM_REG_IOM_MSPICFG_DINDLY_M                  0x07000000
#define AM_REG_IOM_MSPICFG_DINDLY(n)                 (((uint32_t)(n) << 24) & 0x07000000)

// Selects data transfer as MSB first (0) or LSB first (1) for the data portion
// of the SPI transaction.   The offset bytes are always transmitted MSB first.
#define AM_REG_IOM_MSPICFG_SPILSB_S                  23
#define AM_REG_IOM_MSPICFG_SPILSB_M                  0x00800000
#define AM_REG_IOM_MSPICFG_SPILSB(n)                 (((uint32_t)(n) << 23) & 0x00800000)
#define AM_REG_IOM_MSPICFG_SPILSB_MSB                0x00000000
#define AM_REG_IOM_MSPICFG_SPILSB_LSB                0x00800000

// selects the read flow control signal polarity.
#define AM_REG_IOM_MSPICFG_RDFCPOL_S                 22
#define AM_REG_IOM_MSPICFG_RDFCPOL_M                 0x00400000
#define AM_REG_IOM_MSPICFG_RDFCPOL(n)                (((uint32_t)(n) << 22) & 0x00400000)
#define AM_REG_IOM_MSPICFG_RDFCPOL_HIGH              0x00000000
#define AM_REG_IOM_MSPICFG_RDFCPOL_LOW               0x00400000

// selects the write flow control signal polarity. The transfers are halted when
// the selected flow control signal is OPPOSITE polarity of bit. (For example:
// WTFCPOL = 0 will allow a IRQ=1 to pause transfers).
#define AM_REG_IOM_MSPICFG_WTFCPOL_S                 21
#define AM_REG_IOM_MSPICFG_WTFCPOL_M                 0x00200000
#define AM_REG_IOM_MSPICFG_WTFCPOL(n)                (((uint32_t)(n) << 21) & 0x00200000)
#define AM_REG_IOM_MSPICFG_WTFCPOL_HIGH              0x00000000
#define AM_REG_IOM_MSPICFG_WTFCPOL_LOW               0x00200000

// selects the write mode flow control signal.
#define AM_REG_IOM_MSPICFG_WTFCIRQ_S                 20
#define AM_REG_IOM_MSPICFG_WTFCIRQ_M                 0x00100000
#define AM_REG_IOM_MSPICFG_WTFCIRQ(n)                (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_IOM_MSPICFG_WTFCIRQ_MISO              0x00000000
#define AM_REG_IOM_MSPICFG_WTFCIRQ_IRQ               0x00100000

// inverts MOSI when flow control is enabled.
#define AM_REG_IOM_MSPICFG_MOSIINV_S                 18
#define AM_REG_IOM_MSPICFG_MOSIINV_M                 0x00040000
#define AM_REG_IOM_MSPICFG_MOSIINV(n)                (((uint32_t)(n) << 18) & 0x00040000)
#define AM_REG_IOM_MSPICFG_MOSIINV_NORMAL            0x00000000
#define AM_REG_IOM_MSPICFG_MOSIINV_INVERT            0x00040000

// enables read mode flow control.
#define AM_REG_IOM_MSPICFG_RDFC_S                    17
#define AM_REG_IOM_MSPICFG_RDFC_M                    0x00020000
#define AM_REG_IOM_MSPICFG_RDFC(n)                   (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_IOM_MSPICFG_RDFC_DIS                  0x00000000
#define AM_REG_IOM_MSPICFG_RDFC_EN                   0x00020000

// enables write mode flow control.
#define AM_REG_IOM_MSPICFG_WTFC_S                    16
#define AM_REG_IOM_MSPICFG_WTFC_M                    0x00010000
#define AM_REG_IOM_MSPICFG_WTFC(n)                   (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_IOM_MSPICFG_WTFC_DIS                  0x00000000
#define AM_REG_IOM_MSPICFG_WTFC_EN                   0x00010000

// Enables full duplex mode for Master SPI write operations.  Data will be
// captured simultaneously into the read fifo
#define AM_REG_IOM_MSPICFG_FULLDUP_S                 2
#define AM_REG_IOM_MSPICFG_FULLDUP_M                 0x00000004
#define AM_REG_IOM_MSPICFG_FULLDUP(n)                (((uint32_t)(n) << 2) & 0x00000004)

// selects SPI phase.
#define AM_REG_IOM_MSPICFG_SPHA_S                    1
#define AM_REG_IOM_MSPICFG_SPHA_M                    0x00000002
#define AM_REG_IOM_MSPICFG_SPHA(n)                   (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOM_MSPICFG_SPHA_SAMPLE_LEADING_EDGE  0x00000000
#define AM_REG_IOM_MSPICFG_SPHA_SAMPLE_TRAILING_EDGE 0x00000002

// selects SPI polarity.
#define AM_REG_IOM_MSPICFG_SPOL_S                    0
#define AM_REG_IOM_MSPICFG_SPOL_M                    0x00000001
#define AM_REG_IOM_MSPICFG_SPOL(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOM_MSPICFG_SPOL_CLK_BASE_0           0x00000000
#define AM_REG_IOM_MSPICFG_SPOL_CLK_BASE_1           0x00000001

//*****************************************************************************
//
// IOM_MI2CCFG - I2C Master configuration
//
//*****************************************************************************
// Disable detection of clock stretch events smaller than 1 cycle
#define AM_REG_IOM_MI2CCFG_STRDIS_S                  24
#define AM_REG_IOM_MI2CCFG_STRDIS_M                  0x01000000
#define AM_REG_IOM_MI2CCFG_STRDIS(n)                 (((uint32_t)(n) << 24) & 0x01000000)

// Number of Base clk cycles to wait before sampling the SCL clock to determine
// if a clock stretch event has occured
#define AM_REG_IOM_MI2CCFG_SMPCNT_S                  16
#define AM_REG_IOM_MI2CCFG_SMPCNT_M                  0x00FF0000
#define AM_REG_IOM_MI2CCFG_SMPCNT(n)                 (((uint32_t)(n) << 16) & 0x00FF0000)

// Number of IOCLK cycles to delay the SDA output en (all transitions affected).
// Used to delay data relative to clock
#define AM_REG_IOM_MI2CCFG_SDAENDLY_S                12
#define AM_REG_IOM_MI2CCFG_SDAENDLY_M                0x0000F000
#define AM_REG_IOM_MI2CCFG_SDAENDLY(n)               (((uint32_t)(n) << 12) & 0x0000F000)

// Number of IOCLK cycles to delay the rising edge of the SCL output en (clock
// will go low on this edge). Used to allow clock shaping.
#define AM_REG_IOM_MI2CCFG_SCLENDLY_S                8
#define AM_REG_IOM_MI2CCFG_SCLENDLY_M                0x00000F00
#define AM_REG_IOM_MI2CCFG_SCLENDLY(n)               (((uint32_t)(n) << 8) & 0x00000F00)

// Not used.  To reset the module, toggle the SMOD_EN for the module
#define AM_REG_IOM_MI2CCFG_MI2CRST_S                 6
#define AM_REG_IOM_MI2CCFG_MI2CRST_M                 0x00000040
#define AM_REG_IOM_MI2CCFG_MI2CRST(n)                (((uint32_t)(n) << 6) & 0x00000040)

// Delay to enable on the SDA output.  Values are 0x0-0x3.
#define AM_REG_IOM_MI2CCFG_SDADLY_S                  4
#define AM_REG_IOM_MI2CCFG_SDADLY_M                  0x00000030
#define AM_REG_IOM_MI2CCFG_SDADLY(n)                 (((uint32_t)(n) << 4) & 0x00000030)

// Enables multi-master arbitration for the I2C master.  If the bus is known to
// have only a single master, this function can be disabled to save clock cycles
// on I2C transactions
#define AM_REG_IOM_MI2CCFG_ARBEN_S                   2
#define AM_REG_IOM_MI2CCFG_ARBEN_M                   0x00000004
#define AM_REG_IOM_MI2CCFG_ARBEN(n)                  (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_IOM_MI2CCFG_ARBEN_ARBEN               0x00000004
#define AM_REG_IOM_MI2CCFG_ARBEN_ARBDIS              0x00000000

// Direction of data transmit and receive, MSB(0) or LSB(1) first.  Default per
// I2C specification is MSB first. This applies to both read and write data, and
// read data will be bit
#define AM_REG_IOM_MI2CCFG_I2CLSB_S                  1
#define AM_REG_IOM_MI2CCFG_I2CLSB_M                  0x00000002
#define AM_REG_IOM_MI2CCFG_I2CLSB(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOM_MI2CCFG_I2CLSB_MSBFIRST           0x00000000
#define AM_REG_IOM_MI2CCFG_I2CLSB_LSBFIRST           0x00000002

// Sets the I2C master device address size to either 7b (0) or 10b (1).
#define AM_REG_IOM_MI2CCFG_ADDRSZ_S                  0
#define AM_REG_IOM_MI2CCFG_ADDRSZ_M                  0x00000001
#define AM_REG_IOM_MI2CCFG_ADDRSZ(n)                 (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOM_MI2CCFG_ADDRSZ_ADDRSZ7            0x00000000
#define AM_REG_IOM_MI2CCFG_ADDRSZ_ADDRSZ10           0x00000001

//*****************************************************************************
//
// IOM_DEVCFG - I2C Device Configuration register
//
//*****************************************************************************
// I2C address of the device that the Master will use to target for read/write
// operations.  This can be either a 7b or 10b address.
#define AM_REG_IOM_DEVCFG_DEVADDR_S                  0
#define AM_REG_IOM_DEVCFG_DEVADDR_M                  0x000003FF
#define AM_REG_IOM_DEVCFG_DEVADDR(n)                 (((uint32_t)(n) << 0) & 0x000003FF)

//*****************************************************************************
//
// IOM_IOMDBG - IOM Debug Register
//
//*****************************************************************************
// Debug control for various options.   DBGDATA[1:0] is used to select between
// different debug data available in the DBG0 and DBG1 registers.
#define AM_REG_IOM_IOMDBG_DBGDATA_S                  3
#define AM_REG_IOM_IOMDBG_DBGDATA_M                  0xFFFFFFF8
#define AM_REG_IOM_IOMDBG_DBGDATA(n)                 (((uint32_t)(n) << 3) & 0xFFFFFFF8)

// APBCLK debug clock control.  Enable APB_CLK to be active when this bit is
// '1'.  Otherwise, the clock is controlled with gating from the logic as
// needed.
#define AM_REG_IOM_IOMDBG_APBCLKON_S                 2
#define AM_REG_IOM_IOMDBG_APBCLKON_M                 0x00000004
#define AM_REG_IOM_IOMDBG_APBCLKON(n)                (((uint32_t)(n) << 2) & 0x00000004)

// IOCLK debug clock control.  Enable IO_CLK to be active when this bit is '1'.
// Otherwise, the clock is controlled with gating from the logic as needed.
#define AM_REG_IOM_IOMDBG_IOCLKON_S                  1
#define AM_REG_IOM_IOMDBG_IOCLKON_M                  0x00000002
#define AM_REG_IOM_IOMDBG_IOCLKON(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// Debug Enable.  Setting bit will enable the update of data within this
// register, otherwise it is clock gated for power savings
#define AM_REG_IOM_IOMDBG_DBGEN_S                    0
#define AM_REG_IOM_IOMDBG_DBGEN_M                    0x00000001
#define AM_REG_IOM_IOMDBG_DBGEN(n)                   (((uint32_t)(n) << 0) & 0x00000001)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_IOM_H
