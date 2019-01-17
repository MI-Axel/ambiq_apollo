//*****************************************************************************
//
//  am_reg_cachectrl.h
//! @file
//!
//! @brief Register macros for the CACHECTRL module
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
#ifndef AM_REG_CACHECTRL_H
#define AM_REG_CACHECTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_CACHECTRL_NUM_MODULES                 1
#define AM_REG_CACHECTRLn(n) \
    (REG_CACHECTRL_BASEADDR + 0x00001000 * n)

#if !AM_CMSIS_REGS
//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_CACHECTRL_CACHECFG_O                  0x00000000
#define AM_REG_CACHECTRL_FLASHCFG_O                  0x00000004
#define AM_REG_CACHECTRL_CTRL_O                      0x00000008
#define AM_REG_CACHECTRL_NCR0START_O                 0x00000010
#define AM_REG_CACHECTRL_NCR0END_O                   0x00000014
#define AM_REG_CACHECTRL_NCR1START_O                 0x00000018
#define AM_REG_CACHECTRL_NCR1END_O                   0x0000001C
#define AM_REG_CACHECTRL_DMON0_O                     0x00000040
#define AM_REG_CACHECTRL_DMON1_O                     0x00000044
#define AM_REG_CACHECTRL_DMON2_O                     0x00000048
#define AM_REG_CACHECTRL_DMON3_O                     0x0000004C
#define AM_REG_CACHECTRL_IMON0_O                     0x00000050
#define AM_REG_CACHECTRL_IMON1_O                     0x00000054
#define AM_REG_CACHECTRL_IMON2_O                     0x00000058
#define AM_REG_CACHECTRL_IMON3_O                     0x0000005C

//*****************************************************************************
//
// CACHECTRL_CACHECFG - Flash Cache Control Register
//
//*****************************************************************************
// Enable Cache Monitoring Stats.  Cache monitoring consumes additional power
// and should only be enabled when profiling code and counters will increment
// when this bit is set.  Counter values will be retained when this is set to 0,
// allowing software to enable/disable counting for multiple code segments.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_S   24
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_M   0x01000000
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR(n)  (((uint32_t)(n) << 24) & 0x01000000)

// Enable aggressive clock gating of entire data array.  This bit should be set
// to 1 for optimal power efficiency.
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_S     20
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_M     0x00100000
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE(n)    (((uint32_t)(n) << 20) & 0x00100000)

// Enable LS (light sleep) of cache RAMs.  Software should DISABLE this bit
// since cache activity is too high to benefit from LS usage.
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS_S         11
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS_M         0x00000800
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS(n)        (((uint32_t)(n) << 11) & 0x00000800)

// Enable clock gating of cache TAG RAM.  Software should enable this bit for
// optimal power efficiency.
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_S    10
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_M    0x00000400
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE(n)   (((uint32_t)(n) << 10) & 0x00000400)

// Enable Flash Data Caching.
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_S    9
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_M    0x00000200
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE(n)   (((uint32_t)(n) << 9) & 0x00000200)

// Enable Flash Instruction Caching
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_S    8
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_M    0x00000100
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE(n)   (((uint32_t)(n) << 8) & 0x00000100)

// Sets the cache configuration
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_S           4
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_M           0x000000F0
#define AM_REG_CACHECTRL_CACHECFG_CONFIG(n)          (((uint32_t)(n) << 4) & 0x000000F0)
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_W1_128B_512E 0x00000040
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_W2_128B_512E 0x00000050
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_W1_128B_1024E 0x00000080

// Enable Non-cacheable region 1.  See NCR1 registers to define the region.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_S       3
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_M       0x00000008
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1(n)      (((uint32_t)(n) << 3) & 0x00000008)

// Enable Non-cacheable region 0.  See NCR0 registers to define the region.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_S       2
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_M       0x00000004
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0(n)      (((uint32_t)(n) << 2) & 0x00000004)

// Sets the cache repleacment policy.  0=LRR (least recently replaced), 1=LRU
// (least recently used).  LRR minimizes writes to the TAG SRAM.
#define AM_REG_CACHECTRL_CACHECFG_LRU_S              1
#define AM_REG_CACHECTRL_CACHECFG_LRU_M              0x00000002
#define AM_REG_CACHECTRL_CACHECFG_LRU(n)             (((uint32_t)(n) << 1) & 0x00000002)

