//*****************************************************************************
//
//  am_reg_security.h
//! @file
//!
//! @brief Register macros for the SECURITY module
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
#ifndef AM_REG_SECURITY_H
#define AM_REG_SECURITY_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_SECURITY_NUM_MODULES                  1
#define AM_REG_SECURITYn(n) \
    (REG_SECURITY_BASEADDR + 0x00001000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_SECURITY_CTRL_O                       0x00000000
#define AM_REG_SECURITY_SRCADDR_O                    0x00000010
#define AM_REG_SECURITY_LEN_O                        0x00000020
#define AM_REG_SECURITY_RESULT_O                     0x00000030
#define AM_REG_SECURITY_LOCKCTRL_O                   0x00000078
#define AM_REG_SECURITY_LOCKSTAT_O                   0x0000007C
#define AM_REG_SECURITY_KEY0_O                       0x00000080
#define AM_REG_SECURITY_KEY1_O                       0x00000084
#define AM_REG_SECURITY_KEY2_O                       0x00000088
#define AM_REG_SECURITY_KEY3_O                       0x0000008C

//*****************************************************************************
//
// SECURITY_CTRL - Control Register
//
//*****************************************************************************
// CRC Error Status - Set to 1 if an error occurs during a CRC operation.
// Cleared when CTRL register is written (with any value).  Usually indicates an
// invalid address range.
#define AM_REG_SECURITY_CTRL_CRCERROR_S              31
#define AM_REG_SECURITY_CTRL_CRCERROR_M              0x80000000
#define AM_REG_SECURITY_CTRL_CRCERROR(n)             (((uint32_t)(n) << 31) & 0x80000000)

// Function Select
#define AM_REG_SECURITY_CTRL_FUNCTION_S              4
#define AM_REG_SECURITY_CTRL_FUNCTION_M              0x000000F0
#define AM_REG_SECURITY_CTRL_FUNCTION(n)             (((uint32_t)(n) << 4) & 0x000000F0)
#define AM_REG_SECURITY_CTRL_FUNCTION_CRC32          0x00000000

// Function Enable.  Software should set the ENABLE bit to initiate a CRC
// operation.  Hardware will clear the ENABLE bit upon completion.
#define AM_REG_SECURITY_CTRL_ENABLE_S                0
#define AM_REG_SECURITY_CTRL_ENABLE_M                0x00000001
#define AM_REG_SECURITY_CTRL_ENABLE(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SECURITY_SRCADDR - Source Addresss
//
//*****************************************************************************
// Source Buffer Address.  Address may be byte aligned, but the length must be a
// multiple of 4 bits.
#define AM_REG_SECURITY_SRCADDR_ADDR_S               0
#define AM_REG_SECURITY_SRCADDR_ADDR_M               0xFFFFFFFF
#define AM_REG_SECURITY_SRCADDR_ADDR(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SECURITY_LEN - Length
//
//*****************************************************************************
// Buffer size (bottom two bits assumed to be zero to ensure a multiple of 4
// bytes)
#define AM_REG_SECURITY_LEN_LEN_S                    2
#define AM_REG_SECURITY_LEN_LEN_M                    0x000FFFFC
#define AM_REG_SECURITY_LEN_LEN(n)                   (((uint32_t)(n) << 2) & 0x000FFFFC)

//*****************************************************************************
//
// SECURITY_RESULT - CRC Seed/Result Register
//
//*****************************************************************************
// CRC Seed/Result.  Software must seed the CRC with 0xFFFFFFFF before starting
// a CRC operation (unless the CRC is continued from a previous operation).
#define AM_REG_SECURITY_RESULT_CRC_S                 0
#define AM_REG_SECURITY_RESULT_CRC_M                 0xFFFFFFFF
#define AM_REG_SECURITY_RESULT_CRC(n)                (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SECURITY_LOCKCTRL - LOCK Control Register
//
//*****************************************************************************
// LOCK Function Select register.
#define AM_REG_SECURITY_LOCKCTRL_SELECT_S            0
#define AM_REG_SECURITY_LOCKCTRL_SELECT_M            0x000000FF
#define AM_REG_SECURITY_LOCKCTRL_SELECT(n)           (((uint32_t)(n) << 0) & 0x000000FF)
#define AM_REG_SECURITY_LOCKCTRL_SELECT_CUSTOMER_KEY 0x00000001
#define AM_REG_SECURITY_LOCKCTRL_SELECT_NONE         0x00000000

//*****************************************************************************
//
// SECURITY_LOCKSTAT - LOCK Status Register
//
//*****************************************************************************
// LOCK Status register.  This register is a bitmask for which resources are
// currently unlocked.  These bits are one-hot per resource.
#define AM_REG_SECURITY_LOCKSTAT_STATUS_S            0
#define AM_REG_SECURITY_LOCKSTAT_STATUS_M            0xFFFFFFFF
#define AM_REG_SECURITY_LOCKSTAT_STATUS(n)           (((uint32_t)(n) << 0) & 0xFFFFFFFF)
#define AM_REG_SECURITY_LOCKSTAT_STATUS_CUSTOMER_KEY 0x00000001
#define AM_REG_SECURITY_LOCKSTAT_STATUS_NONE         0x00000000

//*****************************************************************************
//
// SECURITY_KEY0 - Key0 Register
//
//*****************************************************************************
// Bits [31:0] of the 128-bit key should be written to this register.  To
// protect key values, the register always returns 0x00000000.
#define AM_REG_SECURITY_KEY0_KEY0_S                  0
#define AM_REG_SECURITY_KEY0_KEY0_M                  0xFFFFFFFF
#define AM_REG_SECURITY_KEY0_KEY0(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SECURITY_KEY1 - Key1 Register
//
//*****************************************************************************
// Bits [63:32] of the 128-bit key should be written to this register.  To
// protect key values, the register always returns 0x00000000.
#define AM_REG_SECURITY_KEY1_KEY1_S                  0
#define AM_REG_SECURITY_KEY1_KEY1_M                  0xFFFFFFFF
#define AM_REG_SECURITY_KEY1_KEY1(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SECURITY_KEY2 - Key2 Register
//
//*****************************************************************************
// Bits [95:64] of the 128-bit key should be written to this register.  To
// protect key values, the register always returns 0x00000000.
#define AM_REG_SECURITY_KEY2_KEY2_S                  0
#define AM_REG_SECURITY_KEY2_KEY2_M                  0xFFFFFFFF
#define AM_REG_SECURITY_KEY2_KEY2(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SECURITY_KEY3 - Key3 Register
//
//*****************************************************************************
// Bits [127:96] of the 128-bit key should be written to this register.  To
// protect key values, the register always returns 0x00000000.
#define AM_REG_SECURITY_KEY3_KEY3_S                  0
#define AM_REG_SECURITY_KEY3_KEY3_M                  0xFFFFFFFF
#define AM_REG_SECURITY_KEY3_KEY3(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_SECURITY_H
