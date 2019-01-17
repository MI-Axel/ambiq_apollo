//*****************************************************************************
//
//  am_reg_pdm.h
//! @file
//!
//! @brief Register macros for the PDM module
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
#ifndef AM_REG_PDM_H
#define AM_REG_PDM_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_PDM_NUM_MODULES                       1
#define AM_REG_PDMn(n) \
    (REG_PDM_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_PDM_PCFG_O                            0x00000000
#define AM_REG_PDM_VCFG_O                            0x00000004
#define AM_REG_PDM_VOICESTAT_O                       0x00000008
#define AM_REG_PDM_FIFOREAD_O                        0x0000000C
#define AM_REG_PDM_FIFOFLUSH_O                       0x00000010
#define AM_REG_PDM_FIFOTHR_O                         0x00000014
#define AM_REG_PDM_DMATRIGEN_O                       0x00000240
#define AM_REG_PDM_DMATRIGSTAT_O                     0x00000244
#define AM_REG_PDM_DMACFG_O                          0x00000280
#define AM_REG_PDM_DMATOTCOUNT_O                     0x00000288
#define AM_REG_PDM_DMATARGADDR_O                     0x0000028C
#define AM_REG_PDM_DMASTAT_O                         0x00000290
#define AM_REG_PDM_INTEN_O                           0x00000200
#define AM_REG_PDM_INTSTAT_O                         0x00000204
#define AM_REG_PDM_INTCLR_O                          0x00000208
#define AM_REG_PDM_INTSET_O                          0x0000020C

//*****************************************************************************
//
// PDM_INTEN - IO Master Interrupts: Enable
//
//*****************************************************************************
// DMA Error receieved
#define AM_REG_PDM_INTEN_DERR_S                      4
#define AM_REG_PDM_INTEN_DERR_M                      0x00000010
#define AM_REG_PDM_INTEN_DERR(n)                     (((uint32_t)(n) << 4) & 0x00000010)

// DMA completed a transfer
#define AM_REG_PDM_INTEN_DCMP_S                      3
#define AM_REG_PDM_INTEN_DCMP_M                      0x00000008
#define AM_REG_PDM_INTEN_DCMP(n)                     (((uint32_t)(n) << 3) & 0x00000008)

// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTEN_UNDFL_S                     2
#define AM_REG_PDM_INTEN_UNDFL_M                     0x00000004
#define AM_REG_PDM_INTEN_UNDFL(n)                    (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTEN_OVF_S                       1
#define AM_REG_PDM_INTEN_OVF_M                       0x00000002
#define AM_REG_PDM_INTEN_OVF(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTEN_THR_S                       0
#define AM_REG_PDM_INTEN_THR_M                       0x00000001
#define AM_REG_PDM_INTEN_THR(n)                      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTSTAT - IO Master Interrupts: Status
//
//*****************************************************************************
// DMA Error receieved
#define AM_REG_PDM_INTSTAT_DERR_S                    4
#define AM_REG_PDM_INTSTAT_DERR_M                    0x00000010
#define AM_REG_PDM_INTSTAT_DERR(n)                   (((uint32_t)(n) << 4) & 0x00000010)

// DMA completed a transfer
#define AM_REG_PDM_INTSTAT_DCMP_S                    3
#define AM_REG_PDM_INTSTAT_DCMP_M                    0x00000008
#define AM_REG_PDM_INTSTAT_DCMP(n)                   (((uint32_t)(n) << 3) & 0x00000008)

// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTSTAT_UNDFL_S                   2
#define AM_REG_PDM_INTSTAT_UNDFL_M                   0x00000004
#define AM_REG_PDM_INTSTAT_UNDFL(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTSTAT_OVF_S                     1
#define AM_REG_PDM_INTSTAT_OVF_M                     0x00000002
#define AM_REG_PDM_INTSTAT_OVF(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTSTAT_THR_S                     0
#define AM_REG_PDM_INTSTAT_THR_M                     0x00000001
#define AM_REG_PDM_INTSTAT_THR(n)                    (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTCLR - IO Master Interrupts: Clear
//
//*****************************************************************************
// DMA Error receieved
#define AM_REG_PDM_INTCLR_DERR_S                     4
#define AM_REG_PDM_INTCLR_DERR_M                     0x00000010
#define AM_REG_PDM_INTCLR_DERR(n)                    (((uint32_t)(n) << 4) & 0x00000010)

// DMA completed a transfer
#define AM_REG_PDM_INTCLR_DCMP_S                     3
#define AM_REG_PDM_INTCLR_DCMP_M                     0x00000008
#define AM_REG_PDM_INTCLR_DCMP(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTCLR_UNDFL_S                    2
#define AM_REG_PDM_INTCLR_UNDFL_M                    0x00000004
#define AM_REG_PDM_INTCLR_UNDFL(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTCLR_OVF_S                      1
#define AM_REG_PDM_INTCLR_OVF_M                      0x00000002
#define AM_REG_PDM_INTCLR_OVF(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTCLR_THR_S                      0
#define AM_REG_PDM_INTCLR_THR_M                      0x00000001
#define AM_REG_PDM_INTCLR_THR(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_INTSET - IO Master Interrupts: Set
//
//*****************************************************************************
// DMA Error receieved
#define AM_REG_PDM_INTSET_DERR_S                     4
#define AM_REG_PDM_INTSET_DERR_M                     0x00000010
#define AM_REG_PDM_INTSET_DERR(n)                    (((uint32_t)(n) << 4) & 0x00000010)

// DMA completed a transfer
#define AM_REG_PDM_INTSET_DCMP_S                     3
#define AM_REG_PDM_INTSET_DCMP_M                     0x00000008
#define AM_REG_PDM_INTSET_DCMP(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// This is the FIFO underflow interrupt.
#define AM_REG_PDM_INTSET_UNDFL_S                    2
#define AM_REG_PDM_INTSET_UNDFL_M                    0x00000004
#define AM_REG_PDM_INTSET_UNDFL(n)                   (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO overflow interrupt.
#define AM_REG_PDM_INTSET_OVF_S                      1
#define AM_REG_PDM_INTSET_OVF_M                      0x00000002
#define AM_REG_PDM_INTSET_OVF(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// This is the FIFO threshold interrupt.
#define AM_REG_PDM_INTSET_THR_S                      0
#define AM_REG_PDM_INTSET_THR_M                      0x00000001
#define AM_REG_PDM_INTSET_THR(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_PCFG - PDM Configuration Register
//
//*****************************************************************************
// Left/right channel swap.
#define AM_REG_PDM_PCFG_LRSWAP_S                     31
#define AM_REG_PDM_PCFG_LRSWAP_M                     0x80000000
#define AM_REG_PDM_PCFG_LRSWAP(n)                    (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PDM_PCFG_LRSWAP_EN                    0x80000000
#define AM_REG_PDM_PCFG_LRSWAP_NOSWAP                0x00000000

// Right channel PGA gain.
#define AM_REG_PDM_PCFG_PGARIGHT_S                   26
#define AM_REG_PDM_PCFG_PGARIGHT_M                   0x7C000000
#define AM_REG_PDM_PCFG_PGARIGHT(n)                  (((uint32_t)(n) << 26) & 0x7C000000)
#define AM_REG_PDM_PCFG_PGARIGHT_P405DB              0x7C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P390DB              0x78000000
#define AM_REG_PDM_PCFG_PGARIGHT_P375DB              0x74000000
#define AM_REG_PDM_PCFG_PGARIGHT_P360DB              0x70000000
#define AM_REG_PDM_PCFG_PGARIGHT_P345DB              0x6C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P330DB              0x68000000
#define AM_REG_PDM_PCFG_PGARIGHT_P315DB              0x64000000
#define AM_REG_PDM_PCFG_PGARIGHT_P300DB              0x60000000
#define AM_REG_PDM_PCFG_PGARIGHT_P285DB              0x5C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P270DB              0x58000000
#define AM_REG_PDM_PCFG_PGARIGHT_P255DB              0x54000000
#define AM_REG_PDM_PCFG_PGARIGHT_P240DB              0x50000000
#define AM_REG_PDM_PCFG_PGARIGHT_P225DB              0x4C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P210DB              0x48000000
#define AM_REG_PDM_PCFG_PGARIGHT_P195DB              0x44000000
#define AM_REG_PDM_PCFG_PGARIGHT_P180DB              0x40000000
#define AM_REG_PDM_PCFG_PGARIGHT_P165DB              0x3C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P150DB              0x38000000
#define AM_REG_PDM_PCFG_PGARIGHT_P135DB              0x34000000
#define AM_REG_PDM_PCFG_PGARIGHT_P120DB              0x30000000
#define AM_REG_PDM_PCFG_PGARIGHT_P105DB              0x2C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P90DB               0x28000000
#define AM_REG_PDM_PCFG_PGARIGHT_P75DB               0x24000000
#define AM_REG_PDM_PCFG_PGARIGHT_P60DB               0x20000000
#define AM_REG_PDM_PCFG_PGARIGHT_P45DB               0x1C000000
#define AM_REG_PDM_PCFG_PGARIGHT_P30DB               0x18000000
#define AM_REG_PDM_PCFG_PGARIGHT_P15DB               0x14000000
#define AM_REG_PDM_PCFG_PGARIGHT_0DB                 0x10000000
#define AM_REG_PDM_PCFG_PGARIGHT_M15DB               0x0C000000
#define AM_REG_PDM_PCFG_PGARIGHT_M300DB              0x08000000
#define AM_REG_PDM_PCFG_PGARIGHT_M45DB               0x04000000
#define AM_REG_PDM_PCFG_PGARIGHT_M60DB               0x00000000

// Left channel PGA gain.
#define AM_REG_PDM_PCFG_PGALEFT_S                    21
#define AM_REG_PDM_PCFG_PGALEFT_M                    0x03E00000
#define AM_REG_PDM_PCFG_PGALEFT(n)                   (((uint32_t)(n) << 21) & 0x03E00000)
#define AM_REG_PDM_PCFG_PGALEFT_P405DB               0x03E00000
#define AM_REG_PDM_PCFG_PGALEFT_P390DB               0x03C00000
#define AM_REG_PDM_PCFG_PGALEFT_P375DB               0x03A00000
#define AM_REG_PDM_PCFG_PGALEFT_P360DB               0x03800000
#define AM_REG_PDM_PCFG_PGALEFT_P345DB               0x03600000
#define AM_REG_PDM_PCFG_PGALEFT_P330DB               0x03400000
#define AM_REG_PDM_PCFG_PGALEFT_P315DB               0x03200000
#define AM_REG_PDM_PCFG_PGALEFT_P300DB               0x03000000
#define AM_REG_PDM_PCFG_PGALEFT_P285DB               0x02E00000
#define AM_REG_PDM_PCFG_PGALEFT_P270DB               0x02C00000
#define AM_REG_PDM_PCFG_PGALEFT_P255DB               0x02A00000
#define AM_REG_PDM_PCFG_PGALEFT_P240DB               0x02800000
#define AM_REG_PDM_PCFG_PGALEFT_P225DB               0x02600000
#define AM_REG_PDM_PCFG_PGALEFT_P210DB               0x02400000
#define AM_REG_PDM_PCFG_PGALEFT_P195DB               0x02200000
#define AM_REG_PDM_PCFG_PGALEFT_P180DB               0x02000000
#define AM_REG_PDM_PCFG_PGALEFT_P165DB               0x01E00000
#define AM_REG_PDM_PCFG_PGALEFT_P150DB               0x01C00000
#define AM_REG_PDM_PCFG_PGALEFT_P135DB               0x01A00000
#define AM_REG_PDM_PCFG_PGALEFT_P120DB               0x01800000
#define AM_REG_PDM_PCFG_PGALEFT_P105DB               0x01600000
#define AM_REG_PDM_PCFG_PGALEFT_P90DB                0x01400000
#define AM_REG_PDM_PCFG_PGALEFT_P75DB                0x01200000
#define AM_REG_PDM_PCFG_PGALEFT_P60DB                0x01000000
#define AM_REG_PDM_PCFG_PGALEFT_P45DB                0x00E00000
#define AM_REG_PDM_PCFG_PGALEFT_P30DB                0x00C00000
#define AM_REG_PDM_PCFG_PGALEFT_P15DB                0x00A00000
#define AM_REG_PDM_PCFG_PGALEFT_0DB                  0x00800000
#define AM_REG_PDM_PCFG_PGALEFT_M15DB                0x00600000
#define AM_REG_PDM_PCFG_PGALEFT_M300DB               0x00400000
#define AM_REG_PDM_PCFG_PGALEFT_M45DB                0x00200000
#define AM_REG_PDM_PCFG_PGALEFT_M60DB                0x00000000

// PDM_CLK frequency divisor.
#define AM_REG_PDM_PCFG_MCLKDIV_S                    17
#define AM_REG_PDM_PCFG_MCLKDIV_M                    0x00060000
#define AM_REG_PDM_PCFG_MCLKDIV(n)                   (((uint32_t)(n) << 17) & 0x00060000)
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV4              0x00060000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV3              0x00040000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV2              0x00020000
#define AM_REG_PDM_PCFG_MCLKDIV_MCKDIV1              0x00000000

// SINC decimation rate.
#define AM_REG_PDM_PCFG_SINCRATE_S                   10
#define AM_REG_PDM_PCFG_SINCRATE_M                   0x0001FC00
#define AM_REG_PDM_PCFG_SINCRATE(n)                  (((uint32_t)(n) << 10) & 0x0001FC00)

// High pass filter control.
#define AM_REG_PDM_PCFG_ADCHPD_S                     9
#define AM_REG_PDM_PCFG_ADCHPD_M                     0x00000200
#define AM_REG_PDM_PCFG_ADCHPD(n)                    (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_PDM_PCFG_ADCHPD_EN                    0x00000200
#define AM_REG_PDM_PCFG_ADCHPD_DIS                   0x00000000

// High pass filter coefficients.
#define AM_REG_PDM_PCFG_HPCUTOFF_S                   5
#define AM_REG_PDM_PCFG_HPCUTOFF_M                   0x000001E0
#define AM_REG_PDM_PCFG_HPCUTOFF(n)                  (((uint32_t)(n) << 5) & 0x000001E0)

// Number of clocks during gain-setting changes.
#define AM_REG_PDM_PCFG_CYCLES_S                     2
#define AM_REG_PDM_PCFG_CYCLES_M                     0x0000001C
#define AM_REG_PDM_PCFG_CYCLES(n)                    (((uint32_t)(n) << 2) & 0x0000001C)

// Soft mute control.
#define AM_REG_PDM_PCFG_SOFTMUTE_S                   1
#define AM_REG_PDM_PCFG_SOFTMUTE_M                   0x00000002
#define AM_REG_PDM_PCFG_SOFTMUTE(n)                  (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PDM_PCFG_SOFTMUTE_EN                  0x00000002
#define AM_REG_PDM_PCFG_SOFTMUTE_DIS                 0x00000000

// Data Streaming Control.
#define AM_REG_PDM_PCFG_PDMCOREEN_S                  0
#define AM_REG_PDM_PCFG_PDMCOREEN_M                  0x00000001
#define AM_REG_PDM_PCFG_PDMCOREEN(n)                 (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PDM_PCFG_PDMCOREEN_EN                 0x00000001
#define AM_REG_PDM_PCFG_PDMCOREEN_DIS                0x00000000

//*****************************************************************************
//
// PDM_VCFG - Voice Configuration Register
//
//*****************************************************************************
// Enable the IO clock.
#define AM_REG_PDM_VCFG_IOCLKEN_S                    31
#define AM_REG_PDM_VCFG_IOCLKEN_M                    0x80000000
#define AM_REG_PDM_VCFG_IOCLKEN(n)                   (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PDM_VCFG_IOCLKEN_DIS                  0x00000000
#define AM_REG_PDM_VCFG_IOCLKEN_EN                   0x80000000

// Reset the IP core.
#define AM_REG_PDM_VCFG_RSTB_S                       30
#define AM_REG_PDM_VCFG_RSTB_M                       0x40000000
#define AM_REG_PDM_VCFG_RSTB(n)                      (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_PDM_VCFG_RSTB_RESET                   0x00000000
#define AM_REG_PDM_VCFG_RSTB_NORM                    0x40000000

// Select the PDM input clock.
#define AM_REG_PDM_VCFG_PDMCLKSEL_S                  27
#define AM_REG_PDM_VCFG_PDMCLKSEL_M                  0x38000000
#define AM_REG_PDM_VCFG_PDMCLKSEL(n)                 (((uint32_t)(n) << 27) & 0x38000000)
#define AM_REG_PDM_VCFG_PDMCLKSEL_DISABLE            0x00000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_12MHz              0x08000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_6MHz               0x10000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_3MHz               0x18000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_1_5MHz             0x20000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_750KHz             0x28000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_375KHz             0x30000000
#define AM_REG_PDM_VCFG_PDMCLKSEL_187KHz             0x38000000

// Enable the serial clock.
#define AM_REG_PDM_VCFG_PDMCLKEN_S                   26
#define AM_REG_PDM_VCFG_PDMCLKEN_M                   0x04000000
#define AM_REG_PDM_VCFG_PDMCLKEN(n)                  (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_PDM_VCFG_PDMCLKEN_DIS                 0x00000000
#define AM_REG_PDM_VCFG_PDMCLKEN_EN                  0x04000000

// I2S interface enable.
#define AM_REG_PDM_VCFG_I2SEN_S                      20
#define AM_REG_PDM_VCFG_I2SEN_M                      0x00100000
#define AM_REG_PDM_VCFG_I2SEN(n)                     (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_PDM_VCFG_I2SEN_DIS                    0x00000000
#define AM_REG_PDM_VCFG_I2SEN_EN                     0x00100000

// I2S BCLK input inversion.
#define AM_REG_PDM_VCFG_BCLKINV_S                    19
#define AM_REG_PDM_VCFG_BCLKINV_M                    0x00080000
#define AM_REG_PDM_VCFG_BCLKINV(n)                   (((uint32_t)(n) << 19) & 0x00080000)
#define AM_REG_PDM_VCFG_BCLKINV_INV                  0x00000000
#define AM_REG_PDM_VCFG_BCLKINV_NORM                 0x00080000

// PDM clock sampling delay.
#define AM_REG_PDM_VCFG_DMICKDEL_S                   17
#define AM_REG_PDM_VCFG_DMICKDEL_M                   0x00020000
#define AM_REG_PDM_VCFG_DMICKDEL(n)                  (((uint32_t)(n) << 17) & 0x00020000)
#define AM_REG_PDM_VCFG_DMICKDEL_0CYC                0x00000000
#define AM_REG_PDM_VCFG_DMICKDEL_1CYC                0x00020000

// Select PDM input clock source.
#define AM_REG_PDM_VCFG_SELAP_S                      16
#define AM_REG_PDM_VCFG_SELAP_M                      0x00010000
#define AM_REG_PDM_VCFG_SELAP(n)                     (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_PDM_VCFG_SELAP_I2S                    0x00010000
#define AM_REG_PDM_VCFG_SELAP_INTERNAL               0x00000000

// PCM data packing enable.
#define AM_REG_PDM_VCFG_PCMPACK_S                    8
#define AM_REG_PDM_VCFG_PCMPACK_M                    0x00000100
#define AM_REG_PDM_VCFG_PCMPACK(n)                   (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PDM_VCFG_PCMPACK_DIS                  0x00000000
#define AM_REG_PDM_VCFG_PCMPACK_EN                   0x00000100

// Set PCM channels.
#define AM_REG_PDM_VCFG_CHSET_S                      3
#define AM_REG_PDM_VCFG_CHSET_M                      0x00000018
#define AM_REG_PDM_VCFG_CHSET(n)                     (((uint32_t)(n) << 3) & 0x00000018)
#define AM_REG_PDM_VCFG_CHSET_DIS                    0x00000000
#define AM_REG_PDM_VCFG_CHSET_LEFT                   0x00000008
#define AM_REG_PDM_VCFG_CHSET_RIGHT                  0x00000010
#define AM_REG_PDM_VCFG_CHSET_STEREO                 0x00000018

//*****************************************************************************
//
// PDM_VOICESTAT - Voice Status Register
//
//*****************************************************************************
// Valid 32-bit entries currently in the FIFO.
#define AM_REG_PDM_VOICESTAT_FIFOCNT_S               0
#define AM_REG_PDM_VOICESTAT_FIFOCNT_M               0x0000003F
#define AM_REG_PDM_VOICESTAT_FIFOCNT(n)              (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// PDM_FIFOREAD - FIFO Read
//
//*****************************************************************************
// FIFO read data.
#define AM_REG_PDM_FIFOREAD_FIFOREAD_S               0
#define AM_REG_PDM_FIFOREAD_FIFOREAD_M               0xFFFFFFFF
#define AM_REG_PDM_FIFOREAD_FIFOREAD(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// PDM_FIFOFLUSH - FIFO Flush
//
//*****************************************************************************
// FIFO FLUSH.
#define AM_REG_PDM_FIFOFLUSH_FIFOFLUSH_S             0
#define AM_REG_PDM_FIFOFLUSH_FIFOFLUSH_M             0x00000001
#define AM_REG_PDM_FIFOFLUSH_FIFOFLUSH(n)            (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_FIFOTHR - FIFO Threshold
//
//*****************************************************************************
// FIFO Threshold value.   When the FIFO count is equal to, or larger than this
// value (in words), a THR interrupt is generated (if enabled)
#define AM_REG_PDM_FIFOTHR_FIFOTHR_S                 0
#define AM_REG_PDM_FIFOTHR_FIFOTHR_M                 0x0000001F
#define AM_REG_PDM_FIFOTHR_FIFOTHR(n)                (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// PDM_DMATRIGEN - DMA Trigger Enable Register
//
//*****************************************************************************
// Trigger DMA at FIFO 90 percent full.  This signal is also used internally for
// AUTOHIP function
#define AM_REG_PDM_DMATRIGEN_DTHR90_S                1
#define AM_REG_PDM_DMATRIGEN_DTHR90_M                0x00000002
#define AM_REG_PDM_DMATRIGEN_DTHR90(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Trigger DMA upon when FIFO iss filled to level indicated by the FIFO
// THRESHOLD,at granularity of 16 bytes only
#define AM_REG_PDM_DMATRIGEN_DTHR_S                  0
#define AM_REG_PDM_DMATRIGEN_DTHR_M                  0x00000001
#define AM_REG_PDM_DMATRIGEN_DTHR(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_DMATRIGSTAT - DMA Trigger Status Register
//
//*****************************************************************************
// Triggered DMA from FIFO reaching 90 percent full
#define AM_REG_PDM_DMATRIGSTAT_DTHR90STAT_S          1
#define AM_REG_PDM_DMATRIGSTAT_DTHR90STAT_M          0x00000002
#define AM_REG_PDM_DMATRIGSTAT_DTHR90STAT(n)         (((uint32_t)(n) << 1) & 0x00000002)

// Triggered DMA from FIFO reaching threshold
#define AM_REG_PDM_DMATRIGSTAT_DTHRSTAT_S            0
#define AM_REG_PDM_DMATRIGSTAT_DTHRSTAT_M            0x00000001
#define AM_REG_PDM_DMATRIGSTAT_DTHRSTAT(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PDM_DMACFG - DMA Configuration Register
//
//*****************************************************************************
// Power Off the ADC System upon DMACPL.
#define AM_REG_PDM_DMACFG_DPWROFF_S                  10
#define AM_REG_PDM_DMACFG_DPWROFF_M                  0x00000400
#define AM_REG_PDM_DMACFG_DPWROFF(n)                 (((uint32_t)(n) << 10) & 0x00000400)

// Raise priority to high on fifo full, and DMAPRI set to low
#define AM_REG_PDM_DMACFG_DAUTOHIP_S                 9
#define AM_REG_PDM_DMACFG_DAUTOHIP_M                 0x00000200
#define AM_REG_PDM_DMACFG_DAUTOHIP(n)                (((uint32_t)(n) << 9) & 0x00000200)

// Sets the Priority of the DMA request
#define AM_REG_PDM_DMACFG_DMAPRI_S                   8
#define AM_REG_PDM_DMACFG_DMAPRI_M                   0x00000100
#define AM_REG_PDM_DMACFG_DMAPRI(n)                  (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PDM_DMACFG_DMAPRI_LOW                 0x00000000
#define AM_REG_PDM_DMACFG_DMAPRI_HIGH                0x00000100

// Direction
#define AM_REG_PDM_DMACFG_DMADIR_S                   2
#define AM_REG_PDM_DMACFG_DMADIR_M                   0x00000004
#define AM_REG_PDM_DMACFG_DMADIR(n)                  (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PDM_DMACFG_DMADIR_P2M                 0x00000000
#define AM_REG_PDM_DMACFG_DMADIR_M2P                 0x00000004

// DMA Enable
#define AM_REG_PDM_DMACFG_DMAEN_S                    0
#define AM_REG_PDM_DMACFG_DMAEN_M                    0x00000001
#define AM_REG_PDM_DMACFG_DMAEN(n)                   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PDM_DMACFG_DMAEN_DIS                  0x00000000
#define AM_REG_PDM_DMACFG_DMAEN_EN                   0x00000001

//*****************************************************************************
//
// PDM_DMATOTCOUNT - DMA Total Transfer Count
//
//*****************************************************************************
// Total Transfer Count. The transfer count must be a multiple of the THR
// setting to avoid DMA overruns.
#define AM_REG_PDM_DMATOTCOUNT_TOTCOUNT_S            0
#define AM_REG_PDM_DMATOTCOUNT_TOTCOUNT_M            0x000FFFFF
#define AM_REG_PDM_DMATOTCOUNT_TOTCOUNT(n)           (((uint32_t)(n) << 0) & 0x000FFFFF)

//*****************************************************************************
//
// PDM_DMATARGADDR - DMA Target Address Register
//
//*****************************************************************************
// SRAM Target
#define AM_REG_PDM_DMATARGADDR_UTARGADDR_S           20
#define AM_REG_PDM_DMATARGADDR_UTARGADDR_M           0xFFF00000
#define AM_REG_PDM_DMATARGADDR_UTARGADDR(n)          (((uint32_t)(n) << 20) & 0xFFF00000)

// DMA Target Address. This register is not updated with the current address of
// the DMA, but will remain static with the original address during the DMA
// transfer.
#define AM_REG_PDM_DMATARGADDR_LTARGADDR_S           0
#define AM_REG_PDM_DMATARGADDR_LTARGADDR_M           0x000FFFFF
#define AM_REG_PDM_DMATARGADDR_LTARGADDR(n)          (((uint32_t)(n) << 0) & 0x000FFFFF)

//*****************************************************************************
//
// PDM_DMASTAT - DMA Status Register
//
//*****************************************************************************
// DMA Error
#define AM_REG_PDM_DMASTAT_DMAERR_S                  2
#define AM_REG_PDM_DMASTAT_DMAERR_M                  0x00000004
#define AM_REG_PDM_DMASTAT_DMAERR(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// DMA Transfer Complete
#define AM_REG_PDM_DMASTAT_DMACPL_S                  1
#define AM_REG_PDM_DMASTAT_DMACPL_M                  0x00000002
#define AM_REG_PDM_DMASTAT_DMACPL(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// DMA Transfer In Progress
#define AM_REG_PDM_DMASTAT_DMATIP_S                  0
#define AM_REG_PDM_DMASTAT_DMATIP_M                  0x00000001
#define AM_REG_PDM_DMASTAT_DMATIP(n)                 (((uint32_t)(n) << 0) & 0x00000001)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_PDM_H