// Enables the flash cache controller and enables power to the cache SRAMs.  The
// ICACHE_ENABLE and DCACHE_ENABLE should be set to enable caching for each type
// of access.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_S           0
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_M           0x00000001
#define AM_REG_CACHECTRL_CACHECFG_ENABLE(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CACHECTRL_FLASHCFG - Flash Control Register
//
//*****************************************************************************
// Controls flash low power modes (control of LPM pin).
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE_S          12
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE_M          0x00003000
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE(n)         (((uint32_t)(n) << 12) & 0x00003000)
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE_NEVER      0x00000000
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE_STANDBY    0x00001000
#define AM_REG_CACHECTRL_FLASHCFG_LPMMODE_ALWAYS     0x00002000

// Sets flash waitstates when in LPM Mode 2 (RD_WAIT in LPM mode 2 only)
#define AM_REG_CACHECTRL_FLASHCFG_LPM_RD_WAIT_S      8
#define AM_REG_CACHECTRL_FLASHCFG_LPM_RD_WAIT_M      0x00000F00
#define AM_REG_CACHECTRL_FLASHCFG_LPM_RD_WAIT(n)     (((uint32_t)(n) << 8) & 0x00000F00)

// Sets SE delay (flash address setup).  A value of 5 is recommended.
#define AM_REG_CACHECTRL_FLASHCFG_SEDELAY_S          4
#define AM_REG_CACHECTRL_FLASHCFG_SEDELAY_M          0x00000070
#define AM_REG_CACHECTRL_FLASHCFG_SEDELAY(n)         (((uint32_t)(n) << 4) & 0x00000070)

