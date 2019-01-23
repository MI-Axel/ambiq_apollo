//*****************************************************************************
//
//! @file hci_drv.c
//!
//! @brief HCI driver interface.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
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
// This is part of revision v2.0.0 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "am_mcu_apollo.h"
#include "am_util.h"
#include "am_devices_em9304.h"
#include "em9304_init.h"
#include "em9304_patches.h"
#include "hci_apollo_config.h"

#define INVALIDATE_UNKNOWN_PATCHES
#define ENABLE_32K_CLK_FROM_APOLLO
#define SLEEP_CLK_PATCH_CONTAINER_ID (0x16)

// Define the HCI Command Type locally.
#define HCI_CMD_TYPE 1

// EM_PatchQuery field offsets
#define PATCH_INDEX_OFFSET    3

// EM_PatchQuery response field offsets
#define CONTAINER_COUNT_INDEX 7
#define CONTAINER_ADDR_INDEX 15
#define CONTAINER_SIZE_INDEX 19
#define BUILD_NUMBER_INDEX 27
#define USER_BUILD_NUMBER_INDEX 29
#define CONTAINER_VERSION_INDEX 32
#define CONTAINER_TYPE_INDEX 33
#define CONTAINER_ID_INDEX 34

// EM_PatchQuery response values
#define CONTAINER_TYPE_CONFIG_DATA_WORD     1
#define CONTAINER_TYPE_RANDOM_DATA_WORD     2
#define CONTAINER_TYPE_RANDOM_DATA_BYTE     3
#define CONTAINER_TYPE_CONFIG_DATA_BYTE     11

// EM_PatchWrite and EM_PatchContine field offsets
#define PATCH_LENGTH_OFFSET 2

// EM_PatchWrite and EM_PatchContinue response field offsets
#define HCI_STATUS_OFFSET 6
#define EM_PATCH_STATUS_OFFSET 7

// EM_PatchWrite and EM_PatchContinue Patch Status values
#define EM_PATCH_APPLIED 1
#define EM_PATCH_CONTINUE 2

// Maximum number of attempts to wait for a response from EM9304.
#define EM9304_MAX_ATTEMPTS     100
#define EM9304_ATTEMPT_DELAY_MS 1

// Initialization function error return status.
enum
{
  EM9304_INIT_STATUS_SUCCESS,
  EM9304_INIT_STATUS_ERROR
} e_em9304_init_status;

//*****************************************************************************
//
// HCI Commands for EM9304
//
//*****************************************************************************
uint8_t g_pui8EM_SleepDisable[] = {0x2D, 0xFC, 0x01, 0x00};
uint8_t g_pui8EM_SetOTPOn[]         = {0x2B, 0xFC, 0x01, 0x01};
uint8_t g_pui8EM_SetOTPOff[]         = {0x2B, 0xFC, 0x01, 0x00};
uint8_t g_pui8EM_SetIRAMOn[]         = {0x2B, 0xFC, 0x01, 0x07};
uint8_t g_pui8EM_PatchQuery[]     = {0x34, 0xFC, 0x02, 0x00, 0x00};
uint8_t g_pui8EM_SleepEnable[]     = {0x2D, 0xFC, 0x01, 0x01};
uint8_t g_pui8EM_CpuReset[]         = {0x32, 0xFC, 0x00};

//*****************************************************************************
//
// HCI RX packet buffer for EM9304 Driver.
//
//*****************************************************************************
static uint32_t g_pui32HCIRXBuffer[64];

//*****************************************************************************
//
// Static record of the EM9304 patch errors
//
//*****************************************************************************

uint32_t g_EMPatchErrors = 0;

