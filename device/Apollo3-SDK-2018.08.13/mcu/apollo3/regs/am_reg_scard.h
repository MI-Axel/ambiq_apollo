//*****************************************************************************
//
//  am_reg_scard.h
//! @file
//!
//! @brief Register macros for the SCARD module
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
#ifndef AM_REG_SCARD_H
#define AM_REG_SCARD_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_SCARD_NUM_MODULES                     1
#define AM_REG_SCARDn(n) \
    (REG_SCARD_BASEADDR + 0x00000000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_SCARD_SR_O                            0x00000000
#define AM_REG_SCARD_DR_O                            0x00000010
#define AM_REG_SCARD_SR1_O                           0x00000020
#define AM_REG_SCARD_RETXCNTRMI_O                    0x00000038
#define AM_REG_SCARD_CLKCTRL_O                       0x00000100

//*****************************************************************************
//
// SCARD_SR - ISO7816 interrupt status
//
//*****************************************************************************
// FIFO Half Full.
#define AM_REG_SCARD_SR_FHF_S                        6
#define AM_REG_SCARD_SR_FHF_M                        0x00000040
#define AM_REG_SCARD_SR_FHF(n)                       (((uint32_t)(n) << 6) & 0x00000040)

// TX to RX finished.
#define AM_REG_SCARD_SR_FT2REND_S                    5
#define AM_REG_SCARD_SR_FT2REND_M                    0x00000020
#define AM_REG_SCARD_SR_FT2REND(n)                   (((uint32_t)(n) << 5) & 0x00000020)

// Parity Error.
#define AM_REG_SCARD_SR_PE_S                         4
#define AM_REG_SCARD_SR_PE_M                         0x00000010
#define AM_REG_SCARD_SR_PE(n)                        (((uint32_t)(n) << 4) & 0x00000010)

// RX FIFO overflow.
#define AM_REG_SCARD_SR_OVR_S                        3
#define AM_REG_SCARD_SR_OVR_M                        0x00000008
#define AM_REG_SCARD_SR_OVR(n)                       (((uint32_t)(n) << 3) & 0x00000008)

// Framing error.
#define AM_REG_SCARD_SR_FER_S                        2
#define AM_REG_SCARD_SR_FER_M                        0x00000004
#define AM_REG_SCARD_SR_FER(n)                       (((uint32_t)(n) << 2) & 0x00000004)

// FIFO empty (transmit) or full (receive).
#define AM_REG_SCARD_SR_TBERBF_S                     1
#define AM_REG_SCARD_SR_TBERBF_M                     0x00000002
#define AM_REG_SCARD_SR_TBERBF(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// RX FIFO not empty.
#define AM_REG_SCARD_SR_FNE_S                        0
#define AM_REG_SCARD_SR_FNE_M                        0x00000001
#define AM_REG_SCARD_SR_FNE(n)                       (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SCARD_DR - ISO7816 data
//
//*****************************************************************************
// Data register.
#define AM_REG_SCARD_DR_DR_S                         0
#define AM_REG_SCARD_DR_DR_M                         0x000000FF
#define AM_REG_SCARD_DR_DR(n)                        (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// SCARD_SR1 - ISO7816 interrupt status 1
//
//*****************************************************************************
// ISO7816 idle.
#define AM_REG_SCARD_SR1_IDLE_S                      3
#define AM_REG_SCARD_SR1_IDLE_M                      0x00000008
#define AM_REG_SCARD_SR1_IDLE(n)                     (((uint32_t)(n) << 3) & 0x00000008)

// Write complete synchronization.
#define AM_REG_SCARD_SR1_SYNCEND_S                   2
#define AM_REG_SCARD_SR1_SYNCEND_M                   0x00000004
#define AM_REG_SCARD_SR1_SYNCEND(n)                  (((uint32_t)(n) << 2) & 0x00000004)

// Card insert/remove.
#define AM_REG_SCARD_SR1_PRL_S                       1
#define AM_REG_SCARD_SR1_PRL_M                       0x00000002
#define AM_REG_SCARD_SR1_PRL(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// ETU counter overflow.
#define AM_REG_SCARD_SR1_ECNTOVER_S                  0
#define AM_REG_SCARD_SR1_ECNTOVER_M                  0x00000001
#define AM_REG_SCARD_SR1_ECNTOVER(n)                 (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SCARD_RETXCNTRMI - ISO7816 resent count inquiry
//
//*****************************************************************************
// Resent count inquiry register.
#define AM_REG_SCARD_RETXCNTRMI_RETXCNTRMI_S         0
#define AM_REG_SCARD_RETXCNTRMI_RETXCNTRMI_M         0x0000000F
#define AM_REG_SCARD_RETXCNTRMI_RETXCNTRMI(n)        (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// SCARD_CLKCTRL - Clock Control
//
//*****************************************************************************
// Enable the SCARD APB clock to run continuously.
#define AM_REG_SCARD_CLKCTRL_APBCLKEN_S              1
#define AM_REG_SCARD_CLKCTRL_APBCLKEN_M              0x00000002
#define AM_REG_SCARD_CLKCTRL_APBCLKEN(n)             (((uint32_t)(n) << 1) & 0x00000002)

// Enable the serial source clock for SCARD.
#define AM_REG_SCARD_CLKCTRL_CLKEN_S                 0
#define AM_REG_SCARD_CLKCTRL_CLKEN_M                 0x00000001
#define AM_REG_SCARD_CLKCTRL_CLKEN(n)                (((uint32_t)(n) << 0) & 0x00000001)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_SCARD_H
