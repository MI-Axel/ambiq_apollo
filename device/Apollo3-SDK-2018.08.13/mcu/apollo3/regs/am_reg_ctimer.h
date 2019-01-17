//*****************************************************************************
//
//  am_reg_ctimer.h
//! @file
//!
//! @brief Register macros for the CTIMER module
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
#ifndef AM_REG_CTIMER_H
#define AM_REG_CTIMER_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_CTIMER_NUM_MODULES                    1
#define AM_REG_CTIMERn(n) \
    (REG_CTIMER_BASEADDR + 0x00000020 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_CTIMER_TMR0_O                         0x00000000
#define AM_REG_CTIMER_CMPRA0_O                       0x00000004
#define AM_REG_CTIMER_CMPRB0_O                       0x00000008
#define AM_REG_CTIMER_CTRL0_O                        0x0000000C
#define AM_REG_CTIMER_CMPRAUXA0_O                    0x00000014
#define AM_REG_CTIMER_CMPRAUXB0_O                    0x00000018
#define AM_REG_CTIMER_AUX0_O                         0x0000001C
#define AM_REG_CTIMER_TMR1_O                         0x00000020
#define AM_REG_CTIMER_CMPRA1_O                       0x00000024
#define AM_REG_CTIMER_CMPRB1_O                       0x00000028
#define AM_REG_CTIMER_CTRL1_O                        0x0000002C
#define AM_REG_CTIMER_CMPRAUXA1_O                    0x00000034
#define AM_REG_CTIMER_CMPRAUXB1_O                    0x00000038
#define AM_REG_CTIMER_AUX1_O                         0x0000003C
#define AM_REG_CTIMER_TMR2_O                         0x00000040
#define AM_REG_CTIMER_CMPRA2_O                       0x00000044
#define AM_REG_CTIMER_CMPRB2_O                       0x00000048
#define AM_REG_CTIMER_CTRL2_O                        0x0000004C
#define AM_REG_CTIMER_CMPRAUXA2_O                    0x00000054
#define AM_REG_CTIMER_CMPRAUXB2_O                    0x00000058
#define AM_REG_CTIMER_AUX2_O                         0x0000005C
#define AM_REG_CTIMER_TMR3_O                         0x00000060
#define AM_REG_CTIMER_CMPRA3_O                       0x00000064
#define AM_REG_CTIMER_CMPRB3_O                       0x00000068
#define AM_REG_CTIMER_CTRL3_O                        0x0000006C
#define AM_REG_CTIMER_CMPRAUXA3_O                    0x00000074
#define AM_REG_CTIMER_CMPRAUXB3_O                    0x00000078
#define AM_REG_CTIMER_AUX3_O                         0x0000007C
#define AM_REG_CTIMER_TMR4_O                         0x00000080
#define AM_REG_CTIMER_CMPRA4_O                       0x00000084
#define AM_REG_CTIMER_CMPRB4_O                       0x00000088
#define AM_REG_CTIMER_CTRL4_O                        0x0000008C
#define AM_REG_CTIMER_CMPRAUXA4_O                    0x00000094
#define AM_REG_CTIMER_CMPRAUXB4_O                    0x00000098
#define AM_REG_CTIMER_AUX4_O                         0x0000009C
#define AM_REG_CTIMER_TMR5_O                         0x000000A0
#define AM_REG_CTIMER_CMPRA5_O                       0x000000A4
#define AM_REG_CTIMER_CMPRB5_O                       0x000000A8
#define AM_REG_CTIMER_CTRL5_O                        0x000000AC
#define AM_REG_CTIMER_CMPRAUXA5_O                    0x000000B4
#define AM_REG_CTIMER_CMPRAUXB5_O                    0x000000B8
#define AM_REG_CTIMER_AUX5_O                         0x000000BC
#define AM_REG_CTIMER_TMR6_O                         0x000000C0
#define AM_REG_CTIMER_CMPRA6_O                       0x000000C4
#define AM_REG_CTIMER_CMPRB6_O                       0x000000C8
#define AM_REG_CTIMER_CTRL6_O                        0x000000CC
#define AM_REG_CTIMER_CMPRAUXA6_O                    0x000000D4
#define AM_REG_CTIMER_CMPRAUXB6_O                    0x000000D8
#define AM_REG_CTIMER_AUX6_O                         0x000000DC
#define AM_REG_CTIMER_TMR7_O                         0x000000E0
#define AM_REG_CTIMER_CMPRA7_O                       0x000000E4
#define AM_REG_CTIMER_CMPRB7_O                       0x000000E8
#define AM_REG_CTIMER_CTRL7_O                        0x000000EC
#define AM_REG_CTIMER_CMPRAUXA7_O                    0x000000F4
#define AM_REG_CTIMER_CMPRAUXB7_O                    0x000000F8
#define AM_REG_CTIMER_AUX7_O                         0x000000FC
#define AM_REG_CTIMER_GLOBEN_O                       0x00000100
#define AM_REG_CTIMER_OUTCFG0_O                      0x00000104
#define AM_REG_CTIMER_OUTCFG1_O                      0x00000108
#define AM_REG_CTIMER_OUTCFG2_O                      0x0000010C
#define AM_REG_CTIMER_OUTCFG3_O                      0x00000114
#define AM_REG_CTIMER_INCFG_O                        0x00000118
#define AM_REG_CTIMER_STCFG_O                        0x00000140
#define AM_REG_CTIMER_STTMR_O                        0x00000144
#define AM_REG_CTIMER_CAPTURECONTROL_O               0x00000148
#define AM_REG_CTIMER_SCMPR0_O                       0x00000150
#define AM_REG_CTIMER_SCMPR1_O                       0x00000154
#define AM_REG_CTIMER_SCMPR2_O                       0x00000158
#define AM_REG_CTIMER_SCMPR3_O                       0x0000015C
#define AM_REG_CTIMER_SCMPR4_O                       0x00000160
#define AM_REG_CTIMER_SCMPR5_O                       0x00000164
#define AM_REG_CTIMER_SCMPR6_O                       0x00000168
#define AM_REG_CTIMER_SCMPR7_O                       0x0000016C
#define AM_REG_CTIMER_SCAPT0_O                       0x000001E0
#define AM_REG_CTIMER_SCAPT1_O                       0x000001E4
#define AM_REG_CTIMER_SCAPT2_O                       0x000001E8
#define AM_REG_CTIMER_SCAPT3_O                       0x000001EC
#define AM_REG_CTIMER_SNVR0_O                        0x000001F0
#define AM_REG_CTIMER_SNVR1_O                        0x000001F4
#define AM_REG_CTIMER_SNVR2_O                        0x000001F8
#define AM_REG_CTIMER_SNVR3_O                        0x000001FC
#define AM_REG_CTIMER_INTEN_O                        0x00000200
#define AM_REG_CTIMER_INTSTAT_O                      0x00000204
#define AM_REG_CTIMER_INTCLR_O                       0x00000208
#define AM_REG_CTIMER_INTSET_O                       0x0000020C
#define AM_REG_CTIMER_STMINTEN_O                     0x00000300
#define AM_REG_CTIMER_STMINTSTAT_O                   0x00000304
#define AM_REG_CTIMER_STMINTCLR_O                    0x00000308
#define AM_REG_CTIMER_STMINTSET_O                    0x0000030C

//*****************************************************************************
//
// CTIMER_INTEN - Counter/Timer Interrupts: Enable
//
//*****************************************************************************
// Counter/Timer B7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB7C1INT_S            31
#define AM_REG_CTIMER_INTEN_CTMRB7C1INT_M            0x80000000
#define AM_REG_CTIMER_INTEN_CTMRB7C1INT(n)           (((uint32_t)(n) << 31) & 0x80000000)

// Counter/Timer A7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA7C1INT_S            30
#define AM_REG_CTIMER_INTEN_CTMRA7C1INT_M            0x40000000
#define AM_REG_CTIMER_INTEN_CTMRA7C1INT(n)           (((uint32_t)(n) << 30) & 0x40000000)

// Counter/Timer B6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB6C1INT_S            29
#define AM_REG_CTIMER_INTEN_CTMRB6C1INT_M            0x20000000
#define AM_REG_CTIMER_INTEN_CTMRB6C1INT(n)           (((uint32_t)(n) << 29) & 0x20000000)

// Counter/Timer A6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA6C1INT_S            28
#define AM_REG_CTIMER_INTEN_CTMRA6C1INT_M            0x10000000
#define AM_REG_CTIMER_INTEN_CTMRA6C1INT(n)           (((uint32_t)(n) << 28) & 0x10000000)

// Counter/Timer B5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB5C1INT_S            27
#define AM_REG_CTIMER_INTEN_CTMRB5C1INT_M            0x08000000
#define AM_REG_CTIMER_INTEN_CTMRB5C1INT(n)           (((uint32_t)(n) << 27) & 0x08000000)

// Counter/Timer A5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA5C1INT_S            26
#define AM_REG_CTIMER_INTEN_CTMRA5C1INT_M            0x04000000
#define AM_REG_CTIMER_INTEN_CTMRA5C1INT(n)           (((uint32_t)(n) << 26) & 0x04000000)

// Counter/Timer B4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB4C1INT_S            25
#define AM_REG_CTIMER_INTEN_CTMRB4C1INT_M            0x02000000
#define AM_REG_CTIMER_INTEN_CTMRB4C1INT(n)           (((uint32_t)(n) << 25) & 0x02000000)

// Counter/Timer A4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA4C1INT_S            24
#define AM_REG_CTIMER_INTEN_CTMRA4C1INT_M            0x01000000
#define AM_REG_CTIMER_INTEN_CTMRA4C1INT(n)           (((uint32_t)(n) << 24) & 0x01000000)

// Counter/Timer B3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB3C1INT_S            23
#define AM_REG_CTIMER_INTEN_CTMRB3C1INT_M            0x00800000
#define AM_REG_CTIMER_INTEN_CTMRB3C1INT(n)           (((uint32_t)(n) << 23) & 0x00800000)

// Counter/Timer A3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA3C1INT_S            22
#define AM_REG_CTIMER_INTEN_CTMRA3C1INT_M            0x00400000
#define AM_REG_CTIMER_INTEN_CTMRA3C1INT(n)           (((uint32_t)(n) << 22) & 0x00400000)

// Counter/Timer B2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB2C1INT_S            21
#define AM_REG_CTIMER_INTEN_CTMRB2C1INT_M            0x00200000
#define AM_REG_CTIMER_INTEN_CTMRB2C1INT(n)           (((uint32_t)(n) << 21) & 0x00200000)

// Counter/Timer A2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA2C1INT_S            20
#define AM_REG_CTIMER_INTEN_CTMRA2C1INT_M            0x00100000
#define AM_REG_CTIMER_INTEN_CTMRA2C1INT(n)           (((uint32_t)(n) << 20) & 0x00100000)

// Counter/Timer B1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB1C1INT_S            19
#define AM_REG_CTIMER_INTEN_CTMRB1C1INT_M            0x00080000
#define AM_REG_CTIMER_INTEN_CTMRB1C1INT(n)           (((uint32_t)(n) << 19) & 0x00080000)

// Counter/Timer A1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA1C1INT_S            18
#define AM_REG_CTIMER_INTEN_CTMRA1C1INT_M            0x00040000
#define AM_REG_CTIMER_INTEN_CTMRA1C1INT(n)           (((uint32_t)(n) << 18) & 0x00040000)

// Counter/Timer B0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRB0C1INT_S            17
#define AM_REG_CTIMER_INTEN_CTMRB0C1INT_M            0x00020000
#define AM_REG_CTIMER_INTEN_CTMRB0C1INT(n)           (((uint32_t)(n) << 17) & 0x00020000)

// Counter/Timer A0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTEN_CTMRA0C1INT_S            16
#define AM_REG_CTIMER_INTEN_CTMRA0C1INT_M            0x00010000
#define AM_REG_CTIMER_INTEN_CTMRA0C1INT(n)           (((uint32_t)(n) << 16) & 0x00010000)

// Counter/Timer B7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB7C0INT_S            15
#define AM_REG_CTIMER_INTEN_CTMRB7C0INT_M            0x00008000
#define AM_REG_CTIMER_INTEN_CTMRB7C0INT(n)           (((uint32_t)(n) << 15) & 0x00008000)

// Counter/Timer A7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA7C0INT_S            14
#define AM_REG_CTIMER_INTEN_CTMRA7C0INT_M            0x00004000
#define AM_REG_CTIMER_INTEN_CTMRA7C0INT(n)           (((uint32_t)(n) << 14) & 0x00004000)

// Counter/Timer B6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB6C0INT_S            13
#define AM_REG_CTIMER_INTEN_CTMRB6C0INT_M            0x00002000
#define AM_REG_CTIMER_INTEN_CTMRB6C0INT(n)           (((uint32_t)(n) << 13) & 0x00002000)

// Counter/Timer A6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA6C0INT_S            12
#define AM_REG_CTIMER_INTEN_CTMRA6C0INT_M            0x00001000
#define AM_REG_CTIMER_INTEN_CTMRA6C0INT(n)           (((uint32_t)(n) << 12) & 0x00001000)

// Counter/Timer B5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB5C0INT_S            11
#define AM_REG_CTIMER_INTEN_CTMRB5C0INT_M            0x00000800
#define AM_REG_CTIMER_INTEN_CTMRB5C0INT(n)           (((uint32_t)(n) << 11) & 0x00000800)

// Counter/Timer A5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA5C0INT_S            10
#define AM_REG_CTIMER_INTEN_CTMRA5C0INT_M            0x00000400
#define AM_REG_CTIMER_INTEN_CTMRA5C0INT(n)           (((uint32_t)(n) << 10) & 0x00000400)

// Counter/Timer B4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB4C0INT_S            9
#define AM_REG_CTIMER_INTEN_CTMRB4C0INT_M            0x00000200
#define AM_REG_CTIMER_INTEN_CTMRB4C0INT(n)           (((uint32_t)(n) << 9) & 0x00000200)

// Counter/Timer A4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA4C0INT_S            8
#define AM_REG_CTIMER_INTEN_CTMRA4C0INT_M            0x00000100
#define AM_REG_CTIMER_INTEN_CTMRA4C0INT(n)           (((uint32_t)(n) << 8) & 0x00000100)

// Counter/Timer B3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB3C0INT_S            7
#define AM_REG_CTIMER_INTEN_CTMRB3C0INT_M            0x00000080
#define AM_REG_CTIMER_INTEN_CTMRB3C0INT(n)           (((uint32_t)(n) << 7) & 0x00000080)

// Counter/Timer A3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA3C0INT_S            6
#define AM_REG_CTIMER_INTEN_CTMRA3C0INT_M            0x00000040
#define AM_REG_CTIMER_INTEN_CTMRA3C0INT(n)           (((uint32_t)(n) << 6) & 0x00000040)

// Counter/Timer B2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB2C0INT_S            5
#define AM_REG_CTIMER_INTEN_CTMRB2C0INT_M            0x00000020
#define AM_REG_CTIMER_INTEN_CTMRB2C0INT(n)           (((uint32_t)(n) << 5) & 0x00000020)

// Counter/Timer A2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA2C0INT_S            4
#define AM_REG_CTIMER_INTEN_CTMRA2C0INT_M            0x00000010
#define AM_REG_CTIMER_INTEN_CTMRA2C0INT(n)           (((uint32_t)(n) << 4) & 0x00000010)

// Counter/Timer B1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB1C0INT_S            3
#define AM_REG_CTIMER_INTEN_CTMRB1C0INT_M            0x00000008
#define AM_REG_CTIMER_INTEN_CTMRB1C0INT(n)           (((uint32_t)(n) << 3) & 0x00000008)

// Counter/Timer A1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA1C0INT_S            2
#define AM_REG_CTIMER_INTEN_CTMRA1C0INT_M            0x00000004
#define AM_REG_CTIMER_INTEN_CTMRA1C0INT(n)           (((uint32_t)(n) << 2) & 0x00000004)

// Counter/Timer B0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRB0C0INT_S            1
#define AM_REG_CTIMER_INTEN_CTMRB0C0INT_M            0x00000002
#define AM_REG_CTIMER_INTEN_CTMRB0C0INT(n)           (((uint32_t)(n) << 1) & 0x00000002)

// Counter/Timer A0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTEN_CTMRA0C0INT_S            0
#define AM_REG_CTIMER_INTEN_CTMRA0C0INT_M            0x00000001
#define AM_REG_CTIMER_INTEN_CTMRA0C0INT(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CTIMER_INTSTAT - Counter/Timer Interrupts: Status
//
//*****************************************************************************
// Counter/Timer B7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB7C1INT_S          31
#define AM_REG_CTIMER_INTSTAT_CTMRB7C1INT_M          0x80000000
#define AM_REG_CTIMER_INTSTAT_CTMRB7C1INT(n)         (((uint32_t)(n) << 31) & 0x80000000)

// Counter/Timer A7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA7C1INT_S          30
#define AM_REG_CTIMER_INTSTAT_CTMRA7C1INT_M          0x40000000
#define AM_REG_CTIMER_INTSTAT_CTMRA7C1INT(n)         (((uint32_t)(n) << 30) & 0x40000000)

// Counter/Timer B6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB6C1INT_S          29
#define AM_REG_CTIMER_INTSTAT_CTMRB6C1INT_M          0x20000000
#define AM_REG_CTIMER_INTSTAT_CTMRB6C1INT(n)         (((uint32_t)(n) << 29) & 0x20000000)

// Counter/Timer A6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA6C1INT_S          28
#define AM_REG_CTIMER_INTSTAT_CTMRA6C1INT_M          0x10000000
#define AM_REG_CTIMER_INTSTAT_CTMRA6C1INT(n)         (((uint32_t)(n) << 28) & 0x10000000)

// Counter/Timer B5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB5C1INT_S          27
#define AM_REG_CTIMER_INTSTAT_CTMRB5C1INT_M          0x08000000
#define AM_REG_CTIMER_INTSTAT_CTMRB5C1INT(n)         (((uint32_t)(n) << 27) & 0x08000000)

// Counter/Timer A5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA5C1INT_S          26
#define AM_REG_CTIMER_INTSTAT_CTMRA5C1INT_M          0x04000000
#define AM_REG_CTIMER_INTSTAT_CTMRA5C1INT(n)         (((uint32_t)(n) << 26) & 0x04000000)

// Counter/Timer B4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB4C1INT_S          25
#define AM_REG_CTIMER_INTSTAT_CTMRB4C1INT_M          0x02000000
#define AM_REG_CTIMER_INTSTAT_CTMRB4C1INT(n)         (((uint32_t)(n) << 25) & 0x02000000)

// Counter/Timer A4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA4C1INT_S          24
#define AM_REG_CTIMER_INTSTAT_CTMRA4C1INT_M          0x01000000
#define AM_REG_CTIMER_INTSTAT_CTMRA4C1INT(n)         (((uint32_t)(n) << 24) & 0x01000000)

// Counter/Timer B3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB3C1INT_S          23
#define AM_REG_CTIMER_INTSTAT_CTMRB3C1INT_M          0x00800000
#define AM_REG_CTIMER_INTSTAT_CTMRB3C1INT(n)         (((uint32_t)(n) << 23) & 0x00800000)

// Counter/Timer A3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA3C1INT_S          22
#define AM_REG_CTIMER_INTSTAT_CTMRA3C1INT_M          0x00400000
#define AM_REG_CTIMER_INTSTAT_CTMRA3C1INT(n)         (((uint32_t)(n) << 22) & 0x00400000)

// Counter/Timer B2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB2C1INT_S          21
#define AM_REG_CTIMER_INTSTAT_CTMRB2C1INT_M          0x00200000
#define AM_REG_CTIMER_INTSTAT_CTMRB2C1INT(n)         (((uint32_t)(n) << 21) & 0x00200000)

// Counter/Timer A2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA2C1INT_S          20
#define AM_REG_CTIMER_INTSTAT_CTMRA2C1INT_M          0x00100000
#define AM_REG_CTIMER_INTSTAT_CTMRA2C1INT(n)         (((uint32_t)(n) << 20) & 0x00100000)

// Counter/Timer B1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB1C1INT_S          19
#define AM_REG_CTIMER_INTSTAT_CTMRB1C1INT_M          0x00080000
#define AM_REG_CTIMER_INTSTAT_CTMRB1C1INT(n)         (((uint32_t)(n) << 19) & 0x00080000)

// Counter/Timer A1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA1C1INT_S          18
#define AM_REG_CTIMER_INTSTAT_CTMRA1C1INT_M          0x00040000
#define AM_REG_CTIMER_INTSTAT_CTMRA1C1INT(n)         (((uint32_t)(n) << 18) & 0x00040000)

// Counter/Timer B0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRB0C1INT_S          17
#define AM_REG_CTIMER_INTSTAT_CTMRB0C1INT_M          0x00020000
#define AM_REG_CTIMER_INTSTAT_CTMRB0C1INT(n)         (((uint32_t)(n) << 17) & 0x00020000)

// Counter/Timer A0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSTAT_CTMRA0C1INT_S          16
#define AM_REG_CTIMER_INTSTAT_CTMRA0C1INT_M          0x00010000
#define AM_REG_CTIMER_INTSTAT_CTMRA0C1INT(n)         (((uint32_t)(n) << 16) & 0x00010000)

// Counter/Timer B7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB7C0INT_S          15
#define AM_REG_CTIMER_INTSTAT_CTMRB7C0INT_M          0x00008000
#define AM_REG_CTIMER_INTSTAT_CTMRB7C0INT(n)         (((uint32_t)(n) << 15) & 0x00008000)

// Counter/Timer A7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA7C0INT_S          14
#define AM_REG_CTIMER_INTSTAT_CTMRA7C0INT_M          0x00004000
#define AM_REG_CTIMER_INTSTAT_CTMRA7C0INT(n)         (((uint32_t)(n) << 14) & 0x00004000)

// Counter/Timer B6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB6C0INT_S          13
#define AM_REG_CTIMER_INTSTAT_CTMRB6C0INT_M          0x00002000
#define AM_REG_CTIMER_INTSTAT_CTMRB6C0INT(n)         (((uint32_t)(n) << 13) & 0x00002000)

// Counter/Timer A6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA6C0INT_S          12
#define AM_REG_CTIMER_INTSTAT_CTMRA6C0INT_M          0x00001000
#define AM_REG_CTIMER_INTSTAT_CTMRA6C0INT(n)         (((uint32_t)(n) << 12) & 0x00001000)

// Counter/Timer B5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB5C0INT_S          11
#define AM_REG_CTIMER_INTSTAT_CTMRB5C0INT_M          0x00000800
#define AM_REG_CTIMER_INTSTAT_CTMRB5C0INT(n)         (((uint32_t)(n) << 11) & 0x00000800)

// Counter/Timer A5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA5C0INT_S          10
#define AM_REG_CTIMER_INTSTAT_CTMRA5C0INT_M          0x00000400
#define AM_REG_CTIMER_INTSTAT_CTMRA5C0INT(n)         (((uint32_t)(n) << 10) & 0x00000400)

// Counter/Timer B4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB4C0INT_S          9
#define AM_REG_CTIMER_INTSTAT_CTMRB4C0INT_M          0x00000200
#define AM_REG_CTIMER_INTSTAT_CTMRB4C0INT(n)         (((uint32_t)(n) << 9) & 0x00000200)

// Counter/Timer A4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA4C0INT_S          8
#define AM_REG_CTIMER_INTSTAT_CTMRA4C0INT_M          0x00000100
#define AM_REG_CTIMER_INTSTAT_CTMRA4C0INT(n)         (((uint32_t)(n) << 8) & 0x00000100)

// Counter/Timer B3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB3C0INT_S          7
#define AM_REG_CTIMER_INTSTAT_CTMRB3C0INT_M          0x00000080
#define AM_REG_CTIMER_INTSTAT_CTMRB3C0INT(n)         (((uint32_t)(n) << 7) & 0x00000080)

// Counter/Timer A3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA3C0INT_S          6
#define AM_REG_CTIMER_INTSTAT_CTMRA3C0INT_M          0x00000040
#define AM_REG_CTIMER_INTSTAT_CTMRA3C0INT(n)         (((uint32_t)(n) << 6) & 0x00000040)

// Counter/Timer B2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB2C0INT_S          5
#define AM_REG_CTIMER_INTSTAT_CTMRB2C0INT_M          0x00000020
#define AM_REG_CTIMER_INTSTAT_CTMRB2C0INT(n)         (((uint32_t)(n) << 5) & 0x00000020)

// Counter/Timer A2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA2C0INT_S          4
#define AM_REG_CTIMER_INTSTAT_CTMRA2C0INT_M          0x00000010
#define AM_REG_CTIMER_INTSTAT_CTMRA2C0INT(n)         (((uint32_t)(n) << 4) & 0x00000010)

// Counter/Timer B1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB1C0INT_S          3
#define AM_REG_CTIMER_INTSTAT_CTMRB1C0INT_M          0x00000008
#define AM_REG_CTIMER_INTSTAT_CTMRB1C0INT(n)         (((uint32_t)(n) << 3) & 0x00000008)

// Counter/Timer A1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA1C0INT_S          2
#define AM_REG_CTIMER_INTSTAT_CTMRA1C0INT_M          0x00000004
#define AM_REG_CTIMER_INTSTAT_CTMRA1C0INT(n)         (((uint32_t)(n) << 2) & 0x00000004)

// Counter/Timer B0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRB0C0INT_S          1
#define AM_REG_CTIMER_INTSTAT_CTMRB0C0INT_M          0x00000002
#define AM_REG_CTIMER_INTSTAT_CTMRB0C0INT(n)         (((uint32_t)(n) << 1) & 0x00000002)

// Counter/Timer A0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSTAT_CTMRA0C0INT_S          0
#define AM_REG_CTIMER_INTSTAT_CTMRA0C0INT_M          0x00000001
#define AM_REG_CTIMER_INTSTAT_CTMRA0C0INT(n)         (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CTIMER_INTCLR - Counter/Timer Interrupts: Clear
//
//*****************************************************************************
// Counter/Timer B7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB7C1INT_S           31
#define AM_REG_CTIMER_INTCLR_CTMRB7C1INT_M           0x80000000
#define AM_REG_CTIMER_INTCLR_CTMRB7C1INT(n)          (((uint32_t)(n) << 31) & 0x80000000)

// Counter/Timer A7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA7C1INT_S           30
#define AM_REG_CTIMER_INTCLR_CTMRA7C1INT_M           0x40000000
#define AM_REG_CTIMER_INTCLR_CTMRA7C1INT(n)          (((uint32_t)(n) << 30) & 0x40000000)

// Counter/Timer B6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB6C1INT_S           29
#define AM_REG_CTIMER_INTCLR_CTMRB6C1INT_M           0x20000000
#define AM_REG_CTIMER_INTCLR_CTMRB6C1INT(n)          (((uint32_t)(n) << 29) & 0x20000000)

// Counter/Timer A6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA6C1INT_S           28
#define AM_REG_CTIMER_INTCLR_CTMRA6C1INT_M           0x10000000
#define AM_REG_CTIMER_INTCLR_CTMRA6C1INT(n)          (((uint32_t)(n) << 28) & 0x10000000)

// Counter/Timer B5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB5C1INT_S           27
#define AM_REG_CTIMER_INTCLR_CTMRB5C1INT_M           0x08000000
#define AM_REG_CTIMER_INTCLR_CTMRB5C1INT(n)          (((uint32_t)(n) << 27) & 0x08000000)

// Counter/Timer A5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA5C1INT_S           26
#define AM_REG_CTIMER_INTCLR_CTMRA5C1INT_M           0x04000000
#define AM_REG_CTIMER_INTCLR_CTMRA5C1INT(n)          (((uint32_t)(n) << 26) & 0x04000000)

// Counter/Timer B4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB4C1INT_S           25
#define AM_REG_CTIMER_INTCLR_CTMRB4C1INT_M           0x02000000
#define AM_REG_CTIMER_INTCLR_CTMRB4C1INT(n)          (((uint32_t)(n) << 25) & 0x02000000)

// Counter/Timer A4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA4C1INT_S           24
#define AM_REG_CTIMER_INTCLR_CTMRA4C1INT_M           0x01000000
#define AM_REG_CTIMER_INTCLR_CTMRA4C1INT(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Counter/Timer B3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB3C1INT_S           23
#define AM_REG_CTIMER_INTCLR_CTMRB3C1INT_M           0x00800000
#define AM_REG_CTIMER_INTCLR_CTMRB3C1INT(n)          (((uint32_t)(n) << 23) & 0x00800000)

// Counter/Timer A3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA3C1INT_S           22
#define AM_REG_CTIMER_INTCLR_CTMRA3C1INT_M           0x00400000
#define AM_REG_CTIMER_INTCLR_CTMRA3C1INT(n)          (((uint32_t)(n) << 22) & 0x00400000)

// Counter/Timer B2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB2C1INT_S           21
#define AM_REG_CTIMER_INTCLR_CTMRB2C1INT_M           0x00200000
#define AM_REG_CTIMER_INTCLR_CTMRB2C1INT(n)          (((uint32_t)(n) << 21) & 0x00200000)

// Counter/Timer A2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA2C1INT_S           20
#define AM_REG_CTIMER_INTCLR_CTMRA2C1INT_M           0x00100000
#define AM_REG_CTIMER_INTCLR_CTMRA2C1INT(n)          (((uint32_t)(n) << 20) & 0x00100000)

// Counter/Timer B1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB1C1INT_S           19
#define AM_REG_CTIMER_INTCLR_CTMRB1C1INT_M           0x00080000
#define AM_REG_CTIMER_INTCLR_CTMRB1C1INT(n)          (((uint32_t)(n) << 19) & 0x00080000)

// Counter/Timer A1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA1C1INT_S           18
#define AM_REG_CTIMER_INTCLR_CTMRA1C1INT_M           0x00040000
#define AM_REG_CTIMER_INTCLR_CTMRA1C1INT(n)          (((uint32_t)(n) << 18) & 0x00040000)

// Counter/Timer B0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRB0C1INT_S           17
#define AM_REG_CTIMER_INTCLR_CTMRB0C1INT_M           0x00020000
#define AM_REG_CTIMER_INTCLR_CTMRB0C1INT(n)          (((uint32_t)(n) << 17) & 0x00020000)

// Counter/Timer A0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTCLR_CTMRA0C1INT_S           16
#define AM_REG_CTIMER_INTCLR_CTMRA0C1INT_M           0x00010000
#define AM_REG_CTIMER_INTCLR_CTMRA0C1INT(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Counter/Timer B7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB7C0INT_S           15
#define AM_REG_CTIMER_INTCLR_CTMRB7C0INT_M           0x00008000
#define AM_REG_CTIMER_INTCLR_CTMRB7C0INT(n)          (((uint32_t)(n) << 15) & 0x00008000)

// Counter/Timer A7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA7C0INT_S           14
#define AM_REG_CTIMER_INTCLR_CTMRA7C0INT_M           0x00004000
#define AM_REG_CTIMER_INTCLR_CTMRA7C0INT(n)          (((uint32_t)(n) << 14) & 0x00004000)

// Counter/Timer B6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB6C0INT_S           13
#define AM_REG_CTIMER_INTCLR_CTMRB6C0INT_M           0x00002000
#define AM_REG_CTIMER_INTCLR_CTMRB6C0INT(n)          (((uint32_t)(n) << 13) & 0x00002000)

// Counter/Timer A6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA6C0INT_S           12
#define AM_REG_CTIMER_INTCLR_CTMRA6C0INT_M           0x00001000
#define AM_REG_CTIMER_INTCLR_CTMRA6C0INT(n)          (((uint32_t)(n) << 12) & 0x00001000)

// Counter/Timer B5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB5C0INT_S           11
#define AM_REG_CTIMER_INTCLR_CTMRB5C0INT_M           0x00000800
#define AM_REG_CTIMER_INTCLR_CTMRB5C0INT(n)          (((uint32_t)(n) << 11) & 0x00000800)

// Counter/Timer A5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA5C0INT_S           10
#define AM_REG_CTIMER_INTCLR_CTMRA5C0INT_M           0x00000400
#define AM_REG_CTIMER_INTCLR_CTMRA5C0INT(n)          (((uint32_t)(n) << 10) & 0x00000400)

// Counter/Timer B4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB4C0INT_S           9
#define AM_REG_CTIMER_INTCLR_CTMRB4C0INT_M           0x00000200
#define AM_REG_CTIMER_INTCLR_CTMRB4C0INT(n)          (((uint32_t)(n) << 9) & 0x00000200)

// Counter/Timer A4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA4C0INT_S           8
#define AM_REG_CTIMER_INTCLR_CTMRA4C0INT_M           0x00000100
#define AM_REG_CTIMER_INTCLR_CTMRA4C0INT(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Counter/Timer B3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB3C0INT_S           7
#define AM_REG_CTIMER_INTCLR_CTMRB3C0INT_M           0x00000080
#define AM_REG_CTIMER_INTCLR_CTMRB3C0INT(n)          (((uint32_t)(n) << 7) & 0x00000080)

// Counter/Timer A3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA3C0INT_S           6
#define AM_REG_CTIMER_INTCLR_CTMRA3C0INT_M           0x00000040
#define AM_REG_CTIMER_INTCLR_CTMRA3C0INT(n)          (((uint32_t)(n) << 6) & 0x00000040)

// Counter/Timer B2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB2C0INT_S           5
#define AM_REG_CTIMER_INTCLR_CTMRB2C0INT_M           0x00000020
#define AM_REG_CTIMER_INTCLR_CTMRB2C0INT(n)          (((uint32_t)(n) << 5) & 0x00000020)

// Counter/Timer A2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA2C0INT_S           4
#define AM_REG_CTIMER_INTCLR_CTMRA2C0INT_M           0x00000010
#define AM_REG_CTIMER_INTCLR_CTMRA2C0INT(n)          (((uint32_t)(n) << 4) & 0x00000010)

// Counter/Timer B1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB1C0INT_S           3
#define AM_REG_CTIMER_INTCLR_CTMRB1C0INT_M           0x00000008
#define AM_REG_CTIMER_INTCLR_CTMRB1C0INT(n)          (((uint32_t)(n) << 3) & 0x00000008)

// Counter/Timer A1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA1C0INT_S           2
#define AM_REG_CTIMER_INTCLR_CTMRA1C0INT_M           0x00000004
#define AM_REG_CTIMER_INTCLR_CTMRA1C0INT(n)          (((uint32_t)(n) << 2) & 0x00000004)

// Counter/Timer B0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRB0C0INT_S           1
#define AM_REG_CTIMER_INTCLR_CTMRB0C0INT_M           0x00000002
#define AM_REG_CTIMER_INTCLR_CTMRB0C0INT(n)          (((uint32_t)(n) << 1) & 0x00000002)

// Counter/Timer A0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTCLR_CTMRA0C0INT_S           0
#define AM_REG_CTIMER_INTCLR_CTMRA0C0INT_M           0x00000001
#define AM_REG_CTIMER_INTCLR_CTMRA0C0INT(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CTIMER_INTSET - Counter/Timer Interrupts: Set
//
//*****************************************************************************
// Counter/Timer B7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB7C1INT_S           31
#define AM_REG_CTIMER_INTSET_CTMRB7C1INT_M           0x80000000
#define AM_REG_CTIMER_INTSET_CTMRB7C1INT(n)          (((uint32_t)(n) << 31) & 0x80000000)

// Counter/Timer A7 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA7C1INT_S           30
#define AM_REG_CTIMER_INTSET_CTMRA7C1INT_M           0x40000000
#define AM_REG_CTIMER_INTSET_CTMRA7C1INT(n)          (((uint32_t)(n) << 30) & 0x40000000)

// Counter/Timer B6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB6C1INT_S           29
#define AM_REG_CTIMER_INTSET_CTMRB6C1INT_M           0x20000000
#define AM_REG_CTIMER_INTSET_CTMRB6C1INT(n)          (((uint32_t)(n) << 29) & 0x20000000)

// Counter/Timer A6 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA6C1INT_S           28
#define AM_REG_CTIMER_INTSET_CTMRA6C1INT_M           0x10000000
#define AM_REG_CTIMER_INTSET_CTMRA6C1INT(n)          (((uint32_t)(n) << 28) & 0x10000000)

// Counter/Timer B5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB5C1INT_S           27
#define AM_REG_CTIMER_INTSET_CTMRB5C1INT_M           0x08000000
#define AM_REG_CTIMER_INTSET_CTMRB5C1INT(n)          (((uint32_t)(n) << 27) & 0x08000000)

// Counter/Timer A5 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA5C1INT_S           26
#define AM_REG_CTIMER_INTSET_CTMRA5C1INT_M           0x04000000
#define AM_REG_CTIMER_INTSET_CTMRA5C1INT(n)          (((uint32_t)(n) << 26) & 0x04000000)

// Counter/Timer B4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB4C1INT_S           25
#define AM_REG_CTIMER_INTSET_CTMRB4C1INT_M           0x02000000
#define AM_REG_CTIMER_INTSET_CTMRB4C1INT(n)          (((uint32_t)(n) << 25) & 0x02000000)

// Counter/Timer A4 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA4C1INT_S           24
#define AM_REG_CTIMER_INTSET_CTMRA4C1INT_M           0x01000000
#define AM_REG_CTIMER_INTSET_CTMRA4C1INT(n)          (((uint32_t)(n) << 24) & 0x01000000)

// Counter/Timer B3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB3C1INT_S           23
#define AM_REG_CTIMER_INTSET_CTMRB3C1INT_M           0x00800000
#define AM_REG_CTIMER_INTSET_CTMRB3C1INT(n)          (((uint32_t)(n) << 23) & 0x00800000)

// Counter/Timer A3 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA3C1INT_S           22
#define AM_REG_CTIMER_INTSET_CTMRA3C1INT_M           0x00400000
#define AM_REG_CTIMER_INTSET_CTMRA3C1INT(n)          (((uint32_t)(n) << 22) & 0x00400000)

// Counter/Timer B2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB2C1INT_S           21
#define AM_REG_CTIMER_INTSET_CTMRB2C1INT_M           0x00200000
#define AM_REG_CTIMER_INTSET_CTMRB2C1INT(n)          (((uint32_t)(n) << 21) & 0x00200000)

// Counter/Timer A2 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA2C1INT_S           20
#define AM_REG_CTIMER_INTSET_CTMRA2C1INT_M           0x00100000
#define AM_REG_CTIMER_INTSET_CTMRA2C1INT(n)          (((uint32_t)(n) << 20) & 0x00100000)

// Counter/Timer B1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB1C1INT_S           19
#define AM_REG_CTIMER_INTSET_CTMRB1C1INT_M           0x00080000
#define AM_REG_CTIMER_INTSET_CTMRB1C1INT(n)          (((uint32_t)(n) << 19) & 0x00080000)

// Counter/Timer A1 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA1C1INT_S           18
#define AM_REG_CTIMER_INTSET_CTMRA1C1INT_M           0x00040000
#define AM_REG_CTIMER_INTSET_CTMRA1C1INT(n)          (((uint32_t)(n) << 18) & 0x00040000)

// Counter/Timer B0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRB0C1INT_S           17
#define AM_REG_CTIMER_INTSET_CTMRB0C1INT_M           0x00020000
#define AM_REG_CTIMER_INTSET_CTMRB0C1INT(n)          (((uint32_t)(n) << 17) & 0x00020000)

// Counter/Timer A0 interrupt based on COMPR1.
#define AM_REG_CTIMER_INTSET_CTMRA0C1INT_S           16
#define AM_REG_CTIMER_INTSET_CTMRA0C1INT_M           0x00010000
#define AM_REG_CTIMER_INTSET_CTMRA0C1INT(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Counter/Timer B7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB7C0INT_S           15
#define AM_REG_CTIMER_INTSET_CTMRB7C0INT_M           0x00008000
#define AM_REG_CTIMER_INTSET_CTMRB7C0INT(n)          (((uint32_t)(n) << 15) & 0x00008000)

// Counter/Timer A7 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA7C0INT_S           14
#define AM_REG_CTIMER_INTSET_CTMRA7C0INT_M           0x00004000
#define AM_REG_CTIMER_INTSET_CTMRA7C0INT(n)          (((uint32_t)(n) << 14) & 0x00004000)

// Counter/Timer B6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB6C0INT_S           13
#define AM_REG_CTIMER_INTSET_CTMRB6C0INT_M           0x00002000
#define AM_REG_CTIMER_INTSET_CTMRB6C0INT(n)          (((uint32_t)(n) << 13) & 0x00002000)

// Counter/Timer A6 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA6C0INT_S           12
#define AM_REG_CTIMER_INTSET_CTMRA6C0INT_M           0x00001000
#define AM_REG_CTIMER_INTSET_CTMRA6C0INT(n)          (((uint32_t)(n) << 12) & 0x00001000)

// Counter/Timer B5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB5C0INT_S           11
#define AM_REG_CTIMER_INTSET_CTMRB5C0INT_M           0x00000800
#define AM_REG_CTIMER_INTSET_CTMRB5C0INT(n)          (((uint32_t)(n) << 11) & 0x00000800)

// Counter/Timer A5 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA5C0INT_S           10
#define AM_REG_CTIMER_INTSET_CTMRA5C0INT_M           0x00000400
#define AM_REG_CTIMER_INTSET_CTMRA5C0INT(n)          (((uint32_t)(n) << 10) & 0x00000400)

// Counter/Timer B4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB4C0INT_S           9
#define AM_REG_CTIMER_INTSET_CTMRB4C0INT_M           0x00000200
#define AM_REG_CTIMER_INTSET_CTMRB4C0INT(n)          (((uint32_t)(n) << 9) & 0x00000200)

// Counter/Timer A4 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA4C0INT_S           8
#define AM_REG_CTIMER_INTSET_CTMRA4C0INT_M           0x00000100
#define AM_REG_CTIMER_INTSET_CTMRA4C0INT(n)          (((uint32_t)(n) << 8) & 0x00000100)

// Counter/Timer B3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB3C0INT_S           7
#define AM_REG_CTIMER_INTSET_CTMRB3C0INT_M           0x00000080
#define AM_REG_CTIMER_INTSET_CTMRB3C0INT(n)          (((uint32_t)(n) << 7) & 0x00000080)

// Counter/Timer A3 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA3C0INT_S           6
#define AM_REG_CTIMER_INTSET_CTMRA3C0INT_M           0x00000040
#define AM_REG_CTIMER_INTSET_CTMRA3C0INT(n)          (((uint32_t)(n) << 6) & 0x00000040)

// Counter/Timer B2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB2C0INT_S           5
#define AM_REG_CTIMER_INTSET_CTMRB2C0INT_M           0x00000020
#define AM_REG_CTIMER_INTSET_CTMRB2C0INT(n)          (((uint32_t)(n) << 5) & 0x00000020)

// Counter/Timer A2 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA2C0INT_S           4
#define AM_REG_CTIMER_INTSET_CTMRA2C0INT_M           0x00000010
#define AM_REG_CTIMER_INTSET_CTMRA2C0INT(n)          (((uint32_t)(n) << 4) & 0x00000010)

// Counter/Timer B1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB1C0INT_S           3
#define AM_REG_CTIMER_INTSET_CTMRB1C0INT_M           0x00000008
#define AM_REG_CTIMER_INTSET_CTMRB1C0INT(n)          (((uint32_t)(n) << 3) & 0x00000008)

// Counter/Timer A1 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA1C0INT_S           2
#define AM_REG_CTIMER_INTSET_CTMRA1C0INT_M           0x00000004
#define AM_REG_CTIMER_INTSET_CTMRA1C0INT(n)          (((uint32_t)(n) << 2) & 0x00000004)

// Counter/Timer B0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRB0C0INT_S           1
#define AM_REG_CTIMER_INTSET_CTMRB0C0INT_M           0x00000002
#define AM_REG_CTIMER_INTSET_CTMRB0C0INT(n)          (((uint32_t)(n) << 1) & 0x00000002)

// Counter/Timer A0 interrupt based on COMPR0.
#define AM_REG_CTIMER_INTSET_CTMRA0C0INT_S           0
#define AM_REG_CTIMER_INTSET_CTMRA0C0INT_M           0x00000001
#define AM_REG_CTIMER_INTSET_CTMRA0C0INT(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CTIMER_STMINTEN - STIMER Interrupt registers: Enable
//
//*****************************************************************************
// CAPTURE register D has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTEN_CAPTURED_S            12
#define AM_REG_CTIMER_STMINTEN_CAPTURED_M            0x00001000
#define AM_REG_CTIMER_STMINTEN_CAPTURED(n)           (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_STMINTEN_CAPTURED_CAPD_INT     0x00001000

// CAPTURE register C has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTEN_CAPTUREC_S            11
#define AM_REG_CTIMER_STMINTEN_CAPTUREC_M            0x00000800
#define AM_REG_CTIMER_STMINTEN_CAPTUREC(n)           (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_STMINTEN_CAPTUREC_CAPC_INT     0x00000800

// CAPTURE register B has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTEN_CAPTUREB_S            10
#define AM_REG_CTIMER_STMINTEN_CAPTUREB_M            0x00000400
#define AM_REG_CTIMER_STMINTEN_CAPTUREB(n)           (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_STMINTEN_CAPTUREB_CAPB_INT     0x00000400

// CAPTURE register A has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTEN_CAPTUREA_S            9
#define AM_REG_CTIMER_STMINTEN_CAPTUREA_M            0x00000200
#define AM_REG_CTIMER_STMINTEN_CAPTUREA(n)           (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_STMINTEN_CAPTUREA_CAPA_INT     0x00000200

// COUNTER over flowed from 0xFFFFFFFF back to 0x00000000.
#define AM_REG_CTIMER_STMINTEN_OVERFLOW_S            8
#define AM_REG_CTIMER_STMINTEN_OVERFLOW_M            0x00000100
#define AM_REG_CTIMER_STMINTEN_OVERFLOW(n)           (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_STMINTEN_OVERFLOW_OFLOW_INT    0x00000100

// COUNTER is greater than or equal to COMPARE register H.
#define AM_REG_CTIMER_STMINTEN_COMPAREH_S            7
#define AM_REG_CTIMER_STMINTEN_COMPAREH_M            0x00000080
#define AM_REG_CTIMER_STMINTEN_COMPAREH(n)           (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_STMINTEN_COMPAREH_COMPARED     0x00000080

// COUNTER is greater than or equal to COMPARE register G.
#define AM_REG_CTIMER_STMINTEN_COMPAREG_S            6
#define AM_REG_CTIMER_STMINTEN_COMPAREG_M            0x00000040
#define AM_REG_CTIMER_STMINTEN_COMPAREG(n)           (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_STMINTEN_COMPAREG_COMPARED     0x00000040

// COUNTER is greater than or equal to COMPARE register F.
#define AM_REG_CTIMER_STMINTEN_COMPAREF_S            5
#define AM_REG_CTIMER_STMINTEN_COMPAREF_M            0x00000020
#define AM_REG_CTIMER_STMINTEN_COMPAREF(n)           (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_STMINTEN_COMPAREF_COMPARED     0x00000020

// COUNTER is greater than or equal to COMPARE register E.
#define AM_REG_CTIMER_STMINTEN_COMPAREE_S            4
#define AM_REG_CTIMER_STMINTEN_COMPAREE_M            0x00000010
#define AM_REG_CTIMER_STMINTEN_COMPAREE(n)           (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_STMINTEN_COMPAREE_COMPARED     0x00000010

// COUNTER is greater than or equal to COMPARE register D.
#define AM_REG_CTIMER_STMINTEN_COMPARED_S            3
#define AM_REG_CTIMER_STMINTEN_COMPARED_M            0x00000008
#define AM_REG_CTIMER_STMINTEN_COMPARED(n)           (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_STMINTEN_COMPARED_COMPARED     0x00000008

// COUNTER is greater than or equal to COMPARE register C.
#define AM_REG_CTIMER_STMINTEN_COMPAREC_S            2
#define AM_REG_CTIMER_STMINTEN_COMPAREC_M            0x00000004
#define AM_REG_CTIMER_STMINTEN_COMPAREC(n)           (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_STMINTEN_COMPAREC_COMPARED     0x00000004

// COUNTER is greater than or equal to COMPARE register B.
#define AM_REG_CTIMER_STMINTEN_COMPAREB_S            1
#define AM_REG_CTIMER_STMINTEN_COMPAREB_M            0x00000002
#define AM_REG_CTIMER_STMINTEN_COMPAREB(n)           (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_STMINTEN_COMPAREB_COMPARED     0x00000002

// COUNTER is greater than or equal to COMPARE register A.
#define AM_REG_CTIMER_STMINTEN_COMPAREA_S            0
#define AM_REG_CTIMER_STMINTEN_COMPAREA_M            0x00000001
#define AM_REG_CTIMER_STMINTEN_COMPAREA(n)           (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_STMINTEN_COMPAREA_COMPARED     0x00000001

//*****************************************************************************
//
// CTIMER_STMINTSTAT - STIMER Interrupt registers: Status
//
//*****************************************************************************
// CAPTURE register D has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSTAT_CAPTURED_S          12
#define AM_REG_CTIMER_STMINTSTAT_CAPTURED_M          0x00001000
#define AM_REG_CTIMER_STMINTSTAT_CAPTURED(n)         (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_STMINTSTAT_CAPTURED_CAPD_INT   0x00001000

// CAPTURE register C has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREC_S          11
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREC_M          0x00000800
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREC(n)         (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREC_CAPC_INT   0x00000800

// CAPTURE register B has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREB_S          10
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREB_M          0x00000400
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREB(n)         (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREB_CAPB_INT   0x00000400

// CAPTURE register A has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREA_S          9
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREA_M          0x00000200
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREA(n)         (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_STMINTSTAT_CAPTUREA_CAPA_INT   0x00000200

// COUNTER over flowed from 0xFFFFFFFF back to 0x00000000.
#define AM_REG_CTIMER_STMINTSTAT_OVERFLOW_S          8
#define AM_REG_CTIMER_STMINTSTAT_OVERFLOW_M          0x00000100
#define AM_REG_CTIMER_STMINTSTAT_OVERFLOW(n)         (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_STMINTSTAT_OVERFLOW_OFLOW_INT  0x00000100

// COUNTER is greater than or equal to COMPARE register H.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREH_S          7
#define AM_REG_CTIMER_STMINTSTAT_COMPAREH_M          0x00000080
#define AM_REG_CTIMER_STMINTSTAT_COMPAREH(n)         (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREH_COMPARED   0x00000080

// COUNTER is greater than or equal to COMPARE register G.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREG_S          6
#define AM_REG_CTIMER_STMINTSTAT_COMPAREG_M          0x00000040
#define AM_REG_CTIMER_STMINTSTAT_COMPAREG(n)         (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREG_COMPARED   0x00000040

// COUNTER is greater than or equal to COMPARE register F.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREF_S          5
#define AM_REG_CTIMER_STMINTSTAT_COMPAREF_M          0x00000020
#define AM_REG_CTIMER_STMINTSTAT_COMPAREF(n)         (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREF_COMPARED   0x00000020

// COUNTER is greater than or equal to COMPARE register E.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREE_S          4
#define AM_REG_CTIMER_STMINTSTAT_COMPAREE_M          0x00000010
#define AM_REG_CTIMER_STMINTSTAT_COMPAREE(n)         (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREE_COMPARED   0x00000010

// COUNTER is greater than or equal to COMPARE register D.
#define AM_REG_CTIMER_STMINTSTAT_COMPARED_S          3
#define AM_REG_CTIMER_STMINTSTAT_COMPARED_M          0x00000008
#define AM_REG_CTIMER_STMINTSTAT_COMPARED(n)         (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_STMINTSTAT_COMPARED_COMPARED   0x00000008

// COUNTER is greater than or equal to COMPARE register C.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREC_S          2
#define AM_REG_CTIMER_STMINTSTAT_COMPAREC_M          0x00000004
#define AM_REG_CTIMER_STMINTSTAT_COMPAREC(n)         (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREC_COMPARED   0x00000004

// COUNTER is greater than or equal to COMPARE register B.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREB_S          1
#define AM_REG_CTIMER_STMINTSTAT_COMPAREB_M          0x00000002
#define AM_REG_CTIMER_STMINTSTAT_COMPAREB(n)         (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREB_COMPARED   0x00000002

// COUNTER is greater than or equal to COMPARE register A.
#define AM_REG_CTIMER_STMINTSTAT_COMPAREA_S          0
#define AM_REG_CTIMER_STMINTSTAT_COMPAREA_M          0x00000001
#define AM_REG_CTIMER_STMINTSTAT_COMPAREA(n)         (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_STMINTSTAT_COMPAREA_COMPARED   0x00000001

//*****************************************************************************
//
// CTIMER_STMINTCLR - STIMER Interrupt registers: Clear
//
//*****************************************************************************
// CAPTURE register D has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTCLR_CAPTURED_S           12
#define AM_REG_CTIMER_STMINTCLR_CAPTURED_M           0x00001000
#define AM_REG_CTIMER_STMINTCLR_CAPTURED(n)          (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_STMINTCLR_CAPTURED_CAPD_INT    0x00001000

// CAPTURE register C has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTCLR_CAPTUREC_S           11
#define AM_REG_CTIMER_STMINTCLR_CAPTUREC_M           0x00000800
#define AM_REG_CTIMER_STMINTCLR_CAPTUREC(n)          (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_STMINTCLR_CAPTUREC_CAPC_INT    0x00000800

// CAPTURE register B has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTCLR_CAPTUREB_S           10
#define AM_REG_CTIMER_STMINTCLR_CAPTUREB_M           0x00000400
#define AM_REG_CTIMER_STMINTCLR_CAPTUREB(n)          (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_STMINTCLR_CAPTUREB_CAPB_INT    0x00000400

// CAPTURE register A has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTCLR_CAPTUREA_S           9
#define AM_REG_CTIMER_STMINTCLR_CAPTUREA_M           0x00000200
#define AM_REG_CTIMER_STMINTCLR_CAPTUREA(n)          (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_STMINTCLR_CAPTUREA_CAPA_INT    0x00000200

// COUNTER over flowed from 0xFFFFFFFF back to 0x00000000.
#define AM_REG_CTIMER_STMINTCLR_OVERFLOW_S           8
#define AM_REG_CTIMER_STMINTCLR_OVERFLOW_M           0x00000100
#define AM_REG_CTIMER_STMINTCLR_OVERFLOW(n)          (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_STMINTCLR_OVERFLOW_OFLOW_INT   0x00000100

// COUNTER is greater than or equal to COMPARE register H.
#define AM_REG_CTIMER_STMINTCLR_COMPAREH_S           7
#define AM_REG_CTIMER_STMINTCLR_COMPAREH_M           0x00000080
#define AM_REG_CTIMER_STMINTCLR_COMPAREH(n)          (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_STMINTCLR_COMPAREH_COMPARED    0x00000080

// COUNTER is greater than or equal to COMPARE register G.
#define AM_REG_CTIMER_STMINTCLR_COMPAREG_S           6
#define AM_REG_CTIMER_STMINTCLR_COMPAREG_M           0x00000040
#define AM_REG_CTIMER_STMINTCLR_COMPAREG(n)          (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_STMINTCLR_COMPAREG_COMPARED    0x00000040

// COUNTER is greater than or equal to COMPARE register F.
#define AM_REG_CTIMER_STMINTCLR_COMPAREF_S           5
#define AM_REG_CTIMER_STMINTCLR_COMPAREF_M           0x00000020
#define AM_REG_CTIMER_STMINTCLR_COMPAREF(n)          (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_STMINTCLR_COMPAREF_COMPARED    0x00000020

// COUNTER is greater than or equal to COMPARE register E.
#define AM_REG_CTIMER_STMINTCLR_COMPAREE_S           4
#define AM_REG_CTIMER_STMINTCLR_COMPAREE_M           0x00000010
#define AM_REG_CTIMER_STMINTCLR_COMPAREE(n)          (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_STMINTCLR_COMPAREE_COMPARED    0x00000010

// COUNTER is greater than or equal to COMPARE register D.
#define AM_REG_CTIMER_STMINTCLR_COMPARED_S           3
#define AM_REG_CTIMER_STMINTCLR_COMPARED_M           0x00000008
#define AM_REG_CTIMER_STMINTCLR_COMPARED(n)          (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_STMINTCLR_COMPARED_COMPARED    0x00000008

// COUNTER is greater than or equal to COMPARE register C.
#define AM_REG_CTIMER_STMINTCLR_COMPAREC_S           2
#define AM_REG_CTIMER_STMINTCLR_COMPAREC_M           0x00000004
#define AM_REG_CTIMER_STMINTCLR_COMPAREC(n)          (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_STMINTCLR_COMPAREC_COMPARED    0x00000004

// COUNTER is greater than or equal to COMPARE register B.
#define AM_REG_CTIMER_STMINTCLR_COMPAREB_S           1
#define AM_REG_CTIMER_STMINTCLR_COMPAREB_M           0x00000002
#define AM_REG_CTIMER_STMINTCLR_COMPAREB(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_STMINTCLR_COMPAREB_COMPARED    0x00000002

// COUNTER is greater than or equal to COMPARE register A.
#define AM_REG_CTIMER_STMINTCLR_COMPAREA_S           0
#define AM_REG_CTIMER_STMINTCLR_COMPAREA_M           0x00000001
#define AM_REG_CTIMER_STMINTCLR_COMPAREA(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_STMINTCLR_COMPAREA_COMPARED    0x00000001

//*****************************************************************************
//
// CTIMER_STMINTSET - STIMER Interrupt registers: Set
//
//*****************************************************************************
// CAPTURE register D has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSET_CAPTURED_S           12
#define AM_REG_CTIMER_STMINTSET_CAPTURED_M           0x00001000
#define AM_REG_CTIMER_STMINTSET_CAPTURED(n)          (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_STMINTSET_CAPTURED_CAPD_INT    0x00001000

// CAPTURE register C has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSET_CAPTUREC_S           11
#define AM_REG_CTIMER_STMINTSET_CAPTUREC_M           0x00000800
#define AM_REG_CTIMER_STMINTSET_CAPTUREC(n)          (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_STMINTSET_CAPTUREC_CAPC_INT    0x00000800

// CAPTURE register B has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSET_CAPTUREB_S           10
#define AM_REG_CTIMER_STMINTSET_CAPTUREB_M           0x00000400
#define AM_REG_CTIMER_STMINTSET_CAPTUREB(n)          (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_STMINTSET_CAPTUREB_CAPB_INT    0x00000400

// CAPTURE register A has grabbed the value in the counter
#define AM_REG_CTIMER_STMINTSET_CAPTUREA_S           9
#define AM_REG_CTIMER_STMINTSET_CAPTUREA_M           0x00000200
#define AM_REG_CTIMER_STMINTSET_CAPTUREA(n)          (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_STMINTSET_CAPTUREA_CAPA_INT    0x00000200

// COUNTER over flowed from 0xFFFFFFFF back to 0x00000000.
#define AM_REG_CTIMER_STMINTSET_OVERFLOW_S           8
#define AM_REG_CTIMER_STMINTSET_OVERFLOW_M           0x00000100
#define AM_REG_CTIMER_STMINTSET_OVERFLOW(n)          (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_STMINTSET_OVERFLOW_OFLOW_INT   0x00000100

// COUNTER is greater than or equal to COMPARE register H.
#define AM_REG_CTIMER_STMINTSET_COMPAREH_S           7
#define AM_REG_CTIMER_STMINTSET_COMPAREH_M           0x00000080
#define AM_REG_CTIMER_STMINTSET_COMPAREH(n)          (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_STMINTSET_COMPAREH_COMPARED    0x00000080

// COUNTER is greater than or equal to COMPARE register G.
#define AM_REG_CTIMER_STMINTSET_COMPAREG_S           6
#define AM_REG_CTIMER_STMINTSET_COMPAREG_M           0x00000040
#define AM_REG_CTIMER_STMINTSET_COMPAREG(n)          (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_STMINTSET_COMPAREG_COMPARED    0x00000040

// COUNTER is greater than or equal to COMPARE register F.
#define AM_REG_CTIMER_STMINTSET_COMPAREF_S           5
#define AM_REG_CTIMER_STMINTSET_COMPAREF_M           0x00000020
#define AM_REG_CTIMER_STMINTSET_COMPAREF(n)          (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_STMINTSET_COMPAREF_COMPARED    0x00000020

// COUNTER is greater than or equal to COMPARE register E.
#define AM_REG_CTIMER_STMINTSET_COMPAREE_S           4
#define AM_REG_CTIMER_STMINTSET_COMPAREE_M           0x00000010
#define AM_REG_CTIMER_STMINTSET_COMPAREE(n)          (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_STMINTSET_COMPAREE_COMPARED    0x00000010

// COUNTER is greater than or equal to COMPARE register D.
#define AM_REG_CTIMER_STMINTSET_COMPARED_S           3
#define AM_REG_CTIMER_STMINTSET_COMPARED_M           0x00000008
#define AM_REG_CTIMER_STMINTSET_COMPARED(n)          (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_STMINTSET_COMPARED_COMPARED    0x00000008

// COUNTER is greater than or equal to COMPARE register C.
#define AM_REG_CTIMER_STMINTSET_COMPAREC_S           2
#define AM_REG_CTIMER_STMINTSET_COMPAREC_M           0x00000004
#define AM_REG_CTIMER_STMINTSET_COMPAREC(n)          (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_STMINTSET_COMPAREC_COMPARED    0x00000004

// COUNTER is greater than or equal to COMPARE register B.
#define AM_REG_CTIMER_STMINTSET_COMPAREB_S           1
#define AM_REG_CTIMER_STMINTSET_COMPAREB_M           0x00000002
#define AM_REG_CTIMER_STMINTSET_COMPAREB(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_STMINTSET_COMPAREB_COMPARED    0x00000002

// COUNTER is greater than or equal to COMPARE register A.
#define AM_REG_CTIMER_STMINTSET_COMPAREA_S           0
#define AM_REG_CTIMER_STMINTSET_COMPAREA_M           0x00000001
#define AM_REG_CTIMER_STMINTSET_COMPAREA(n)          (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_STMINTSET_COMPAREA_COMPARED    0x00000001

//*****************************************************************************
//
// CTIMER_TMR0 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B0.
#define AM_REG_CTIMER_TMR0_CTTMRB0_S                 16
#define AM_REG_CTIMER_TMR0_CTTMRB0_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR0_CTTMRB0(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A0.
#define AM_REG_CTIMER_TMR0_CTTMRA0_S                 0
#define AM_REG_CTIMER_TMR0_CTTMRA0_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR0_CTTMRA0(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA0 - Counter/Timer A0 Compare Registers
//
//*****************************************************************************
// Counter/Timer A0 Compare Register 1. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRA0_CMPR1A0_S               16
#define AM_REG_CTIMER_CMPRA0_CMPR1A0_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA0_CMPR1A0(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A0 Compare Register 0. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRA0_CMPR0A0_S               0
#define AM_REG_CTIMER_CMPRA0_CMPR0A0_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA0_CMPR0A0(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB0 - Counter/Timer B0 Compare Registers
//
//*****************************************************************************
// Counter/Timer B0 Compare Register 1. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRB0_CMPR1B0_S               16
#define AM_REG_CTIMER_CMPRB0_CMPR1B0_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB0_CMPR1B0(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B0 Compare Register 0. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRB0_CMPR0B0_S               0
#define AM_REG_CTIMER_CMPRB0_CMPR0B0_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB0_CMPR0B0(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL0 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A0/B0 Link bit.
#define AM_REG_CTIMER_CTRL0_CTLINK0_S                31
#define AM_REG_CTIMER_CTRL0_CTLINK0_M                0x80000000
#define AM_REG_CTIMER_CTRL0_CTLINK0(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL0_CTLINK0_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL0_CTLINK0_32BIT_TIMER      0x80000000

// Counter/Timer B0 output polarity.
#define AM_REG_CTIMER_CTRL0_TMRB0POL_S               28
#define AM_REG_CTIMER_CTRL0_TMRB0POL_M               0x10000000
#define AM_REG_CTIMER_CTRL0_TMRB0POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL0_TMRB0POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0POL_INVERTED        0x10000000

// Counter/Timer B0 Clear bit.
#define AM_REG_CTIMER_CTRL0_TMRB0CLR_S               27
#define AM_REG_CTIMER_CTRL0_TMRB0CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL0_TMRB0CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL0_TMRB0CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0CLR_CLEAR           0x08000000

// Counter/Timer B0 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL0_TMRB0IE1_S               26
#define AM_REG_CTIMER_CTRL0_TMRB0IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL0_TMRB0IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL0_TMRB0IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0IE1_EN              0x04000000

// Counter/Timer B0 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL0_TMRB0IE0_S               25
#define AM_REG_CTIMER_CTRL0_TMRB0IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL0_TMRB0IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL0_TMRB0IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0IE0_EN              0x02000000

// Counter/Timer B0 Function Select.
#define AM_REG_CTIMER_CTRL0_TMRB0FN_S                22
#define AM_REG_CTIMER_CTRL0_TMRB0FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL0_TMRB0FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL0_TMRB0FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL0_TMRB0FN_ALTPWN           0x01C00000

// Counter/Timer B0 Clock Select.
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_S               17
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRA0          0x00280000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB1          0x002A0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRA1          0x002C0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRA2          0x002E0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB2          0x00300000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB3          0x00320000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB4          0x00340000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB5          0x00360000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_CTMRB6          0x00380000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL0_TMRB0CLK_BUCKA           0x003E0000

// Counter/Timer B0 Enable bit.
#define AM_REG_CTIMER_CTRL0_TMRB0EN_S                16
#define AM_REG_CTIMER_CTRL0_TMRB0EN_M                0x00010000
#define AM_REG_CTIMER_CTRL0_TMRB0EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL0_TMRB0EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL0_TMRB0EN_EN               0x00010000

// Counter/Timer A0 output polarity.
#define AM_REG_CTIMER_CTRL0_TMRA0POL_S               12
#define AM_REG_CTIMER_CTRL0_TMRA0POL_M               0x00001000
#define AM_REG_CTIMER_CTRL0_TMRA0POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL0_TMRA0POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0POL_INVERTED        0x00001000

// Counter/Timer A0 Clear bit.
#define AM_REG_CTIMER_CTRL0_TMRA0CLR_S               11
#define AM_REG_CTIMER_CTRL0_TMRA0CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL0_TMRA0CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL0_TMRA0CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0CLR_CLEAR           0x00000800

// Counter/Timer A0 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL0_TMRA0IE1_S               10
#define AM_REG_CTIMER_CTRL0_TMRA0IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL0_TMRA0IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL0_TMRA0IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0IE1_EN              0x00000400

// Counter/Timer A0 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL0_TMRA0IE0_S               9
#define AM_REG_CTIMER_CTRL0_TMRA0IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL0_TMRA0IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL0_TMRA0IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0IE0_EN              0x00000200

// Counter/Timer A0 Function Select.
#define AM_REG_CTIMER_CTRL0_TMRA0FN_S                6
#define AM_REG_CTIMER_CTRL0_TMRA0FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL0_TMRA0FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL0_TMRA0FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL0_TMRA0FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL0_TMRA0FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL0_TMRA0FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL0_TMRA0FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL0_TMRA0FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL0_TMRA0FN_ALTPWN           0x000001C0

// Counter/Timer A0 Clock Select.
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_S               1
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL0_TMRA0CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_HCLK_DIV4       0x0000001E
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB0          0x00000028
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRA1          0x0000002A
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB1          0x0000002C
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRA2          0x0000002E
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB2          0x00000030
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB3          0x00000032
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB4          0x00000034
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB5          0x00000036
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_CTMRB6          0x00000038
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL0_TMRA0CLK_BUCKA           0x0000003E

// Counter/Timer A0 Enable bit.
#define AM_REG_CTIMER_CTRL0_TMRA0EN_S                0
#define AM_REG_CTIMER_CTRL0_TMRA0EN_M                0x00000001
#define AM_REG_CTIMER_CTRL0_TMRA0EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL0_TMRA0EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL0_TMRA0EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA0 - Counter/Timer A0 Compare Registers
//
//*****************************************************************************
// Counter/Timer A0 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA0_CMPR3A0_S            16
#define AM_REG_CTIMER_CMPRAUXA0_CMPR3A0_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA0_CMPR3A0(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A0 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA0_CMPR2A0_S            0
#define AM_REG_CTIMER_CMPRAUXA0_CMPR2A0_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA0_CMPR2A0(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB0 - Counter/Timer B0 Compare Registers
//
//*****************************************************************************
// Counter/Timer B0 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB0_CMPR3B0_S            16
#define AM_REG_CTIMER_CMPRAUXB0_CMPR3B0_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB0_CMPR3B0(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B0 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB0_CMPR2B0_S            0
#define AM_REG_CTIMER_CMPRAUXB0_CMPR2B0_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB0_CMPR2B0(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX0 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B0 Upper compare enable.
#define AM_REG_CTIMER_AUX0_TMRB0EN23_S               30
#define AM_REG_CTIMER_AUX0_TMRB0EN23_M               0x40000000
#define AM_REG_CTIMER_AUX0_TMRB0EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX0_TMRB0EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX0_TMRB0EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX0_TMRB0POL23_S              29
#define AM_REG_CTIMER_AUX0_TMRB0POL23_M              0x20000000
#define AM_REG_CTIMER_AUX0_TMRB0POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX0_TMRB0POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX0_TMRB0POL23_INV            0x20000000

// Counter/Timer B0 Invert on trigger.
#define AM_REG_CTIMER_AUX0_TMRB0TINV_S               28
#define AM_REG_CTIMER_AUX0_TMRB0TINV_M               0x10000000
#define AM_REG_CTIMER_AUX0_TMRB0TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX0_TMRB0TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX0_TMRB0TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX0_TMRB0NOSYNC_S             27
#define AM_REG_CTIMER_AUX0_TMRB0NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX0_TMRB0NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX0_TMRB0NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX0_TMRB0NOSYNC_NOSYNC        0x08000000

// Counter/Timer B0 Trigger Select.
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_S               23
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A0OUT           0x00800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B2OUT           0x02000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B5OUT           0x02800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A4OUT           0x03000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B4OUT           0x03800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B7OUT2          0x05000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A2OUT2          0x05800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_B5OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX0_TMRB0TRIG_A5OUT2DUAL      0x07800000

// Counter/Timer B0 Pattern Limit Count.
#define AM_REG_CTIMER_AUX0_TMRB0LMT_S                16
#define AM_REG_CTIMER_AUX0_TMRB0LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX0_TMRB0LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A0 Upper compare enable.
#define AM_REG_CTIMER_AUX0_TMRA0EN23_S               14
#define AM_REG_CTIMER_AUX0_TMRA0EN23_M               0x00004000
#define AM_REG_CTIMER_AUX0_TMRA0EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX0_TMRA0EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX0_TMRA0EN23_EN              0x00000000

// Counter/Timer A0 Upper output polarity
#define AM_REG_CTIMER_AUX0_TMRA0POL23_S              13
#define AM_REG_CTIMER_AUX0_TMRA0POL23_M              0x00002000
#define AM_REG_CTIMER_AUX0_TMRA0POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX0_TMRA0POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX0_TMRA0POL23_INV            0x00002000

// Counter/Timer A0 Invert on trigger.
#define AM_REG_CTIMER_AUX0_TMRA0TINV_S               12
#define AM_REG_CTIMER_AUX0_TMRA0TINV_M               0x00001000
#define AM_REG_CTIMER_AUX0_TMRA0TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX0_TMRA0TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX0_TMRA0TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX0_TMRA0NOSYNC_S             11
#define AM_REG_CTIMER_AUX0_TMRA0NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX0_TMRA0NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX0_TMRA0NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX0_TMRA0NOSYNC_NOSYNC        0x00000800

// Counter/Timer A0 Trigger Select.
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_S               7
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX0_TMRA0TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B0OUT           0x00000080
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A1OUT           0x00000200
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B1OUT           0x00000280
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A5OUT           0x00000300
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B5OUT           0x00000380
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B6OUT2          0x00000500
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A2OUT2          0x00000580
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_B4OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX0_TMRA0TRIG_A4OUT2DUAL      0x00000780

// Counter/Timer A0 Pattern Limit Count.
#define AM_REG_CTIMER_AUX0_TMRA0LMT_S                0
#define AM_REG_CTIMER_AUX0_TMRA0LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX0_TMRA0LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR1 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B1.
#define AM_REG_CTIMER_TMR1_CTTMRB1_S                 16
#define AM_REG_CTIMER_TMR1_CTTMRB1_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR1_CTTMRB1(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A1.
#define AM_REG_CTIMER_TMR1_CTTMRA1_S                 0
#define AM_REG_CTIMER_TMR1_CTTMRA1_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR1_CTTMRA1(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA1 - Counter/Timer A1 Compare Registers
//
//*****************************************************************************
// Counter/Timer A1 Compare Register 1.
#define AM_REG_CTIMER_CMPRA1_CMPR1A1_S               16
#define AM_REG_CTIMER_CMPRA1_CMPR1A1_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA1_CMPR1A1(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A1 Compare Register 0.
#define AM_REG_CTIMER_CMPRA1_CMPR0A1_S               0
#define AM_REG_CTIMER_CMPRA1_CMPR0A1_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA1_CMPR0A1(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB1 - Counter/Timer B1 Compare Registers
//
//*****************************************************************************
// Counter/Timer B1 Compare Register 1.
#define AM_REG_CTIMER_CMPRB1_CMPR1B1_S               16
#define AM_REG_CTIMER_CMPRB1_CMPR1B1_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB1_CMPR1B1(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B1 Compare Register 0.
#define AM_REG_CTIMER_CMPRB1_CMPR0B1_S               0
#define AM_REG_CTIMER_CMPRB1_CMPR0B1_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB1_CMPR0B1(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL1 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A1/B1 Link bit.
#define AM_REG_CTIMER_CTRL1_CTLINK1_S                31
#define AM_REG_CTIMER_CTRL1_CTLINK1_M                0x80000000
#define AM_REG_CTIMER_CTRL1_CTLINK1(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL1_CTLINK1_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL1_CTLINK1_32BIT_TIMER      0x80000000

// Counter/Timer B1 output polarity.
#define AM_REG_CTIMER_CTRL1_TMRB1POL_S               28
#define AM_REG_CTIMER_CTRL1_TMRB1POL_M               0x10000000
#define AM_REG_CTIMER_CTRL1_TMRB1POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL1_TMRB1POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1POL_INVERTED        0x10000000

// Counter/Timer B1 Clear bit.
#define AM_REG_CTIMER_CTRL1_TMRB1CLR_S               27
#define AM_REG_CTIMER_CTRL1_TMRB1CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL1_TMRB1CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL1_TMRB1CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1CLR_CLEAR           0x08000000

// Counter/Timer B1 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL1_TMRB1IE1_S               26
#define AM_REG_CTIMER_CTRL1_TMRB1IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL1_TMRB1IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL1_TMRB1IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1IE1_EN              0x04000000

// Counter/Timer B1 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL1_TMRB1IE0_S               25
#define AM_REG_CTIMER_CTRL1_TMRB1IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL1_TMRB1IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL1_TMRB1IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1IE0_EN              0x02000000

// Counter/Timer B1 Function Select.
#define AM_REG_CTIMER_CTRL1_TMRB1FN_S                22
#define AM_REG_CTIMER_CTRL1_TMRB1FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL1_TMRB1FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL1_TMRB1FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL1_TMRB1FN_ALTPWN           0x01C00000

// Counter/Timer B1 Clock Select.
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_S               17
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRA1          0x00280000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRA0          0x002A0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB0          0x002C0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRA2          0x002E0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB2          0x00300000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB3          0x00320000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB4          0x00340000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB5          0x00360000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_CTMRB6          0x00380000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL1_TMRB1CLK_BUCKA           0x003E0000

// Counter/Timer B1 Enable bit.
#define AM_REG_CTIMER_CTRL1_TMRB1EN_S                16
#define AM_REG_CTIMER_CTRL1_TMRB1EN_M                0x00010000
#define AM_REG_CTIMER_CTRL1_TMRB1EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL1_TMRB1EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL1_TMRB1EN_EN               0x00010000

// Counter/Timer A1 output polarity.
#define AM_REG_CTIMER_CTRL1_TMRA1POL_S               12
#define AM_REG_CTIMER_CTRL1_TMRA1POL_M               0x00001000
#define AM_REG_CTIMER_CTRL1_TMRA1POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL1_TMRA1POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1POL_INVERTED        0x00001000

// Counter/Timer A1 Clear bit.
#define AM_REG_CTIMER_CTRL1_TMRA1CLR_S               11
#define AM_REG_CTIMER_CTRL1_TMRA1CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL1_TMRA1CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL1_TMRA1CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1CLR_CLEAR           0x00000800

// Counter/Timer A1 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL1_TMRA1IE1_S               10
#define AM_REG_CTIMER_CTRL1_TMRA1IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL1_TMRA1IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL1_TMRA1IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1IE1_EN              0x00000400

// Counter/Timer A1 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL1_TMRA1IE0_S               9
#define AM_REG_CTIMER_CTRL1_TMRA1IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL1_TMRA1IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL1_TMRA1IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1IE0_EN              0x00000200

// Counter/Timer A1 Function Select.
#define AM_REG_CTIMER_CTRL1_TMRA1FN_S                6
#define AM_REG_CTIMER_CTRL1_TMRA1FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL1_TMRA1FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL1_TMRA1FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL1_TMRA1FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL1_TMRA1FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL1_TMRA1FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL1_TMRA1FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL1_TMRA1FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL1_TMRA1FN_ALTPWN           0x000001C0
#define AM_REG_CTIMER_CTRL1_TMRA1FN_TRIGCOPY         0x000001C0
#define AM_REG_CTIMER_CTRL1_TMRA1FN_DUALTRIGPATTERN  0x00000100

// Counter/Timer A1 Clock Select.
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_S               1
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL1_TMRA1CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB1          0x00000028
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRA0          0x0000002A
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB0          0x0000002C
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRA2          0x0000002E
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB2          0x00000030
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB3          0x00000032
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB4          0x00000034
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB5          0x00000036
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_CTMRB6          0x00000038
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL1_TMRA1CLK_BUCKA           0x0000003E

// Counter/Timer A1 Enable bit.
#define AM_REG_CTIMER_CTRL1_TMRA1EN_S                0
#define AM_REG_CTIMER_CTRL1_TMRA1EN_M                0x00000001
#define AM_REG_CTIMER_CTRL1_TMRA1EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL1_TMRA1EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL1_TMRA1EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA1 - Counter/Timer A1 Compare Registers
//
//*****************************************************************************
// Counter/Timer A1 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA1_CMPR3A1_S            16
#define AM_REG_CTIMER_CMPRAUXA1_CMPR3A1_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA1_CMPR3A1(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A1 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA1_CMPR2A1_S            0
#define AM_REG_CTIMER_CMPRAUXA1_CMPR2A1_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA1_CMPR2A1(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB1 - Counter/Timer B1 Compare Registers
//
//*****************************************************************************
// Counter/Timer B1 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB1_CMPR3B1_S            16
#define AM_REG_CTIMER_CMPRAUXB1_CMPR3B1_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB1_CMPR3B1(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B1 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB1_CMPR2B1_S            0
#define AM_REG_CTIMER_CMPRAUXB1_CMPR2B1_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB1_CMPR2B1(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX1 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B1 Upper compare enable.
#define AM_REG_CTIMER_AUX1_TMRB1EN23_S               30
#define AM_REG_CTIMER_AUX1_TMRB1EN23_M               0x40000000
#define AM_REG_CTIMER_AUX1_TMRB1EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX1_TMRB1EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX1_TMRB1EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX1_TMRB1POL23_S              29
#define AM_REG_CTIMER_AUX1_TMRB1POL23_M              0x20000000
#define AM_REG_CTIMER_AUX1_TMRB1POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX1_TMRB1POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX1_TMRB1POL23_INV            0x20000000

// Counter/Timer B1 Invert on trigger.
#define AM_REG_CTIMER_AUX1_TMRB1TINV_S               28
#define AM_REG_CTIMER_AUX1_TMRB1TINV_M               0x10000000
#define AM_REG_CTIMER_AUX1_TMRB1TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX1_TMRB1TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX1_TMRB1TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX1_TMRB1NOSYNC_S             27
#define AM_REG_CTIMER_AUX1_TMRB1NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX1_TMRB1NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX1_TMRB1NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX1_TMRB1NOSYNC_NOSYNC        0x08000000

// Counter/Timer B1 Trigger Select.
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_S               23
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A1OUT           0x00800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A6OUT           0x02000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B6OUT           0x02800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A0OUT           0x03000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B0OUT           0x03800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A4OUT2          0x05000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B4OUT2          0x05800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_B5OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX1_TMRB1TRIG_A5OUT2DUAL      0x07800000

// Counter/Timer B1 Pattern Limit Count.
#define AM_REG_CTIMER_AUX1_TMRB1LMT_S                16
#define AM_REG_CTIMER_AUX1_TMRB1LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX1_TMRB1LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A1 Upper compare enable.
#define AM_REG_CTIMER_AUX1_TMRA1EN23_S               14
#define AM_REG_CTIMER_AUX1_TMRA1EN23_M               0x00004000
#define AM_REG_CTIMER_AUX1_TMRA1EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX1_TMRA1EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX1_TMRA1EN23_EN              0x00000000

// Counter/Timer A1 Upper output polarity
#define AM_REG_CTIMER_AUX1_TMRA1POL23_S              13
#define AM_REG_CTIMER_AUX1_TMRA1POL23_M              0x00002000
#define AM_REG_CTIMER_AUX1_TMRA1POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX1_TMRA1POL23_NORMAL         0x00000000
#define AM_REG_CTIMER_AUX1_TMRA1POL23_INV            0x00002000

// Counter/Timer A1 Invert on trigger.
#define AM_REG_CTIMER_AUX1_TMRA1TINV_S               12
#define AM_REG_CTIMER_AUX1_TMRA1TINV_M               0x00001000
#define AM_REG_CTIMER_AUX1_TMRA1TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX1_TMRA1TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX1_TMRA1TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX1_TMRA1NOSYNC_S             11
#define AM_REG_CTIMER_AUX1_TMRA1NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX1_TMRA1NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX1_TMRA1NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX1_TMRA1NOSYNC_NOSYNC        0x00000800

// Counter/Timer A1 Trigger Select.
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_S               7
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX1_TMRA1TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B1OUT           0x00000080
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A0OUT           0x00000200
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B0OUT           0x00000280
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A5OUT           0x00000300
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B5OUT           0x00000380
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A4OUT2          0x00000500
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B4OUT2          0x00000580
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_B5OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX1_TMRA1TRIG_A5OUT2DUAL      0x00000780

// Counter/Timer A1 Pattern Limit Count.
#define AM_REG_CTIMER_AUX1_TMRA1LMT_S                0
#define AM_REG_CTIMER_AUX1_TMRA1LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX1_TMRA1LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR2 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B2.
#define AM_REG_CTIMER_TMR2_CTTMRB2_S                 16
#define AM_REG_CTIMER_TMR2_CTTMRB2_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR2_CTTMRB2(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A2.
#define AM_REG_CTIMER_TMR2_CTTMRA2_S                 0
#define AM_REG_CTIMER_TMR2_CTTMRA2_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR2_CTTMRA2(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA2 - Counter/Timer A2 Compare Registers
//
//*****************************************************************************
// Counter/Timer A2 Compare Register 1.
#define AM_REG_CTIMER_CMPRA2_CMPR1A2_S               16
#define AM_REG_CTIMER_CMPRA2_CMPR1A2_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA2_CMPR1A2(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A2 Compare Register 0.
#define AM_REG_CTIMER_CMPRA2_CMPR0A2_S               0
#define AM_REG_CTIMER_CMPRA2_CMPR0A2_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA2_CMPR0A2(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB2 - Counter/Timer B2 Compare Registers
//
//*****************************************************************************
// Counter/Timer B2 Compare Register 1.
#define AM_REG_CTIMER_CMPRB2_CMPR1B2_S               16
#define AM_REG_CTIMER_CMPRB2_CMPR1B2_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB2_CMPR1B2(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B2 Compare Register 0.
#define AM_REG_CTIMER_CMPRB2_CMPR0B2_S               0
#define AM_REG_CTIMER_CMPRB2_CMPR0B2_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB2_CMPR0B2(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL2 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A2/B2 Link bit.
#define AM_REG_CTIMER_CTRL2_CTLINK2_S                31
#define AM_REG_CTIMER_CTRL2_CTLINK2_M                0x80000000
#define AM_REG_CTIMER_CTRL2_CTLINK2(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL2_CTLINK2_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL2_CTLINK2_32BIT_TIMER      0x80000000

// Counter/Timer B2 output polarity.
#define AM_REG_CTIMER_CTRL2_TMRB2POL_S               28
#define AM_REG_CTIMER_CTRL2_TMRB2POL_M               0x10000000
#define AM_REG_CTIMER_CTRL2_TMRB2POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL2_TMRB2POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2POL_INVERTED        0x10000000

// Counter/Timer B2 Clear bit.
#define AM_REG_CTIMER_CTRL2_TMRB2CLR_S               27
#define AM_REG_CTIMER_CTRL2_TMRB2CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL2_TMRB2CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL2_TMRB2CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2CLR_CLEAR           0x08000000

// Counter/Timer B2 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL2_TMRB2IE1_S               26
#define AM_REG_CTIMER_CTRL2_TMRB2IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL2_TMRB2IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL2_TMRB2IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2IE1_EN              0x04000000

// Counter/Timer B2 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL2_TMRB2IE0_S               25
#define AM_REG_CTIMER_CTRL2_TMRB2IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL2_TMRB2IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL2_TMRB2IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2IE0_EN              0x02000000

// Counter/Timer B2 Function Select.
#define AM_REG_CTIMER_CTRL2_TMRB2FN_S                22
#define AM_REG_CTIMER_CTRL2_TMRB2FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL2_TMRB2FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL2_TMRB2FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL2_TMRB2FN_ALTPWN           0x01C00000

// Counter/Timer B2 Clock Select.
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_S               17
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRA2          0x00280000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB3          0x002A0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRA3          0x002C0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRA4          0x002E0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB4          0x00300000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB0          0x00320000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB1          0x00340000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB5          0x00360000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_CTMRB6          0x00380000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL2_TMRB2CLK_BUCKA           0x003E0000

// Counter/Timer B2 Enable bit.
#define AM_REG_CTIMER_CTRL2_TMRB2EN_S                16
#define AM_REG_CTIMER_CTRL2_TMRB2EN_M                0x00010000
#define AM_REG_CTIMER_CTRL2_TMRB2EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL2_TMRB2EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL2_TMRB2EN_EN               0x00010000

// Counter/Timer A2 output polarity.
#define AM_REG_CTIMER_CTRL2_TMRA2POL_S               12
#define AM_REG_CTIMER_CTRL2_TMRA2POL_M               0x00001000
#define AM_REG_CTIMER_CTRL2_TMRA2POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL2_TMRA2POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2POL_INVERTED        0x00001000

// Counter/Timer A2 Clear bit.
#define AM_REG_CTIMER_CTRL2_TMRA2CLR_S               11
#define AM_REG_CTIMER_CTRL2_TMRA2CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL2_TMRA2CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL2_TMRA2CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2CLR_CLEAR           0x00000800

// Counter/Timer A2 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL2_TMRA2IE1_S               10
#define AM_REG_CTIMER_CTRL2_TMRA2IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL2_TMRA2IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL2_TMRA2IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2IE1_EN              0x00000400

// Counter/Timer A2 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL2_TMRA2IE0_S               9
#define AM_REG_CTIMER_CTRL2_TMRA2IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL2_TMRA2IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL2_TMRA2IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2IE0_EN              0x00000200

// Counter/Timer A2 Function Select.
#define AM_REG_CTIMER_CTRL2_TMRA2FN_S                6
#define AM_REG_CTIMER_CTRL2_TMRA2FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL2_TMRA2FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL2_TMRA2FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL2_TMRA2FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL2_TMRA2FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL2_TMRA2FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL2_TMRA2FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL2_TMRA2FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL2_TMRA2FN_ALTPWN           0x000001C0

// Counter/Timer A2 Clock Select.
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_S               1
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL2_TMRA2CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB2          0x00000028
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB3          0x0000002A
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRA3          0x0000002C
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRA4          0x0000002E
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB4          0x00000030
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB0          0x00000032
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB1          0x00000034
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB5          0x00000036
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_CTMRB6          0x00000038
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL2_TMRA2CLK_BUCKA           0x0000003E

// Counter/Timer A2 Enable bit.
#define AM_REG_CTIMER_CTRL2_TMRA2EN_S                0
#define AM_REG_CTIMER_CTRL2_TMRA2EN_M                0x00000001
#define AM_REG_CTIMER_CTRL2_TMRA2EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL2_TMRA2EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL2_TMRA2EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA2 - Counter/Timer A2 Compare Registers
//
//*****************************************************************************
// Counter/Timer A2 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA2_CMPR3A2_S            16
#define AM_REG_CTIMER_CMPRAUXA2_CMPR3A2_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA2_CMPR3A2(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A2 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA2_CMPR2A2_S            0
#define AM_REG_CTIMER_CMPRAUXA2_CMPR2A2_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA2_CMPR2A2(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB2 - Counter/Timer B2 Compare Registers
//
//*****************************************************************************
// Counter/Timer B2 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB2_CMPR3B2_S            16
#define AM_REG_CTIMER_CMPRAUXB2_CMPR3B2_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB2_CMPR3B2(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B2 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB2_CMPR2B2_S            0
#define AM_REG_CTIMER_CMPRAUXB2_CMPR2B2_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB2_CMPR2B2(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX2 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B2 Upper compare enable.
#define AM_REG_CTIMER_AUX2_TMRB2EN23_S               30
#define AM_REG_CTIMER_AUX2_TMRB2EN23_M               0x40000000
#define AM_REG_CTIMER_AUX2_TMRB2EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX2_TMRB2EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX2_TMRB2EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX2_TMRB2POL23_S              29
#define AM_REG_CTIMER_AUX2_TMRB2POL23_M              0x20000000
#define AM_REG_CTIMER_AUX2_TMRB2POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX2_TMRB2POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX2_TMRB2POL23_INV            0x20000000

// Counter/Timer B2 Invert on trigger.
#define AM_REG_CTIMER_AUX2_TMRB2TINV_S               28
#define AM_REG_CTIMER_AUX2_TMRB2TINV_M               0x10000000
#define AM_REG_CTIMER_AUX2_TMRB2TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX2_TMRB2TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX2_TMRB2TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX2_TMRB2NOSYNC_S             27
#define AM_REG_CTIMER_AUX2_TMRB2NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX2_TMRB2NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX2_TMRB2NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX2_TMRB2NOSYNC_NOSYNC        0x08000000

// Counter/Timer B2 Trigger Select.
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_S               23
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A2OUT           0x00800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A1OUT           0x02000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B1OUT           0x02800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A4OUT           0x03000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B4OUT           0x03800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A5OUT2          0x05000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B5OUT2          0x05800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_B4OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX2_TMRB2TRIG_A4OUT2DUAL      0x07800000

// Counter/Timer B2 Pattern Limit Count.
#define AM_REG_CTIMER_AUX2_TMRB2LMT_S                16
#define AM_REG_CTIMER_AUX2_TMRB2LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX2_TMRB2LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A2 Upper compare enable.
#define AM_REG_CTIMER_AUX2_TMRA2EN23_S               14
#define AM_REG_CTIMER_AUX2_TMRA2EN23_M               0x00004000
#define AM_REG_CTIMER_AUX2_TMRA2EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX2_TMRA2EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX2_TMRA2EN23_EN              0x00000000

// Counter/Timer A2 Upper output polarity
#define AM_REG_CTIMER_AUX2_TMRA2POL23_S              13
#define AM_REG_CTIMER_AUX2_TMRA2POL23_M              0x00002000
#define AM_REG_CTIMER_AUX2_TMRA2POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX2_TMRA2POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX2_TMRA2POL23_INV            0x00002000

// Counter/Timer A2 Invert on trigger.
#define AM_REG_CTIMER_AUX2_TMRA2TINV_S               12
#define AM_REG_CTIMER_AUX2_TMRA2TINV_M               0x00001000
#define AM_REG_CTIMER_AUX2_TMRA2TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX2_TMRA2TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX2_TMRA2TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX2_TMRA2NOSYNC_S             11
#define AM_REG_CTIMER_AUX2_TMRA2NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX2_TMRA2NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX2_TMRA2NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX2_TMRA2NOSYNC_NOSYNC        0x00000800

// Counter/Timer A2 Trigger Select.
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_S               7
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX2_TMRA2TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B2OUT           0x00000080
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A0OUT           0x00000200
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B0OUT           0x00000280
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A4OUT           0x00000300
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B4OUT           0x00000380
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A5OUT2          0x00000500
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B5OUT2          0x00000580
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_B4OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX2_TMRA2TRIG_A4OUT2DUAL      0x00000780

// Counter/Timer A2 Pattern Limit Count.
#define AM_REG_CTIMER_AUX2_TMRA2LMT_S                0
#define AM_REG_CTIMER_AUX2_TMRA2LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX2_TMRA2LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR3 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B3.
#define AM_REG_CTIMER_TMR3_CTTMRB3_S                 16
#define AM_REG_CTIMER_TMR3_CTTMRB3_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR3_CTTMRB3(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A3.
#define AM_REG_CTIMER_TMR3_CTTMRA3_S                 0
#define AM_REG_CTIMER_TMR3_CTTMRA3_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR3_CTTMRA3(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA3 - Counter/Timer A3 Compare Registers
//
//*****************************************************************************
// Counter/Timer A3 Compare Register 1.
#define AM_REG_CTIMER_CMPRA3_CMPR1A3_S               16
#define AM_REG_CTIMER_CMPRA3_CMPR1A3_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA3_CMPR1A3(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A3 Compare Register 0.
#define AM_REG_CTIMER_CMPRA3_CMPR0A3_S               0
#define AM_REG_CTIMER_CMPRA3_CMPR0A3_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA3_CMPR0A3(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB3 - Counter/Timer B3 Compare Registers
//
//*****************************************************************************
// Counter/Timer B3 Compare Register 1.
#define AM_REG_CTIMER_CMPRB3_CMPR1B3_S               16
#define AM_REG_CTIMER_CMPRB3_CMPR1B3_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB3_CMPR1B3(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B3 Compare Register 0.
#define AM_REG_CTIMER_CMPRB3_CMPR0B3_S               0
#define AM_REG_CTIMER_CMPRB3_CMPR0B3_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB3_CMPR0B3(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL3 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A3/B3 Link bit.
#define AM_REG_CTIMER_CTRL3_CTLINK3_S                31
#define AM_REG_CTIMER_CTRL3_CTLINK3_M                0x80000000
#define AM_REG_CTIMER_CTRL3_CTLINK3(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL3_CTLINK3_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL3_CTLINK3_32BIT_TIMER      0x80000000

// Counter/Timer B3 output polarity.
#define AM_REG_CTIMER_CTRL3_TMRB3POL_S               28
#define AM_REG_CTIMER_CTRL3_TMRB3POL_M               0x10000000
#define AM_REG_CTIMER_CTRL3_TMRB3POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL3_TMRB3POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3POL_INVERTED        0x10000000

// Counter/Timer B3 Clear bit.
#define AM_REG_CTIMER_CTRL3_TMRB3CLR_S               27
#define AM_REG_CTIMER_CTRL3_TMRB3CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL3_TMRB3CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL3_TMRB3CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3CLR_CLEAR           0x08000000

// Counter/Timer B3 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL3_TMRB3IE1_S               26
#define AM_REG_CTIMER_CTRL3_TMRB3IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL3_TMRB3IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL3_TMRB3IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3IE1_EN              0x04000000

// Counter/Timer B3 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL3_TMRB3IE0_S               25
#define AM_REG_CTIMER_CTRL3_TMRB3IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL3_TMRB3IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL3_TMRB3IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3IE0_EN              0x02000000

// Counter/Timer B3 Function Select.
#define AM_REG_CTIMER_CTRL3_TMRB3FN_S                22
#define AM_REG_CTIMER_CTRL3_TMRB3FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL3_TMRB3FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL3_TMRB3FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL3_TMRB3FN_ALTPWN           0x01C00000

// Counter/Timer B3 Clock Select.
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_S               17
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRA3          0x00280000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRA2          0x002A0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB2          0x002C0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRA4          0x002E0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB4          0x00300000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB0          0x00320000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB1          0x00340000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB5          0x00360000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_CTMRB6          0x00380000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL3_TMRB3CLK_BUCKA           0x003E0000

// Counter/Timer B3 Enable bit.
#define AM_REG_CTIMER_CTRL3_TMRB3EN_S                16
#define AM_REG_CTIMER_CTRL3_TMRB3EN_M                0x00010000
#define AM_REG_CTIMER_CTRL3_TMRB3EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL3_TMRB3EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL3_TMRB3EN_EN               0x00010000

// Special Timer A3 enable for ADC function.
#define AM_REG_CTIMER_CTRL3_ADCEN_S                  15
#define AM_REG_CTIMER_CTRL3_ADCEN_M                  0x00008000
#define AM_REG_CTIMER_CTRL3_ADCEN(n)                 (((uint32_t)(n) << 15) & 0x00008000)

// Counter/Timer A3 output polarity.
#define AM_REG_CTIMER_CTRL3_TMRA3POL_S               12
#define AM_REG_CTIMER_CTRL3_TMRA3POL_M               0x00001000
#define AM_REG_CTIMER_CTRL3_TMRA3POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL3_TMRA3POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3POL_INVERTED        0x00001000

// Counter/Timer A3 Clear bit.
#define AM_REG_CTIMER_CTRL3_TMRA3CLR_S               11
#define AM_REG_CTIMER_CTRL3_TMRA3CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL3_TMRA3CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL3_TMRA3CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3CLR_CLEAR           0x00000800

// Counter/Timer A3 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL3_TMRA3IE1_S               10
#define AM_REG_CTIMER_CTRL3_TMRA3IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL3_TMRA3IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL3_TMRA3IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3IE1_EN              0x00000400

// Counter/Timer A3 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL3_TMRA3IE0_S               9
#define AM_REG_CTIMER_CTRL3_TMRA3IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL3_TMRA3IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL3_TMRA3IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3IE0_EN              0x00000200

// Counter/Timer A3 Function Select.
#define AM_REG_CTIMER_CTRL3_TMRA3FN_S                6
#define AM_REG_CTIMER_CTRL3_TMRA3FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL3_TMRA3FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL3_TMRA3FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL3_TMRA3FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL3_TMRA3FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL3_TMRA3FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL3_TMRA3FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL3_TMRA3FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL3_TMRA3FN_ALTPWN           0x000001C0

// Counter/Timer A3 Clock Select.
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_S               1
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL3_TMRA3CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB3          0x00000028
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRA2          0x0000002A
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB2          0x0000002C
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRA4          0x0000002E
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB4          0x00000030
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB0          0x00000032
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB1          0x00000034
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB5          0x00000036
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_CTMRB6          0x00000038
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL3_TMRA3CLK_BUCKA           0x0000003E

// Counter/Timer A3 Enable bit.
#define AM_REG_CTIMER_CTRL3_TMRA3EN_S                0
#define AM_REG_CTIMER_CTRL3_TMRA3EN_M                0x00000001
#define AM_REG_CTIMER_CTRL3_TMRA3EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL3_TMRA3EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL3_TMRA3EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA3 - Counter/Timer A3 Compare Registers
//
//*****************************************************************************
// Counter/Timer A3 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA3_CMPR3A3_S            16
#define AM_REG_CTIMER_CMPRAUXA3_CMPR3A3_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA3_CMPR3A3(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A3 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA3_CMPR2A3_S            0
#define AM_REG_CTIMER_CMPRAUXA3_CMPR2A3_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA3_CMPR2A3(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB3 - Counter/Timer B3 Compare Registers
//
//*****************************************************************************
// Counter/Timer B3 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB3_CMPR3B3_S            16
#define AM_REG_CTIMER_CMPRAUXB3_CMPR3B3_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB3_CMPR3B3(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B3 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB3_CMPR2B3_S            0
#define AM_REG_CTIMER_CMPRAUXB3_CMPR2B3_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB3_CMPR2B3(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX3 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B3 Upper compare enable.
#define AM_REG_CTIMER_AUX3_TMRB3EN23_S               30
#define AM_REG_CTIMER_AUX3_TMRB3EN23_M               0x40000000
#define AM_REG_CTIMER_AUX3_TMRB3EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX3_TMRB3EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX3_TMRB3EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX3_TMRB3POL23_S              29
#define AM_REG_CTIMER_AUX3_TMRB3POL23_M              0x20000000
#define AM_REG_CTIMER_AUX3_TMRB3POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX3_TMRB3POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX3_TMRB3POL23_INV            0x20000000

// Counter/Timer B3 Invert on trigger.
#define AM_REG_CTIMER_AUX3_TMRB3TINV_S               28
#define AM_REG_CTIMER_AUX3_TMRB3TINV_M               0x10000000
#define AM_REG_CTIMER_AUX3_TMRB3TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX3_TMRB3TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX3_TMRB3TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX3_TMRB3NOSYNC_S             27
#define AM_REG_CTIMER_AUX3_TMRB3NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX3_TMRB3NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX3_TMRB3NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX3_TMRB3NOSYNC_NOSYNC        0x08000000

// Counter/Timer B3 Trigger Select.
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_S               23
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A3OUT           0x00800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B2OUT           0x01000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A2OUT           0x01800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A4OUT           0x02000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B4OUT           0x02800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A6OUT           0x03000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B6OUT           0x03800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B5OUT2          0x04000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A5OUT2          0x04800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A1OUT2          0x05000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B1OUT2          0x05800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_B2OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX3_TMRB3TRIG_A2OUT2DUAL      0x07800000

// Counter/Timer B3 Pattern Limit Count.
#define AM_REG_CTIMER_AUX3_TMRB3LMT_S                16
#define AM_REG_CTIMER_AUX3_TMRB3LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX3_TMRB3LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A3 Upper compare enable.
#define AM_REG_CTIMER_AUX3_TMRA3EN23_S               14
#define AM_REG_CTIMER_AUX3_TMRA3EN23_M               0x00004000
#define AM_REG_CTIMER_AUX3_TMRA3EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX3_TMRA3EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX3_TMRA3EN23_EN              0x00000000

// Counter/Timer A3 Upper output polarity
#define AM_REG_CTIMER_AUX3_TMRA3POL23_S              13
#define AM_REG_CTIMER_AUX3_TMRA3POL23_M              0x00002000
#define AM_REG_CTIMER_AUX3_TMRA3POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX3_TMRA3POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX3_TMRA3POL23_INV            0x00002000

// Counter/Timer A3 Invert on trigger.
#define AM_REG_CTIMER_AUX3_TMRA3TINV_S               12
#define AM_REG_CTIMER_AUX3_TMRA3TINV_M               0x00001000
#define AM_REG_CTIMER_AUX3_TMRA3TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX3_TMRA3TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX3_TMRA3TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX3_TMRA3NOSYNC_S             11
#define AM_REG_CTIMER_AUX3_TMRA3NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX3_TMRA3NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX3_TMRA3NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX3_TMRA3NOSYNC_NOSYNC        0x00000800

// Counter/Timer A3 Trigger Select.
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_S               7
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX3_TMRA3TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B3OUT           0x00000080
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B2OUT           0x00000100
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A2OUT           0x00000180
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A4OUT           0x00000200
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B4OUT           0x00000280
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A7OUT           0x00000300
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B7OUT           0x00000380
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B5OUT2          0x00000400
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A5OUT2          0x00000480
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A1OUT2          0x00000500
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B1OUT2          0x00000580
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_B2OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX3_TMRA3TRIG_A2OUT2DUAL      0x00000780

// Counter/Timer A3 Pattern Limit Count.
#define AM_REG_CTIMER_AUX3_TMRA3LMT_S                0
#define AM_REG_CTIMER_AUX3_TMRA3LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX3_TMRA3LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR4 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B4.
#define AM_REG_CTIMER_TMR4_CTTMRB4_S                 16
#define AM_REG_CTIMER_TMR4_CTTMRB4_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR4_CTTMRB4(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A4.
#define AM_REG_CTIMER_TMR4_CTTMRA4_S                 0
#define AM_REG_CTIMER_TMR4_CTTMRA4_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR4_CTTMRA4(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA4 - Counter/Timer A4 Compare Registers
//
//*****************************************************************************
// Counter/Timer A4 Compare Register 1. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRA4_CMPR1A4_S               16
#define AM_REG_CTIMER_CMPRA4_CMPR1A4_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA4_CMPR1A4(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A4 Compare Register 0. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRA4_CMPR0A4_S               0
#define AM_REG_CTIMER_CMPRA4_CMPR0A4_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA4_CMPR0A4(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB4 - Counter/Timer B4 Compare Registers
//
//*****************************************************************************
// Counter/Timer B4 Compare Register 1. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRB4_CMPR1B4_S               16
#define AM_REG_CTIMER_CMPRB4_CMPR1B4_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB4_CMPR1B4(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B4 Compare Register 0. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRB4_CMPR0B4_S               0
#define AM_REG_CTIMER_CMPRB4_CMPR0B4_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB4_CMPR0B4(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL4 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A4/B4 Link bit.
#define AM_REG_CTIMER_CTRL4_CTLINK4_S                31
#define AM_REG_CTIMER_CTRL4_CTLINK4_M                0x80000000
#define AM_REG_CTIMER_CTRL4_CTLINK4(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL4_CTLINK4_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL4_CTLINK4_32BIT_TIMER      0x80000000

// Counter/Timer B4 output polarity.
#define AM_REG_CTIMER_CTRL4_TMRB4POL_S               28
#define AM_REG_CTIMER_CTRL4_TMRB4POL_M               0x10000000
#define AM_REG_CTIMER_CTRL4_TMRB4POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL4_TMRB4POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4POL_INVERTED        0x10000000

// Counter/Timer B4 Clear bit.
#define AM_REG_CTIMER_CTRL4_TMRB4CLR_S               27
#define AM_REG_CTIMER_CTRL4_TMRB4CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL4_TMRB4CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL4_TMRB4CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4CLR_CLEAR           0x08000000

// Counter/Timer B4 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL4_TMRB4IE1_S               26
#define AM_REG_CTIMER_CTRL4_TMRB4IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL4_TMRB4IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL4_TMRB4IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4IE1_EN              0x04000000

// Counter/Timer B4 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL4_TMRB4IE0_S               25
#define AM_REG_CTIMER_CTRL4_TMRB4IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL4_TMRB4IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL4_TMRB4IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4IE0_EN              0x02000000

// Counter/Timer B4 Function Select.
#define AM_REG_CTIMER_CTRL4_TMRB4FN_S                22
#define AM_REG_CTIMER_CTRL4_TMRB4FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL4_TMRB4FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL4_TMRB4FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL4_TMRB4FN_ALTPWN           0x01C00000

// Counter/Timer B4 Clock Select.
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_S               17
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRA4          0x00280000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRA1          0x002A0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB1          0x002C0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRA5          0x002E0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB5          0x00300000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB0          0x00320000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB2          0x00340000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB3          0x00360000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_CTMRB6          0x00380000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL4_TMRB4CLK_BUCKA           0x003E0000

// Counter/Timer B4 Enable bit.
#define AM_REG_CTIMER_CTRL4_TMRB4EN_S                16
#define AM_REG_CTIMER_CTRL4_TMRB4EN_M                0x00010000
#define AM_REG_CTIMER_CTRL4_TMRB4EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL4_TMRB4EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL4_TMRB4EN_EN               0x00010000

// Counter/Timer A4 output polarity.
#define AM_REG_CTIMER_CTRL4_TMRA4POL_S               12
#define AM_REG_CTIMER_CTRL4_TMRA4POL_M               0x00001000
#define AM_REG_CTIMER_CTRL4_TMRA4POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL4_TMRA4POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4POL_INVERTED        0x00001000

// Counter/Timer A4 Clear bit.
#define AM_REG_CTIMER_CTRL4_TMRA4CLR_S               11
#define AM_REG_CTIMER_CTRL4_TMRA4CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL4_TMRA4CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL4_TMRA4CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4CLR_CLEAR           0x00000800

// Counter/Timer A4 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL4_TMRA4IE1_S               10
#define AM_REG_CTIMER_CTRL4_TMRA4IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL4_TMRA4IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL4_TMRA4IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4IE1_EN              0x00000400

// Counter/Timer A4 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL4_TMRA4IE0_S               9
#define AM_REG_CTIMER_CTRL4_TMRA4IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL4_TMRA4IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL4_TMRA4IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4IE0_EN              0x00000200

// Counter/Timer A4 Function Select.
#define AM_REG_CTIMER_CTRL4_TMRA4FN_S                6
#define AM_REG_CTIMER_CTRL4_TMRA4FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL4_TMRA4FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL4_TMRA4FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL4_TMRA4FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL4_TMRA4FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL4_TMRA4FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL4_TMRA4FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL4_TMRA4FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL4_TMRA4FN_ALTPWN           0x000001C0

// Counter/Timer A4 Clock Select.
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_S               1
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL4_TMRA4CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_HCLK_DIV4       0x0000001E
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB4          0x00000028
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRA1          0x0000002A
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB1          0x0000002C
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRA5          0x0000002E
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB5          0x00000030
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB0          0x00000032
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB2          0x00000034
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB3          0x00000036
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_CTMRB6          0x00000038
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL4_TMRA4CLK_BUCKA           0x0000003E

// Counter/Timer A4 Enable bit.
#define AM_REG_CTIMER_CTRL4_TMRA4EN_S                0
#define AM_REG_CTIMER_CTRL4_TMRA4EN_M                0x00000001
#define AM_REG_CTIMER_CTRL4_TMRA4EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL4_TMRA4EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL4_TMRA4EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA4 - Counter/Timer A4 Compare Registers
//
//*****************************************************************************
// Counter/Timer A4 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA4_CMPR3A4_S            16
#define AM_REG_CTIMER_CMPRAUXA4_CMPR3A4_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA4_CMPR3A4(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A4 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA4_CMPR2A4_S            0
#define AM_REG_CTIMER_CMPRAUXA4_CMPR2A4_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA4_CMPR2A4(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB4 - Counter/Timer B4 Compare Registers
//
//*****************************************************************************
// Counter/Timer B4 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB4_CMPR3B4_S            16
#define AM_REG_CTIMER_CMPRAUXB4_CMPR3B4_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB4_CMPR3B4(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B4 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB4_CMPR2B4_S            0
#define AM_REG_CTIMER_CMPRAUXB4_CMPR2B4_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB4_CMPR2B4(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX4 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B4 Upper compare enable.
#define AM_REG_CTIMER_AUX4_TMRB4EN23_S               30
#define AM_REG_CTIMER_AUX4_TMRB4EN23_M               0x40000000
#define AM_REG_CTIMER_AUX4_TMRB4EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX4_TMRB4EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX4_TMRB4EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX4_TMRB4POL23_S              29
#define AM_REG_CTIMER_AUX4_TMRB4POL23_M              0x20000000
#define AM_REG_CTIMER_AUX4_TMRB4POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX4_TMRB4POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX4_TMRB4POL23_INV            0x20000000

// Counter/Timer B4 Invert on trigger.
#define AM_REG_CTIMER_AUX4_TMRB4TINV_S               28
#define AM_REG_CTIMER_AUX4_TMRB4TINV_M               0x10000000
#define AM_REG_CTIMER_AUX4_TMRB4TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX4_TMRB4TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX4_TMRB4TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX4_TMRB4NOSYNC_S             27
#define AM_REG_CTIMER_AUX4_TMRB4NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX4_TMRB4NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX4_TMRB4NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX4_TMRB4NOSYNC_NOSYNC        0x08000000

// Counter/Timer B4 Trigger Select.
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_S               23
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A4OUT           0x00800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A7OUT           0x02000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B7OUT           0x02800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A1OUT           0x03000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B1OUT           0x03800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A1OUT2          0x05000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B1OUT2          0x05800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_B5OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX4_TMRB4TRIG_A5OUT2DUAL      0x07800000

// Counter/Timer B4 Pattern Limit Count.
#define AM_REG_CTIMER_AUX4_TMRB4LMT_S                16
#define AM_REG_CTIMER_AUX4_TMRB4LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX4_TMRB4LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A4 Upper compare enable.
#define AM_REG_CTIMER_AUX4_TMRA4EN23_S               14
#define AM_REG_CTIMER_AUX4_TMRA4EN23_M               0x00004000
#define AM_REG_CTIMER_AUX4_TMRA4EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX4_TMRA4EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX4_TMRA4EN23_EN              0x00000000

// Counter/Timer A4 Upper output polarity
#define AM_REG_CTIMER_AUX4_TMRA4POL23_S              13
#define AM_REG_CTIMER_AUX4_TMRA4POL23_M              0x00002000
#define AM_REG_CTIMER_AUX4_TMRA4POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX4_TMRA4POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX4_TMRA4POL23_INV            0x00002000

// Counter/Timer A4 Invert on trigger.
#define AM_REG_CTIMER_AUX4_TMRA4TINV_S               12
#define AM_REG_CTIMER_AUX4_TMRA4TINV_M               0x00001000
#define AM_REG_CTIMER_AUX4_TMRA4TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX4_TMRA4TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX4_TMRA4TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX4_TMRA4NOSYNC_S             11
#define AM_REG_CTIMER_AUX4_TMRA4NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX4_TMRA4NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX4_TMRA4NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX4_TMRA4NOSYNC_NOSYNC        0x00000800

// Counter/Timer A4 Trigger Select.
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_S               7
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX4_TMRA4TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B4OUT           0x00000080
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A6OUT           0x00000200
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B6OUT           0x00000280
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A2OUT           0x00000300
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B2OUT           0x00000380
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A1OUT2          0x00000500
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B1OUT2          0x00000580
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_B5OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX4_TMRA4TRIG_A5OUT2DUAL      0x00000780

// Counter/Timer A4 Pattern Limit Count.
#define AM_REG_CTIMER_AUX4_TMRA4LMT_S                0
#define AM_REG_CTIMER_AUX4_TMRA4LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX4_TMRA4LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR5 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B5.
#define AM_REG_CTIMER_TMR5_CTTMRB5_S                 16
#define AM_REG_CTIMER_TMR5_CTTMRB5_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR5_CTTMRB5(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A5.
#define AM_REG_CTIMER_TMR5_CTTMRA5_S                 0
#define AM_REG_CTIMER_TMR5_CTTMRA5_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR5_CTTMRA5(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA5 - Counter/Timer A5 Compare Registers
//
//*****************************************************************************
// Counter/Timer A5 Compare Register 1.
#define AM_REG_CTIMER_CMPRA5_CMPR1A5_S               16
#define AM_REG_CTIMER_CMPRA5_CMPR1A5_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA5_CMPR1A5(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A5 Compare Register 0.
#define AM_REG_CTIMER_CMPRA5_CMPR0A5_S               0
#define AM_REG_CTIMER_CMPRA5_CMPR0A5_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA5_CMPR0A5(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB5 - Counter/Timer B5 Compare Registers
//
//*****************************************************************************
// Counter/Timer B5 Compare Register 1.
#define AM_REG_CTIMER_CMPRB5_CMPR1B5_S               16
#define AM_REG_CTIMER_CMPRB5_CMPR1B5_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB5_CMPR1B5(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B5 Compare Register 0.
#define AM_REG_CTIMER_CMPRB5_CMPR0B5_S               0
#define AM_REG_CTIMER_CMPRB5_CMPR0B5_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB5_CMPR0B5(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL5 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A5/B5 Link bit.
#define AM_REG_CTIMER_CTRL5_CTLINK5_S                31
#define AM_REG_CTIMER_CTRL5_CTLINK5_M                0x80000000
#define AM_REG_CTIMER_CTRL5_CTLINK5(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL5_CTLINK5_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL5_CTLINK5_32BIT_TIMER      0x80000000

// Counter/Timer B5 output polarity.
#define AM_REG_CTIMER_CTRL5_TMRB5POL_S               28
#define AM_REG_CTIMER_CTRL5_TMRB5POL_M               0x10000000
#define AM_REG_CTIMER_CTRL5_TMRB5POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL5_TMRB5POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5POL_INVERTED        0x10000000

// Counter/Timer B5 Clear bit.
#define AM_REG_CTIMER_CTRL5_TMRB5CLR_S               27
#define AM_REG_CTIMER_CTRL5_TMRB5CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL5_TMRB5CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL5_TMRB5CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5CLR_CLEAR           0x08000000

// Counter/Timer B5 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL5_TMRB5IE1_S               26
#define AM_REG_CTIMER_CTRL5_TMRB5IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL5_TMRB5IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL5_TMRB5IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5IE1_EN              0x04000000

// Counter/Timer B5 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL5_TMRB5IE0_S               25
#define AM_REG_CTIMER_CTRL5_TMRB5IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL5_TMRB5IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL5_TMRB5IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5IE0_EN              0x02000000

// Counter/Timer B5 Function Select.
#define AM_REG_CTIMER_CTRL5_TMRB5FN_S                22
#define AM_REG_CTIMER_CTRL5_TMRB5FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL5_TMRB5FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL5_TMRB5FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL5_TMRB5FN_ALTPWN           0x01C00000

// Counter/Timer B5 Clock Select.
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_S               17
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRA5          0x00280000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRA0          0x002A0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB0          0x002C0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRA6          0x002E0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB6          0x00300000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB1          0x00320000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB2          0x00340000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB3          0x00360000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_CTMRB4          0x00380000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL5_TMRB5CLK_BUCKA           0x003E0000

// Counter/Timer B5 Enable bit.
#define AM_REG_CTIMER_CTRL5_TMRB5EN_S                16
#define AM_REG_CTIMER_CTRL5_TMRB5EN_M                0x00010000
#define AM_REG_CTIMER_CTRL5_TMRB5EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL5_TMRB5EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL5_TMRB5EN_EN               0x00010000

// Counter/Timer A5 output polarity.
#define AM_REG_CTIMER_CTRL5_TMRA5POL_S               12
#define AM_REG_CTIMER_CTRL5_TMRA5POL_M               0x00001000
#define AM_REG_CTIMER_CTRL5_TMRA5POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL5_TMRA5POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5POL_INVERTED        0x00001000

// Counter/Timer A5 Clear bit.
#define AM_REG_CTIMER_CTRL5_TMRA5CLR_S               11
#define AM_REG_CTIMER_CTRL5_TMRA5CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL5_TMRA5CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL5_TMRA5CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5CLR_CLEAR           0x00000800

// Counter/Timer A5 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL5_TMRA5IE1_S               10
#define AM_REG_CTIMER_CTRL5_TMRA5IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL5_TMRA5IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL5_TMRA5IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5IE1_EN              0x00000400

// Counter/Timer A5 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL5_TMRA5IE0_S               9
#define AM_REG_CTIMER_CTRL5_TMRA5IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL5_TMRA5IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL5_TMRA5IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5IE0_EN              0x00000200

// Counter/Timer A5 Function Select.
#define AM_REG_CTIMER_CTRL5_TMRA5FN_S                6
#define AM_REG_CTIMER_CTRL5_TMRA5FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL5_TMRA5FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL5_TMRA5FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL5_TMRA5FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL5_TMRA5FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL5_TMRA5FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL5_TMRA5FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL5_TMRA5FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL5_TMRA5FN_ALTPWN           0x000001C0
#define AM_REG_CTIMER_CTRL5_TMRA5FN_TRIGCOPY         0x000001C0
#define AM_REG_CTIMER_CTRL5_TMRA5FN_DUALTRIGPATTERN  0x00000100

// Counter/Timer A5 Clock Select.
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_S               1
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL5_TMRA5CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB5          0x00000028
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRA0          0x0000002A
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB0          0x0000002C
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRA6          0x0000002E
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB6          0x00000030
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB1          0x00000032
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB2          0x00000034
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB3          0x00000036
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_CTMRB4          0x00000038
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL5_TMRA5CLK_BUCKA           0x0000003E

// Counter/Timer A5 Enable bit.
#define AM_REG_CTIMER_CTRL5_TMRA5EN_S                0
#define AM_REG_CTIMER_CTRL5_TMRA5EN_M                0x00000001
#define AM_REG_CTIMER_CTRL5_TMRA5EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL5_TMRA5EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL5_TMRA5EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA5 - Counter/Timer A5 Compare Registers
//
//*****************************************************************************
// Counter/Timer A5 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA5_CMPR3A5_S            16
#define AM_REG_CTIMER_CMPRAUXA5_CMPR3A5_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA5_CMPR3A5(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A5 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA5_CMPR2A5_S            0
#define AM_REG_CTIMER_CMPRAUXA5_CMPR2A5_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA5_CMPR2A5(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB5 - Counter/Timer B5 Compare Registers
//
//*****************************************************************************
// Counter/Timer B5 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB5_CMPR3B5_S            16
#define AM_REG_CTIMER_CMPRAUXB5_CMPR3B5_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB5_CMPR3B5(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B5 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB5_CMPR2B5_S            0
#define AM_REG_CTIMER_CMPRAUXB5_CMPR2B5_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB5_CMPR2B5(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX5 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B5 Upper compare enable.
#define AM_REG_CTIMER_AUX5_TMRB5EN23_S               30
#define AM_REG_CTIMER_AUX5_TMRB5EN23_M               0x40000000
#define AM_REG_CTIMER_AUX5_TMRB5EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX5_TMRB5EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX5_TMRB5EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX5_TMRB5POL23_S              29
#define AM_REG_CTIMER_AUX5_TMRB5POL23_M              0x20000000
#define AM_REG_CTIMER_AUX5_TMRB5POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX5_TMRB5POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX5_TMRB5POL23_INV            0x20000000

// Counter/Timer B5 Invert on trigger.
#define AM_REG_CTIMER_AUX5_TMRB5TINV_S               28
#define AM_REG_CTIMER_AUX5_TMRB5TINV_M               0x10000000
#define AM_REG_CTIMER_AUX5_TMRB5TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX5_TMRB5TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX5_TMRB5TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX5_TMRB5NOSYNC_S             27
#define AM_REG_CTIMER_AUX5_TMRB5NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX5_TMRB5NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX5_TMRB5NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX5_TMRB5NOSYNC_NOSYNC        0x08000000

// Counter/Timer B5 Trigger Select.
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_S               23
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A5OUT           0x00800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A6OUT           0x02000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B6OUT           0x02800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A1OUT           0x03000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B1OUT           0x03800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A0OUT2          0x05000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B0OUT2          0x05800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_B4OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX5_TMRB5TRIG_A4OUT2DUAL      0x07800000

// Counter/Timer B5 Pattern Limit Count.
#define AM_REG_CTIMER_AUX5_TMRB5LMT_S                16
#define AM_REG_CTIMER_AUX5_TMRB5LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX5_TMRB5LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A5 Upper compare enable.
#define AM_REG_CTIMER_AUX5_TMRA5EN23_S               14
#define AM_REG_CTIMER_AUX5_TMRA5EN23_M               0x00004000
#define AM_REG_CTIMER_AUX5_TMRA5EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX5_TMRA5EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX5_TMRA5EN23_EN              0x00000000

// Counter/Timer A5 Upper output polarity
#define AM_REG_CTIMER_AUX5_TMRA5POL23_S              13
#define AM_REG_CTIMER_AUX5_TMRA5POL23_M              0x00002000
#define AM_REG_CTIMER_AUX5_TMRA5POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX5_TMRA5POL23_NORMAL         0x00000000
#define AM_REG_CTIMER_AUX5_TMRA5POL23_INV            0x00002000

// Counter/Timer A5 Invert on trigger.
#define AM_REG_CTIMER_AUX5_TMRA5TINV_S               12
#define AM_REG_CTIMER_AUX5_TMRA5TINV_M               0x00001000
#define AM_REG_CTIMER_AUX5_TMRA5TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX5_TMRA5TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX5_TMRA5TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX5_TMRA5NOSYNC_S             11
#define AM_REG_CTIMER_AUX5_TMRA5NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX5_TMRA5NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX5_TMRA5NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX5_TMRA5NOSYNC_NOSYNC        0x00000800

// Counter/Timer A5 Trigger Select.
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_S               7
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX5_TMRA5TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B5OUT           0x00000080
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A4OUT           0x00000200
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B4OUT           0x00000280
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A2OUT           0x00000300
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B2OUT           0x00000380
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A0OUT2          0x00000500
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B0OUT2          0x00000580
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_B4OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX5_TMRA5TRIG_A4OUT2DUAL      0x00000780

// Counter/Timer A5 Pattern Limit Count.
#define AM_REG_CTIMER_AUX5_TMRA5LMT_S                0
#define AM_REG_CTIMER_AUX5_TMRA5LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX5_TMRA5LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR6 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B6.
#define AM_REG_CTIMER_TMR6_CTTMRB6_S                 16
#define AM_REG_CTIMER_TMR6_CTTMRB6_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR6_CTTMRB6(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A6.
#define AM_REG_CTIMER_TMR6_CTTMRA6_S                 0
#define AM_REG_CTIMER_TMR6_CTTMRA6_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR6_CTTMRA6(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA6 - Counter/Timer A6 Compare Registers
//
//*****************************************************************************
// Counter/Timer A6 Compare Register 1.
#define AM_REG_CTIMER_CMPRA6_CMPR1A6_S               16
#define AM_REG_CTIMER_CMPRA6_CMPR1A6_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA6_CMPR1A6(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A6 Compare Register 0.
#define AM_REG_CTIMER_CMPRA6_CMPR0A6_S               0
#define AM_REG_CTIMER_CMPRA6_CMPR0A6_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA6_CMPR0A6(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB6 - Counter/Timer B6 Compare Registers
//
//*****************************************************************************
// Counter/Timer B6 Compare Register 1.
#define AM_REG_CTIMER_CMPRB6_CMPR1B6_S               16
#define AM_REG_CTIMER_CMPRB6_CMPR1B6_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB6_CMPR1B6(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B6 Compare Register 0.
#define AM_REG_CTIMER_CMPRB6_CMPR0B6_S               0
#define AM_REG_CTIMER_CMPRB6_CMPR0B6_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB6_CMPR0B6(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL6 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A6/B6 Link bit.
#define AM_REG_CTIMER_CTRL6_CTLINK6_S                31
#define AM_REG_CTIMER_CTRL6_CTLINK6_M                0x80000000
#define AM_REG_CTIMER_CTRL6_CTLINK6(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL6_CTLINK6_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL6_CTLINK6_32BIT_TIMER      0x80000000

// Counter/Timer B6 output polarity.
#define AM_REG_CTIMER_CTRL6_TMRB6POL_S               28
#define AM_REG_CTIMER_CTRL6_TMRB6POL_M               0x10000000
#define AM_REG_CTIMER_CTRL6_TMRB6POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL6_TMRB6POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6POL_INVERTED        0x10000000

// Counter/Timer B6 Clear bit.
#define AM_REG_CTIMER_CTRL6_TMRB6CLR_S               27
#define AM_REG_CTIMER_CTRL6_TMRB6CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL6_TMRB6CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL6_TMRB6CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6CLR_CLEAR           0x08000000

// Counter/Timer B6 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL6_TMRB6IE1_S               26
#define AM_REG_CTIMER_CTRL6_TMRB6IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL6_TMRB6IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL6_TMRB6IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6IE1_EN              0x04000000

// Counter/Timer B6 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL6_TMRB6IE0_S               25
#define AM_REG_CTIMER_CTRL6_TMRB6IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL6_TMRB6IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL6_TMRB6IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6IE0_EN              0x02000000

// Counter/Timer B6 Function Select.
#define AM_REG_CTIMER_CTRL6_TMRB6FN_S                22
#define AM_REG_CTIMER_CTRL6_TMRB6FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL6_TMRB6FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL6_TMRB6FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL6_TMRB6FN_ALTPWN           0x01C00000

// Counter/Timer B6 Clock Select.
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_S               17
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRA6          0x00280000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRA3          0x002A0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB3          0x002C0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRA7          0x002E0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB7          0x00300000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB0          0x00320000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB1          0x00340000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB2          0x00360000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_CTMRB4          0x00380000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL6_TMRB6CLK_BUCKA           0x003E0000

// Counter/Timer B6 Enable bit.
#define AM_REG_CTIMER_CTRL6_TMRB6EN_S                16
#define AM_REG_CTIMER_CTRL6_TMRB6EN_M                0x00010000
#define AM_REG_CTIMER_CTRL6_TMRB6EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL6_TMRB6EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL6_TMRB6EN_EN               0x00010000

// Counter/Timer A6 output polarity.
#define AM_REG_CTIMER_CTRL6_TMRA6POL_S               12
#define AM_REG_CTIMER_CTRL6_TMRA6POL_M               0x00001000
#define AM_REG_CTIMER_CTRL6_TMRA6POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL6_TMRA6POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6POL_INVERTED        0x00001000

// Counter/Timer A6 Clear bit.
#define AM_REG_CTIMER_CTRL6_TMRA6CLR_S               11
#define AM_REG_CTIMER_CTRL6_TMRA6CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL6_TMRA6CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL6_TMRA6CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6CLR_CLEAR           0x00000800

// Counter/Timer A6 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL6_TMRA6IE1_S               10
#define AM_REG_CTIMER_CTRL6_TMRA6IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL6_TMRA6IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL6_TMRA6IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6IE1_EN              0x00000400

// Counter/Timer A6 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL6_TMRA6IE0_S               9
#define AM_REG_CTIMER_CTRL6_TMRA6IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL6_TMRA6IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL6_TMRA6IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6IE0_EN              0x00000200

// Counter/Timer A6 Function Select.
#define AM_REG_CTIMER_CTRL6_TMRA6FN_S                6
#define AM_REG_CTIMER_CTRL6_TMRA6FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL6_TMRA6FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL6_TMRA6FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL6_TMRA6FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL6_TMRA6FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL6_TMRA6FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL6_TMRA6FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL6_TMRA6FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL6_TMRA6FN_ALTPWN           0x000001C0

// Counter/Timer A6 Clock Select.
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_S               1
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL6_TMRA6CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB6          0x00000028
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRA3          0x0000002A
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB3          0x0000002C
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRA7          0x0000002E
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB7          0x00000030
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB0          0x00000032
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB1          0x00000034
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB2          0x00000036
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_CTMRB4          0x00000038
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL6_TMRA6CLK_BUCKA           0x0000003E

// Counter/Timer A6 Enable bit.
#define AM_REG_CTIMER_CTRL6_TMRA6EN_S                0
#define AM_REG_CTIMER_CTRL6_TMRA6EN_M                0x00000001
#define AM_REG_CTIMER_CTRL6_TMRA6EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL6_TMRA6EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL6_TMRA6EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA6 - Counter/Timer A6 Compare Registers
//
//*****************************************************************************
// Counter/Timer A6 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA6_CMPR3A6_S            16
#define AM_REG_CTIMER_CMPRAUXA6_CMPR3A6_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA6_CMPR3A6(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A6 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA6_CMPR2A6_S            0
#define AM_REG_CTIMER_CMPRAUXA6_CMPR2A6_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA6_CMPR2A6(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB6 - Counter/Timer B6 Compare Registers
//
//*****************************************************************************
// Counter/Timer B6 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB6_CMPR3B6_S            16
#define AM_REG_CTIMER_CMPRAUXB6_CMPR3B6_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB6_CMPR3B6(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B6 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB6_CMPR2B6_S            0
#define AM_REG_CTIMER_CMPRAUXB6_CMPR2B6_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB6_CMPR2B6(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX6 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B6 Upper compare enable.
#define AM_REG_CTIMER_AUX6_TMRB6EN23_S               30
#define AM_REG_CTIMER_AUX6_TMRB6EN23_M               0x40000000
#define AM_REG_CTIMER_AUX6_TMRB6EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX6_TMRB6EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX6_TMRB6EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX6_TMRB6POL23_S              29
#define AM_REG_CTIMER_AUX6_TMRB6POL23_M              0x20000000
#define AM_REG_CTIMER_AUX6_TMRB6POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX6_TMRB6POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX6_TMRB6POL23_INV            0x20000000

// Counter/Timer B6 Invert on trigger.
#define AM_REG_CTIMER_AUX6_TMRB6TINV_S               28
#define AM_REG_CTIMER_AUX6_TMRB6TINV_M               0x10000000
#define AM_REG_CTIMER_AUX6_TMRB6TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX6_TMRB6TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX6_TMRB6TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX6_TMRB6NOSYNC_S             27
#define AM_REG_CTIMER_AUX6_TMRB6NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX6_TMRB6NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX6_TMRB6NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX6_TMRB6NOSYNC_NOSYNC        0x08000000

// Counter/Timer B6 Trigger Select.
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_S               23
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A6OUT           0x00800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A4OUT           0x02000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B4OUT           0x02800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A1OUT           0x03000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B1OUT           0x03800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A2OUT2          0x05000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B2OUT2          0x05800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_B0OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX6_TMRB6TRIG_A0OUT2DUAL      0x07800000

// Counter/Timer B6 Pattern Limit Count.
#define AM_REG_CTIMER_AUX6_TMRB6LMT_S                16
#define AM_REG_CTIMER_AUX6_TMRB6LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX6_TMRB6LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A6 Upper compare enable.
#define AM_REG_CTIMER_AUX6_TMRA6EN23_S               14
#define AM_REG_CTIMER_AUX6_TMRA6EN23_M               0x00004000
#define AM_REG_CTIMER_AUX6_TMRA6EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX6_TMRA6EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX6_TMRA6EN23_EN              0x00000000

// Counter/Timer A6 Upper output polarity
#define AM_REG_CTIMER_AUX6_TMRA6POL23_S              13
#define AM_REG_CTIMER_AUX6_TMRA6POL23_M              0x00002000
#define AM_REG_CTIMER_AUX6_TMRA6POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX6_TMRA6POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX6_TMRA6POL23_INV            0x00002000

// Counter/Timer A6 Invert on trigger.
#define AM_REG_CTIMER_AUX6_TMRA6TINV_S               12
#define AM_REG_CTIMER_AUX6_TMRA6TINV_M               0x00001000
#define AM_REG_CTIMER_AUX6_TMRA6TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX6_TMRA6TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX6_TMRA6TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX6_TMRA6NOSYNC_S             11
#define AM_REG_CTIMER_AUX6_TMRA6NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX6_TMRA6NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX6_TMRA6NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX6_TMRA6NOSYNC_NOSYNC        0x00000800

// Counter/Timer A6 Trigger Select.
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_S               7
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX6_TMRA6TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B6OUT           0x00000080
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A5OUT           0x00000200
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B5OUT           0x00000280
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A1OUT           0x00000300
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B1OUT           0x00000380
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A2OUT2          0x00000500
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B2OUT2          0x00000580
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A5OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A7OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_B0OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX6_TMRA6TRIG_A0OUT2DUAL      0x00000780

// Counter/Timer A6 Pattern Limit Count.
#define AM_REG_CTIMER_AUX6_TMRA6LMT_S                0
#define AM_REG_CTIMER_AUX6_TMRA6LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX6_TMRA6LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_TMR7 - Counter/Timer Register
//
//*****************************************************************************
// Counter/Timer B7.
#define AM_REG_CTIMER_TMR7_CTTMRB7_S                 16
#define AM_REG_CTIMER_TMR7_CTTMRB7_M                 0xFFFF0000
#define AM_REG_CTIMER_TMR7_CTTMRB7(n)                (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A7.
#define AM_REG_CTIMER_TMR7_CTTMRA7_S                 0
#define AM_REG_CTIMER_TMR7_CTTMRA7_M                 0x0000FFFF
#define AM_REG_CTIMER_TMR7_CTTMRA7(n)                (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRA7 - Counter/Timer A7 Compare Registers
//
//*****************************************************************************
// Counter/Timer A7 Compare Register 1.
#define AM_REG_CTIMER_CMPRA7_CMPR1A7_S               16
#define AM_REG_CTIMER_CMPRA7_CMPR1A7_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRA7_CMPR1A7(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A7 Compare Register 0.
#define AM_REG_CTIMER_CMPRA7_CMPR0A7_S               0
#define AM_REG_CTIMER_CMPRA7_CMPR0A7_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRA7_CMPR0A7(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRB7 - Counter/Timer B7 Compare Registers
//
//*****************************************************************************
// Counter/Timer B3 Compare Register 1.
#define AM_REG_CTIMER_CMPRB7_CMPR1B7_S               16
#define AM_REG_CTIMER_CMPRB7_CMPR1B7_M               0xFFFF0000
#define AM_REG_CTIMER_CMPRB7_CMPR1B7(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B3 Compare Register 0.
#define AM_REG_CTIMER_CMPRB7_CMPR0B7_S               0
#define AM_REG_CTIMER_CMPRB7_CMPR0B7_M               0x0000FFFF
#define AM_REG_CTIMER_CMPRB7_CMPR0B7(n)              (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CTRL7 - Counter/Timer Control
//
//*****************************************************************************
// Counter/Timer A7/B7 Link bit.
#define AM_REG_CTIMER_CTRL7_CTLINK7_S                31
#define AM_REG_CTIMER_CTRL7_CTLINK7_M                0x80000000
#define AM_REG_CTIMER_CTRL7_CTLINK7(n)               (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_CTRL7_CTLINK7_TWO_16BIT_TIMERS 0x00000000
#define AM_REG_CTIMER_CTRL7_CTLINK7_32BIT_TIMER      0x80000000

// Counter/Timer B7 output polarity.
#define AM_REG_CTIMER_CTRL7_TMRB7POL_S               28
#define AM_REG_CTIMER_CTRL7_TMRB7POL_M               0x10000000
#define AM_REG_CTIMER_CTRL7_TMRB7POL(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_CTRL7_TMRB7POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7POL_INVERTED        0x10000000

// Counter/Timer B7 Clear bit.
#define AM_REG_CTIMER_CTRL7_TMRB7CLR_S               27
#define AM_REG_CTIMER_CTRL7_TMRB7CLR_M               0x08000000
#define AM_REG_CTIMER_CTRL7_TMRB7CLR(n)              (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_CTRL7_TMRB7CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7CLR_CLEAR           0x08000000

// Counter/Timer B7 Interrupt Enable bit for COMPR1.
#define AM_REG_CTIMER_CTRL7_TMRB7IE1_S               26
#define AM_REG_CTIMER_CTRL7_TMRB7IE1_M               0x04000000
#define AM_REG_CTIMER_CTRL7_TMRB7IE1(n)              (((uint32_t)(n) << 26) & 0x04000000)
#define AM_REG_CTIMER_CTRL7_TMRB7IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7IE1_EN              0x04000000

// Counter/Timer B7 Interrupt Enable bit for COMPR0.
#define AM_REG_CTIMER_CTRL7_TMRB7IE0_S               25
#define AM_REG_CTIMER_CTRL7_TMRB7IE0_M               0x02000000
#define AM_REG_CTIMER_CTRL7_TMRB7IE0(n)              (((uint32_t)(n) << 25) & 0x02000000)
#define AM_REG_CTIMER_CTRL7_TMRB7IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7IE0_EN              0x02000000

// Counter/Timer B7 Function Select.
#define AM_REG_CTIMER_CTRL7_TMRB7FN_S                22
#define AM_REG_CTIMER_CTRL7_TMRB7FN_M                0x01C00000
#define AM_REG_CTIMER_CTRL7_TMRB7FN(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_CTRL7_TMRB7FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_REPEATEDCOUNT    0x00400000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_PULSE_ONCE       0x00800000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_PULSE_CONT       0x00C00000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_SINGLEPATTERN    0x01000000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_REPEATPATTERN    0x01400000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_CONTINUOUS       0x01800000
#define AM_REG_CTIMER_CTRL7_TMRB7FN_ALTPWN           0x01C00000

// Counter/Timer B7 Clock Select.
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_S               17
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_M               0x003E0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK(n)              (((uint32_t)(n) << 17) & 0x003E0000)
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HFRC_DIV4       0x00020000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HFRC_DIV16      0x00040000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HFRC_DIV256     0x00060000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HFRC_DIV1024    0x00080000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HFRC_DIV4K      0x000A0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT              0x000C0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV2         0x000E0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV16        0x00100000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV128       0x00120000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_LFRC_DIV2       0x00140000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_LFRC_DIV32      0x00160000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_LFRC_DIV1K      0x00180000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_LFRC            0x001A0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_RTC_100HZ       0x001C0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_HCLK            0x001E0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV4         0x00200000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV8         0x00220000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_XT_DIV32        0x00240000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_RSVD            0x00260000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRA7          0x00280000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRA2          0x002A0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB2          0x002C0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRA0          0x002E0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB0          0x00300000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB1          0x00320000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB3          0x00340000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB4          0x00360000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_CTMRB5          0x00380000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_BUCKBLE         0x003A0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_BUCKB           0x003C0000
#define AM_REG_CTIMER_CTRL7_TMRB7CLK_BUCKA           0x003E0000

// Counter/Timer B7 Enable bit.
#define AM_REG_CTIMER_CTRL7_TMRB7EN_S                16
#define AM_REG_CTIMER_CTRL7_TMRB7EN_M                0x00010000
#define AM_REG_CTIMER_CTRL7_TMRB7EN(n)               (((uint32_t)(n) << 16) & 0x00010000)
#define AM_REG_CTIMER_CTRL7_TMRB7EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL7_TMRB7EN_EN               0x00010000

// Counter/Timer A7 output polarity.
#define AM_REG_CTIMER_CTRL7_TMRA7POL_S               12
#define AM_REG_CTIMER_CTRL7_TMRA7POL_M               0x00001000
#define AM_REG_CTIMER_CTRL7_TMRA7POL(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_CTRL7_TMRA7POL_NORMAL          0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7POL_INVERTED        0x00001000

// Counter/Timer A7 Clear bit.
#define AM_REG_CTIMER_CTRL7_TMRA7CLR_S               11
#define AM_REG_CTIMER_CTRL7_TMRA7CLR_M               0x00000800
#define AM_REG_CTIMER_CTRL7_TMRA7CLR(n)              (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_CTRL7_TMRA7CLR_RUN             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7CLR_CLEAR           0x00000800

// Counter/Timer A7 Interrupt Enable bit based on COMPR1.
#define AM_REG_CTIMER_CTRL7_TMRA7IE1_S               10
#define AM_REG_CTIMER_CTRL7_TMRA7IE1_M               0x00000400
#define AM_REG_CTIMER_CTRL7_TMRA7IE1(n)              (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_CTRL7_TMRA7IE1_DIS             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7IE1_EN              0x00000400

// Counter/Timer A7 Interrupt Enable bit based on COMPR0.
#define AM_REG_CTIMER_CTRL7_TMRA7IE0_S               9
#define AM_REG_CTIMER_CTRL7_TMRA7IE0_M               0x00000200
#define AM_REG_CTIMER_CTRL7_TMRA7IE0(n)              (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_CTRL7_TMRA7IE0_DIS             0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7IE0_EN              0x00000200

// Counter/Timer A7 Function Select.
#define AM_REG_CTIMER_CTRL7_TMRA7FN_S                6
#define AM_REG_CTIMER_CTRL7_TMRA7FN_M                0x000001C0
#define AM_REG_CTIMER_CTRL7_TMRA7FN(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_CTRL7_TMRA7FN_SINGLECOUNT      0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7FN_REPEATEDCOUNT    0x00000040
#define AM_REG_CTIMER_CTRL7_TMRA7FN_PULSE_ONCE       0x00000080
#define AM_REG_CTIMER_CTRL7_TMRA7FN_PULSE_CONT       0x000000C0
#define AM_REG_CTIMER_CTRL7_TMRA7FN_SINGLEPATTERN    0x00000100
#define AM_REG_CTIMER_CTRL7_TMRA7FN_REPEATPATTERN    0x00000140
#define AM_REG_CTIMER_CTRL7_TMRA7FN_CONTINUOUS       0x00000180
#define AM_REG_CTIMER_CTRL7_TMRA7FN_ALTPWN           0x000001C0

// Counter/Timer A7 Clock Select.
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_S               1
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_M               0x0000003E
#define AM_REG_CTIMER_CTRL7_TMRA7CLK(n)              (((uint32_t)(n) << 1) & 0x0000003E)
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_TMRPIN          0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HFRC_DIV4       0x00000002
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HFRC_DIV16      0x00000004
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HFRC_DIV256     0x00000006
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HFRC_DIV1024    0x00000008
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HFRC_DIV4K      0x0000000A
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT              0x0000000C
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV2         0x0000000E
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV16        0x00000010
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV128       0x00000012
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_LFRC_DIV2       0x00000014
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_LFRC_DIV32      0x00000016
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_LFRC_DIV1K      0x00000018
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_LFRC            0x0000001A
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_RTC_100HZ       0x0000001C
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_HCLK            0x0000001E
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV4         0x00000020
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV8         0x00000022
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_XT_DIV32        0x00000024
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_RSVD            0x00000026
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB7          0x00000028
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRA2          0x0000002A
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB2          0x0000002C
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRA0          0x0000002E
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB0          0x00000030
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB1          0x00000032
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB3          0x00000034
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB4          0x00000036
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_CTMRB5          0x00000038
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_BUCKBLE         0x0000003A
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_BUCKB           0x0000003C
#define AM_REG_CTIMER_CTRL7_TMRA7CLK_BUCKA           0x0000003E

// Counter/Timer A7 Enable bit.
#define AM_REG_CTIMER_CTRL7_TMRA7EN_S                0
#define AM_REG_CTIMER_CTRL7_TMRA7EN_M                0x00000001
#define AM_REG_CTIMER_CTRL7_TMRA7EN(n)               (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CTRL7_TMRA7EN_DIS              0x00000000
#define AM_REG_CTIMER_CTRL7_TMRA7EN_EN               0x00000001

//*****************************************************************************
//
// CTIMER_CMPRAUXA7 - Counter/Timer A7 Compare Registers
//
//*****************************************************************************
// Counter/Timer A7 Compare Register 3. Holds the upper limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA7_CMPR3A7_S            16
#define AM_REG_CTIMER_CMPRAUXA7_CMPR3A7_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXA7_CMPR3A7(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer A7 Compare Register 2. Holds the lower limit for timer half A.
#define AM_REG_CTIMER_CMPRAUXA7_CMPR2A7_S            0
#define AM_REG_CTIMER_CMPRAUXA7_CMPR2A7_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXA7_CMPR2A7(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_CMPRAUXB7 - Counter/Timer B7 Compare Registers
//
//*****************************************************************************
// Counter/Timer B7 Compare Register 3. Holds the upper limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB7_CMPR3B7_S            16
#define AM_REG_CTIMER_CMPRAUXB7_CMPR3B7_M            0xFFFF0000
#define AM_REG_CTIMER_CMPRAUXB7_CMPR3B7(n)           (((uint32_t)(n) << 16) & 0xFFFF0000)

// Counter/Timer B7 Compare Register 2. Holds the lower limit for timer half B.
#define AM_REG_CTIMER_CMPRAUXB7_CMPR2B7_S            0
#define AM_REG_CTIMER_CMPRAUXB7_CMPR2B7_M            0x0000FFFF
#define AM_REG_CTIMER_CMPRAUXB7_CMPR2B7(n)           (((uint32_t)(n) << 0) & 0x0000FFFF)

//*****************************************************************************
//
// CTIMER_AUX7 - Counter/Timer Auxiliary
//
//*****************************************************************************
// Counter/Timer B7 Upper compare enable.
#define AM_REG_CTIMER_AUX7_TMRB7EN23_S               30
#define AM_REG_CTIMER_AUX7_TMRB7EN23_M               0x40000000
#define AM_REG_CTIMER_AUX7_TMRB7EN23(n)              (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_AUX7_TMRB7EN23_DIS             0x40000000
#define AM_REG_CTIMER_AUX7_TMRB7EN23_EN              0x00000000

// Upper output polarity
#define AM_REG_CTIMER_AUX7_TMRB7POL23_S              29
#define AM_REG_CTIMER_AUX7_TMRB7POL23_M              0x20000000
#define AM_REG_CTIMER_AUX7_TMRB7POL23(n)             (((uint32_t)(n) << 29) & 0x20000000)
#define AM_REG_CTIMER_AUX7_TMRB7POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX7_TMRB7POL23_INV            0x20000000

// Counter/Timer B7 Invert on trigger.
#define AM_REG_CTIMER_AUX7_TMRB7TINV_S               28
#define AM_REG_CTIMER_AUX7_TMRB7TINV_M               0x10000000
#define AM_REG_CTIMER_AUX7_TMRB7TINV(n)              (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_CTIMER_AUX7_TMRB7TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX7_TMRB7TINV_EN              0x10000000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX7_TMRB7NOSYNC_S             27
#define AM_REG_CTIMER_AUX7_TMRB7NOSYNC_M             0x08000000
#define AM_REG_CTIMER_AUX7_TMRB7NOSYNC(n)            (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_CTIMER_AUX7_TMRB7NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX7_TMRB7NOSYNC_NOSYNC        0x08000000

// Counter/Timer B7 Trigger Select.
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_S               23
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_M               0x07800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG(n)              (((uint32_t)(n) << 23) & 0x07800000)
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A7OUT           0x00800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B3OUT           0x01000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A3OUT           0x01800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A5OUT           0x02000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B5OUT           0x02800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A2OUT           0x03000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B2OUT           0x03800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B3OUT2          0x04000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A3OUT2          0x04800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A2OUT2          0x05000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B2OUT2          0x05800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A6OUT2DUAL      0x06000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A7OUT2DUAL      0x06800000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_B1OUT2DUAL      0x07000000
#define AM_REG_CTIMER_AUX7_TMRB7TRIG_A1OUT2DUAL      0x07800000

// Counter/Timer B7 Pattern Limit Count.
#define AM_REG_CTIMER_AUX7_TMRB7LMT_S                16
#define AM_REG_CTIMER_AUX7_TMRB7LMT_M                0x003F0000
#define AM_REG_CTIMER_AUX7_TMRB7LMT(n)               (((uint32_t)(n) << 16) & 0x003F0000)

// Counter/Timer A7 Upper compare enable.
#define AM_REG_CTIMER_AUX7_TMRA7EN23_S               14
#define AM_REG_CTIMER_AUX7_TMRA7EN23_M               0x00004000
#define AM_REG_CTIMER_AUX7_TMRA7EN23(n)              (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_AUX7_TMRA7EN23_DIS             0x00004000
#define AM_REG_CTIMER_AUX7_TMRA7EN23_EN              0x00000000

// Counter/Timer A7 Upper output polarity
#define AM_REG_CTIMER_AUX7_TMRA7POL23_S              13
#define AM_REG_CTIMER_AUX7_TMRA7POL23_M              0x00002000
#define AM_REG_CTIMER_AUX7_TMRA7POL23(n)             (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_AUX7_TMRA7POL23_NORM           0x00000000
#define AM_REG_CTIMER_AUX7_TMRA7POL23_INV            0x00002000

// Counter/Timer A7 Invert on trigger.
#define AM_REG_CTIMER_AUX7_TMRA7TINV_S               12
#define AM_REG_CTIMER_AUX7_TMRA7TINV_M               0x00001000
#define AM_REG_CTIMER_AUX7_TMRA7TINV(n)              (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_AUX7_TMRA7TINV_DIS             0x00000000
#define AM_REG_CTIMER_AUX7_TMRA7TINV_EN              0x00001000

// Source clock synchronization control.
#define AM_REG_CTIMER_AUX7_TMRA7NOSYNC_S             11
#define AM_REG_CTIMER_AUX7_TMRA7NOSYNC_M             0x00000800
#define AM_REG_CTIMER_AUX7_TMRA7NOSYNC(n)            (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_AUX7_TMRA7NOSYNC_DIS           0x00000000
#define AM_REG_CTIMER_AUX7_TMRA7NOSYNC_NOSYNC        0x00000800

// Counter/Timer A7 Trigger Select.
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_S               7
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_M               0x00000780
#define AM_REG_CTIMER_AUX7_TMRA7TRIG(n)              (((uint32_t)(n) << 7) & 0x00000780)
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_DIS             0x00000000
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B7OUT           0x00000080
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B3OUT           0x00000100
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A3OUT           0x00000180
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A1OUT           0x00000200
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B1OUT           0x00000280
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A4OUT           0x00000300
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B4OUT           0x00000380
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B3OUT2          0x00000400
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A3OUT2          0x00000480
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A2OUT2          0x00000500
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B2OUT2          0x00000580
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A6OUT2DUAL      0x00000600
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A5OUT2DUAL      0x00000680
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_B4OUT2DUAL      0x00000700
#define AM_REG_CTIMER_AUX7_TMRA7TRIG_A4OUT2DUAL      0x00000780

// Counter/Timer A7 Pattern Limit Count.
#define AM_REG_CTIMER_AUX7_TMRA7LMT_S                0
#define AM_REG_CTIMER_AUX7_TMRA7LMT_M                0x0000007F
#define AM_REG_CTIMER_AUX7_TMRA7LMT(n)               (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// CTIMER_GLOBEN - Counter/Timer Global Enable
//
//*****************************************************************************
// Alternate enable for B7.
#define AM_REG_CTIMER_GLOBEN_ENB7_S                  15
#define AM_REG_CTIMER_GLOBEN_ENB7_M                  0x00008000
#define AM_REG_CTIMER_GLOBEN_ENB7(n)                 (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_CTIMER_GLOBEN_ENB7_LCO                0x00008000
#define AM_REG_CTIMER_GLOBEN_ENB7_DIS                0x00000000

// Alternate enable for A7
#define AM_REG_CTIMER_GLOBEN_ENA7_S                  14
#define AM_REG_CTIMER_GLOBEN_ENA7_M                  0x00004000
#define AM_REG_CTIMER_GLOBEN_ENA7(n)                 (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_GLOBEN_ENA7_LCO                0x00004000
#define AM_REG_CTIMER_GLOBEN_ENA7_DIS                0x00000000

// Alternate enable for B6
#define AM_REG_CTIMER_GLOBEN_ENB6_S                  13
#define AM_REG_CTIMER_GLOBEN_ENB6_M                  0x00002000
#define AM_REG_CTIMER_GLOBEN_ENB6(n)                 (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_GLOBEN_ENB6_LCO                0x00002000
#define AM_REG_CTIMER_GLOBEN_ENB6_DIS                0x00000000

// Alternate enable for A6
#define AM_REG_CTIMER_GLOBEN_ENA6_S                  12
#define AM_REG_CTIMER_GLOBEN_ENA6_M                  0x00001000
#define AM_REG_CTIMER_GLOBEN_ENA6(n)                 (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_GLOBEN_ENA6_LCO                0x00001000
#define AM_REG_CTIMER_GLOBEN_ENA6_DIS                0x00000000

// Alternate enable for B5
#define AM_REG_CTIMER_GLOBEN_ENB5_S                  11
#define AM_REG_CTIMER_GLOBEN_ENB5_M                  0x00000800
#define AM_REG_CTIMER_GLOBEN_ENB5(n)                 (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_GLOBEN_ENB5_LCO                0x00000800
#define AM_REG_CTIMER_GLOBEN_ENB5_DIS                0x00000000

// Alternate enable for A5
#define AM_REG_CTIMER_GLOBEN_ENA5_S                  10
#define AM_REG_CTIMER_GLOBEN_ENA5_M                  0x00000400
#define AM_REG_CTIMER_GLOBEN_ENA5(n)                 (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_GLOBEN_ENA5_LCO                0x00000400
#define AM_REG_CTIMER_GLOBEN_ENA5_DIS                0x00000000

// Alternate enable for B4
#define AM_REG_CTIMER_GLOBEN_ENB4_S                  9
#define AM_REG_CTIMER_GLOBEN_ENB4_M                  0x00000200
#define AM_REG_CTIMER_GLOBEN_ENB4(n)                 (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_GLOBEN_ENB4_LCO                0x00000200
#define AM_REG_CTIMER_GLOBEN_ENB4_DIS                0x00000000

// Alternate enable for A4
#define AM_REG_CTIMER_GLOBEN_ENA4_S                  8
#define AM_REG_CTIMER_GLOBEN_ENA4_M                  0x00000100
#define AM_REG_CTIMER_GLOBEN_ENA4(n)                 (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_GLOBEN_ENA4_LCO                0x00000100
#define AM_REG_CTIMER_GLOBEN_ENA4_DIS                0x00000000

// Alternate enable for B3.
#define AM_REG_CTIMER_GLOBEN_ENB3_S                  7
#define AM_REG_CTIMER_GLOBEN_ENB3_M                  0x00000080
#define AM_REG_CTIMER_GLOBEN_ENB3(n)                 (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_GLOBEN_ENB3_LCO                0x00000080
#define AM_REG_CTIMER_GLOBEN_ENB3_DIS                0x00000000

// Alternate enable for A3
#define AM_REG_CTIMER_GLOBEN_ENA3_S                  6
#define AM_REG_CTIMER_GLOBEN_ENA3_M                  0x00000040
#define AM_REG_CTIMER_GLOBEN_ENA3(n)                 (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_GLOBEN_ENA3_LCO                0x00000040
#define AM_REG_CTIMER_GLOBEN_ENA3_DIS                0x00000000

// Alternate enable for B2
#define AM_REG_CTIMER_GLOBEN_ENB2_S                  5
#define AM_REG_CTIMER_GLOBEN_ENB2_M                  0x00000020
#define AM_REG_CTIMER_GLOBEN_ENB2(n)                 (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_GLOBEN_ENB2_LCO                0x00000020
#define AM_REG_CTIMER_GLOBEN_ENB2_DIS                0x00000000

// Alternate enable for A2
#define AM_REG_CTIMER_GLOBEN_ENA2_S                  4
#define AM_REG_CTIMER_GLOBEN_ENA2_M                  0x00000010
#define AM_REG_CTIMER_GLOBEN_ENA2(n)                 (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_GLOBEN_ENA2_LCO                0x00000010
#define AM_REG_CTIMER_GLOBEN_ENA2_DIS                0x00000000

// Alternate enable for B1
#define AM_REG_CTIMER_GLOBEN_ENB1_S                  3
#define AM_REG_CTIMER_GLOBEN_ENB1_M                  0x00000008
#define AM_REG_CTIMER_GLOBEN_ENB1(n)                 (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_GLOBEN_ENB1_LCO                0x00000008
#define AM_REG_CTIMER_GLOBEN_ENB1_DIS                0x00000000

// Alternate enable for A1
#define AM_REG_CTIMER_GLOBEN_ENA1_S                  2
#define AM_REG_CTIMER_GLOBEN_ENA1_M                  0x00000004
#define AM_REG_CTIMER_GLOBEN_ENA1(n)                 (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_GLOBEN_ENA1_LCO                0x00000004
#define AM_REG_CTIMER_GLOBEN_ENA1_DIS                0x00000000

// Alternate enable for B0
#define AM_REG_CTIMER_GLOBEN_ENB0_S                  1
#define AM_REG_CTIMER_GLOBEN_ENB0_M                  0x00000002
#define AM_REG_CTIMER_GLOBEN_ENB0(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_GLOBEN_ENB0_LCO                0x00000002
#define AM_REG_CTIMER_GLOBEN_ENB0_DIS                0x00000000

// Alternate enable for A0
#define AM_REG_CTIMER_GLOBEN_ENA0_S                  0
#define AM_REG_CTIMER_GLOBEN_ENA0_M                  0x00000001
#define AM_REG_CTIMER_GLOBEN_ENA0(n)                 (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_GLOBEN_ENA0_LCO                0x00000001
#define AM_REG_CTIMER_GLOBEN_ENA0_DIS                0x00000000

//*****************************************************************************
//
// CTIMER_OUTCFG0 - Counter/Timer Output Config 0
//
//*****************************************************************************
// Pad output 9 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG9_S                 28
#define AM_REG_CTIMER_OUTCFG0_CFG9_M                 0x70000000
#define AM_REG_CTIMER_OUTCFG0_CFG9(n)                (((uint32_t)(n) << 28) & 0x70000000)
#define AM_REG_CTIMER_OUTCFG0_CFG9_A7OUT2            0x70000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_A6OUT2            0x60000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_B0OUT             0x50000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_A4OUT             0x40000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_A2OUT             0x30000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_A2OUT2            0x20000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_ONE               0x10000000
#define AM_REG_CTIMER_OUTCFG0_CFG9_ZERO              0x00000000

// Pad output 8 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG8_S                 25
#define AM_REG_CTIMER_OUTCFG0_CFG8_M                 0x0E000000
#define AM_REG_CTIMER_OUTCFG0_CFG8(n)                (((uint32_t)(n) << 25) & 0x0E000000)
#define AM_REG_CTIMER_OUTCFG0_CFG8_A7OUT2            0x0E000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_A6OUT2            0x0C000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_B6OUT             0x0A000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_A4OUT2            0x08000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_A3OUT2            0x06000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_A2OUT             0x04000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_ONE               0x02000000
#define AM_REG_CTIMER_OUTCFG0_CFG8_ZERO              0x00000000

// Pad output 7 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG7_S                 22
#define AM_REG_CTIMER_OUTCFG0_CFG7_M                 0x01C00000
#define AM_REG_CTIMER_OUTCFG0_CFG7(n)                (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_OUTCFG0_CFG7_A7OUT2            0x01C00000
#define AM_REG_CTIMER_OUTCFG0_CFG7_A6OUT2            0x01800000
#define AM_REG_CTIMER_OUTCFG0_CFG7_A7OUT             0x01400000
#define AM_REG_CTIMER_OUTCFG0_CFG7_B5OUT             0x01000000
#define AM_REG_CTIMER_OUTCFG0_CFG7_B1OUT             0x00C00000
#define AM_REG_CTIMER_OUTCFG0_CFG7_B1OUT2            0x00800000
#define AM_REG_CTIMER_OUTCFG0_CFG7_ONE               0x00400000
#define AM_REG_CTIMER_OUTCFG0_CFG7_ZERO              0x00000000

// Pad output 6 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG6_S                 19
#define AM_REG_CTIMER_OUTCFG0_CFG6_M                 0x00380000
#define AM_REG_CTIMER_OUTCFG0_CFG6(n)                (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_CTIMER_OUTCFG0_CFG6_A7OUT2            0x00380000
#define AM_REG_CTIMER_OUTCFG0_CFG6_A6OUT2            0x00300000
#define AM_REG_CTIMER_OUTCFG0_CFG6_B7OUT             0x00280000
#define AM_REG_CTIMER_OUTCFG0_CFG6_B5OUT2            0x00200000
#define AM_REG_CTIMER_OUTCFG0_CFG6_A1OUT             0x00180000
#define AM_REG_CTIMER_OUTCFG0_CFG6_B1OUT             0x00100000
#define AM_REG_CTIMER_OUTCFG0_CFG6_ONE               0x00080000
#define AM_REG_CTIMER_OUTCFG0_CFG6_ZERO              0x00000000

// Pad output 5 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG5_S                 16
#define AM_REG_CTIMER_OUTCFG0_CFG5_M                 0x00070000
#define AM_REG_CTIMER_OUTCFG0_CFG5(n)                (((uint32_t)(n) << 16) & 0x00070000)
#define AM_REG_CTIMER_OUTCFG0_CFG5_A7OUT2            0x00070000
#define AM_REG_CTIMER_OUTCFG0_CFG5_A6OUT2            0x00060000
#define AM_REG_CTIMER_OUTCFG0_CFG5_A7OUT             0x00050000
#define AM_REG_CTIMER_OUTCFG0_CFG5_B6OUT             0x00040000
#define AM_REG_CTIMER_OUTCFG0_CFG5_A1OUT             0x00030000
#define AM_REG_CTIMER_OUTCFG0_CFG5_A1OUT2            0x00020000
#define AM_REG_CTIMER_OUTCFG0_CFG5_ONE               0x00010000
#define AM_REG_CTIMER_OUTCFG0_CFG5_ZERO              0x00000000

// Pad output 4 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG4_S                 12
#define AM_REG_CTIMER_OUTCFG0_CFG4_M                 0x00007000
#define AM_REG_CTIMER_OUTCFG0_CFG4(n)                (((uint32_t)(n) << 12) & 0x00007000)
#define AM_REG_CTIMER_OUTCFG0_CFG4_A7OUT2            0x00007000
#define AM_REG_CTIMER_OUTCFG0_CFG4_A6OUT2            0x00006000
#define AM_REG_CTIMER_OUTCFG0_CFG4_B5OUT             0x00005000
#define AM_REG_CTIMER_OUTCFG0_CFG4_A5OUT2            0x00004000
#define AM_REG_CTIMER_OUTCFG0_CFG4_A2OUT2            0x00003000
#define AM_REG_CTIMER_OUTCFG0_CFG4_A1OUT             0x00002000
#define AM_REG_CTIMER_OUTCFG0_CFG4_ONE               0x00001000
#define AM_REG_CTIMER_OUTCFG0_CFG4_ZERO              0x00000000

// Pad output 3 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG3_S                 9
#define AM_REG_CTIMER_OUTCFG0_CFG3_M                 0x00000E00
#define AM_REG_CTIMER_OUTCFG0_CFG3(n)                (((uint32_t)(n) << 9) & 0x00000E00)
#define AM_REG_CTIMER_OUTCFG0_CFG3_A7OUT2            0x00000E00
#define AM_REG_CTIMER_OUTCFG0_CFG3_A6OUT2            0x00000C00
#define AM_REG_CTIMER_OUTCFG0_CFG3_A6OUT             0x00000A00
#define AM_REG_CTIMER_OUTCFG0_CFG3_A1OUT             0x00000800
#define AM_REG_CTIMER_OUTCFG0_CFG3_B0OUT             0x00000600
#define AM_REG_CTIMER_OUTCFG0_CFG3_B0OUT2            0x00000400
#define AM_REG_CTIMER_OUTCFG0_CFG3_ONE               0x00000200
#define AM_REG_CTIMER_OUTCFG0_CFG3_ZERO              0x00000000

// Pad output 2 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG2_S                 6
#define AM_REG_CTIMER_OUTCFG0_CFG2_M                 0x000001C0
#define AM_REG_CTIMER_OUTCFG0_CFG2(n)                (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_OUTCFG0_CFG2_A7OUT2            0x000001C0
#define AM_REG_CTIMER_OUTCFG0_CFG2_A6OUT2            0x00000180
#define AM_REG_CTIMER_OUTCFG0_CFG2_A7OUT             0x00000140
#define AM_REG_CTIMER_OUTCFG0_CFG2_B6OUT2            0x00000100
#define AM_REG_CTIMER_OUTCFG0_CFG2_B1OUT2            0x000000C0
#define AM_REG_CTIMER_OUTCFG0_CFG2_B0OUT             0x00000080
#define AM_REG_CTIMER_OUTCFG0_CFG2_ONE               0x00000040
#define AM_REG_CTIMER_OUTCFG0_CFG2_ZERO              0x00000000

// Pad output 1 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG1_S                 3
#define AM_REG_CTIMER_OUTCFG0_CFG1_M                 0x00000038
#define AM_REG_CTIMER_OUTCFG0_CFG1(n)                (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_CTIMER_OUTCFG0_CFG1_A7OUT2            0x00000038
#define AM_REG_CTIMER_OUTCFG0_CFG1_A6OUT2            0x00000030
#define AM_REG_CTIMER_OUTCFG0_CFG1_B7OUT2            0x00000028
#define AM_REG_CTIMER_OUTCFG0_CFG1_A5OUT             0x00000020
#define AM_REG_CTIMER_OUTCFG0_CFG1_A0OUT             0x00000018
#define AM_REG_CTIMER_OUTCFG0_CFG1_A0OUT2            0x00000010
#define AM_REG_CTIMER_OUTCFG0_CFG1_ONE               0x00000008
#define AM_REG_CTIMER_OUTCFG0_CFG1_ZERO              0x00000000

// Pad output 0 configuration
#define AM_REG_CTIMER_OUTCFG0_CFG0_S                 0
#define AM_REG_CTIMER_OUTCFG0_CFG0_M                 0x00000007
#define AM_REG_CTIMER_OUTCFG0_CFG0(n)                (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_CTIMER_OUTCFG0_CFG0_A7OUT2            0x00000007
#define AM_REG_CTIMER_OUTCFG0_CFG0_A6OUT2            0x00000006
#define AM_REG_CTIMER_OUTCFG0_CFG0_A6OUT             0x00000005
#define AM_REG_CTIMER_OUTCFG0_CFG0_A5OUT2            0x00000004
#define AM_REG_CTIMER_OUTCFG0_CFG0_B2OUT2            0x00000003
#define AM_REG_CTIMER_OUTCFG0_CFG0_A0OUT             0x00000002
#define AM_REG_CTIMER_OUTCFG0_CFG0_ONE               0x00000001
#define AM_REG_CTIMER_OUTCFG0_CFG0_ZERO              0x00000000

//*****************************************************************************
//
// CTIMER_OUTCFG1 - Counter/Timer Output Config 1
//
//*****************************************************************************
// Pad output 19 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG19_S                28
#define AM_REG_CTIMER_OUTCFG1_CFG19_M                0x70000000
#define AM_REG_CTIMER_OUTCFG1_CFG19(n)               (((uint32_t)(n) << 28) & 0x70000000)
#define AM_REG_CTIMER_OUTCFG1_CFG19_A7OUT2           0x70000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_A6OUT2           0x60000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_B1OUT2           0x50000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_B4OUT            0x40000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_A2OUT            0x30000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_B4OUT2           0x20000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_ONE              0x10000000
#define AM_REG_CTIMER_OUTCFG1_CFG19_ZERO             0x00000000

// Pad output 18 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG18_S                25
#define AM_REG_CTIMER_OUTCFG1_CFG18_M                0x0E000000
#define AM_REG_CTIMER_OUTCFG1_CFG18(n)               (((uint32_t)(n) << 25) & 0x0E000000)
#define AM_REG_CTIMER_OUTCFG1_CFG18_A7OUT2           0x0E000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_A6OUT2           0x0C000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_A3OUT2           0x0A000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_A0OUT            0x08000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_B0OUT            0x06000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_B4OUT            0x04000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_ONE              0x02000000
#define AM_REG_CTIMER_OUTCFG1_CFG18_ZERO             0x00000000

// Pad output 17 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG17_S                22
#define AM_REG_CTIMER_OUTCFG1_CFG17_M                0x01C00000
#define AM_REG_CTIMER_OUTCFG1_CFG17(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_OUTCFG1_CFG17_A7OUT2           0x01C00000
#define AM_REG_CTIMER_OUTCFG1_CFG17_A6OUT2           0x01800000
#define AM_REG_CTIMER_OUTCFG1_CFG17_A1OUT2           0x01400000
#define AM_REG_CTIMER_OUTCFG1_CFG17_A4OUT            0x01000000
#define AM_REG_CTIMER_OUTCFG1_CFG17_B7OUT            0x00C00000
#define AM_REG_CTIMER_OUTCFG1_CFG17_A4OUT2           0x00800000
#define AM_REG_CTIMER_OUTCFG1_CFG17_ONE              0x00400000
#define AM_REG_CTIMER_OUTCFG1_CFG17_ZERO             0x00000000

// Pad output 16 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG16_S                19
#define AM_REG_CTIMER_OUTCFG1_CFG16_M                0x00380000
#define AM_REG_CTIMER_OUTCFG1_CFG16(n)               (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_CTIMER_OUTCFG1_CFG16_A7OUT2           0x00380000
#define AM_REG_CTIMER_OUTCFG1_CFG16_A6OUT2           0x00300000
#define AM_REG_CTIMER_OUTCFG1_CFG16_B3OUT2           0x00280000
#define AM_REG_CTIMER_OUTCFG1_CFG16_A0OUT2           0x00200000
#define AM_REG_CTIMER_OUTCFG1_CFG16_A0OUT            0x00180000
#define AM_REG_CTIMER_OUTCFG1_CFG16_A4OUT            0x00100000
#define AM_REG_CTIMER_OUTCFG1_CFG16_ONE              0x00080000
#define AM_REG_CTIMER_OUTCFG1_CFG16_ZERO             0x00000000

// Pad output 15 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG15_S                16
#define AM_REG_CTIMER_OUTCFG1_CFG15_M                0x00070000
#define AM_REG_CTIMER_OUTCFG1_CFG15(n)               (((uint32_t)(n) << 16) & 0x00070000)
#define AM_REG_CTIMER_OUTCFG1_CFG15_A7OUT2           0x00070000
#define AM_REG_CTIMER_OUTCFG1_CFG15_A6OUT2           0x00060000
#define AM_REG_CTIMER_OUTCFG1_CFG15_A4OUT2           0x00050000
#define AM_REG_CTIMER_OUTCFG1_CFG15_A7OUT            0x00040000
#define AM_REG_CTIMER_OUTCFG1_CFG15_B3OUT            0x00030000
#define AM_REG_CTIMER_OUTCFG1_CFG15_B3OUT2           0x00020000
#define AM_REG_CTIMER_OUTCFG1_CFG15_ONE              0x00010000
#define AM_REG_CTIMER_OUTCFG1_CFG15_ZERO             0x00000000

// Pad output 14 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG14_S                12
#define AM_REG_CTIMER_OUTCFG1_CFG14_M                0x00007000
#define AM_REG_CTIMER_OUTCFG1_CFG14(n)               (((uint32_t)(n) << 12) & 0x00007000)
#define AM_REG_CTIMER_OUTCFG1_CFG14_A7OUT2           0x00007000
#define AM_REG_CTIMER_OUTCFG1_CFG14_A6OUT2           0x00006000
#define AM_REG_CTIMER_OUTCFG1_CFG14_A7OUT            0x00005000
#define AM_REG_CTIMER_OUTCFG1_CFG14_B7OUT2           0x00004000
#define AM_REG_CTIMER_OUTCFG1_CFG14_B1OUT            0x00003000
#define AM_REG_CTIMER_OUTCFG1_CFG14_B3OUT            0x00002000
#define AM_REG_CTIMER_OUTCFG1_CFG14_ONE              0x00001000
#define AM_REG_CTIMER_OUTCFG1_CFG14_ZERO             0x00000000

// Pad output 13 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG13_S                9
#define AM_REG_CTIMER_OUTCFG1_CFG13_M                0x00000E00
#define AM_REG_CTIMER_OUTCFG1_CFG13(n)               (((uint32_t)(n) << 9) & 0x00000E00)
#define AM_REG_CTIMER_OUTCFG1_CFG13_A7OUT2           0x00000E00
#define AM_REG_CTIMER_OUTCFG1_CFG13_A6OUT2           0x00000C00
#define AM_REG_CTIMER_OUTCFG1_CFG13_B4OUT2           0x00000A00
#define AM_REG_CTIMER_OUTCFG1_CFG13_A6OUT            0x00000800
#define AM_REG_CTIMER_OUTCFG1_CFG13_A3OUT            0x00000600
#define AM_REG_CTIMER_OUTCFG1_CFG13_A3OUT2           0x00000400
#define AM_REG_CTIMER_OUTCFG1_CFG13_ONE              0x00000200
#define AM_REG_CTIMER_OUTCFG1_CFG13_ZERO             0x00000000

// Pad output 12 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG12_S                6
#define AM_REG_CTIMER_OUTCFG1_CFG12_M                0x000001C0
#define AM_REG_CTIMER_OUTCFG1_CFG12(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_OUTCFG1_CFG12_A7OUT2           0x000001C0
#define AM_REG_CTIMER_OUTCFG1_CFG12_A6OUT2           0x00000180
#define AM_REG_CTIMER_OUTCFG1_CFG12_B6OUT2           0x00000140
#define AM_REG_CTIMER_OUTCFG1_CFG12_B0OUT2           0x00000100
#define AM_REG_CTIMER_OUTCFG1_CFG12_B1OUT            0x000000C0
#define AM_REG_CTIMER_OUTCFG1_CFG12_A3OUT            0x00000080
#define AM_REG_CTIMER_OUTCFG1_CFG12_ONE              0x00000040
#define AM_REG_CTIMER_OUTCFG1_CFG12_ZERO             0x00000000

// Pad output 11 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG11_S                3
#define AM_REG_CTIMER_OUTCFG1_CFG11_M                0x00000038
#define AM_REG_CTIMER_OUTCFG1_CFG11(n)               (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_CTIMER_OUTCFG1_CFG11_A7OUT2           0x00000038
#define AM_REG_CTIMER_OUTCFG1_CFG11_A6OUT2           0x00000030
#define AM_REG_CTIMER_OUTCFG1_CFG11_B5OUT2           0x00000028
#define AM_REG_CTIMER_OUTCFG1_CFG11_B4OUT            0x00000020
#define AM_REG_CTIMER_OUTCFG1_CFG11_B2OUT            0x00000018
#define AM_REG_CTIMER_OUTCFG1_CFG11_B2OUT2           0x00000010
#define AM_REG_CTIMER_OUTCFG1_CFG11_ONE              0x00000008
#define AM_REG_CTIMER_OUTCFG1_CFG11_ZERO             0x00000000

// Pad output 10 configuration
#define AM_REG_CTIMER_OUTCFG1_CFG10_S                0
#define AM_REG_CTIMER_OUTCFG1_CFG10_M                0x00000007
#define AM_REG_CTIMER_OUTCFG1_CFG10(n)               (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_CTIMER_OUTCFG1_CFG10_A7OUT2           0x00000007
#define AM_REG_CTIMER_OUTCFG1_CFG10_A6OUT2           0x00000006
#define AM_REG_CTIMER_OUTCFG1_CFG10_A6OUT            0x00000005
#define AM_REG_CTIMER_OUTCFG1_CFG10_B4OUT2           0x00000004
#define AM_REG_CTIMER_OUTCFG1_CFG10_B3OUT2           0x00000003
#define AM_REG_CTIMER_OUTCFG1_CFG10_B2OUT            0x00000002
#define AM_REG_CTIMER_OUTCFG1_CFG10_ONE              0x00000001
#define AM_REG_CTIMER_OUTCFG1_CFG10_ZERO             0x00000000

//*****************************************************************************
//
// CTIMER_OUTCFG2 - Counter/Timer Output Config 2
//
//*****************************************************************************
// Pad output 29 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG29_S                28
#define AM_REG_CTIMER_OUTCFG2_CFG29_M                0x70000000
#define AM_REG_CTIMER_OUTCFG2_CFG29(n)               (((uint32_t)(n) << 28) & 0x70000000)
#define AM_REG_CTIMER_OUTCFG2_CFG29_A7OUT2           0x70000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_A6OUT2           0x60000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_A3OUT2           0x50000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_A7OUT            0x40000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_A1OUT            0x30000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_B5OUT2           0x20000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_ONE              0x10000000
#define AM_REG_CTIMER_OUTCFG2_CFG29_ZERO             0x00000000

// Pad output 28 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG28_S                25
#define AM_REG_CTIMER_OUTCFG2_CFG28_M                0x0E000000
#define AM_REG_CTIMER_OUTCFG2_CFG28(n)               (((uint32_t)(n) << 25) & 0x0E000000)
#define AM_REG_CTIMER_OUTCFG2_CFG28_A7OUT2           0x0E000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_A6OUT2           0x0C000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_B0OUT2           0x0A000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_A5OUT2           0x08000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_A3OUT            0x06000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_A7OUT            0x04000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_ONE              0x02000000
#define AM_REG_CTIMER_OUTCFG2_CFG28_ZERO             0x00000000

// Pad output 27 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG27_S                22
#define AM_REG_CTIMER_OUTCFG2_CFG27_M                0x01C00000
#define AM_REG_CTIMER_OUTCFG2_CFG27(n)               (((uint32_t)(n) << 22) & 0x01C00000)
#define AM_REG_CTIMER_OUTCFG2_CFG27_A7OUT2           0x01C00000
#define AM_REG_CTIMER_OUTCFG2_CFG27_A6OUT2           0x01800000
#define AM_REG_CTIMER_OUTCFG2_CFG27_B2OUT2           0x01400000
#define AM_REG_CTIMER_OUTCFG2_CFG27_B6OUT            0x01000000
#define AM_REG_CTIMER_OUTCFG2_CFG27_A1OUT            0x00C00000
#define AM_REG_CTIMER_OUTCFG2_CFG27_B6OUT2           0x00800000
#define AM_REG_CTIMER_OUTCFG2_CFG27_ONE              0x00400000
#define AM_REG_CTIMER_OUTCFG2_CFG27_ZERO             0x00000000

// Pad output 26 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG26_S                19
#define AM_REG_CTIMER_OUTCFG2_CFG26_M                0x00380000
#define AM_REG_CTIMER_OUTCFG2_CFG26(n)               (((uint32_t)(n) << 19) & 0x00380000)
#define AM_REG_CTIMER_OUTCFG2_CFG26_A7OUT2           0x00380000
#define AM_REG_CTIMER_OUTCFG2_CFG26_A6OUT2           0x00300000
#define AM_REG_CTIMER_OUTCFG2_CFG26_A1OUT2           0x00280000
#define AM_REG_CTIMER_OUTCFG2_CFG26_A5OUT            0x00200000
#define AM_REG_CTIMER_OUTCFG2_CFG26_B2OUT            0x00180000
#define AM_REG_CTIMER_OUTCFG2_CFG26_B6OUT            0x00100000
#define AM_REG_CTIMER_OUTCFG2_CFG26_ONE              0x00080000
#define AM_REG_CTIMER_OUTCFG2_CFG26_ZERO             0x00000000

// Pad output 25 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG25_S                16
#define AM_REG_CTIMER_OUTCFG2_CFG25_M                0x00070000
#define AM_REG_CTIMER_OUTCFG2_CFG25(n)               (((uint32_t)(n) << 16) & 0x00070000)
#define AM_REG_CTIMER_OUTCFG2_CFG25_A7OUT2           0x00070000
#define AM_REG_CTIMER_OUTCFG2_CFG25_A6OUT2           0x00060000
#define AM_REG_CTIMER_OUTCFG2_CFG25_A2OUT2           0x00050000
#define AM_REG_CTIMER_OUTCFG2_CFG25_A6OUT            0x00040000
#define AM_REG_CTIMER_OUTCFG2_CFG25_B2OUT            0x00030000
#define AM_REG_CTIMER_OUTCFG2_CFG25_B4OUT2           0x00020000
#define AM_REG_CTIMER_OUTCFG2_CFG25_ONE              0x00010000
#define AM_REG_CTIMER_OUTCFG2_CFG25_ZERO             0x00000000

// Pad output 24 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG24_S                12
#define AM_REG_CTIMER_OUTCFG2_CFG24_M                0x00007000
#define AM_REG_CTIMER_OUTCFG2_CFG24(n)               (((uint32_t)(n) << 12) & 0x00007000)
#define AM_REG_CTIMER_OUTCFG2_CFG24_A7OUT2           0x00007000
#define AM_REG_CTIMER_OUTCFG2_CFG24_A6OUT2           0x00006000
#define AM_REG_CTIMER_OUTCFG2_CFG24_B1OUT2           0x00005000
#define AM_REG_CTIMER_OUTCFG2_CFG24_A1OUT            0x00004000
#define AM_REG_CTIMER_OUTCFG2_CFG24_A2OUT            0x00003000
#define AM_REG_CTIMER_OUTCFG2_CFG24_A6OUT            0x00002000
#define AM_REG_CTIMER_OUTCFG2_CFG24_ONE              0x00001000
#define AM_REG_CTIMER_OUTCFG2_CFG24_ZERO             0x00000000

// Pad output 23 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG23_S                9
#define AM_REG_CTIMER_OUTCFG2_CFG23_M                0x00000E00
#define AM_REG_CTIMER_OUTCFG2_CFG23(n)               (((uint32_t)(n) << 9) & 0x00000E00)
#define AM_REG_CTIMER_OUTCFG2_CFG23_A7OUT2           0x00000E00
#define AM_REG_CTIMER_OUTCFG2_CFG23_A6OUT2           0x00000C00
#define AM_REG_CTIMER_OUTCFG2_CFG23_B0OUT2           0x00000A00
#define AM_REG_CTIMER_OUTCFG2_CFG23_A5OUT            0x00000800
#define AM_REG_CTIMER_OUTCFG2_CFG23_A7OUT            0x00000600
#define AM_REG_CTIMER_OUTCFG2_CFG23_B5OUT2           0x00000400
#define AM_REG_CTIMER_OUTCFG2_CFG23_ONE              0x00000200
#define AM_REG_CTIMER_OUTCFG2_CFG23_ZERO             0x00000000

// Pad output 22 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG22_S                6
#define AM_REG_CTIMER_OUTCFG2_CFG22_M                0x000001C0
#define AM_REG_CTIMER_OUTCFG2_CFG22(n)               (((uint32_t)(n) << 6) & 0x000001C0)
#define AM_REG_CTIMER_OUTCFG2_CFG22_A7OUT2           0x000001C0
#define AM_REG_CTIMER_OUTCFG2_CFG22_A6OUT2           0x00000180
#define AM_REG_CTIMER_OUTCFG2_CFG22_A2OUT2           0x00000140
#define AM_REG_CTIMER_OUTCFG2_CFG22_A1OUT            0x00000100
#define AM_REG_CTIMER_OUTCFG2_CFG22_A6OUT            0x000000C0
#define AM_REG_CTIMER_OUTCFG2_CFG22_B5OUT            0x00000080
#define AM_REG_CTIMER_OUTCFG2_CFG22_ONE              0x00000040
#define AM_REG_CTIMER_OUTCFG2_CFG22_ZERO             0x00000000

// Pad output 21 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG21_S                3
#define AM_REG_CTIMER_OUTCFG2_CFG21_M                0x00000038
#define AM_REG_CTIMER_OUTCFG2_CFG21(n)               (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_CTIMER_OUTCFG2_CFG21_A7OUT2           0x00000038
#define AM_REG_CTIMER_OUTCFG2_CFG21_A6OUT2           0x00000030
#define AM_REG_CTIMER_OUTCFG2_CFG21_A0OUT2           0x00000028
#define AM_REG_CTIMER_OUTCFG2_CFG21_B5OUT            0x00000020
#define AM_REG_CTIMER_OUTCFG2_CFG21_A1OUT            0x00000018
#define AM_REG_CTIMER_OUTCFG2_CFG21_A5OUT2           0x00000010
#define AM_REG_CTIMER_OUTCFG2_CFG21_ONE              0x00000008
#define AM_REG_CTIMER_OUTCFG2_CFG21_ZERO             0x00000000

// Pad output 20 configuration
#define AM_REG_CTIMER_OUTCFG2_CFG20_S                0
#define AM_REG_CTIMER_OUTCFG2_CFG20_M                0x00000007
#define AM_REG_CTIMER_OUTCFG2_CFG20(n)               (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_CTIMER_OUTCFG2_CFG20_A7OUT2           0x00000007
#define AM_REG_CTIMER_OUTCFG2_CFG20_A6OUT2           0x00000006
#define AM_REG_CTIMER_OUTCFG2_CFG20_B2OUT2           0x00000005
#define AM_REG_CTIMER_OUTCFG2_CFG20_A1OUT2           0x00000004
#define AM_REG_CTIMER_OUTCFG2_CFG20_A1OUT            0x00000003
#define AM_REG_CTIMER_OUTCFG2_CFG20_A5OUT            0x00000002
#define AM_REG_CTIMER_OUTCFG2_CFG20_ONE              0x00000001
#define AM_REG_CTIMER_OUTCFG2_CFG20_ZERO             0x00000000

//*****************************************************************************
//
// CTIMER_OUTCFG3 - Counter/Timer Output Config 3
//
//*****************************************************************************
// Pad output 31 configuration
#define AM_REG_CTIMER_OUTCFG3_CFG31_S                3
#define AM_REG_CTIMER_OUTCFG3_CFG31_M                0x00000038
#define AM_REG_CTIMER_OUTCFG3_CFG31(n)               (((uint32_t)(n) << 3) & 0x00000038)
#define AM_REG_CTIMER_OUTCFG3_CFG31_A7OUT2           0x00000038
#define AM_REG_CTIMER_OUTCFG3_CFG31_A6OUT2           0x00000030
#define AM_REG_CTIMER_OUTCFG3_CFG31_B3OUT2           0x00000028
#define AM_REG_CTIMER_OUTCFG3_CFG31_B7OUT            0x00000020
#define AM_REG_CTIMER_OUTCFG3_CFG31_A6OUT            0x00000018
#define AM_REG_CTIMER_OUTCFG3_CFG31_B7OUT2           0x00000010
#define AM_REG_CTIMER_OUTCFG3_CFG31_ONE              0x00000008
#define AM_REG_CTIMER_OUTCFG3_CFG31_ZERO             0x00000000

// Pad output 30 configuration
#define AM_REG_CTIMER_OUTCFG3_CFG30_S                0
#define AM_REG_CTIMER_OUTCFG3_CFG30_M                0x00000007
#define AM_REG_CTIMER_OUTCFG3_CFG30(n)               (((uint32_t)(n) << 0) & 0x00000007)
#define AM_REG_CTIMER_OUTCFG3_CFG30_A7OUT2           0x00000007
#define AM_REG_CTIMER_OUTCFG3_CFG30_A6OUT2           0x00000006
#define AM_REG_CTIMER_OUTCFG3_CFG30_A0OUT2           0x00000005
#define AM_REG_CTIMER_OUTCFG3_CFG30_A4OUT2           0x00000004
#define AM_REG_CTIMER_OUTCFG3_CFG30_B3OUT            0x00000003
#define AM_REG_CTIMER_OUTCFG3_CFG30_B7OUT            0x00000002
#define AM_REG_CTIMER_OUTCFG3_CFG30_ONE              0x00000001
#define AM_REG_CTIMER_OUTCFG3_CFG30_ZERO             0x00000000

//*****************************************************************************
//
// CTIMER_INCFG - Counter/Timer Input Config
//
//*****************************************************************************
// CTIMER B7 input configuration
#define AM_REG_CTIMER_INCFG_CFGB7_S                  15
#define AM_REG_CTIMER_INCFG_CFGB7_M                  0x00008000
#define AM_REG_CTIMER_INCFG_CFGB7(n)                 (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_CTIMER_INCFG_CFGB7_CT31               0x00008000
#define AM_REG_CTIMER_INCFG_CFGB7_CT30               0x00000000

// CTIMER A7 input configuration
#define AM_REG_CTIMER_INCFG_CFGA7_S                  14
#define AM_REG_CTIMER_INCFG_CFGA7_M                  0x00004000
#define AM_REG_CTIMER_INCFG_CFGA7(n)                 (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_INCFG_CFGA7_CT29               0x00004000
#define AM_REG_CTIMER_INCFG_CFGA7_CT28               0x00000000

// CTIMER B6 input configuration
#define AM_REG_CTIMER_INCFG_CFGB6_S                  13
#define AM_REG_CTIMER_INCFG_CFGB6_M                  0x00002000
#define AM_REG_CTIMER_INCFG_CFGB6(n)                 (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_INCFG_CFGB6_CT27               0x00002000
#define AM_REG_CTIMER_INCFG_CFGB6_CT26               0x00000000

// CTIMER A6 input configuration
#define AM_REG_CTIMER_INCFG_CFGA6_S                  12
#define AM_REG_CTIMER_INCFG_CFGA6_M                  0x00001000
#define AM_REG_CTIMER_INCFG_CFGA6(n)                 (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_INCFG_CFGA6_CT25               0x00001000
#define AM_REG_CTIMER_INCFG_CFGA6_CT24               0x00000000

// CTIMER B5 input configuration
#define AM_REG_CTIMER_INCFG_CFGB5_S                  11
#define AM_REG_CTIMER_INCFG_CFGB5_M                  0x00000800
#define AM_REG_CTIMER_INCFG_CFGB5(n)                 (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_INCFG_CFGB5_CT23               0x00000800
#define AM_REG_CTIMER_INCFG_CFGB5_CT22               0x00000000

// CTIMER A5 input configuration
#define AM_REG_CTIMER_INCFG_CFGA5_S                  10
#define AM_REG_CTIMER_INCFG_CFGA5_M                  0x00000400
#define AM_REG_CTIMER_INCFG_CFGA5(n)                 (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_INCFG_CFGA5_CT21               0x00000400
#define AM_REG_CTIMER_INCFG_CFGA5_CT20               0x00000000

// CTIMER B4 input configuration
#define AM_REG_CTIMER_INCFG_CFGB4_S                  9
#define AM_REG_CTIMER_INCFG_CFGB4_M                  0x00000200
#define AM_REG_CTIMER_INCFG_CFGB4(n)                 (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_INCFG_CFGB4_CT19               0x00000200
#define AM_REG_CTIMER_INCFG_CFGB4_CT18               0x00000000

// CTIMER A4 input configuration
#define AM_REG_CTIMER_INCFG_CFGA4_S                  8
#define AM_REG_CTIMER_INCFG_CFGA4_M                  0x00000100
#define AM_REG_CTIMER_INCFG_CFGA4(n)                 (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_INCFG_CFGA4_CT17               0x00000100
#define AM_REG_CTIMER_INCFG_CFGA4_CT16               0x00000000

// CTIMER B3 input configuration
#define AM_REG_CTIMER_INCFG_CFGB3_S                  7
#define AM_REG_CTIMER_INCFG_CFGB3_M                  0x00000080
#define AM_REG_CTIMER_INCFG_CFGB3(n)                 (((uint32_t)(n) << 7) & 0x00000080)
#define AM_REG_CTIMER_INCFG_CFGB3_CT15               0x00000080
#define AM_REG_CTIMER_INCFG_CFGB3_CT14               0x00000000

// CTIMER A3 input configuration
#define AM_REG_CTIMER_INCFG_CFGA3_S                  6
#define AM_REG_CTIMER_INCFG_CFGA3_M                  0x00000040
#define AM_REG_CTIMER_INCFG_CFGA3(n)                 (((uint32_t)(n) << 6) & 0x00000040)
#define AM_REG_CTIMER_INCFG_CFGA3_CT13               0x00000040
#define AM_REG_CTIMER_INCFG_CFGA3_CT12               0x00000000

// CTIMER B2 input configuration
#define AM_REG_CTIMER_INCFG_CFGB2_S                  5
#define AM_REG_CTIMER_INCFG_CFGB2_M                  0x00000020
#define AM_REG_CTIMER_INCFG_CFGB2(n)                 (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_CTIMER_INCFG_CFGB2_CT11               0x00000020
#define AM_REG_CTIMER_INCFG_CFGB2_CT10               0x00000000

// CTIMER A2 input configuration
#define AM_REG_CTIMER_INCFG_CFGA2_S                  4
#define AM_REG_CTIMER_INCFG_CFGA2_M                  0x00000010
#define AM_REG_CTIMER_INCFG_CFGA2(n)                 (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_CTIMER_INCFG_CFGA2_CT9                0x00000010
#define AM_REG_CTIMER_INCFG_CFGA2_CT8                0x00000000

// CTIMER B1 input configuration
#define AM_REG_CTIMER_INCFG_CFGB1_S                  3
#define AM_REG_CTIMER_INCFG_CFGB1_M                  0x00000008
#define AM_REG_CTIMER_INCFG_CFGB1(n)                 (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_INCFG_CFGB1_CT7                0x00000008
#define AM_REG_CTIMER_INCFG_CFGB1_CT6                0x00000000

// CTIMER A1 input configuration
#define AM_REG_CTIMER_INCFG_CFGA1_S                  2
#define AM_REG_CTIMER_INCFG_CFGA1_M                  0x00000004
#define AM_REG_CTIMER_INCFG_CFGA1(n)                 (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_INCFG_CFGA1_CT5                0x00000004
#define AM_REG_CTIMER_INCFG_CFGA1_CT4                0x00000000

// CTIMER B0 input configuration
#define AM_REG_CTIMER_INCFG_CFGB0_S                  1
#define AM_REG_CTIMER_INCFG_CFGB0_M                  0x00000002
#define AM_REG_CTIMER_INCFG_CFGB0(n)                 (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_INCFG_CFGB0_CT3                0x00000002
#define AM_REG_CTIMER_INCFG_CFGB0_CT2                0x00000000

// CTIMER A0 input configuration
#define AM_REG_CTIMER_INCFG_CFGA0_S                  0
#define AM_REG_CTIMER_INCFG_CFGA0_M                  0x00000001
#define AM_REG_CTIMER_INCFG_CFGA0(n)                 (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_INCFG_CFGA0_CT1                0x00000001
#define AM_REG_CTIMER_INCFG_CFGA0_CT0                0x00000000

//*****************************************************************************
//
// CTIMER_STCFG - Configuration Register
//
//*****************************************************************************
// Set this bit to one to freeze the clock input to the COUNTER register. Once
// frozen, the value can be safely written from the MCU.  Unfreeze to resume.
#define AM_REG_CTIMER_STCFG_FREEZE_S                 31
#define AM_REG_CTIMER_STCFG_FREEZE_M                 0x80000000
#define AM_REG_CTIMER_STCFG_FREEZE(n)                (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_CTIMER_STCFG_FREEZE_THAW              0x00000000
#define AM_REG_CTIMER_STCFG_FREEZE_FREEZE            0x80000000

// Set this bit to one to clear the System Timer register.  If this bit is set
// to '1', the system timer register will stay cleared.  It needs to be set to
// '0' for the system timer to start running.
#define AM_REG_CTIMER_STCFG_CLEAR_S                  30
#define AM_REG_CTIMER_STCFG_CLEAR_M                  0x40000000
#define AM_REG_CTIMER_STCFG_CLEAR(n)                 (((uint32_t)(n) << 30) & 0x40000000)
#define AM_REG_CTIMER_STCFG_CLEAR_RUN                0x00000000
#define AM_REG_CTIMER_STCFG_CLEAR_CLEAR              0x40000000

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_H_EN_S           15
#define AM_REG_CTIMER_STCFG_COMPARE_H_EN_M           0x00008000
#define AM_REG_CTIMER_STCFG_COMPARE_H_EN(n)          (((uint32_t)(n) << 15) & 0x00008000)
#define AM_REG_CTIMER_STCFG_COMPARE_H_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_H_EN_ENABLE      0x00008000

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_G_EN_S           14
#define AM_REG_CTIMER_STCFG_COMPARE_G_EN_M           0x00004000
#define AM_REG_CTIMER_STCFG_COMPARE_G_EN(n)          (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_CTIMER_STCFG_COMPARE_G_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_G_EN_ENABLE      0x00004000

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_F_EN_S           13
#define AM_REG_CTIMER_STCFG_COMPARE_F_EN_M           0x00002000
#define AM_REG_CTIMER_STCFG_COMPARE_F_EN(n)          (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_CTIMER_STCFG_COMPARE_F_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_F_EN_ENABLE      0x00002000

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_E_EN_S           12
#define AM_REG_CTIMER_STCFG_COMPARE_E_EN_M           0x00001000
#define AM_REG_CTIMER_STCFG_COMPARE_E_EN(n)          (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_CTIMER_STCFG_COMPARE_E_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_E_EN_ENABLE      0x00001000

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_D_EN_S           11
#define AM_REG_CTIMER_STCFG_COMPARE_D_EN_M           0x00000800
#define AM_REG_CTIMER_STCFG_COMPARE_D_EN(n)          (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_CTIMER_STCFG_COMPARE_D_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_D_EN_ENABLE      0x00000800

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_C_EN_S           10
#define AM_REG_CTIMER_STCFG_COMPARE_C_EN_M           0x00000400
#define AM_REG_CTIMER_STCFG_COMPARE_C_EN(n)          (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_CTIMER_STCFG_COMPARE_C_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_C_EN_ENABLE      0x00000400

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_B_EN_S           9
#define AM_REG_CTIMER_STCFG_COMPARE_B_EN_M           0x00000200
#define AM_REG_CTIMER_STCFG_COMPARE_B_EN(n)          (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_CTIMER_STCFG_COMPARE_B_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_B_EN_ENABLE      0x00000200

// Selects whether compare is enabled for the corresponding SCMPR register. If
// compare is enabled, the interrupt status is set once the comparision is met.
#define AM_REG_CTIMER_STCFG_COMPARE_A_EN_S           8
#define AM_REG_CTIMER_STCFG_COMPARE_A_EN_M           0x00000100
#define AM_REG_CTIMER_STCFG_COMPARE_A_EN(n)          (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_CTIMER_STCFG_COMPARE_A_EN_DISABLE     0x00000000
#define AM_REG_CTIMER_STCFG_COMPARE_A_EN_ENABLE      0x00000100

// Selects an appropriate clock source and divider to use for the System Timer
// clock.
#define AM_REG_CTIMER_STCFG_CLKSEL_S                 0
#define AM_REG_CTIMER_STCFG_CLKSEL_M                 0x0000000F
#define AM_REG_CTIMER_STCFG_CLKSEL(n)                (((uint32_t)(n) << 0) & 0x0000000F)
#define AM_REG_CTIMER_STCFG_CLKSEL_NOCLK             0x00000000
#define AM_REG_CTIMER_STCFG_CLKSEL_HFRC_DIV16        0x00000001
#define AM_REG_CTIMER_STCFG_CLKSEL_HFRC_DIV256       0x00000002
#define AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV1         0x00000003
#define AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV2         0x00000004
#define AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV32        0x00000005
#define AM_REG_CTIMER_STCFG_CLKSEL_LFRC_DIV1         0x00000006
#define AM_REG_CTIMER_STCFG_CLKSEL_CTIMER0A          0x00000007
#define AM_REG_CTIMER_STCFG_CLKSEL_CTIMER0B          0x00000008

//*****************************************************************************
//
// CTIMER_STTMR - System Timer Count Register (Real Time Counter)
//
//*****************************************************************************
// Value of the 32-bit counter as it ticks over.
#define AM_REG_CTIMER_STTMR_STTMR_S                  0
#define AM_REG_CTIMER_STTMR_STTMR_M                  0xFFFFFFFF
#define AM_REG_CTIMER_STTMR_STTMR(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_CAPTURECONTROL - Capture Control Register
//
//*****************************************************************************
// Selects whether capture is enabled for the specified capture register.
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE3_S      3
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE3_M      0x00000008
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE3(n)     (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE3_DISABLE 0x00000000
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE3_ENABLE 0x00000008

// Selects whether capture is enabled for the specified capture register.
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE2_S      2
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE2_M      0x00000004
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE2(n)     (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE2_DISABLE 0x00000000
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE2_ENABLE 0x00000004

// Selects whether capture is enabled for the specified capture register.
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE1_S      1
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE1_M      0x00000002
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE1(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE1_DISABLE 0x00000000
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE1_ENABLE 0x00000002

// Selects whether capture is enabled for the specified capture register.
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE0_S      0
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE0_M      0x00000001
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE0(n)     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE0_DISABLE 0x00000000
#define AM_REG_CTIMER_CAPTURECONTROL_CAPTURE0_ENABLE 0x00000001

//*****************************************************************************
//
// CTIMER_SCMPR0 - Compare Register A
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_A_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR0_SCMPR0_S                0
#define AM_REG_CTIMER_SCMPR0_SCMPR0_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR0_SCMPR0(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR1 - Compare Register B
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_B_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR1_SCMPR1_S                0
#define AM_REG_CTIMER_SCMPR1_SCMPR1_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR1_SCMPR1(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR2 - Compare Register C
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_C_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR2_SCMPR2_S                0
#define AM_REG_CTIMER_SCMPR2_SCMPR2_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR2_SCMPR2(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR3 - Compare Register D
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_D_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR3_SCMPR3_S                0
#define AM_REG_CTIMER_SCMPR3_SCMPR3_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR3_SCMPR3(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR4 - Compare Register E
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_E_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR4_SCMPR4_S                0
#define AM_REG_CTIMER_SCMPR4_SCMPR4_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR4_SCMPR4(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR5 - Compare Register F
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_F_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR5_SCMPR5_S                0
#define AM_REG_CTIMER_SCMPR5_SCMPR5_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR5_SCMPR5(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR6 - Compare Register G
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_G_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR6_SCMPR6_S                0
#define AM_REG_CTIMER_SCMPR6_SCMPR6_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR6_SCMPR6(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCMPR7 - Compare Register H
//
//*****************************************************************************
// Compare this value to the value in the COUNTER register according to the
// match criterion, as selected in the COMPARE_H_EN bit in the REG_CTIMER_STCGF
// register.
#define AM_REG_CTIMER_SCMPR7_SCMPR7_S                0
#define AM_REG_CTIMER_SCMPR7_SCMPR7_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCMPR7_SCMPR7(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCAPT0 - Capture Register A
//
//*****************************************************************************
// Whenever the event is detected, the value in the COUNTER is copied into this
// register and the corresponding interrupt status bit is set.
#define AM_REG_CTIMER_SCAPT0_SCAPT0_S                0
#define AM_REG_CTIMER_SCAPT0_SCAPT0_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCAPT0_SCAPT0(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCAPT1 - Capture Register B
//
//*****************************************************************************
// Whenever the event is detected, the value in the COUNTER is copied into this
// register and the corresponding interrupt status bit is set.
#define AM_REG_CTIMER_SCAPT1_SCAPT1_S                0
#define AM_REG_CTIMER_SCAPT1_SCAPT1_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCAPT1_SCAPT1(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCAPT2 - Capture Register C
//
//*****************************************************************************
// Whenever the event is detected, the value in the COUNTER is copied into this
// register and the corresponding interrupt status bit is set.
#define AM_REG_CTIMER_SCAPT2_SCAPT2_S                0
#define AM_REG_CTIMER_SCAPT2_SCAPT2_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCAPT2_SCAPT2(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SCAPT3 - Capture Register D
//
//*****************************************************************************
// Whenever the event is detected, the value in the COUNTER is copied into this
// register and the corresponding interrupt status bit is set.
#define AM_REG_CTIMER_SCAPT3_SCAPT3_S                0
#define AM_REG_CTIMER_SCAPT3_SCAPT3_M                0xFFFFFFFF
#define AM_REG_CTIMER_SCAPT3_SCAPT3(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SNVR0 - System Timer NVRAM_A Register
//
//*****************************************************************************
// Value of the 32-bit counter as it ticks over.
#define AM_REG_CTIMER_SNVR0_SNVR0_S                  0
#define AM_REG_CTIMER_SNVR0_SNVR0_M                  0xFFFFFFFF
#define AM_REG_CTIMER_SNVR0_SNVR0(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SNVR1 - System Timer NVRAM_B Register
//
//*****************************************************************************
// Value of the 32-bit counter as it ticks over.
#define AM_REG_CTIMER_SNVR1_SNVR1_S                  0
#define AM_REG_CTIMER_SNVR1_SNVR1_M                  0xFFFFFFFF
#define AM_REG_CTIMER_SNVR1_SNVR1(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SNVR2 - System Timer NVRAM_C Register
//
//*****************************************************************************
// Value of the 32-bit counter as it ticks over.
#define AM_REG_CTIMER_SNVR2_SNVR2_S                  0
#define AM_REG_CTIMER_SNVR2_SNVR2_M                  0xFFFFFFFF
#define AM_REG_CTIMER_SNVR2_SNVR2(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CTIMER_SNVR3 - System Timer NVRAM_D Register
//
//*****************************************************************************
// Value of the 32-bit counter as it ticks over.
#define AM_REG_CTIMER_SNVR3_SNVR3_S                  0
#define AM_REG_CTIMER_SNVR3_SNVR3_M                  0xFFFFFFFF
#define AM_REG_CTIMER_SNVR3_SNVR3(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_CTIMER_H
