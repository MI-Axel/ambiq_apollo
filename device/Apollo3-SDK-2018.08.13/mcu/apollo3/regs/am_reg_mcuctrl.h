//*****************************************************************************
//
//  am_reg_mcuctrl.h
//! @file
//!
//! @brief Register macros for the MCUCTRL module
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
#ifndef AM_REG_MCUCTRL_H
#define AM_REG_MCUCTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_MCUCTRL_NUM_MODULES                   1
#define AM_REG_MCUCTRLn(n) \
    (REG_MCUCTRL_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_MCUCTRL_CHIPPN_O                      0x00000000
#define AM_REG_MCUCTRL_CHIPID0_O                     0x00000004
#define AM_REG_MCUCTRL_CHIPID1_O                     0x00000008
#define AM_REG_MCUCTRL_CHIPREV_O                     0x0000000C
#define AM_REG_MCUCTRL_VENDORID_O                    0x00000010
#define AM_REG_MCUCTRL_SKU_O                         0x00000014
#define AM_REG_MCUCTRL_FEATUREENABLE_O               0x00000018
#define AM_REG_MCUCTRL_DEBUGGER_O                    0x00000020
#define AM_REG_MCUCTRL_BODCTRL_O                     0x00000100
#define AM_REG_MCUCTRL_ADCPWRDLY_O                   0x00000104
#define AM_REG_MCUCTRL_ADCCAL_O                      0x0000010C
#define AM_REG_MCUCTRL_ADCBATTLOAD_O                 0x00000110
#define AM_REG_MCUCTRL_ADCTRIM_O                     0x00000118
#define AM_REG_MCUCTRL_ADCREFCOMP_O                  0x0000011C
#define AM_REG_MCUCTRL_XTALCTRL_O                    0x00000120
#define AM_REG_MCUCTRL_XTALGENCTRL_O                 0x00000124
#define AM_REG_MCUCTRL_MISCCTRL_O                    0x00000198
#define AM_REG_MCUCTRL_BOOTLOADER_O                  0x000001A0
#define AM_REG_MCUCTRL_SHADOWVALID_O                 0x000001A4
#define AM_REG_MCUCTRL_SCRATCH0_O                    0x000001B0
#define AM_REG_MCUCTRL_SCRATCH1_O                    0x000001B4
#define AM_REG_MCUCTRL_ICODEFAULTADDR_O              0x000001C0
#define AM_REG_MCUCTRL_DCODEFAULTADDR_O              0x000001C4
#define AM_REG_MCUCTRL_SYSFAULTADDR_O                0x000001C8
#define AM_REG_MCUCTRL_FAULTSTATUS_O                 0x000001CC
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_O              0x000001D0
#define AM_REG_MCUCTRL_DBGR1_O                       0x00000200
#define AM_REG_MCUCTRL_DBGR2_O                       0x00000204
#define AM_REG_MCUCTRL_PMUENABLE_O                   0x00000220
#define AM_REG_MCUCTRL_TPIUCTRL_O                    0x00000250
#define AM_REG_MCUCTRL_OTAPOINTER_O                  0x00000264
#define AM_REG_MCUCTRL_APBDMACTRL_O                  0x00000280
#define AM_REG_MCUCTRL_SRAMMODE_O                    0x00000284
#define AM_REG_MCUCTRL_SIMOBUCK4_O                   0x0000035C
#define AM_REG_MCUCTRL_BLEBUCK2_O                    0x00000368
#define AM_REG_MCUCTRL_FLASHWPROT0_O                 0x000003A0
#define AM_REG_MCUCTRL_FLASHWPROT1_O                 0x000003A4
#define AM_REG_MCUCTRL_FLASHRPROT0_O                 0x000003B0
#define AM_REG_MCUCTRL_FLASHRPROT1_O                 0x000003B4
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT0_O        0x000003C0
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT1_O        0x000003C4
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT0_O         0x000003D0
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT1_O         0x000003D4
#define AM_REG_MCUCTRL_KEXTCLKSEL_O                  0x00000348

//*****************************************************************************
//
// Key values.
//
//*****************************************************************************
#define AM_REG_MCUCTRL_KEXTCLKSEL_KEYVAL             0x00000053

//*****************************************************************************
//
// MCUCTRL_CHIPPN - Chip Information Register
//
//*****************************************************************************
// BCD part number.
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_S              0
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_M              0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM(n)             (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_APOLLO3        0x06000000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_APOLLO2        0x03000000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_APOLLO         0x01000000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PN_M           0xFF000000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PN_S           0x00000018
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_FLASHSIZE_M    0x00F00000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_FLASHSIZE_S    0x00000014
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_SRAMSIZE_M     0x000F0000
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_SRAMSIZE_S     0x00000010
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_REV_M          0x0000FF00
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_REV_S          0x00000008
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PKG_M          0x000000C0
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PKG_S          0x00000006
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PINS_M         0x00000038
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_PINS_S         0x00000003
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_TEMP_M         0x00000006
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_TEMP_S         0x00000001
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_QUAL_M         0x00000001
#define AM_REG_MCUCTRL_CHIPPN_PARTNUM_QUAL_S         0x00000000

//*****************************************************************************
//
// MCUCTRL_CHIPID0 - Unique Chip ID 0
//
//*****************************************************************************
// Unique chip ID 0.
#define AM_REG_MCUCTRL_CHIPID0_CHIPID0_S             0
#define AM_REG_MCUCTRL_CHIPID0_CHIPID0_M             0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIPID0_CHIPID0(n)            (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIPID0_CHIPID0_APOLLO3       0x00000000

//*****************************************************************************
//
// MCUCTRL_CHIPID1 - Unique Chip ID 1
//
//*****************************************************************************
// Unique chip ID 1.
#define AM_REG_MCUCTRL_CHIPID1_CHIPID1_S             0
#define AM_REG_MCUCTRL_CHIPID1_CHIPID1_M             0xFFFFFFFF
#define AM_REG_MCUCTRL_CHIPID1_CHIPID1(n)            (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_CHIPID1_CHIPID1_APOLLO3       0x00000000

//*****************************************************************************
//
// MCUCTRL_CHIPREV - Chip Revision
//
//*****************************************************************************
// Silicon Part ID
#define AM_REG_MCUCTRL_CHIPREV_SIPART_S              8
#define AM_REG_MCUCTRL_CHIPREV_SIPART_M              0x000FFF00
#define AM_REG_MCUCTRL_CHIPREV_SIPART(n)             (((uint32_t)(n) << 8) & 0x000FFF00)

// Major Revision ID.
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_S              4
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_M              0x000000F0
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ(n)             (((uint32_t)(n) << 4) & 0x000000F0)
#define AM_REG_MCUCTRL_CHIPREV_REVMAJ_A              0x00000010

// Minor Revision ID.
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_S              0
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_M              0x0000000F
#define AM_REG_MCUCTRL_CHIPREV_REVMIN(n)             (((uint32_t)(n) << 0) & 0x0000000F)
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_REV1           0x00000002
#define AM_REG_MCUCTRL_CHIPREV_REVMIN_REV0           0x00000001

//*****************************************************************************
//
// MCUCTRL_VENDORID - Unique Vendor ID
//
//*****************************************************************************
// Unique Vendor ID
#define AM_REG_MCUCTRL_VENDORID_VENDORID_S           0
#define AM_REG_MCUCTRL_VENDORID_VENDORID_M           0xFFFFFFFF
#define AM_REG_MCUCTRL_VENDORID_VENDORID(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_MCUCTRL_VENDORID_VENDORID_AMBIQ       0x414D4251

//*****************************************************************************
//
// MCUCTRL_SKU - Unique Chip SKU
//
//*****************************************************************************
// Secure boot feature allowed
#define AM_REG_MCUCTRL_SKU_SECBOOT_S                 2
#define AM_REG_MCUCTRL_SKU_SECBOOT_M                 0x00000004
#define AM_REG_MCUCTRL_SKU_SECBOOT(n)                (((uint32_t)(n) << 2) & 0x00000004)

// Allow BLE feature
#define AM_REG_MCUCTRL_SKU_ALLOWBLE_S                1
#define AM_REG_MCUCTRL_SKU_ALLOWBLE_M                0x00000002
#define AM_REG_MCUCTRL_SKU_ALLOWBLE(n)               (((uint32_t)(n) << 1) & 0x00000002)

// Allow Burst feature
#define AM_REG_MCUCTRL_SKU_ALLOWBURST_S              0
#define AM_REG_MCUCTRL_SKU_ALLOWBURST_M              0x00000001
#define AM_REG_MCUCTRL_SKU_ALLOWBURST(n)             (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_FEATUREENABLE - Feature Enable on Burst and BLE
//
//*****************************************************************************
// Availability of Burst functionality
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTAVAIL_S    6
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTAVAIL_M    0x00000040
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTAVAIL(n)   (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTAVAIL_AVAIL 0x00000040
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTAVAIL_NOTAVAIL 0x00000000

// ACK for BURSTREQ
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTACK_S      5
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTACK_M      0x00000020
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTACK(n)     (((uint32_t)(n) << 5) & 0x00000020)

// Controls the Burst functionality
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTREQ_S      4
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTREQ_M      0x00000010
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTREQ(n)     (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTREQ_EN     0x00000010
#define AM_REG_MCUCTRL_FEATUREENABLE_BURSTREQ_DIS    0x00000000

// AVAILABILITY of the BLE functionality
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_S      2
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_M      0x00000004
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL(n)     (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_AVAIL  0x00000004
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_NOTAVAIL 0x00000000

// ACK for BLEREQ
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEACK_S        1
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEACK_M        0x00000002
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEACK(n)       (((uint32_t)(n) << 1) & 0x00000002)

// Controls the BLE functionality
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_S        0
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_M        0x00000001
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ(n)       (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_EN       0x00000001
#define AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_DIS      0x00000000

//*****************************************************************************
//
// MCUCTRL_DEBUGGER - Debugger Control
//
//*****************************************************************************
// Lockout of debugger (SWD).
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT_S            0
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT_M            0x00000001
#define AM_REG_MCUCTRL_DEBUGGER_LOCKOUT(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_BODCTRL - BOD control Register
//
//*****************************************************************************
// BODH External Reference Select. Note: the SWE mux select in PWRSEQ2SWE must
// be set for this to take effect.
#define AM_REG_MCUCTRL_BODCTRL_BODHVREFSEL_S         5
#define AM_REG_MCUCTRL_BODCTRL_BODHVREFSEL_M         0x00000020
#define AM_REG_MCUCTRL_BODCTRL_BODHVREFSEL(n)        (((uint32_t)(n) << 5) & 0x00000020)

// BODL External Reference Select. Note: the SWE mux select in PWRSEQ2SWE must
// be set for this to take effect.
#define AM_REG_MCUCTRL_BODCTRL_BODLVREFSEL_S         4
#define AM_REG_MCUCTRL_BODCTRL_BODLVREFSEL_M         0x00000010
#define AM_REG_MCUCTRL_BODCTRL_BODLVREFSEL(n)        (((uint32_t)(n) << 4) & 0x00000010)

// BODF Power Down.
#define AM_REG_MCUCTRL_BODCTRL_BODFPWD_S             3
#define AM_REG_MCUCTRL_BODCTRL_BODFPWD_M             0x00000008
#define AM_REG_MCUCTRL_BODCTRL_BODFPWD(n)            (((uint32_t)(n) << 3) & 0x00000008)

// BODC Power Down.
#define AM_REG_MCUCTRL_BODCTRL_BODCPWD_S             2
#define AM_REG_MCUCTRL_BODCTRL_BODCPWD_M             0x00000004
#define AM_REG_MCUCTRL_BODCTRL_BODCPWD(n)            (((uint32_t)(n) << 2) & 0x00000004)

// BODH Power Down.
#define AM_REG_MCUCTRL_BODCTRL_BODHPWD_S             1
#define AM_REG_MCUCTRL_BODCTRL_BODHPWD_M             0x00000002
#define AM_REG_MCUCTRL_BODCTRL_BODHPWD(n)            (((uint32_t)(n) << 1) & 0x00000002)

// BODL Power Down.
#define AM_REG_MCUCTRL_BODCTRL_BODLPWD_S             0
#define AM_REG_MCUCTRL_BODCTRL_BODLPWD_M             0x00000001
#define AM_REG_MCUCTRL_BODCTRL_BODLPWD(n)            (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_ADCPWRDLY - ADC Power Up Delay Control
//
//*****************************************************************************
// ADC Reference Keeper enable delay in 16 ADC CLK increments for ADC_CLKSEL =
// 0x1, 8 ADC CLOCK increments for ADC_CLKSEL = 0x2.
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1_S           8
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1_M           0x0000FF00
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR1(n)          (((uint32_t)(n) << 8) & 0x0000FF00)

// ADC Reference Buffer Power Enable delay in 64 ADC CLK increments for
// ADC_CLKSEL = 0x1, 32 ADC CLOCK increments for ADC_CLKSEL = 0x2.
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0_S           0
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0_M           0x000000FF
#define AM_REG_MCUCTRL_ADCPWRDLY_ADCPWR0(n)          (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// MCUCTRL_ADCCAL - ADC Calibration Control
//
//*****************************************************************************
// Status for ADC Calibration
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_S        1
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_M        0x00000002
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED(n)       (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_FALSE    0x00000000
#define AM_REG_MCUCTRL_ADCCAL_ADCCALIBRATED_TRUE     0x00000002

// Run ADC Calibration on initial power up sequence
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_S           0
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_M           0x00000001
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_DIS         0x00000000
#define AM_REG_MCUCTRL_ADCCAL_CALONPWRUP_EN          0x00000001

//*****************************************************************************
//
// MCUCTRL_ADCBATTLOAD - ADC Battery Load Enable
//
//*****************************************************************************
// Enable the ADC battery load resistor
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_S        0
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_M        0x00000001
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD(n)       (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_DIS      0x00000000
#define AM_REG_MCUCTRL_ADCBATTLOAD_BATTLOAD_EN       0x00000001

//*****************************************************************************
//
// MCUCTRL_ADCTRIM - ADC Trims
//
//*****************************************************************************
// ADC reference buffer input bias trim
#define AM_REG_MCUCTRL_ADCTRIM_ADCRFBUFIBTRIM_S      11
#define AM_REG_MCUCTRL_ADCTRIM_ADCRFBUFIBTRIM_M      0x00001800
#define AM_REG_MCUCTRL_ADCTRIM_ADCRFBUFIBTRIM(n)     (((uint32_t)(n) << 11) & 0x00001800)

// ADC Reference buffer trim
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFBUFTRIM_S       6
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFBUFTRIM_M       0x000007C0
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFBUFTRIM(n)      (((uint32_t)(n) << 6) & 0x000007C0)

// ADC Reference Ibias trim
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFKEEPIBTRIM_S    0
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFKEEPIBTRIM_M    0x00000003
#define AM_REG_MCUCTRL_ADCTRIM_ADCREFKEEPIBTRIM(n)   (((uint32_t)(n) << 0) & 0x00000003)

//*****************************************************************************
//
// MCUCTRL_ADCREFCOMP - ADC Referece Keeper and Comparator Control
//
//*****************************************************************************
// ADC Reference comparator power down
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCRFCMPEN_S       16
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCRFCMPEN_M       0x00010000
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCRFCMPEN(n)      (((uint32_t)(n) << 16) & 0x00010000)

// ADC Reference Keeper Trim
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCREFKEEPTRIM_S   8
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCREFKEEPTRIM_M   0x00001F00
#define AM_REG_MCUCTRL_ADCREFCOMP_ADCREFKEEPTRIM(n)  (((uint32_t)(n) << 8) & 0x00001F00)

// Output of the ADC reference comparator
#define AM_REG_MCUCTRL_ADCREFCOMP_ADC_REFCOMP_OUT_S  0
#define AM_REG_MCUCTRL_ADCREFCOMP_ADC_REFCOMP_OUT_M  0x00000001
#define AM_REG_MCUCTRL_ADCREFCOMP_ADC_REFCOMP_OUT(n) (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_XTALCTRL - XTAL Oscillator Control
//
//*****************************************************************************
// XTAL ICOMP trim
#define AM_REG_MCUCTRL_XTALCTRL_XTALICOMPTRIM_S      8
#define AM_REG_MCUCTRL_XTALCTRL_XTALICOMPTRIM_M      0x00000300
#define AM_REG_MCUCTRL_XTALCTRL_XTALICOMPTRIM(n)     (((uint32_t)(n) << 8) & 0x00000300)

// XTAL IBUFF trim
#define AM_REG_MCUCTRL_XTALCTRL_XTALIBUFTRIM_S       6
#define AM_REG_MCUCTRL_XTALCTRL_XTALIBUFTRIM_M       0x000000C0
#define AM_REG_MCUCTRL_XTALCTRL_XTALIBUFTRIM(n)      (((uint32_t)(n) << 6) & 0x000000C0)

// XTAL Power down on brown out.
#define AM_REG_MCUCTRL_XTALCTRL_PWDBODXTAL_S         5
#define AM_REG_MCUCTRL_XTALCTRL_PWDBODXTAL_M         0x00000020
#define AM_REG_MCUCTRL_XTALCTRL_PWDBODXTAL(n)        (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_MCUCTRL_XTALCTRL_PWDBODXTAL_PWRUPBOD  0x00000000
#define AM_REG_MCUCTRL_XTALCTRL_PWDBODXTAL_PWRDNBOD  0x00000020

// XTAL Oscillator Power Down Comparator.
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCMPRXTAL_S       4
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCMPRXTAL_M       0x00000010
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCMPRXTAL(n)      (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCMPRXTAL_PWRUPCOMP 0x00000010
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCMPRXTAL_PWRDNCOMP 0x00000000

// XTAL Oscillator Power Down Core.
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCOREXTAL_S       3
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCOREXTAL_M       0x00000008
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCOREXTAL(n)      (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCOREXTAL_PWRUPCORE 0x00000008
#define AM_REG_MCUCTRL_XTALCTRL_PDNBCOREXTAL_PWRDNCORE 0x00000000

// XTAL Oscillator Bypass Comparator.
#define AM_REG_MCUCTRL_XTALCTRL_BYPCMPRXTAL_S        2
#define AM_REG_MCUCTRL_XTALCTRL_BYPCMPRXTAL_M        0x00000004
#define AM_REG_MCUCTRL_XTALCTRL_BYPCMPRXTAL(n)       (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_XTALCTRL_BYPCMPRXTAL_USECOMP  0x00000000
#define AM_REG_MCUCTRL_XTALCTRL_BYPCMPRXTAL_BYPCOMP  0x00000004

// XTAL Oscillator Disable Feedback.
#define AM_REG_MCUCTRL_XTALCTRL_FDBKDSBLXTAL_S       1
#define AM_REG_MCUCTRL_XTALCTRL_FDBKDSBLXTAL_M       0x00000002
#define AM_REG_MCUCTRL_XTALCTRL_FDBKDSBLXTAL(n)      (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_XTALCTRL_FDBKDSBLXTAL_EN      0x00000000
#define AM_REG_MCUCTRL_XTALCTRL_FDBKDSBLXTAL_DIS     0x00000002

// XTAL Software Override Enable.
#define AM_REG_MCUCTRL_XTALCTRL_XTALSWE_S            0
#define AM_REG_MCUCTRL_XTALCTRL_XTALSWE_M            0x00000001
#define AM_REG_MCUCTRL_XTALCTRL_XTALSWE(n)           (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_XTALCTRL_XTALSWE_OVERRIDE_DIS 0x00000000
#define AM_REG_MCUCTRL_XTALCTRL_XTALSWE_OVERRIDE_EN  0x00000001

//*****************************************************************************
//
// MCUCTRL_XTALGENCTRL - XTAL Oscillator General Control
//
//*****************************************************************************
// XTAL IBIAS Kick start trim. This trim value is used during the startup
// process to enable a faster lock.
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALKSBIASTRIM_S  8
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALKSBIASTRIM_M  0x00003F00
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALKSBIASTRIM(n) (((uint32_t)(n) << 8) & 0x00003F00)

// XTAL BIAS trim
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALBIASTRIM_S    2
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALBIASTRIM_M    0x000000FC
#define AM_REG_MCUCTRL_XTALGENCTRL_XTALBIASTRIM(n)   (((uint32_t)(n) << 2) & 0x000000FC)

// Auto-calibration delay control
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_S        0
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_M        0x00000003
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP(n)       (((uint32_t)(n) << 0) & 0x00000003)
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_SEC1     0x00000000
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_SEC2     0x00000001
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_SEC4     0x00000002
#define AM_REG_MCUCTRL_XTALGENCTRL_ACWARMUP_SEC8     0x00000003

//*****************************************************************************
//
// MCUCTRL_MISCCTRL - Miscellaneous control register.
//
//*****************************************************************************
// BLE reset signal.
#define AM_REG_MCUCTRL_MISCCTRL_BLE_RESETN_S         5
#define AM_REG_MCUCTRL_MISCCTRL_BLE_RESETN_M         0x00000020
#define AM_REG_MCUCTRL_MISCCTRL_BLE_RESETN(n)        (((uint32_t)(n) << 5) & 0x00000020)

// Reserved bits, always leave unchanged.  The MISCCTRL register must be
// modified via atomic RMW, leaving this bitfield completely unmodified.
// Failure to do so will result in unpredictable behavior.
#define AM_REG_MCUCTRL_MISCCTRL_RESERVED_RW_0_S      0
#define AM_REG_MCUCTRL_MISCCTRL_RESERVED_RW_0_M      0x0000001F
#define AM_REG_MCUCTRL_MISCCTRL_RESERVED_RW_0(n)     (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// MCUCTRL_BOOTLOADER - Bootloader and secure boot functions
//
//*****************************************************************************
// Indicates whether the secure boot on warm reset is enabled
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST_S     30
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST_M     0xC0000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST(n)    (((uint32_t)(n) << 30) & 0xC0000000)
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST_DISABLED 0x00000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST_ENABLED 0x40000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTONRST_ERROR 0x80000000

// Indicates whether the secure boot on cold reset is enabled
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT_S          28
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT_M          0x30000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT(n)         (((uint32_t)(n) << 28) & 0x30000000)
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT_DISABLED   0x00000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT_ENABLED    0x10000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOT_ERROR      0x20000000

// Indicates whether the secure boot feature is enabled.
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE_S   26
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE_M   0x0C000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE(n)  (((uint32_t)(n) << 26) & 0x0C000000)
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE_DISABLED 0x00000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE_ENABLED 0x04000000
#define AM_REG_MCUCTRL_BOOTLOADER_SECBOOTFEATURE_ERROR 0x08000000

// Flash protection lock.  Always resets to 1, write 1 to clear.  Enables writes
// to flash protection register set.
#define AM_REG_MCUCTRL_BOOTLOADER_PROTLOCK_S         2
#define AM_REG_MCUCTRL_BOOTLOADER_PROTLOCK_M         0x00000004
#define AM_REG_MCUCTRL_BOOTLOADER_PROTLOCK(n)        (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_BOOTLOADER_PROTLOCK_LOCK      0x00000004

// Secure boot lock.  Always resets to 1, write 1 to clear.  Enables system
// visibility to bootloader until set.
#define AM_REG_MCUCTRL_BOOTLOADER_SBLOCK_S           1
#define AM_REG_MCUCTRL_BOOTLOADER_SBLOCK_M           0x00000002
#define AM_REG_MCUCTRL_BOOTLOADER_SBLOCK(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_BOOTLOADER_SBLOCK_LOCK        0x00000002

// Determines whether the bootloader code is visible at address 0x00000000 or
// not.  Resets to 1, write 1 to clear.
#define AM_REG_MCUCTRL_BOOTLOADER_BOOTLOADERLOW_S    0
#define AM_REG_MCUCTRL_BOOTLOADER_BOOTLOADERLOW_M    0x00000001
#define AM_REG_MCUCTRL_BOOTLOADER_BOOTLOADERLOW(n)   (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_BOOTLOADER_BOOTLOADERLOW_ADDR0 0x00000001

//*****************************************************************************
//
// MCUCTRL_SHADOWVALID - Register to indicate whether the shadow registers have
// been successfully loaded from the Flash Information Space.
//
//*****************************************************************************
// Indicates whether info0 contains valid data
#define AM_REG_MCUCTRL_SHADOWVALID_INFO0_VALID_S     2
#define AM_REG_MCUCTRL_SHADOWVALID_INFO0_VALID_M     0x00000004
#define AM_REG_MCUCTRL_SHADOWVALID_INFO0_VALID(n)    (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_SHADOWVALID_INFO0_VALID_VALID 0x00000004

// Indicates whether the bootloader should sleep or deep sleep if no image
// loaded.
#define AM_REG_MCUCTRL_SHADOWVALID_BLDSLEEP_S        1
#define AM_REG_MCUCTRL_SHADOWVALID_BLDSLEEP_M        0x00000002
#define AM_REG_MCUCTRL_SHADOWVALID_BLDSLEEP(n)       (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_SHADOWVALID_BLDSLEEP_DEEPSLEEP 0x00000002

// Indicates whether the shadow registers contain valid data from the Flash
// Information Space.
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_S           0
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_M           0x00000001
#define AM_REG_MCUCTRL_SHADOWVALID_VALID(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_SHADOWVALID_VALID_VALID       0x00000001

//*****************************************************************************
//
// MCUCTRL_SCRATCH0 - Scratch register that is not reset by any reset
//
//*****************************************************************************
// Scratch register 0.
#define AM_REG_MCUCTRL_SCRATCH0_SCRATCH0_S           0
#define AM_REG_MCUCTRL_SCRATCH0_SCRATCH0_M           0xFFFFFFFF
#define AM_REG_MCUCTRL_SCRATCH0_SCRATCH0(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_SCRATCH1 - Scratch register that is not reset by any reset
//
//*****************************************************************************
// Scratch register 1.
#define AM_REG_MCUCTRL_SCRATCH1_SCRATCH1_S           0
#define AM_REG_MCUCTRL_SCRATCH1_SCRATCH1_M           0xFFFFFFFF
#define AM_REG_MCUCTRL_SCRATCH1_SCRATCH1(n)          (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_ICODEFAULTADDR - ICODE bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// The ICODE bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ICODEFAULTADDR_S 0
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ICODEFAULTADDR_M 0xFFFFFFFF
#define AM_REG_MCUCTRL_ICODEFAULTADDR_ICODEFAULTADDR(n) (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DCODEFAULTADDR - DCODE bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// The DCODE bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_DCODEFAULTADDR_DCODEFAULTADDR_S 0
#define AM_REG_MCUCTRL_DCODEFAULTADDR_DCODEFAULTADDR_M 0xFFFFFFFF
#define AM_REG_MCUCTRL_DCODEFAULTADDR_DCODEFAULTADDR(n) (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_SYSFAULTADDR - System bus address which was present when a bus fault
// occurred.
//
//*****************************************************************************
// SYS bus address observed when a Bus Fault occurred. Once an address is
// captured in this field, it is held until the corresponding Fault Observed bit
// is cleared in the FAULTSTATUS register.
#define AM_REG_MCUCTRL_SYSFAULTADDR_SYSFAULTADDR_S   0
#define AM_REG_MCUCTRL_SYSFAULTADDR_SYSFAULTADDR_M   0xFFFFFFFF
#define AM_REG_MCUCTRL_SYSFAULTADDR_SYSFAULTADDR(n)  (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_FAULTSTATUS - Reflects the status of the bus decoders' fault
// detection. Any write to this register will clear all of the status bits
// within the register.
//
//*****************************************************************************
// SYS Bus Decoder Fault Detected bit. When set, a fault has been detected, and
// the SYSFAULTADDR register will contain the bus address which generated the
// fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_SYSFAULT_S        2
#define AM_REG_MCUCTRL_FAULTSTATUS_SYSFAULT_M        0x00000004
#define AM_REG_MCUCTRL_FAULTSTATUS_SYSFAULT(n)       (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_MCUCTRL_FAULTSTATUS_SYSFAULT_NOFAULT  0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_SYSFAULT_FAULT    0x00000004

// DCODE Bus Decoder Fault Detected bit. When set, a fault has been detected,
// and the DCODEFAULTADDR register will contain the bus address which generated
// the fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODEFAULT_S      1
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODEFAULT_M      0x00000002
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODEFAULT(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODEFAULT_NOFAULT 0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_DCODEFAULT_FAULT  0x00000002

// The ICODE Bus Decoder Fault Detected bit. When set, a fault has been
// detected, and the ICODEFAULTADDR register will contain the bus address which
// generated the fault.
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODEFAULT_S      0
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODEFAULT_M      0x00000001
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODEFAULT(n)     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODEFAULT_NOFAULT 0x00000000
#define AM_REG_MCUCTRL_FAULTSTATUS_ICODEFAULT_FAULT  0x00000001

//*****************************************************************************
//
// MCUCTRL_FAULTCAPTUREEN - Enable the fault capture registers
//
//*****************************************************************************
// Fault Capture Enable field. When set, the Fault Capture monitors are enabled
// and addresses which generate a hard fault are captured into the FAULTADDR
// registers.
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_FAULTCAPTUREEN_S 0
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_FAULTCAPTUREEN_M 0x00000001
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_FAULTCAPTUREEN(n) (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_FAULTCAPTUREEN_DIS 0x00000000
#define AM_REG_MCUCTRL_FAULTCAPTUREEN_FAULTCAPTUREEN_EN 0x00000001

//*****************************************************************************
//
// MCUCTRL_DBGR1 - Read-only debug register 1
//
//*****************************************************************************
// Read-only register for communication validation
#define AM_REG_MCUCTRL_DBGR1_ONETO8_S                0
#define AM_REG_MCUCTRL_DBGR1_ONETO8_M                0xFFFFFFFF
#define AM_REG_MCUCTRL_DBGR1_ONETO8(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DBGR2 - Read-only debug register 2
//
//*****************************************************************************
// Read-only register for communication validation
#define AM_REG_MCUCTRL_DBGR2_COOLCODE_S              0
#define AM_REG_MCUCTRL_DBGR2_COOLCODE_M              0xFFFFFFFF
#define AM_REG_MCUCTRL_DBGR2_COOLCODE(n)             (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_PMUENABLE - Control bit to enable/disable the PMU
//
//*****************************************************************************
// PMU Enable Control bit. When set, the MCU's PMU will place the MCU into the
// lowest power consuming Deep Sleep mode upon execution of a WFI instruction
// (dependent on the setting of the SLEEPDEEP bit in the ARM SCR register). When
// cleared, regardless of the requested sleep mode, the PMU will not enter the
// lowest power Deep Sleep mode, instead entering the Sleep mode.
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_S            0
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_M            0x00000001
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE(n)           (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_DIS          0x00000000
#define AM_REG_MCUCTRL_PMUENABLE_ENABLE_EN           0x00000001

//*****************************************************************************
//
// MCUCTRL_TPIUCTRL - TPIU Control Register. Determines the clock enable and
// frequency for the M4's TPIU interface.
//
//*****************************************************************************
// This field selects the frequency of the ARM M4 TPIU port.
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_S             8
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_M             0x00000700
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL(n)            (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_LOWPWR        0x00000000
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRCDIV2      0x00000100
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRCDIV8      0x00000200
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRCDIV16     0x00000300
#define AM_REG_MCUCTRL_TPIUCTRL_CLKSEL_HFRCDIV32     0x00000400

// TPIU Enable field. When set, the ARM M4 TPIU is enabled and data can be
// streamed out of the MCU's SWO port using the ARM ITM and TPIU modules.
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_S             0
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_M             0x00000001
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE(n)            (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_DIS           0x00000000
#define AM_REG_MCUCTRL_TPIUCTRL_ENABLE_EN            0x00000001

//*****************************************************************************
//
// MCUCTRL_OTAPOINTER - OTA (Over the Air) Update Pointer/Status.  Reset only by
// POA
//
//*****************************************************************************
// Flash page pointer with updated OTA image
#define AM_REG_MCUCTRL_OTAPOINTER_OTAPOINTER_S       2
#define AM_REG_MCUCTRL_OTAPOINTER_OTAPOINTER_M       0xFFFFFFFC
#define AM_REG_MCUCTRL_OTAPOINTER_OTAPOINTER(n)      (((uint32_t)(n) << 2) & 0xFFFFFFFC)

// Indicates that the sbl_init has been updated
#define AM_REG_MCUCTRL_OTAPOINTER_OTASBLUPDATE_S     1
#define AM_REG_MCUCTRL_OTAPOINTER_OTASBLUPDATE_M     0x00000002
#define AM_REG_MCUCTRL_OTAPOINTER_OTASBLUPDATE(n)    (((uint32_t)(n) << 1) & 0x00000002)

// Indicates that an OTA update is valid
#define AM_REG_MCUCTRL_OTAPOINTER_OTAVALID_S         0
#define AM_REG_MCUCTRL_OTAPOINTER_OTAVALID_M         0x00000001
#define AM_REG_MCUCTRL_OTAPOINTER_OTAVALID(n)        (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_APBDMACTRL - DMA Control Register. Determines misc settings for DMA
// operation
//
//*****************************************************************************
// This field determines how long the DMA will remain active during deep sleep
// before shutting down and returning the system to full deep sleep.  Values are
// based on a 94KHz clock and are roughly 10us increments for a range of ~10us
// to 2.55ms
#define AM_REG_MCUCTRL_APBDMACTRL_HYSTERESIS_S       8
#define AM_REG_MCUCTRL_APBDMACTRL_HYSTERESIS_M       0x0000FF00
#define AM_REG_MCUCTRL_APBDMACTRL_HYSTERESIS(n)      (((uint32_t)(n) << 8) & 0x0000FF00)

// APB Decode Abort. When set, the APB bridge will issue a data abort (bus
// fault) on transactions to peripherals that are powered down. When set to 0,
// writes are quietly discarded and reads return 0.
#define AM_REG_MCUCTRL_APBDMACTRL_DECODEABORT_S      1
#define AM_REG_MCUCTRL_APBDMACTRL_DECODEABORT_M      0x00000002
#define AM_REG_MCUCTRL_APBDMACTRL_DECODEABORT(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_MCUCTRL_APBDMACTRL_DECODEABORT_DISABLE 0x00000000
#define AM_REG_MCUCTRL_APBDMACTRL_DECODEABORT_ENABLE 0x00000002

// Enable the DMA controller.  When disabled, DMA requests will be ignored by
// the controller
#define AM_REG_MCUCTRL_APBDMACTRL_DMA_ENABLE_S       0
#define AM_REG_MCUCTRL_APBDMACTRL_DMA_ENABLE_M       0x00000001
#define AM_REG_MCUCTRL_APBDMACTRL_DMA_ENABLE(n)      (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_MCUCTRL_APBDMACTRL_DMA_ENABLE_DISABLE 0x00000000
#define AM_REG_MCUCTRL_APBDMACTRL_DMA_ENABLE_ENABLE  0x00000001

//*****************************************************************************
//
// MCUCTRL_SRAMMODE - SRAM Controller mode bits
//
//*****************************************************************************
// Secondary prefetch feature that will cache prefetched data across bus
// waitstates (requires DPREFETCH to be set).
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH_CACHE_S    5
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH_CACHE_M    0x00000020
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH_CACHE(n)   (((uint32_t)(n) << 5) & 0x00000020)

// When set, data bus accesses to the SRAM banks will be prefetched (normally 2
// cycle read access).  Use of this mode bit is only recommended if the work
// flow has a large number of sequential accesses.
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH_S          4
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH_M          0x00000010
#define AM_REG_MCUCTRL_SRAMMODE_DPREFETCH(n)         (((uint32_t)(n) << 4) & 0x00000010)

// Secondary prefetch feature that will cache prefetched data across bus
// waitstates (requires IPREFETCH to be set).
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH_CACHE_S    1
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH_CACHE_M    0x00000002
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH_CACHE(n)   (((uint32_t)(n) << 1) & 0x00000002)

// When set, instruction accesses to the SRAM banks will be prefetched (normally
// 2 cycle read access).  Generally, this mode bit should be set for improved
// performance when executing instructions from SRAM.
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH_S          0
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH_M          0x00000001
#define AM_REG_MCUCTRL_SRAMMODE_IPREFETCH(n)         (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// MCUCTRL_SIMOBUCK4 - SIMO Buck Control Reg1
//
//*****************************************************************************
// simobuck_clkdiv_sel
#define AM_REG_MCUCTRL_SIMOBUCK4_SIMOBUCKCLKDIVSEL_S 21
#define AM_REG_MCUCTRL_SIMOBUCK4_SIMOBUCKCLKDIVSEL_M 0x00600000
#define AM_REG_MCUCTRL_SIMOBUCK4_SIMOBUCKCLKDIVSEL(n) (((uint32_t)(n) << 21) & 0x00600000)

//*****************************************************************************
//
// MCUCTRL_BLEBUCK2 - BLEBUCK2 Control Reg
//
//*****************************************************************************
// blebuck_ton_hi_trim
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONHITRIM_S   6
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONHITRIM_M   0x00000FC0
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONHITRIM(n)  (((uint32_t)(n) << 6) & 0x00000FC0)

// blebuck_ton_low_trim
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONLOWTRIM_S  0
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONLOWTRIM_M  0x0000003F
#define AM_REG_MCUCTRL_BLEBUCK2_BLEBUCKTONLOWTRIM(n) (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// MCUCTRL_FLASHWPROT0 - Flash Write Protection Bits
//
//*****************************************************************************
// Write protect flash 0x00000000 - 0x0007FFFF. Each bit provides write
// protection for 16KB chunks of flash data space.  Bits are cleared by writing
// a 1 to the bit.  When read, 0 indicates the region is protected.   Bits are
// sticky (can be set when PROTLOCK is 1, but only cleared by reset)
#define AM_REG_MCUCTRL_FLASHWPROT0_FW0BITS_S         0
#define AM_REG_MCUCTRL_FLASHWPROT0_FW0BITS_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_FLASHWPROT0_FW0BITS(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_FLASHWPROT1 - Flash Write Protection Bits
//
//*****************************************************************************
// Write protect flash 0x00080000 - 0x000FFFFF. Each bit provides write
// protection for 16KB chunks of flash data space.  Bits are cleared by writing
// a 1 to the bit.  When read, 0 indicates the region is protected. Bits are
// sticky (can be set when PROTLOCK is 1, but only cleared by reset)
#define AM_REG_MCUCTRL_FLASHWPROT1_FW1BITS_S         0
#define AM_REG_MCUCTRL_FLASHWPROT1_FW1BITS_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_FLASHWPROT1_FW1BITS(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_FLASHRPROT0 - Flash Read Protection Bits
//
//*****************************************************************************
// Copy (read) protect flash 0x00000000 - 0x0007FFFF. Each bit provides read
// protection for 16KB chunks of flash.  Bits are cleared by writing a 1 to the
// bit.  When read, 0 indicates the region is protected. Bits are sticky (can be
// set when PROTLOCK is 1, but only cleared by reset)
#define AM_REG_MCUCTRL_FLASHRPROT0_FR0BITS_S         0
#define AM_REG_MCUCTRL_FLASHRPROT0_FR0BITS_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_FLASHRPROT0_FR0BITS(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_FLASHRPROT1 - Flash Read Protection Bits
//
//*****************************************************************************
// Copy (read) protect flash 0x00080000 - 0x000FFFFF. Each bit provides read
// protection for 16KB chunks of flash.  Bits are cleared by writing a 1 to the
// bit.  When read, 0 indicates the region is protected. Bits are sticky (can be
// set when PROTLOCK is 1, but only cleared by reset)
#define AM_REG_MCUCTRL_FLASHRPROT1_FR1BITS_S         0
#define AM_REG_MCUCTRL_FLASHRPROT1_FR1BITS_M         0xFFFFFFFF
#define AM_REG_MCUCTRL_FLASHRPROT1_FR1BITS(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DMASRAMWRITEPROTECT0 - SRAM write-protection bits.
//
//*****************************************************************************
// Write protect SRAM from DMA.  Each bit provides write protection for an 8KB
// region of memory.  When set to 1, the region will be protected from DMA
// writes, when set to 0, DMA may write the region.
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT0_DMA_WPROT0_S 0
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT0_DMA_WPROT0_M 0xFFFFFFFF
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT0_DMA_WPROT0(n) (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DMASRAMWRITEPROTECT1 - SRAM write-protection bits.
//
//*****************************************************************************
// Write protect SRAM from DMA.  Each bit provides write protection for an 8KB
// region of memory.  When set to 1, the region will be protected from DMA
// writes, when set to 0, DMA may write the region.
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT1_DMA_WPROT1_S 0
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT1_DMA_WPROT1_M 0x0000FFFF
#define AM_REG_MCUCTRL_DMASRAMWRITEPROTECT1_DMA_WPROT1(n) (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// MCUCTRL_DMASRAMREADPROTECT0 - SRAM read-protection bits.
//
//*****************************************************************************
// Read protect SRAM from DMA.  Each bit provides write protection for an 8KB
// region of memory.  When set to 1, the region will be protected from DMA
// reads, when set to 0, DMA may read the region.
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT0_DMA_RPROT0_S 0
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT0_DMA_RPROT0_M 0xFFFFFFFF
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT0_DMA_RPROT0(n) (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// MCUCTRL_DMASRAMREADPROTECT1 - SRAM read-protection bits.
//
//*****************************************************************************
// Read protect SRAM from DMA.  Each bit provides write protection for an 8KB
// region of memory.  When set to 1, the region will be protected from DMA
// reads, when set to 0, DMA may read the region.
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT1_DMA_RPROT1_S 0
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT1_DMA_RPROT1_M 0x0000FFFF
#define AM_REG_MCUCTRL_DMASRAMREADPROTECT1_DMA_RPROT1(n) (((uint32_t)(n) << 0) & 0x0000FFFF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_MCUCTRL_H