//*****************************************************************************
//
//! @brief Patch Response helper functions for the EM9304 patches.  This
//!        routine blocks on a response from the EM9304 and filters the
//!        vendor specific events.
//!
//! @return none.
//
//*****************************************************************************
uint32_t
waitEM9304Response(void)
{
  uint32_t numBytesRx;

  // HCI Respone should return in 1-2 messages at most, but driver returns
  // 0 bytes when nothing is available, so wait up to 10msec.
  for (uint32_t attempts = 0; attempts < EM9304_MAX_ATTEMPTS; attempts++)
  {
    numBytesRx = am_devices_em9304_block_read(&g_sEm9304, g_pui32HCIRXBuffer, 0);
    // Look for "no message" return while filtering out the EM9304 vendor specific events.
    if ((numBytesRx !=0) && (!((numBytesRx == 4) && (0x0000FF04 == (g_pui32HCIRXBuffer[0] & 0x0000FFFF)))))
    {
      return EM9304_INIT_STATUS_SUCCESS;
    }
    am_util_delay_ms(EM9304_ATTEMPT_DELAY_MS);
  }
  return EM9304_INIT_STATUS_ERROR;

}

//*****************************************************************************
//
//! @brief Function to check for valid patches in the em9304_patches.* files.
//!        Invalid patches means that the scripts to generate the patch files
//!        were run without valid *.emp files as input.
//!
//! @return bool (TRUE = patches are valid).
//
//*****************************************************************************
bool
validEM9304Patches(void)
{
  //
  // Check to see if we have valid patches.
  // NULL patch has a specific signature.
  //
  if ((1 == EM9304_PATCHES_NUM_PATCHES) &&
      (0xFFFF == g_pEm9304Patches[0].buildNumber) &&
        (0xFFFF == g_pEm9304Patches[0].userBuildNumber) &&
          (0xFF == g_pEm9304Patches[0].containerVersion) &&
            (0xFF == g_pEm9304Patches[0].containerType) &&
              (0xFF == g_pEm9304Patches[0].containerID) &&
                (0x00 == g_pEm9304Patches[0].applyPatch) &&
                  (0x00 == g_pEm9304Patches[0].startingPatch) &&
                    (0x00 == g_pEm9304Patches[0].endingPatch))
  {
    am_util_debug_printf("em9304_patches.c contains NULL patch only\n");
    return false;
  }
  else
  {
    am_util_debug_printf("Valid em9304_patches.c file found\n");
    return true;
  }
}

//*****************************************************************************
//
//! @brief Function to invalidate a patch at a given address.  The size field
//!        is changed to corrupt the patch in OTP.
//!
//! @return status.
//
//*****************************************************************************
#ifdef INVALIDATE_UNKNOWN_PATCHES
static uint32_t invalidateEM9304Patch(uint32_t addr, uint32_t size)
{
  uint8_t   *bytePtr = (uint8_t *)&g_pui32HCIRXBuffer;

  uint8_t payload[] =
  {
      0x22, 0xFC,               //WriteAtAddr command
      0x0C,                     //HCI param length
      0, 0, 0, 0,               // container address placeholder
      0x33, 0x39, 0x6D, 0x65,   //signature
      0, 0, 0, 0                //size placeholder
  };

  am_util_debug_printf("Invalidating patch at %x\n", addr);

  payload[3] = (uint8_t)(addr & 0xFF);
  payload[4] = (uint8_t)((addr & 0xFF00) >> 8);
  payload[5] = (uint8_t)((addr & 0xFF0000) >> 16);
  payload[6] = (uint8_t)((addr & 0xFF000000) >> 24);

  size |= 0x36000000;  // mask the size to change the patch (invalidate it).

  payload[11] = (uint8_t)(size & 0xFF);
  payload[12] = (uint8_t)((size & 0xFF00) >> 8);
  payload[13] = (uint8_t)((size & 0xFF0000) >> 16);
  payload[14] = (uint8_t)((size & 0xFF000000) >> 24);

  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, payload, sizeof(payload));

  if ((EM9304_INIT_STATUS_SUCCESS != waitEM9304Response()) || (bytePtr[HCI_STATUS_OFFSET] != 0))
  {
    return EM9304_INIT_STATUS_ERROR;
  }

  return EM9304_INIT_STATUS_SUCCESS;
}
#endif