// Sets read waitstates for normal (fast) operation.  A value of 1 is
// recommended.
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT_S          0
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT_M          0x0000000F
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT(n)         (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// CACHECTRL_CTRL - Cache Control
//
//*****************************************************************************
// Enable Flash Sleep Mode.  Write to 1 to put flash 1 into sleep mode.  NOTE:
// there is a 5us latency after waking flash until the first access will be
// returned.
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_ENABLE_S    10
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_ENABLE_M    0x00000400
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_ENABLE(n)   (((uint32_t)(n) << 10) & 0x00000400)

// Disable Flash Sleep Mode.  Write 1 to wake flash1 from sleep mode (reading
// the array will also automatically wake it).
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_DISABLE_S   9
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_DISABLE_M   0x00000200
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_DISABLE(n)  (((uint32_t)(n) << 9) & 0x00000200)

// Flash Sleep Mode Status.  1 indicates that flash1 is in sleep mode, 0
// indicates flash1 is in normal mode.
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_STATUS_S    8
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_STATUS_M    0x00000100
#define AM_REG_CACHECTRL_CTRL_FLASH1_SLM_STATUS(n)   (((uint32_t)(n) << 8) & 0x00000100)

// Enable Flash Sleep Mode.  Write to 1 to put flash 0 into sleep mode.  NOTE:
// there is a 5us latency after waking flash until the first access will be
// returned.
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_ENABLE_S    6
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_ENABLE_M    0x00000040
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_ENABLE(n)   (((uint32_t)(n) << 6) & 0x00000040)

// Disable Flash Sleep Mode.  Write 1 to wake flash0 from sleep mode (reading
// the array will also automatically wake it).
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_DISABLE_S   5
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_DISABLE_M   0x00000020
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_DISABLE(n)  (((uint32_t)(n) << 5) & 0x00000020)

// Flash Sleep Mode Status.  1 indicates that flash0 is in sleep mode, 0
// indicates flash0 is in normal mode.
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_STATUS_S    4
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_STATUS_M    0x00000010
#define AM_REG_CACHECTRL_CTRL_FLASH0_SLM_STATUS(n)   (((uint32_t)(n) << 4) & 0x00000010)

// Cache Ready Status (enabled and not processing an invalidate operation)
#define AM_REG_CACHECTRL_CTRL_CACHE_READY_S          2
#define AM_REG_CACHECTRL_CTRL_CACHE_READY_M          0x00000004
#define AM_REG_CACHECTRL_CTRL_CACHE_READY(n)         (((uint32_t)(n) << 2) & 0x00000004)

// Reset Cache Statistics.  When written to a 1, the cache monitor counters will
// be cleared.  The monitor counters can be reset only when the
// CACHECFG.ENABLE_MONITOR bit is set.
#define AM_REG_CACHECTRL_CTRL_RESET_STAT_S           1
#define AM_REG_CACHECTRL_CTRL_RESET_STAT_M           0x00000002
#define AM_REG_CACHECTRL_CTRL_RESET_STAT(n)          (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CACHECTRL_CTRL_RESET_STAT_CLEAR       0x00000002

// Writing a 1 to this bitfield invalidates the flash cache contents.
#define AM_REG_CACHECTRL_CTRL_INVALIDATE_S           0
#define AM_REG_CACHECTRL_CTRL_INVALIDATE_M           0x00000001
#define AM_REG_CACHECTRL_CTRL_INVALIDATE(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CACHECTRL_NCR0START - Flash Cache Noncachable Region 0 Start
//
//*****************************************************************************
// Start address for non-cacheable region 0
#define AM_REG_CACHECTRL_NCR0START_ADDR_S            4
#define AM_REG_CACHECTRL_NCR0START_ADDR_M            0x07FFFFF0
#define AM_REG_CACHECTRL_NCR0START_ADDR(n)           (((uint32_t)(n) << 4) & 0x07FFFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR0END - Flash Cache Noncachable Region 0 End
//
//*****************************************************************************
// End address for non-cacheable region 0
#define AM_REG_CACHECTRL_NCR0END_ADDR_S              4
#define AM_REG_CACHECTRL_NCR0END_ADDR_M              0x07FFFFF0
#define AM_REG_CACHECTRL_NCR0END_ADDR(n)             (((uint32_t)(n) << 4) & 0x07FFFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR1START - Flash Cache Noncachable Region 1 Start
//
//*****************************************************************************
// Start address for non-cacheable region 1
#define AM_REG_CACHECTRL_NCR1START_ADDR_S            4
#define AM_REG_CACHECTRL_NCR1START_ADDR_M            0x07FFFFF0
#define AM_REG_CACHECTRL_NCR1START_ADDR(n)           (((uint32_t)(n) << 4) & 0x07FFFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR1END - Flash Cache Noncachable Region 1 End
//
//*****************************************************************************
// End address for non-cacheable region 1
#define AM_REG_CACHECTRL_NCR1END_ADDR_S              4
#define AM_REG_CACHECTRL_NCR1END_ADDR_M              0x07FFFFF0
#define AM_REG_CACHECTRL_NCR1END_ADDR(n)             (((uint32_t)(n) << 4) & 0x07FFFFF0)

//*****************************************************************************
//
// CACHECTRL_DMON0 - Data Cache Total Accesses
//
//*****************************************************************************
// Total accesses to data cache.  All performance metrics should be relative to
// the number of accesses performed.
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT_S       0
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON1 - Data Cache Tag Lookups
//
//*****************************************************************************
// Total tag lookups from data cache.
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT_S       0
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON2 - Data Cache Hits
//
//*****************************************************************************
// Cache hits from lookup operations.
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT_S          0
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT_M          0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT(n)         (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON3 - Data Cache Line Hits
//
//*****************************************************************************
// Cache hits from line cache
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT_S         0
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT_M         0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON0 - Instruction Cache Total Accesses
//
//*****************************************************************************
// Total accesses to Instruction cache
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT_S       0
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON1 - Instruction Cache Tag Lookups
//
//*****************************************************************************
// Total tag lookups from Instruction cache
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT_S       0
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON2 - Instruction Cache Hits
//
//*****************************************************************************
// Cache hits from lookup operations
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT_S          0
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT_M          0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT(n)         (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON3 - Instruction Cache Line Hits
//
//*****************************************************************************
// Cache hits from line cache
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT_S         0
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT_M         0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

#endif // !AM_CMSIS_REGS

#endif // AM_REG_CACHECTRL_H
