//*****************************************************************************
//
//  am_reg_apbdma.h
//! @file
//!
//! @brief Register macros for the APBDMA module
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
#ifndef AM_REG_APBDMA_H
#define AM_REG_APBDMA_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_APBDMA_NUM_MODULES                    1
#define AM_REG_APBDMAn(n) \
    (REG_APBDMA_BASEADDR + 0x00001000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_APBDMA_BBVALUE_O                      0x00000000
#define AM_REG_APBDMA_BBSETCLEAR_O                   0x00000004
#define AM_REG_APBDMA_BBINPUT_O                      0x00000008
#define AM_REG_APBDMA_DEBUGDATA_O                    0x00000020
#define AM_REG_APBDMA_DEBUG_O                        0x00000040

//*****************************************************************************
//
// APBDMA_BBVALUE - Control Register
//
//*****************************************************************************
// PIO values
#define AM_REG_APBDMA_BBVALUE_PIN_S                  16
#define AM_REG_APBDMA_BBVALUE_PIN_M                  0x00FF0000
#define AM_REG_APBDMA_BBVALUE_PIN(n)                 (((uint32_t)(n) << 16) & 0x00FF0000)

// Data Output Values
#define AM_REG_APBDMA_BBVALUE_DATAOUT_S              0
#define AM_REG_APBDMA_BBVALUE_DATAOUT_M              0x000000FF
#define AM_REG_APBDMA_BBVALUE_DATAOUT(n)             (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// APBDMA_BBSETCLEAR - Set/Clear Register
//
//*****************************************************************************
// Write 1 to Clear PIO value
#define AM_REG_APBDMA_BBSETCLEAR_CLEAR_S             16
#define AM_REG_APBDMA_BBSETCLEAR_CLEAR_M             0x00FF0000
#define AM_REG_APBDMA_BBSETCLEAR_CLEAR(n)            (((uint32_t)(n) << 16) & 0x00FF0000)

// Write 1 to Set PIO value (set hier priority than clear if both bit set)
#define AM_REG_APBDMA_BBSETCLEAR_SET_S               0
#define AM_REG_APBDMA_BBSETCLEAR_SET_M               0x000000FF
#define AM_REG_APBDMA_BBSETCLEAR_SET(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// APBDMA_BBINPUT - PIO Input Values
//
//*****************************************************************************
// PIO values
#define AM_REG_APBDMA_BBINPUT_DATAIN_S               0
#define AM_REG_APBDMA_BBINPUT_DATAIN_M               0x000000FF
#define AM_REG_APBDMA_BBINPUT_DATAIN(n)              (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// APBDMA_DEBUGDATA - PIO Input Values
//
//*****************************************************************************
// Debug Data
#define AM_REG_APBDMA_DEBUGDATA_DEBUGDATA_S          0
#define AM_REG_APBDMA_DEBUGDATA_DEBUGDATA_M          0xFFFFFFFF
#define AM_REG_APBDMA_DEBUGDATA_DEBUGDATA(n)         (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// APBDMA_DEBUG - PIO Input Values
//
//*****************************************************************************
// Debug Enable
#define AM_REG_APBDMA_DEBUG_DEBUGEN_S                0
#define AM_REG_APBDMA_DEBUG_DEBUGEN_M                0x0000000F
#define AM_REG_APBDMA_DEBUG_DEBUGEN(n)               (((uint32_t)(n) << 0) & 0x0000000F)
#define AM_REG_APBDMA_DEBUG_DEBUGEN_OFF              0x00000000
#define AM_REG_APBDMA_DEBUG_DEBUGEN_ARB              0x00000001

#endif // !AM_CMSIS_REGS

#endif // AM_REG_APBDMA_H