//*****************************************************************************
//
//! @brief Query the EM9304 patches.  This routine uses the EM_PatchQuery HCI
//!        command to interogate the connected EM9304 about its current patch
//!        state and then update the patch Container Info data structure.
//!
//! @return status.
//
//*****************************************************************************
uint32_t
queryEM9304Patches(void)
{
  uint32_t containerCount;
  uint32_t buildNumber, userBuildNumber, containerVersion, containerType, containerID;
#ifdef INVALIDATE_UNKNOWN_PATCHES
  uint32_t  containerAddr, containerSize;
  bool      invalidatePatch = false;
#endif
  uint8_t *pBuf = (uint8_t *)g_pui32HCIRXBuffer;

  // Initialize the container info patch status
  for (uint32_t patch = 0; patch < EM9304_PATCHES_NUM_PATCHES; patch++)
  {
    // Check patch for enabling 32Khz clck from Apollo MCU
    if ( (g_pEm9304Patches[patch].userBuildNumber == 2)
        && (g_pEm9304Patches[patch].containerID == SLEEP_CLK_PATCH_CONTAINER_ID))
    {
      uint32_t  ui32PN;

      //
      // Device identification
      //
      ui32PN = AM_REG(MCUCTRL, CHIP_INFO)  &
               AM_UTIL_MCUCTRL_CHIP_INFO_PARTNUM_PN_M;

      #ifdef ENABLE_32K_CLK_FROM_APOLLO
      // Currently only enable this for Apollo2-Blue
      if (ui32PN == AM_UTIL_MCUCTRL_CHIP_INFO_PARTNUM_APOLLOBL)
      {
        g_pEm9304Patches[patch].applyPatch = true;

        // GPIO 24 in Apollo2-blue connected to LFCLK in EM9304
        am_hal_gpio_pin_config(24, AM_HAL_PIN_24_CLKOUT);
        am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_XT);
        am_util_delay_ms(500);
        am_hal_clkgen_clkout_enable(AM_HAL_CLKGEN_CLKOUT_CKSEL_XT);
      }
      #endif
    }
    else
    {
      g_pEm9304Patches[patch].applyPatch = true;
    }
  }

  // Send the EM_SetSleepOptions command to disable sleep and check the response.
  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_SleepDisable, sizeof(g_pui8EM_SleepDisable) );

  if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
  {
    am_util_debug_printf("No Response to EM9304 Sleep Disable\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Check that the response is to the Sleep Disable.
  if ((0x01040E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC2D != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
  {
    am_util_debug_printf("Invalid Response to EM9304 Sleep Disable\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Send the EM_SetMemoryMode command to turn on OTP and check the response.
  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_SetOTPOn, sizeof(g_pui8EM_SetOTPOn) );

  if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
  {
    am_util_debug_printf("No Response to EM9304 OTP Enable\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Check that the response is to the OTP enable.
  if ((0x01040E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC2B != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
  {
    am_util_debug_printf("Invalid Response to EM9304 OTP Enable\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Query the EM9304 with the EM_PatchQuery and Patch Index = 0.  This will return the Container Count.
  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_PatchQuery, sizeof(g_pui8EM_PatchQuery) );

  if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
  {
    am_util_debug_printf("No Response to EM9304 Patch Query\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Check that the response is to the Patch Query.
  if ((0x01200E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC34 != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
  {
    am_util_debug_printf("Invalid Response to EM9304 Patch Query\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  // Extract the container information from the query response.
  containerCount = (uint32_t)pBuf[CONTAINER_COUNT_INDEX] +
    ((uint32_t)pBuf[CONTAINER_COUNT_INDEX + 1] << 8);

  // Assume the first patch is the manufacturing trim patch.
  // This is the only patch that never should be invalidated.
  am_util_debug_printf("Number of patch containers on EM9304 excluding Patch#0: %d\n", containerCount - 1);

  // For each container in Container Count
  for (uint32_t container = 1; container < containerCount; container++)
  {
    // Send the EM_PatchQuery for the Container.
    g_pui8EM_PatchQuery[PATCH_INDEX_OFFSET] = container;
    am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_PatchQuery, sizeof(g_pui8EM_PatchQuery) );

    if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
    {
      am_util_debug_printf("No Response to EM9304 Patch Query\n");
      return EM9304_INIT_STATUS_ERROR;
    }

    // Extract the container information from the query response.
    containerCount = (uint32_t)pBuf[CONTAINER_COUNT_INDEX] +
      ((uint32_t)pBuf[CONTAINER_COUNT_INDEX + 1] << 8);
    buildNumber = (uint32_t)pBuf[BUILD_NUMBER_INDEX] +
      ((uint32_t)(pBuf[BUILD_NUMBER_INDEX + 1] << 8));
    userBuildNumber = (uint32_t)pBuf[USER_BUILD_NUMBER_INDEX] +
      ((uint32_t)(pBuf[USER_BUILD_NUMBER_INDEX + 1] << 8));
    containerVersion = pBuf[CONTAINER_VERSION_INDEX];
    containerType = pBuf[CONTAINER_TYPE_INDEX];
    containerID = pBuf[CONTAINER_ID_INDEX];
#ifdef INVALIDATE_UNKNOWN_PATCHES
    containerAddr = (uint32_t)((pBuf[CONTAINER_ADDR_INDEX + 3] << 24) +
                               (pBuf[CONTAINER_ADDR_INDEX + 2] << 16) +
                                 (pBuf[CONTAINER_ADDR_INDEX + 1] << 8) +
                                   pBuf[CONTAINER_ADDR_INDEX]);
    containerSize = (uint32_t)((pBuf[CONTAINER_SIZE_INDEX + 3] << 24) +
                               (pBuf[CONTAINER_SIZE_INDEX + 2] << 16) +
                                 (pBuf[CONTAINER_SIZE_INDEX + 1] << 8) +
                                   pBuf[CONTAINER_SIZE_INDEX]);

    am_util_debug_printf("Patch #%d: Container Address = %8.8X Container Size = %4.4d Container Type=%d Container ID=%d Container Version=%d Build Number=%d User Build Number=%d\n",
                         container, containerAddr, containerSize, containerType, containerID, containerVersion, buildNumber, userBuildNumber);

    // Check for patches that are likely not configuration managed by the customer.
    // Avoid invalidating these patches.
    if ( ((CONTAINER_TYPE_CONFIG_DATA_WORD == containerType) ||
          (CONTAINER_TYPE_RANDOM_DATA_WORD == containerType)  ||
            (CONTAINER_TYPE_CONFIG_DATA_BYTE == containerType) ||
              (CONTAINER_TYPE_RANDOM_DATA_BYTE == containerType)) &&
        ((0 == buildNumber) || (3089 == buildNumber)) &&
          (0 == userBuildNumber) )
    {
      invalidatePatch = false;
    }
    else
    {
      // Initialize the invalidate flag.
      invalidatePatch = true;
    }
#endif

    // For each local patch, compare the Container Version, Container Type, and Container ID to the container info.
    for (uint32_t patch = 0; patch < EM9304_PATCHES_NUM_PATCHES; patch++)
    {
      if ((g_pEm9304Patches[patch].buildNumber == buildNumber) &&
          (g_pEm9304Patches[patch].userBuildNumber == userBuildNumber) &&
            (g_pEm9304Patches[patch].containerVersion == containerVersion) &&
              (g_pEm9304Patches[patch].containerType == containerType) &&
                (g_pEm9304Patches[patch].containerID == containerID))
      {
        g_pEm9304Patches[patch].applyPatch = false;     // Patch is already installed, so don't apply.
#ifdef INVALIDATE_UNKNOWN_PATCHES
        // Note that we will "re-enable" patches here even if they met the criteria above (which can happen!)
        invalidatePatch = false;
#endif
        break;
      }
    }

#ifdef INVALIDATE_UNKNOWN_PATCHES
    // Check to see if we need to invalidate the patch.
    if (invalidatePatch)
    {
      invalidateEM9304Patch(containerAddr, containerSize);
    }
#endif

  }


  if (DEST_MEMORY_IRAM == EM9304_PATCHES_DEST_MEMORY)
  {
    // Send the EM_SetMemoryMode command to turn off OTP and check the response.
    am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_SetOTPOff, sizeof(g_pui8EM_SetOTPOff) );

    if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
    {
      am_util_debug_printf("No Response to EM9304 OTP Disable\n");
      return EM9304_INIT_STATUS_ERROR;
    }

    // Check that the response is to the OTP Disable.
    if ((0x01040E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC2B != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
    {
      am_util_debug_printf("Invalid Response to EM9304 OTP Disable\n");
      return EM9304_INIT_STATUS_ERROR;
    }
  }

  // Send the EM_SetSleepOptions command to disable sleep and check the response.
  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_SleepEnable, sizeof(g_pui8EM_SleepEnable) );

  if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
  {
    am_util_debug_printf("No Response to EM9304 Sleep Enable\n");
    return EM9304_INIT_STATUS_ERROR;
  }


  // Check that the response is to the Sleep Enable.
  if ((0x01040E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC2D != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
  {
    am_util_debug_printf("Invalid Response to EM9304 Sleep Enable\n");
    return EM9304_INIT_STATUS_ERROR;
  }

  return EM9304_INIT_STATUS_SUCCESS;

}

//*****************************************************************************
//
//! @brief Apply the EM9304 patches.  This routine uses the EM_PatchQuery HCI
//!        command to interogate the connected EM9304 about its current patch
//!        state and then update the patch Container Info data structure.
//!
//!
//! @return Returns the status of the patch application (< 0 is an error).
//
//*****************************************************************************
uint32_t
applyEM9304Patches(void)
{
  uint8_t   *bytePtr = (uint8_t *)&g_pui32HCIRXBuffer;
  uint32_t  ui32PN;

  g_EMPatchErrors = 0;

  //
  // Device identification
  //
  ui32PN = AM_REG(MCUCTRL, CHIP_INFO)  &
           AM_UTIL_MCUCTRL_CHIP_INFO_PARTNUM_PN_M;

  // only enable clock for Apollo2-blue (maybe later Apollo3 as well)
  if (ui32PN == AM_UTIL_MCUCTRL_CHIP_INFO_PARTNUM_APOLLOBL)
  {

  }

  if (DEST_MEMORY_IRAM == EM9304_PATCHES_DEST_MEMORY)
  {
    // Send the EM_SetMemoryMode command to turn on IRAM and check the response.
    am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_SetIRAMOn, sizeof(g_pui8EM_SetIRAMOn) );

    if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
    {
      am_util_debug_printf("No Response to EM9304 IRAM Enable\n");
      return EM9304_INIT_STATUS_ERROR;
    }

    // Check that the response is to the IRAM enable.
    if ((0x01040E04 != g_pui32HCIRXBuffer[0]) || (0x0000FC2B != (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
    {
      am_util_debug_printf("Invalid Response to EM9304 IRAM Enable\n");
      return EM9304_INIT_STATUS_ERROR;
    }
  }

  // Loop through the patches and apply those that are not already there.
  // For each local patch, compare the Container Version, Container Type, and Container ID to the container info.
  for (uint32_t patch = 0; patch < EM9304_PATCHES_NUM_PATCHES; patch++)
  {
    if (g_pEm9304Patches[patch].applyPatch)
    {
            am_util_debug_printf("Applying Patch #%d: Container Type=%d Container ID=%d Container Version=%d Build Number=%d User Build Number=%d\n",
                                 patch, g_pEm9304Patches[patch].containerType, g_pEm9304Patches[patch].containerID, g_pEm9304Patches[patch].containerVersion,
                                 g_pEm9304Patches[patch].buildNumber, g_pEm9304Patches[patch].userBuildNumber);


      for (uint32_t index = g_pEm9304Patches[patch].startingPatch; index < g_pEm9304Patches[patch].endingPatch; index ++)
      {
        am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, (uint8_t *)g_pEm9304PatchesHCICmd[index],
                                      g_pEm9304PatchesHCICmd[index][PATCH_LENGTH_OFFSET] + 3 );

        if (EM9304_INIT_STATUS_SUCCESS != waitEM9304Response())
        {
          am_util_debug_printf("No Response to EM9304 Patch Write\n");
          return EM9304_INIT_STATUS_ERROR;
        }

        if ((g_pEm9304PatchesHCICmd[index][1] == 0x27) &&
            (bytePtr[EM_PATCH_STATUS_OFFSET] != EM_PATCH_APPLIED))
        {
          am_util_debug_printf("Error Response to EM9304 Patch Write\n");
          return EM9304_INIT_STATUS_ERROR;
        }
        else if (g_pEm9304PatchesHCICmd[index][1] == 0x28)
        {
          if (((index + 1) == g_pEm9304Patches[patch].endingPatch) && (bytePtr[EM_PATCH_STATUS_OFFSET] != EM_PATCH_APPLIED))
          {
            am_util_debug_printf("Error Response to EM9304 Patch Continue (next to last patch segment)\n");
            return EM9304_INIT_STATUS_ERROR;
          }
          else if (bytePtr[EM_PATCH_STATUS_OFFSET] != EM_PATCH_CONTINUE)
          {
            am_util_debug_printf("Error Response to EM9304 Patch Continue (last patch segment)\n");
            return EM9304_INIT_STATUS_ERROR;
          }
        }
      }
    }
  }

  return EM9304_INIT_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Configure the necessary pins and start the EM9304 radio.
//
//*****************************************************************************
uint32_t
initEM9304(void)
{
  uint32_t numBytesRx;

  if (validEM9304Patches())
  {
    //
    // Query the EM9304 for patches
    //
    if (EM9304_INIT_STATUS_SUCCESS == queryEM9304Patches())
    {
      //
      // Apply the patches not already in the EM9304
      //
      if (EM9304_INIT_STATUS_SUCCESS != applyEM9304Patches())
      {
        am_util_debug_printf("EM9304 Patch Application Failed\n");
      }
    }
    else
    {
      am_util_debug_printf("EM9304 Patching Query Failed.  Patch update not applied\n");
    }

  }
  // Send EM_CpuReset HCI command.
  am_devices_em9304_block_write(&g_sEm9304, HCI_CMD_TYPE, g_pui8EM_CpuReset, sizeof(g_pui8EM_CpuReset) );

  // HCI Respone should return in 1-2 messages at most, but driver returns
  // 0 bytes when nothing is available, so wait up to 10msec.
  for (uint32_t attempts = 0; attempts < EM9304_MAX_ATTEMPTS; attempts++)
  {
    numBytesRx = am_devices_em9304_block_read(&g_sEm9304, g_pui32HCIRXBuffer, 0);
    if ((numBytesRx == 7) && (0x0000FC32 == (g_pui32HCIRXBuffer[1] & 0x0000FFFF)))
    {
      am_util_debug_printf("EM9304 CPU Reset Successfully\n");
      break;
    }
    am_util_delay_ms(EM9304_ATTEMPT_DELAY_MS);
  }

  return EM9304_PATCHES_DEST_MEMORY;
}
