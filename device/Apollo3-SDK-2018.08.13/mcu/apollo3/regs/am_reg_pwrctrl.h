//*****************************************************************************
//
//  am_reg_pwrctrl.h
//! @file
//!
//! @brief Register macros for the PWRCTRL module
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
#ifndef AM_REG_PWRCTRL_H
#define AM_REG_PWRCTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_PWRCTRL_NUM_MODULES                   1
#define AM_REG_PWRCTRLn(n) \
    (REG_PWRCTRL_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_PWRCTRL_SUPPLYSRC_O                   0x00000000
#define AM_REG_PWRCTRL_SUPPLYSTATUS_O                0x00000004
#define AM_REG_PWRCTRL_DEVPWREN_O                    0x00000008
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_O               0x0000000C
#define AM_REG_PWRCTRL_MEMPWREN_O                    0x00000010
#define AM_REG_PWRCTRL_MEMPWRSTATUS_O                0x00000014
#define AM_REG_PWRCTRL_DEVPWRSTATUS_O                0x00000018
#define AM_REG_PWRCTRL_SRAMCTRL_O                    0x0000001C
#define AM_REG_PWRCTRL_ADCSTATUS_O                   0x00000020
#define AM_REG_PWRCTRL_MISC_O                        0x00000024
#define AM_REG_PWRCTRL_DEVPWREVENTEN_O               0x00000028
#define AM_REG_PWRCTRL_MEMPWREVENTEN_O               0x0000002C

//*****************************************************************************
//
// PWRCTRL_SUPPLYSRC - Voltage Regulator Select Register
//
//*****************************************************************************
// Enables and Selects the BLE Buck as the supply for the BLE power domain or
// for Burst LDO. It takes the initial value from Customer INFO space. Buck will
// be powered up only if there is an active request for BLEH domain or Burst
// mode and appropriate feature is allowed.
#define AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN_S         0
#define AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN_M         0x00000001
#define AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN(n)        (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN_EN        0x00000001
#define AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN_DIS       0x00000000

//*****************************************************************************
//
// PWRCTRL_SUPPLYSTATUS - Voltage Regulators status
//
//*****************************************************************************
// Indicates whether the BLE (if supported) domain and burst (if supported)
// domain is supplied from the LDO or the Buck. Buck will be powered up only if
// there is an active request for BLEH domain or Burst mode and appropriate
// reature is allowed.
#define AM_REG_PWRCTRL_SUPPLYSTATUS_BLEBUCKON_S      1
#define AM_REG_PWRCTRL_SUPPLYSTATUS_BLEBUCKON_M      0x00000002
#define AM_REG_PWRCTRL_SUPPLYSTATUS_BLEBUCKON(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_SUPPLYSTATUS_BLEBUCKON_LDO    0x00000000
#define AM_REG_PWRCTRL_SUPPLYSTATUS_BLEBUCKON_BUCK   0x00000002

// Indicates whether the Core/Mem low-voltage domains are supplied from the LDO
// or the Buck.
#define AM_REG_PWRCTRL_SUPPLYSTATUS_SIMOBUCKON_S     0
#define AM_REG_PWRCTRL_SUPPLYSTATUS_SIMOBUCKON_M     0x00000001
#define AM_REG_PWRCTRL_SUPPLYSTATUS_SIMOBUCKON(n)    (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_SUPPLYSTATUS_SIMOBUCKON_OFF   0x00000000
#define AM_REG_PWRCTRL_SUPPLYSTATUS_SIMOBUCKON_ON    0x00000001

//*****************************************************************************
//
// PWRCTRL_DEVPWREN - Device Power Enables
//
//*****************************************************************************
// Power up BLE controller
#define AM_REG_PWRCTRL_DEVPWREN_PWRBLEL_S            13
#define AM_REG_PWRCTRL_DEVPWREN_PWRBLEL_M            0x00002000
#define AM_REG_PWRCTRL_DEVPWREN_PWRBLEL(n)           (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_PWRCTRL_DEVPWREN_PWRBLEL_EN           0x00002000
#define AM_REG_PWRCTRL_DEVPWREN_PWRBLEL_DIS          0x00000000

// Power up PDM block
#define AM_REG_PWRCTRL_DEVPWREN_PWRPDM_S             12
#define AM_REG_PWRCTRL_DEVPWREN_PWRPDM_M             0x00001000
#define AM_REG_PWRCTRL_DEVPWREN_PWRPDM(n)            (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_PWRCTRL_DEVPWREN_PWRPDM_EN            0x00001000
#define AM_REG_PWRCTRL_DEVPWREN_PWRPDM_DIS           0x00000000

// Power up MSPI Controller
#define AM_REG_PWRCTRL_DEVPWREN_PWRMSPI_S            11
#define AM_REG_PWRCTRL_DEVPWREN_PWRMSPI_M            0x00000800
#define AM_REG_PWRCTRL_DEVPWREN_PWRMSPI(n)           (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_PWRCTRL_DEVPWREN_PWRMSPI_EN           0x00000800
#define AM_REG_PWRCTRL_DEVPWREN_PWRMSPI_DIS          0x00000000

// Power up SCARD Controller
#define AM_REG_PWRCTRL_DEVPWREN_PWRSCARD_S           10
#define AM_REG_PWRCTRL_DEVPWREN_PWRSCARD_M           0x00000400
#define AM_REG_PWRCTRL_DEVPWREN_PWRSCARD(n)          (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_PWRCTRL_DEVPWREN_PWRSCARD_EN          0x00000400
#define AM_REG_PWRCTRL_DEVPWREN_PWRSCARD_DIS         0x00000000

// Power up ADC Digital Controller
#define AM_REG_PWRCTRL_DEVPWREN_PWRADC_S             9
#define AM_REG_PWRCTRL_DEVPWREN_PWRADC_M             0x00000200
#define AM_REG_PWRCTRL_DEVPWREN_PWRADC(n)            (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_PWRCTRL_DEVPWREN_PWRADC_EN            0x00000200
#define AM_REG_PWRCTRL_DEVPWREN_PWRADC_DIS           0x00000000

// Power up UART Controller 1
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART1_S           8
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART1_M           0x00000100
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART1(n)          (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART1_EN          0x00000100
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART1_DIS         0x00000000

// Power up UART Controller 0
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART0_S           7
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART0_M           0x00000080
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART0(n)          (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART0_EN          0x00000080
#define AM_REG_PWRCTRL_DEVPWREN_PWRUART0_DIS         0x00000000

// Power up IO Master 5
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM5_S            6
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM5_M            0x00000040
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM5(n)           (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM5_EN           0x00000040
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM5_DIS          0x00000000

// Power up IO Master 4
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM4_S            5
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM4_M            0x00000020
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM4(n)           (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM4_EN           0x00000020
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM4_DIS          0x00000000

// Power up IO Master 3
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM3_S            4
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM3_M            0x00000010
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM3(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM3_EN           0x00000010
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM3_DIS          0x00000000

// Power up IO Master 2
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM2_S            3
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM2_M            0x00000008
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM2(n)           (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM2_EN           0x00000008
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM2_DIS          0x00000000

// Power up IO Master 1
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM1_S            2
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM1_M            0x00000004
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM1(n)           (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM1_EN           0x00000004
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM1_DIS          0x00000000

// Power up IO Master 0
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM0_S            1
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM0_M            0x00000002
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM0(n)           (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM0_EN           0x00000002
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOM0_DIS          0x00000000

// Power up IO Slave
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOS_S             0
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOS_M             0x00000001
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOS(n)            (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOS_EN            0x00000001
#define AM_REG_PWRCTRL_DEVPWREN_PWRIOS_DIS           0x00000000

//*****************************************************************************
//
// PWRCTRL_MEMPWDINSLEEP - Powerdown SRAM banks in Deep Sleep mode
//
//*****************************************************************************
// power down cache in deep sleep
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_CACHEPWDSLP_S   31
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_CACHEPWDSLP_M   0x80000000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_CACHEPWDSLP(n)  (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_CACHEPWDSLP_EN  0x80000000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_CACHEPWDSLP_DIS 0x00000000

// Powerdown flash1 in deep sleep
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH1PWDSLP_S  14
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH1PWDSLP_M  0x00004000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH1PWDSLP(n) (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH1PWDSLP_EN 0x00004000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH1PWDSLP_DIS 0x00000000

// Powerdown flash0 in deep sleep
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH0PWDSLP_S  13
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH0PWDSLP_M  0x00002000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH0PWDSLP(n) (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH0PWDSLP_EN 0x00002000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_FLASH0PWDSLP_DIS 0x00000000

// Selects which SRAM banks are powered down in deep sleep mode, causing the
// contents of the bank to be lost.
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_S    3
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_M    0x00001FF8
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP(n)   (((uint32_t)(n) << 3) & 0x00001FF8)
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_NONE 0x00000000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP0 0x00000008
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP1 0x00000010
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP2 0x00000020
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP3 0x00000040
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP4 0x00000080
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP5 0x00000100
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP6 0x00000200
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP7 0x00000400
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP8 0x00000800
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_GROUP9 0x00001000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_SRAM32K 0x00000008
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_SRAM64K 0x00000018
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_SRAM128K 0x00000078
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER32K 0x00001FF0
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER64K 0x00001FE0
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER128K 0x00001F80
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALL  0x00001FF8

// power down DTCM in deep sleep
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_S    0
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_M    0x00000007
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP(n)   (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_NONE 0x00000000
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_GROUP0DTCM0 0x00000001
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_GROUP0DTCM1 0x00000002
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_GROUP0 0x00000003
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_ALLBUTGROUP0DTCM0 0x00000006
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_GROUP1 0x00000004
#define AM_REG_PWRCTRL_MEMPWDINSLEEP_DTCMPWDSLP_ALL  0x00000007

//*****************************************************************************
//
// PWRCTRL_MEMPWREN - Enables individual banks of the MEMORY array
//
//*****************************************************************************
// Power up Cache Bank 2. This works in conjunction with Cache enable from
// flash_cache module. To power up cache bank2, cache has to be enabled and this
// bit has to be set.
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB2_S            31
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB2_M            0x80000000
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB2(n)           (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB2_EN           0x80000000
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB2_DIS          0x00000000

// Power up Cache Bank 0. This works in conjunction with Cache enable from
// flash_cache module. To power up cache bank0, cache has to be enabled and this
// bit has to be set.
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB0_S            30
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB0_M            0x40000000
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB0(n)           (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB0_EN           0x40000000
#define AM_REG_PWRCTRL_MEMPWREN_CACHEB0_DIS          0x00000000

// Power up Flash1
#define AM_REG_PWRCTRL_MEMPWREN_FLASH1_S             14
#define AM_REG_PWRCTRL_MEMPWREN_FLASH1_M             0x00004000
#define AM_REG_PWRCTRL_MEMPWREN_FLASH1(n)            (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_PWRCTRL_MEMPWREN_FLASH1_EN            0x00004000
#define AM_REG_PWRCTRL_MEMPWREN_FLASH1_DIS           0x00000000

// Power up Flash0
#define AM_REG_PWRCTRL_MEMPWREN_FLASH0_S             13
#define AM_REG_PWRCTRL_MEMPWREN_FLASH0_M             0x00002000
#define AM_REG_PWRCTRL_MEMPWREN_FLASH0(n)            (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_PWRCTRL_MEMPWREN_FLASH0_EN            0x00002000
#define AM_REG_PWRCTRL_MEMPWREN_FLASH0_DIS           0x00000000

// Power up SRAM groups
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_S               3
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_M               0x00001FF8
#define AM_REG_PWRCTRL_MEMPWREN_SRAM(n)              (((uint32_t)(n) << 3) & 0x00001FF8)
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_NONE            0x00000000
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP0          0x00000008
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP1          0x00000010
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP2          0x00000020
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP3          0x00000040
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP4          0x00000080
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP5          0x00000100
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP6          0x00000200
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP7          0x00000400
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP8          0x00000800
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_GROUP9          0x00001000
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_SRAM32K         0x00000008
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_SRAM64K         0x00000018
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_SRAM128K        0x00000078
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_SRAM256K        0x000007F8
#define AM_REG_PWRCTRL_MEMPWREN_SRAM_ALL             0x00001FF8

// Power up DTCM
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_S               0
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_M               0x00000007
#define AM_REG_PWRCTRL_MEMPWREN_DTCM(n)              (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_NONE            0x00000000
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_GROUP0DTCM0     0x00000001
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_GROUP0DTCM1     0x00000002
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_GROUP0          0x00000003
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_GROUP1          0x00000004
#define AM_REG_PWRCTRL_MEMPWREN_DTCM_ALL             0x00000007

//*****************************************************************************
//
// PWRCTRL_MEMPWRSTATUS - Mem Power ON Status
//
//*****************************************************************************
// This bit is 1 if power is supplied to Cache Bank 2
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB2_S        16
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB2_M        0x00010000
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB2(n)       (((uint32_t)(n) << 16) & 0x00010000)

// This bit is 1 if power is supplied to Cache Bank 0
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB0_S        15
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB0_M        0x00008000
#define AM_REG_PWRCTRL_MEMPWRSTATUS_CACHEB0(n)       (((uint32_t)(n) << 15) & 0x00008000)

// This bit is 1 if power is supplied to FLASH 1
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH1_S         14
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH1_M         0x00004000
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH1(n)        (((uint32_t)(n) << 14) & 0x00004000)

// This bit is 1 if power is supplied to FLASH 0
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH0_S         13
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH0_M         0x00002000
#define AM_REG_PWRCTRL_MEMPWRSTATUS_FLASH0(n)        (((uint32_t)(n) << 13) & 0x00002000)

// This bit is 1 if power is supplied to SRAM GROUP9
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM9_S          12
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM9_M          0x00001000
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM9(n)         (((uint32_t)(n) << 12) & 0x00001000)

// This bit is 1 if power is supplied to SRAM GROUP8
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM8_S          11
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM8_M          0x00000800
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM8(n)         (((uint32_t)(n) << 11) & 0x00000800)

// This bit is 1 if power is supplied to SRAM GROUP7
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM7_S          10
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM7_M          0x00000400
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM7(n)         (((uint32_t)(n) << 10) & 0x00000400)

// This bit is 1 if power is supplied to SRAM GROUP6
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM6_S          9
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM6_M          0x00000200
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM6(n)         (((uint32_t)(n) << 9) & 0x00000200)

// This bit is 1 if power is supplied to SRAM GROUP5
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM5_S          8
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM5_M          0x00000100
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM5(n)         (((uint32_t)(n) << 8) & 0x00000100)

// This bit is 1 if power is supplied to SRAM GROUP4
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM4_S          7
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM4_M          0x00000080
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM4(n)         (((uint32_t)(n) << 7) & 0x00000080)

// This bit is 1 if power is supplied to SRAM GROUP3
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM3_S          6
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM3_M          0x00000040
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM3(n)         (((uint32_t)(n) << 6) & 0x00000040)

// This bit is 1 if power is supplied to SRAM GROUP2
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM2_S          5
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM2_M          0x00000020
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM2(n)         (((uint32_t)(n) << 5) & 0x00000020)

// This bit is 1 if power is supplied to SRAM GROUP1
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM1_S          4
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM1_M          0x00000010
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM1(n)         (((uint32_t)(n) << 4) & 0x00000010)

// This bit is 1 if power is supplied to SRAM GROUP0
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM0_S          3
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM0_M          0x00000008
#define AM_REG_PWRCTRL_MEMPWRSTATUS_SRAM0(n)         (((uint32_t)(n) << 3) & 0x00000008)

// This bit is 1 if power is supplied to DTCM GROUP1
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM1_S          2
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM1_M          0x00000004
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM1(n)         (((uint32_t)(n) << 2) & 0x00000004)

// This bit is 1 if power is supplied to DTCM GROUP0_1
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM01_S         1
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM01_M         0x00000002
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM01(n)        (((uint32_t)(n) << 1) & 0x00000002)

// This bit is 1 if power is supplied to DTCM GROUP0_0
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM00_S         0
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM00_M         0x00000001
#define AM_REG_PWRCTRL_MEMPWRSTATUS_DTCM00(n)        (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PWRCTRL_DEVPWRSTATUS - Device Power ON Status
//
//*****************************************************************************
// This bit is 1 if SYSTEM has been in Deep Sleep.  Write '1' to this bit to
// clear it.
#define AM_REG_PWRCTRL_DEVPWRSTATUS_SYSDEEPSLEEP_S   31
#define AM_REG_PWRCTRL_DEVPWRSTATUS_SYSDEEPSLEEP_M   0x80000000
#define AM_REG_PWRCTRL_DEVPWRSTATUS_SYSDEEPSLEEP(n)  (((uint32_t)(n) << 31) & 0x80000000)

// This bit is 1 if CORE has been in Deep Sleep.  Write '1' to this bit to clear
// it.
#define AM_REG_PWRCTRL_DEVPWRSTATUS_COREDEEPSLEEP_S  30
#define AM_REG_PWRCTRL_DEVPWRSTATUS_COREDEEPSLEEP_M  0x40000000
#define AM_REG_PWRCTRL_DEVPWRSTATUS_COREDEEPSLEEP(n) (((uint32_t)(n) << 30) & 0x40000000)

// This bit is 1 if CORE has been in SLEEP State.  Write '1' to this bit to
// clear it.
#define AM_REG_PWRCTRL_DEVPWRSTATUS_CORESLEEP_S      29
#define AM_REG_PWRCTRL_DEVPWRSTATUS_CORESLEEP_M      0x20000000
#define AM_REG_PWRCTRL_DEVPWRSTATUS_CORESLEEP(n)     (((uint32_t)(n) << 29) & 0x20000000)

// This bit is 1 if power is supplied to BLEH
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEH_S           9
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEH_M           0x00000200
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEH(n)          (((uint32_t)(n) << 9) & 0x00000200)

// This bit is 1 if power is supplied to BLEL
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEL_S           8
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEL_M           0x00000100
#define AM_REG_PWRCTRL_DEVPWRSTATUS_BLEL(n)          (((uint32_t)(n) << 8) & 0x00000100)

// This bit is 1 if power is supplied to PDM
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRPDM_S         7
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRPDM_M         0x00000080
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRPDM(n)        (((uint32_t)(n) << 7) & 0x00000080)

// This bit is 1 if power is supplied to MSPI
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRMSPI_S        6
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRMSPI_M        0x00000040
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRMSPI(n)       (((uint32_t)(n) << 6) & 0x00000040)

// This bit is 1 if power is supplied to ADC
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRADC_S         5
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRADC_M         0x00000020
#define AM_REG_PWRCTRL_DEVPWRSTATUS_PWRADC(n)        (((uint32_t)(n) << 5) & 0x00000020)

// This bit is 1 if power is supplied to HCPC domain (IO MASTER4, 5, 6)
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_S           4
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_M           0x00000010
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC(n)          (((uint32_t)(n) << 4) & 0x00000010)

// This bit is 1 if power is supplied to HCPB domain (IO MASTER 0, 1, 2)
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_S           3
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_M           0x00000008
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB(n)          (((uint32_t)(n) << 3) & 0x00000008)

// This bit is 1 if power is supplied to HCPA domain (IO SLAVE, UART0, UART1,
// SCARD)
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_S           2
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M           0x00000004
#define AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA(n)          (((uint32_t)(n) << 2) & 0x00000004)

// This bit is 1 if power is supplied to MCUH
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUH_S           1
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUH_M           0x00000002
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUH(n)          (((uint32_t)(n) << 1) & 0x00000002)

// This bit is 1 if power is supplied to MCUL
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUL_S           0
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUL_M           0x00000001
#define AM_REG_PWRCTRL_DEVPWRSTATUS_MCUL(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PWRCTRL_SRAMCTRL - SRAM Control register
//
//*****************************************************************************
// Light Sleep enable for each TCM/SRAM bank.  When 1, corresponding bank will
// be put into light sleep.  For optimal power, banks should be put into light
// sleep while the system is active but the bank has minimal or no accesses.
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMLIGHTSLEEP_S     8
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMLIGHTSLEEP_M     0x000FFF00
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMLIGHTSLEEP(n)    (((uint32_t)(n) << 8) & 0x000FFF00)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMLIGHTSLEEP_ALL   0x0000FF00
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMLIGHTSLEEP_DIS   0x00000000

// This bit is 1 when the master clock gate is enabled (top-level clock gate for
// entire SRAM block)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMMASTERCLKGATE_S  2
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMMASTERCLKGATE_M  0x00000004
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMMASTERCLKGATE(n) (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMMASTERCLKGATE_EN 0x00000004
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMMASTERCLKGATE_DIS 0x00000000

// This bit is 1 if clock gating is allowed for individual system SRAMs
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMCLKGATE_S        1
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMCLKGATE_M        0x00000002
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMCLKGATE(n)       (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMCLKGATE_EN       0x00000002
#define AM_REG_PWRCTRL_SRAMCTRL_SRAMCLKGATE_DIS      0x00000000

//*****************************************************************************
//
// PWRCTRL_ADCSTATUS - Power Status Register for ADC Block
//
//*****************************************************************************
// This bit indicates that the ADC REFBUF is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_REFBUFPWD_S         5
#define AM_REG_PWRCTRL_ADCSTATUS_REFBUFPWD_M         0x00000020
#define AM_REG_PWRCTRL_ADCSTATUS_REFBUFPWD(n)        (((uint32_t)(n) << 5) & 0x00000020)

// This bit indicates that the ADC REFKEEP is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_REFKEEPPWD_S        4
#define AM_REG_PWRCTRL_ADCSTATUS_REFKEEPPWD_M        0x00000010
#define AM_REG_PWRCTRL_ADCSTATUS_REFKEEPPWD(n)       (((uint32_t)(n) << 4) & 0x00000010)

// This bit indicates that the ADC VBAT resistor divider is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_VBATPWD_S           3
#define AM_REG_PWRCTRL_ADCSTATUS_VBATPWD_M           0x00000008
#define AM_REG_PWRCTRL_ADCSTATUS_VBATPWD(n)          (((uint32_t)(n) << 3) & 0x00000008)

// This bit indicates that the ADC temperature sensor input buffer is powered
// down
#define AM_REG_PWRCTRL_ADCSTATUS_VPTATPWD_S          2
#define AM_REG_PWRCTRL_ADCSTATUS_VPTATPWD_M          0x00000004
#define AM_REG_PWRCTRL_ADCSTATUS_VPTATPWD(n)         (((uint32_t)(n) << 2) & 0x00000004)

// This bit indicates that the ADC Band Gap is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_BGTPWD_S            1
#define AM_REG_PWRCTRL_ADCSTATUS_BGTPWD_M            0x00000002
#define AM_REG_PWRCTRL_ADCSTATUS_BGTPWD(n)           (((uint32_t)(n) << 1) & 0x00000002)

// This bit indicates that the ADC is powered down
#define AM_REG_PWRCTRL_ADCSTATUS_ADCPWD_S            0
#define AM_REG_PWRCTRL_ADCSTATUS_ADCPWD_M            0x00000001
#define AM_REG_PWRCTRL_ADCSTATUS_ADCPWD(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// PWRCTRL_MISC - Power Optimization Control Bits
//
//*****************************************************************************
// Control Bit to let Mem VR go to lp mode in deep sleep even when BLEL or BLEH
// is powered on given none of the other domains require it.
#define AM_REG_PWRCTRL_MISC_MEMVRLPBLE_S             6
#define AM_REG_PWRCTRL_MISC_MEMVRLPBLE_M             0x00000040
#define AM_REG_PWRCTRL_MISC_MEMVRLPBLE(n)            (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_PWRCTRL_MISC_MEMVRLPBLE_EN            0x00000040
#define AM_REG_PWRCTRL_MISC_MEMVRLPBLE_DIS           0x00000000

// Control Bit to force Mem VR to LP mode in deep sleep even when hfrc based
// ctimer or stimer is running.
#define AM_REG_PWRCTRL_MISC_FORCEMEMVRLPTIMERS_S     3
#define AM_REG_PWRCTRL_MISC_FORCEMEMVRLPTIMERS_M     0x00000008
#define AM_REG_PWRCTRL_MISC_FORCEMEMVRLPTIMERS(n)    (((uint32_t)(n) << 3) & 0x00000008)

//*****************************************************************************
//
// PWRCTRL_DEVPWREVENTEN - Event enable register to control which DEVPWRSTATUS
// bits are routed to event input of CPU.
//
//*****************************************************************************
// Control BURST status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTEVEN_S     31
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTEVEN_M     0x80000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTEVEN(n)    (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTEVEN_EN    0x80000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTEVEN_DIS   0x00000000

// Control BURSTFEATURE status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTFEATUREEVEN_S 30
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTFEATUREEVEN_M 0x40000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTFEATUREEVEN(n) (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTFEATUREEVEN_EN 0x40000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BURSTFEATUREEVEN_DIS 0x00000000

// Control BLEFEATURE status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLEFEATUREEVEN_S 29
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLEFEATUREEVEN_M 0x20000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLEFEATUREEVEN(n) (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLEFEATUREEVEN_EN 0x20000000
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLEFEATUREEVEN_DIS 0x00000000

// Control BLE power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN_S      8
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN_M      0x00000100
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN(n)     (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN_EN     0x00000100
#define AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN_DIS    0x00000000

// Control PDM power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN_S       7
#define AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN_M       0x00000080
#define AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN(n)      (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN_EN      0x00000080
#define AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN_DIS     0x00000000

// Control MSPI power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN_S      6
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN_M      0x00000040
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN(n)     (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN_EN     0x00000040
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN_DIS    0x00000000

// Control ADC power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN_S       5
#define AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN_M       0x00000020
#define AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN(n)      (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN_EN      0x00000020
#define AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN_DIS     0x00000000

// Control HCPC power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_S      4
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_M      0x00000010
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN(n)     (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN     0x00000010
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_DIS    0x00000000

// Control HCPB power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_S      3
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_M      0x00000008
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN(n)     (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN     0x00000008
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_DIS    0x00000000

// Control HCPA power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_S      2
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_M      0x00000004
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN(n)     (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN     0x00000004
#define AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_DIS    0x00000000

// Control MCUH power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCUHEVEN_S      1
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCUHEVEN_M      0x00000002
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCUHEVEN(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCUHEVEN_EN     0x00000002
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCUHEVEN_DIS    0x00000000

// Control MCUL power-on status event
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCULEVEN_S      0
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCULEVEN_M      0x00000001
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCULEVEN(n)     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCULEVEN_EN     0x00000001
#define AM_REG_PWRCTRL_DEVPWREVENTEN_MCULEVEN_DIS    0x00000000

//*****************************************************************************
//
// PWRCTRL_MEMPWREVENTEN - Event enable register to control which MEMPWRSTATUS
// bits are routed to event input of CPU.
//
//*****************************************************************************
// Control CACHEB2 power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB2EN_S     31
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB2EN_M     0x80000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB2EN(n)    (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB2EN_EN    0x80000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB2EN_DIS   0x00000000

// Control CACHE BANK 0 power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB0EN_S     30
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB0EN_M     0x40000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB0EN(n)    (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB0EN_EN    0x40000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_CACHEB0EN_DIS   0x00000000

// Control Flash power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH1EN_S      14
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH1EN_M      0x00004000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH1EN(n)     (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH1EN_EN     0x00004000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH1EN_DIS    0x00000000

// Control Flash power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH0EN_S      13
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH0EN_M      0x00002000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH0EN(n)     (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH0EN_EN     0x00002000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_FLASH0EN_DIS    0x00000000

// Control SRAM power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_S        3
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_M        0x00001FF8
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN(n)       (((uint32_t)(n) << 3) & 0x00001FF8)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_NONE     0x00000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP0EN 0x00000008
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP1EN 0x00000010
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP2EN 0x00000020
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP3EN 0x00000040
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP4EN 0x00000080
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP5EN 0x00000100
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP6EN 0x00000200
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP7EN 0x00000400
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP8EN 0x00000800
#define AM_REG_PWRCTRL_MEMPWREVENTEN_SRAMEN_GROUP9EN 0x00001000

// Enable DTCM power-on status event
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_S        0
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_M        0x00000007
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN(n)       (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_NONE     0x00000000
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_GROUP0DTCM0EN 0x00000001
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_GROUP0DTCM1EN 0x00000002
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_GROUP0EN 0x00000003
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_GROUP1EN 0x00000004
#define AM_REG_PWRCTRL_MEMPWREVENTEN_DTCMEN_ALL      0x00000007

#endif // !AM_CMSIS_REGS

#endif // AM_REG_PWRCTRL_H
