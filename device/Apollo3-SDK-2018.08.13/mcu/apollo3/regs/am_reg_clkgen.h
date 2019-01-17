//*****************************************************************************
//
//  am_reg_clkgen.h
//! @file
//!
//! @brief Register macros for the CLKGEN module
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
#ifndef AM_REG_CLKGEN_H
#define AM_REG_CLKGEN_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_CLKGEN_NUM_MODULES                    1
#define AM_REG_CLKGENn(n) \
    (REG_CLKGEN_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_CLKGEN_CALXT_O                        0x00000000
#define AM_REG_CLKGEN_CALRC_O                        0x00000004
#define AM_REG_CLKGEN_ACALCTR_O                      0x00000008
#define AM_REG_CLKGEN_OCTRL_O                        0x0000000C
#define AM_REG_CLKGEN_CLKOUT_O                       0x00000010
#define AM_REG_CLKGEN_CCTRL_O                        0x00000018
#define AM_REG_CLKGEN_STATUS_O                       0x0000001C
#define AM_REG_CLKGEN_HFADJ_O                        0x00000020
#define AM_REG_CLKGEN_CLOCKENSTAT_O                  0x00000028
#define AM_REG_CLKGEN_CLOCKEN2STAT_O                 0x0000002C
#define AM_REG_CLKGEN_CLOCKEN3STAT_O                 0x00000030
#define AM_REG_CLKGEN_FREQCTRL_O                     0x00000034
#define AM_REG_CLKGEN_BLEBUCKTONADJ_O                0x0000003C
#define AM_REG_CLKGEN_CLKKEY_O                       0x00000014
#define AM_REG_CLKGEN_INTRPTEN_O                     0x00000100
#define AM_REG_CLKGEN_INTRPTSTAT_O                   0x00000104
#define AM_REG_CLKGEN_INTRPTCLR_O                    0x00000108
#define AM_REG_CLKGEN_INTRPTSET_O                    0x0000010C

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_CLKGEN_CLKKEY_KEYVAL                  0x00000047

//*****************************************************************************
//
// CLKGEN_INTRPTEN - CLKGEN Interrupt Register: Enable
//
//*****************************************************************************
// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTRPTEN_OF_S                  2
#define AM_REG_CLKGEN_INTRPTEN_OF_M                  0x00000004
#define AM_REG_CLKGEN_INTRPTEN_OF(n)                 (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTRPTEN_ACC_S                 1
#define AM_REG_CLKGEN_INTRPTEN_ACC_M                 0x00000002
#define AM_REG_CLKGEN_INTRPTEN_ACC(n)                (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTRPTEN_ACF_S                 0
#define AM_REG_CLKGEN_INTRPTEN_ACF_M                 0x00000001
#define AM_REG_CLKGEN_INTRPTEN_ACF(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTRPTSTAT - CLKGEN Interrupt Register: Status
//
//*****************************************************************************
// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTRPTSTAT_OF_S                2
#define AM_REG_CLKGEN_INTRPTSTAT_OF_M                0x00000004
#define AM_REG_CLKGEN_INTRPTSTAT_OF(n)               (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTRPTSTAT_ACC_S               1
#define AM_REG_CLKGEN_INTRPTSTAT_ACC_M               0x00000002
#define AM_REG_CLKGEN_INTRPTSTAT_ACC(n)              (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTRPTSTAT_ACF_S               0
#define AM_REG_CLKGEN_INTRPTSTAT_ACF_M               0x00000001
#define AM_REG_CLKGEN_INTRPTSTAT_ACF(n)              (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTRPTCLR - CLKGEN Interrupt Register: Clear
//
//*****************************************************************************
// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTRPTCLR_OF_S                 2
#define AM_REG_CLKGEN_INTRPTCLR_OF_M                 0x00000004
#define AM_REG_CLKGEN_INTRPTCLR_OF(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTRPTCLR_ACC_S                1
#define AM_REG_CLKGEN_INTRPTCLR_ACC_M                0x00000002
#define AM_REG_CLKGEN_INTRPTCLR_ACC(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTRPTCLR_ACF_S                0
#define AM_REG_CLKGEN_INTRPTCLR_ACF_M                0x00000001
#define AM_REG_CLKGEN_INTRPTCLR_ACF(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_INTRPTSET - CLKGEN Interrupt Register: Set
//
//*****************************************************************************
// XT Oscillator Fail interrupt
#define AM_REG_CLKGEN_INTRPTSET_OF_S                 2
#define AM_REG_CLKGEN_INTRPTSET_OF_M                 0x00000004
#define AM_REG_CLKGEN_INTRPTSET_OF(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_CLKGEN_INTRPTSET_ACC_S                1
#define AM_REG_CLKGEN_INTRPTSET_ACC_M                0x00000002
#define AM_REG_CLKGEN_INTRPTSET_ACC(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_CLKGEN_INTRPTSET_ACF_S                0
#define AM_REG_CLKGEN_INTRPTSET_ACF_M                0x00000001
#define AM_REG_CLKGEN_INTRPTSET_ACF(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_CALXT - XT Oscillator Control
//
//*****************************************************************************
// XT Oscillator calibration value.  This register will enable the hardware to
// increase or decrease the number of cycles in a 16KHz clock derived from the
// original 32KHz version.  The most significant bit is the sign.  A '1' is a
// reduction, and a '0' is an addition.  This calibration value will add or
// reduce the number of cycles programmed here across a 32 second interval.  The
// maximum value that is effective is from -1024 to 1023.
#define AM_REG_CLKGEN_CALXT_CALXT_S                  0
#define AM_REG_CLKGEN_CALXT_CALXT_M                  0x000007FF
#define AM_REG_CLKGEN_CALXT_CALXT(n)                 (((uint32_t)(n) << 0) & 0x000007FF)

//*****************************************************************************
//
// CLKGEN_CALRC - RC Oscillator Control
//
//*****************************************************************************
// LFRC Oscillator calibration value.   This register will enable the hardware
// to increase or decrease the number of cycles in a 512 Hz clock derived from
// the original 1024 version.  The most significant bit is the sign.  A '1' is a
// reduction, and a '0' is an addition.  This calibration value will add or
// reduce the number of cycles programmed here across a 32 second interval.  The
// range is from -131072 (decimal) to 131071 (decimal).  This register is
// normally used in conjuction with ACALCTR register.  The CALRC register will
// load the ACALCTR register (bits 17:0) if the ACALCTR register is set to
// measure the LFRC with the XT clock.
#define AM_REG_CLKGEN_CALRC_CALRC_S                  0
#define AM_REG_CLKGEN_CALRC_CALRC_M                  0x0003FFFF
#define AM_REG_CLKGEN_CALRC_CALRC(n)                 (((uint32_t)(n) << 0) & 0x0003FFFF)

//*****************************************************************************
//
// CLKGEN_ACALCTR - Autocalibration Counter
//
//*****************************************************************************
// Autocalibration Counter result. Bits 17 down to 0 of this is feed directly to
// the CALRC register if ACAL register in OCTRL register is set to 1024SEC or
// 512SEC.
#define AM_REG_CLKGEN_ACALCTR_ACALCTR_S              0
#define AM_REG_CLKGEN_ACALCTR_ACALCTR_M              0x00FFFFFF
#define AM_REG_CLKGEN_ACALCTR_ACALCTR(n)             (((uint32_t)(n) << 0) & 0x00FFFFFF)

//*****************************************************************************
//
// CLKGEN_OCTRL - Oscillator Control
//
//*****************************************************************************
// Autocalibration control.  This selects the source to be used in the
// autocalibration flow.  This flow can also be used to measure an internal
// clock against an external clock source, with the external clock normally used
// as the reference.
#define AM_REG_CLKGEN_OCTRL_ACAL_S                   8
#define AM_REG_CLKGEN_OCTRL_ACAL_M                   0x00000700
#define AM_REG_CLKGEN_OCTRL_ACAL(n)                  (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_CLKGEN_OCTRL_ACAL_DIS                 0x00000000
#define AM_REG_CLKGEN_OCTRL_ACAL_1024SEC             0x00000200
#define AM_REG_CLKGEN_OCTRL_ACAL_512SEC              0x00000300
#define AM_REG_CLKGEN_OCTRL_ACAL_XTFREQ              0x00000600
#define AM_REG_CLKGEN_OCTRL_ACAL_EXTFREQ             0x00000700

// Selects the RTC oscillator (1 => LFRC, 0 => XT)
#define AM_REG_CLKGEN_OCTRL_OSEL_S                   7
#define AM_REG_CLKGEN_OCTRL_OSEL_M                   0x00000080
#define AM_REG_CLKGEN_OCTRL_OSEL(n)                  (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CLKGEN_OCTRL_OSEL_RTC_XT              0x00000000
#define AM_REG_CLKGEN_OCTRL_OSEL_RTC_LFRC            0x00000080

// Oscillator switch on failure function.  If this is set, then LFRC clock
// source will switch from XT to RC.
#define AM_REG_CLKGEN_OCTRL_FOS_S                    6
#define AM_REG_CLKGEN_OCTRL_FOS_M                    0x00000040
#define AM_REG_CLKGEN_OCTRL_FOS(n)                   (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CLKGEN_OCTRL_FOS_DIS                  0x00000000
#define AM_REG_CLKGEN_OCTRL_FOS_EN                   0x00000040

// Stop the LFRC Oscillator to the RTC
#define AM_REG_CLKGEN_OCTRL_STOPRC_S                 1
#define AM_REG_CLKGEN_OCTRL_STOPRC_M                 0x00000002
#define AM_REG_CLKGEN_OCTRL_STOPRC(n)                (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CLKGEN_OCTRL_STOPRC_EN                0x00000000
#define AM_REG_CLKGEN_OCTRL_STOPRC_STOP              0x00000002

// Stop the XT Oscillator to the RTC
#define AM_REG_CLKGEN_OCTRL_STOPXT_S                 0
#define AM_REG_CLKGEN_OCTRL_STOPXT_M                 0x00000001
#define AM_REG_CLKGEN_OCTRL_STOPXT(n)                (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_OCTRL_STOPXT_EN                0x00000000
#define AM_REG_CLKGEN_OCTRL_STOPXT_STOP              0x00000001

//*****************************************************************************
//
// CLKGEN_CLKOUT - CLKOUT Frequency Select
//
//*****************************************************************************
// Enable the CLKOUT signal
#define AM_REG_CLKGEN_CLKOUT_CKEN_S                  7
#define AM_REG_CLKGEN_CLKOUT_CKEN_M                  0x00000080
#define AM_REG_CLKGEN_CLKOUT_CKEN(n)                 (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CLKGEN_CLKOUT_CKEN_DIS                0x00000000
#define AM_REG_CLKGEN_CLKOUT_CKEN_EN                 0x00000080

// CLKOUT signal select
#define AM_REG_CLKGEN_CLKOUT_CKSEL_S                 0
#define AM_REG_CLKGEN_CLKOUT_CKSEL_M                 0x0000003F
#define AM_REG_CLKGEN_CLKOUT_CKSEL(n)                (((uint32_t)(n) << 0) & 0x0000003F)
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC              0x00000000
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2           0x00000001
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV4           0x00000002
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8           0x00000003
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV16          0x00000004
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV32          0x00000005
#define AM_REG_CLKGEN_CLKOUT_CKSEL_RTC_1Hz           0x00000010
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2M          0x00000016
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT                0x00000017
#define AM_REG_CLKGEN_CLKOUT_CKSEL_CG_100Hz          0x00000018
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2         0x00000023
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32        0x00000024
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV512       0x00000025
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32K       0x00000026
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV256         0x00000027
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8K          0x00000028
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV64K         0x00000029
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV16       0x0000002A
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV128      0x0000002B
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_1Hz         0x0000002C
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV4K       0x0000002D
#define AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV1M       0x0000002E
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV1M        0x00000031
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE              0x00000035
#define AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE_DIV16        0x00000036
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE_DIV32      0x00000037
#define AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE            0x00000039

//*****************************************************************************
//
// CLKGEN_CCTRL - HFRC Clock Control
//
//*****************************************************************************
// Core Clock divisor
#define AM_REG_CLKGEN_CCTRL_CORESEL_S                0
#define AM_REG_CLKGEN_CCTRL_CORESEL_M                0x00000001
#define AM_REG_CLKGEN_CCTRL_CORESEL(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_CCTRL_CORESEL_HFRC             0x00000000
#define AM_REG_CLKGEN_CCTRL_CORESEL_HFRC_DIV2        0x00000001

//*****************************************************************************
//
// CLKGEN_STATUS - Clock Generator Status
//
//*****************************************************************************
// XT Oscillator is enabled but not oscillating
#define AM_REG_CLKGEN_STATUS_OSCF_S                  1
#define AM_REG_CLKGEN_STATUS_OSCF_M                  0x00000002
#define AM_REG_CLKGEN_STATUS_OSCF(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// Current RTC oscillator (1 => LFRC, 0 => XT).  After an RTC oscillator change,
// it may take up to 2 seconds for this field to reflect the new oscillator.
#define AM_REG_CLKGEN_STATUS_OMODE_S                 0
#define AM_REG_CLKGEN_STATUS_OMODE_M                 0x00000001
#define AM_REG_CLKGEN_STATUS_OMODE(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CLKGEN_HFADJ - HFRC Adjustment
//
//*****************************************************************************
// Gain control for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_S              21
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_M              0x00E00000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN(n)             (((uint32_t)(n) << 21) & 0x00E00000)
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1      0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_2 0x00200000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_4 0x00400000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_8 0x00600000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_16 0x00800000
#define AM_REG_CLKGEN_HFADJ_HFADJGAIN_Gain_of_1_in_32 0x00A00000

// XT warmup period for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_S               20
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_M               0x00100000
#define AM_REG_CLKGEN_HFADJ_HFWARMUP(n)              (((uint32_t)(n) << 20) & 0x00100000)
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_1SEC            0x00000000
#define AM_REG_CLKGEN_HFADJ_HFWARMUP_2SEC            0x00100000

// Target HFRC adjustment value.
#define AM_REG_CLKGEN_HFADJ_HFXTADJ_S                8
#define AM_REG_CLKGEN_HFADJ_HFXTADJ_M                0x000FFF00
#define AM_REG_CLKGEN_HFADJ_HFXTADJ(n)               (((uint32_t)(n) << 8) & 0x000FFF00)

// Repeat period for HFRC adjustment
#define AM_REG_CLKGEN_HFADJ_HFADJCK_S                1
#define AM_REG_CLKGEN_HFADJ_HFADJCK_M                0x0000000E
#define AM_REG_CLKGEN_HFADJ_HFADJCK(n)               (((uint32_t)(n) << 1) & 0x0000000E)
#define AM_REG_CLKGEN_HFADJ_HFADJCK_4SEC             0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJCK_16SEC            0x00000002
#define AM_REG_CLKGEN_HFADJ_HFADJCK_32SEC            0x00000004
#define AM_REG_CLKGEN_HFADJ_HFADJCK_64SEC            0x00000006
#define AM_REG_CLKGEN_HFADJ_HFADJCK_128SEC           0x00000008
#define AM_REG_CLKGEN_HFADJ_HFADJCK_256SEC           0x0000000A
#define AM_REG_CLKGEN_HFADJ_HFADJCK_512SEC           0x0000000C
#define AM_REG_CLKGEN_HFADJ_HFADJCK_1024SEC          0x0000000E

// HFRC adjustment control
#define AM_REG_CLKGEN_HFADJ_HFADJEN_S                0
#define AM_REG_CLKGEN_HFADJ_HFADJEN_M                0x00000001
#define AM_REG_CLKGEN_HFADJ_HFADJEN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_HFADJ_HFADJEN_DIS              0x00000000
#define AM_REG_CLKGEN_HFADJ_HFADJEN_EN               0x00000001

//*****************************************************************************
//
// CLKGEN_CLOCKENSTAT - Clock Enable Status
//
//*****************************************************************************
// Clock enable status
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_S      0
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_M      0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT(n)     (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_ADC_CLKEN 0x00000001
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_ACTIVITY_CLKEN 0x00000002
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_AOH_CLKEN 0x00000004
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_AOL_CLKEN 0x00000008
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_APB_CLKEN 0x00000010
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_BLEL_CLKEN 0x00000020
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_HCPA_CLKEN 0x00000040
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_HCPB_CLKEN 0x00000080
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_HCPC_CLKEN 0x00000100
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_MSPI_CLKEN 0x00000200
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_APBDMA_PDM_CLKEN 0x00000400
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_BLEIF_CLK_CLKEN 0x00000800
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_BLEIF_CLK32K_CLKEN 0x00001000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER_CLKEN 0x00002000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER0A_CLKEN 0x00004000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER0B_CLKEN 0x00008000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER1A_CLKEN 0x00010000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER1B_CLKEN 0x00020000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER2A_CLKEN 0x00040000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER2B_CLKEN 0x00080000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER3A_CLKEN 0x00100000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER3B_CLKEN 0x00200000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER4A_CLKEN 0x00400000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER4B_CLKEN 0x00800000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER5A_CLKEN 0x01000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER5B_CLKEN 0x02000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER6A_CLKEN 0x04000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER6B_CLKEN 0x08000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER7A_CLKEN 0x10000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_CTIMER7B_CLKEN 0x20000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_DAP_CLKEN 0x40000000
#define AM_REG_CLKGEN_CLOCKENSTAT_CLOCKENSTAT_IOMSTRIFC0_CLKEN 0x80000000

//*****************************************************************************
//
// CLKGEN_CLOCKEN2STAT - Clock Enable Status
//
//*****************************************************************************
// Clock enable status 2
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_S    0
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_M    0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT(n)   (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_IOMSTRIFC1_CLKEN 0x00000001
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_IOMSTRIFC2_CLKEN 0x00000002
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_IOMSTRIFC3_CLKEN 0x00000004
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_IOMSTRIFC4_CLKEN 0x00000008
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_IOMSTRIFC5_CLKEN 0x00000010
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_PDM_CLKEN 0x00000020
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_PDMIFC_CLKEN 0x00000040
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_PWRCTRL_CLKEN 0x00000080
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_RSTGEN_CLKEN 0x00000100
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_SCARD_CLKEN 0x00000200
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_SCARD_ALTAPB_CLKEN 0x00000400
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_STIMER_CNT_CLKEN 0x00000800
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_TPIU_CLKEN 0x00001000
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_UART0HF_CLKEN 0x00002000
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_UART1HF_CLKEN 0x00004000
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_XT_32KHZ_EN 0x40000000
#define AM_REG_CLKGEN_CLOCKEN2STAT_CLOCKEN2STAT_FORCEHFRC 0x80000000

//*****************************************************************************
//
// CLKGEN_CLOCKEN3STAT - Clock Enable Status
//
//*****************************************************************************
// Clock enable status 3
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_S    0
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_M    0xFFFFFFFF
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT(n)   (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_XTAL_enabled 0x01000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_HFRC_enabled 0x02000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_HFADJEN 0x04000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_HFRC_en_out 0x08000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_RTC_XT 0x10000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_clkout_xtal_en 0x20000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_clkout_hfrc_en 0x40000000
#define AM_REG_CLKGEN_CLOCKEN3STAT_CLOCKEN3STAT_flashclk_en 0x80000000

//*****************************************************************************
//
// CLKGEN_FREQCTRL - HFRC Frequency Control register
//
//*****************************************************************************
// This represents frequency burst status.
#define AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS_S         2
#define AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS_M         0x00000004
#define AM_REG_CLKGEN_FREQCTRL_BURSTSTATUS(n)        (((uint32_t)(n) << 2) & 0x00000004)

// Frequency Burst Request Acknowledge. Frequency burst requested is always
// acknowledged whether burst is granted or not depending on feature enable.
#define AM_REG_CLKGEN_FREQCTRL_BURSTACK_S            1
#define AM_REG_CLKGEN_FREQCTRL_BURSTACK_M            0x00000002
#define AM_REG_CLKGEN_FREQCTRL_BURSTACK(n)           (((uint32_t)(n) << 1) & 0x00000002)

// Frequency Burst Enable Request
#define AM_REG_CLKGEN_FREQCTRL_BURSTREQ_S            0
#define AM_REG_CLKGEN_FREQCTRL_BURSTREQ_M            0x00000001
#define AM_REG_CLKGEN_FREQCTRL_BURSTREQ(n)           (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CLKGEN_FREQCTRL_BURSTREQ_DIS          0x00000000
#define AM_REG_CLKGEN_FREQCTRL_BURSTREQ_EN           0x00000001

//*****************************************************************************
//
// CLKGEN_BLEBUCKTONADJ - BLE BUCK TON ADJUST
//
//*****************************************************************************
// BLEBUCK ZERO LENGTH DETECT ENABLE
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_S 27
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_M 0x08000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN(n) (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_DIS 0x00000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTEN_EN 0x08000000

// BLEBUCK ZERO LENGTH DETECT TRIM
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_S 23
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_M 0x07800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM(n) (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetF 0x07800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetE 0x07000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetD 0x06800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetC 0x06000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetB 0x05800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_SetA 0x05000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set9 0x04800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set8 0x04000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set7 0x03800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set6 0x03000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set5 0x02800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set4 0x02000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set3 0x01800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set2 0x01000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set1 0x00800000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_ZEROLENDETECTTRIM_Set0 0x00000000

// TON ADJUST ENABLE
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_S    22
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_M    0x00400000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN(n)   (((uint32_t)(n) << 22) & 0x00400000)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_DIS  0x00000000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTEN_EN   0x00400000

// TON ADJUST PERIOD
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_S 20
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_M 0x00300000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD(n) (((uint32_t)(n) << 20) & 0x00300000)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_3KHz 0x00300000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_12KHz 0x00200000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_47KHz 0x00100000
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONADJUSTPERIOD_HFRC_94KHz 0x00000000

// TON ADJUST HIGH THRESHOLD.  Suggested values are #15(94KHz) #2A(47Khz)
// #A6(12Khz) #29A(3Khz)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONHIGHTHRESHOLD_S 10
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONHIGHTHRESHOLD_M 0x000FFC00
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONHIGHTHRESHOLD(n) (((uint32_t)(n) << 10) & 0x000FFC00)

// TON ADJUST LOW THRESHOLD.  Suggested values are #A(94KHz) #15(47KHz)
// #53(12Khz) #14D(3Khz)
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONLOWTHRESHOLD_S 0
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONLOWTHRESHOLD_M 0x000003FF
#define AM_REG_CLKGEN_BLEBUCKTONADJ_TONLOWTHRESHOLD(n) (((uint32_t)(n) << 0) & 0x000003FF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_CLKGEN_H
