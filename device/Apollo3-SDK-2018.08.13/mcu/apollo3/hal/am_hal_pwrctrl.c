//*****************************************************************************
//
//  am_hal_pwrctrl.c
//! @file
//!
//! @brief Functions for enabling and disabling power domains.
//!
//! @addtogroup pwrctrl3 Power Control
//! @ingroup apollo3hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// ${copyright}
//
// This is part of revision ${version} of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

// #### INTERNAL BEGIN ####
#if APOLLO3_FPGA
#warning "am_hal_pwrctrl.c: APOLLO3_FPGA is defined in am_mcu_apollo.h and used in this module. It must be removed for silicon."
#endif
// #### INTERNAL END ####
//
// Maximum number of checks to memory power status before declaring error.
//
#define AM_HAL_PWRCTRL_MAX_WFE  20

//
// Define the peripheral control structure.
//
const struct
{
    uint32_t      ui32PeriphEnable;
    uint32_t      ui32PeriphStatus;
    uint32_t      ui32PeriphEvent;
}
am_hal_pwrctrl_peripheral_control[AM_HAL_PWRCTRL_PERIPH_MAX] =
{
#if AM_CMSIS_REGS
    {0, 0, 0},                                  //  AM_HAL_PWRCTRL_PERIPH_NONE
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOS, PWRCTRL_DEVPWREN_PWRIOS_EN),
     PWRCTRL_DEVPWRSTATUS_HCPA_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPAEVEN, PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN)},  // AM_HAL_PWRCTRL_PERIPH_IOS
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM0, PWRCTRL_DEVPWREN_PWRIOM0_EN),
     PWRCTRL_DEVPWRSTATUS_HCPB_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPBEVEN, PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM0
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM1, PWRCTRL_DEVPWREN_PWRIOM1_EN),
     PWRCTRL_DEVPWRSTATUS_HCPB_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPBEVEN, PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM1
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM2, PWRCTRL_DEVPWREN_PWRIOM2_EN),
     PWRCTRL_DEVPWRSTATUS_HCPB_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPBEVEN, PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM2
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM3, PWRCTRL_DEVPWREN_PWRIOM3_EN),
     PWRCTRL_DEVPWRSTATUS_HCPC_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPCEVEN, PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM3
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM4, PWRCTRL_DEVPWREN_PWRIOM4_EN),
     PWRCTRL_DEVPWRSTATUS_HCPC_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPCEVEN, PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM4
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRIOM5, PWRCTRL_DEVPWREN_PWRIOM5_EN),
     PWRCTRL_DEVPWRSTATUS_HCPC_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPCEVEN, PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_IOM5
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRUART0, PWRCTRL_DEVPWREN_PWRUART0_EN),
     PWRCTRL_DEVPWRSTATUS_HCPA_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPAEVEN, PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_UART0
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRUART1, PWRCTRL_DEVPWREN_PWRUART1_EN),
     PWRCTRL_DEVPWRSTATUS_HCPA_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPAEVEN, PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_UART1
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRADC, PWRCTRL_DEVPWREN_PWRADC_EN),
     PWRCTRL_DEVPWRSTATUS_PWRADC_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_ADCEVEN, PWRCTRL_DEVPWREVENTEN_ADCEVEN_EN)},    //  AM_HAL_PWRCTRL_PERIPH_ADC
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRSCARD, PWRCTRL_DEVPWREN_PWRSCARD_EN),
     PWRCTRL_DEVPWRSTATUS_HCPA_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_HCPAEVEN, PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_SCARD
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRMSPI, PWRCTRL_DEVPWREN_PWRMSPI_EN),
     PWRCTRL_DEVPWRSTATUS_PWRMSPI_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_MSPIEVEN, PWRCTRL_DEVPWREVENTEN_MSPIEVEN_EN)},  //  AM_HAL_PWRCTRL_PERIPH_MSPI
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRPDM, PWRCTRL_DEVPWREN_PWRPDM_EN),
     PWRCTRL_DEVPWRSTATUS_PWRPDM_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_PDMEVEN, PWRCTRL_DEVPWREVENTEN_PDMEVEN_EN)},    //  AM_HAL_PWRCTRL_PERIPH_PDM
    {_VAL2FLD(PWRCTRL_DEVPWREN_PWRBLEL, PWRCTRL_DEVPWREN_PWRBLEL_EN),
     PWRCTRL_DEVPWRSTATUS_BLEL_Msk,
     _VAL2FLD(PWRCTRL_DEVPWREVENTEN_BLELEVEN, PWRCTRL_DEVPWREVENTEN_BLELEVEN_EN)}   //  AM_HAL_PWRCTRL_PERIPH_BLEL
#else // AM_CMSIS_REGS
    {0, 0, 0},                                  //  AM_HAL_PWRCTRL_PERIPH_NONE
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOS_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN}, // AM_HAL_PWRCTRL_PERIPH_IOS
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM0_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM0
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM1_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM1
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM2_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPBEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM2
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM3_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM3
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM4_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM4
    {AM_REG_PWRCTRL_DEVPWREN_PWRIOM5_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPCEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_IOM5
    {AM_REG_PWRCTRL_DEVPWREN_PWRUART0_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_UART0
    {AM_REG_PWRCTRL_DEVPWREN_PWRUART1_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_UART1
    {AM_REG_PWRCTRL_DEVPWREN_PWRADC_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_PWRADC_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_ADCEVEN_EN},  //  AM_HAL_PWRCTRL_PERIPH_ADC
    {AM_REG_PWRCTRL_DEVPWREN_PWRSCARD_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_HCPAEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_SCARD
    {AM_REG_PWRCTRL_DEVPWREN_PWRMSPI_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_PWRMSPI_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_MSPIEVEN_EN}, //  AM_HAL_PWRCTRL_PERIPH_MSPI
    {AM_REG_PWRCTRL_DEVPWREN_PWRPDM_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_PWRPDM_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_PDMEVEN_EN},  //  AM_HAL_PWRCTRL_PERIPH_PDM
    {AM_REG_PWRCTRL_DEVPWREN_PWRBLEL_EN,
     AM_REG_PWRCTRL_DEVPWRSTATUS_BLEL_M,
     AM_REG_PWRCTRL_DEVPWREVENTEN_BLELEVEN_EN}  //  AM_HAL_PWRCTRL_PERIPH_BLEL
#endif // AM_CMSIS_REGS
};


//
// Define the memory control structure.
//
const struct
{
    uint32_t      ui32MemoryEnable;
    uint32_t      ui32MemoryStatus;
    uint32_t      ui32MemoryEvent;
    uint32_t      ui32MemoryMask;
    uint32_t      ui32StatusMask;
}
am_hal_pwrctrl_memory_control[AM_HAL_PWRCTRL_MEM_MAX] =
{
    {0, 0, 0},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_8K_DTCM,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_8K_DTCM,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_8K_DTCM,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_32K_DTCM,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_32K_DTCM,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_32K_DTCM,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_64K_DTCM,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_64K_DTCM,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_64K_DTCM,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_96K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_96K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_96K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_128K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_128K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_128K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_160K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_160K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_160K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_192K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_192K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_192K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_224K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_224K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_224K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_256K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_256K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_256K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_288K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_288K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_288K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_320K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_320K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_320K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_352K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_352K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_352K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_SRAM_384K,
     AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_384K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_SRAM_384K,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_SRAM_MASK},
    {AM_HAL_PWRCTRL_MEMEN_FLASH_512K,
     AM_HAL_PWRCTRL_PWRONSTATUS_FLASH_512K,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_FLASH_512K,
     AM_HAL_PWRCTRL_MEM_REGION_FLASH_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_FLASH_MASK},
    {AM_HAL_PWRCTRL_MEMEN_FLASH_1M,
     AM_HAL_PWRCTRL_PWRONSTATUS_FLASH_1M,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_FLASH_1M,
     AM_HAL_PWRCTRL_MEM_REGION_FLASH_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_FLASH_MASK},
    {AM_HAL_PWRCTRL_MEMEN_CACHE,
     AM_HAL_PWRCTRL_PWRONSTATUS_CACHE,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_CACHE,
     AM_HAL_PWRCTRL_MEM_REGION_CACHE_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_ALT_CACHE_MASK},
    {AM_HAL_PWRCTRL_MEMEN_ALL,
     AM_HAL_PWRCTRL_PWRONSTATUS_ALL,
     AM_HAL_PWRCTRL_MEMPWREVENTEN_ALL,
     AM_HAL_PWRCTRL_MEM_REGION_ALL_MASK,
     AM_HAL_PWRCTRL_MEM_REGION_ALT_ALL_MASK}
};

// ****************************************************************************
//
//  am_hal_pwrctrl_periph_enable()
//  Enable power for a peripheral.
//
// ****************************************************************************
uint32_t
am_hal_pwrctrl_periph_enable(am_hal_pwrctrl_periph_e ePeripheral)
{
#if AM_CMSIS_REGS

// #### INTERNAL BEGIN ####
#if !APOLLO3_FPGA
// #### INTERNAL END ####

    //
    // Enable power control for the given device.
    //
    AM_CRITICAL_BEGIN
    PWRCTRL->DEVPWREN |= am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable;
    AM_CRITICAL_END


// #### INTERNAL BEGIN ####
#else // APOLLO_FPGA
    //
    // Enable power control for the given device.
    //
    AM_CRITICAL_BEGIN
    PWRCTRL->DEVPWREN |= am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable;
    AM_CRITICAL_END

    am_hal_flash_delay(FLASH_CYCLES_US(10));
#endif // !APOLLO3_FPGA
// #### INTERNAL END ####


    for (uint32_t wait_usecs = 0; wait_usecs < AM_HAL_PWRCTRL_MAX_WFE; wait_usecs += 10)
    {
        am_hal_flash_delay(FLASH_CYCLES_US(10));

        if ( (PWRCTRL->DEVPWRSTATUS & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) > 0)
        {
            break;
        }
    }

    //
    // Check the device status.
    //
    if ( (PWRCTRL->DEVPWRSTATUS & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) > 0 )
    {
        return AM_HAL_STATUS_SUCCESS;
    }
    else
    {
        return AM_HAL_STATUS_FAIL;
    }

#else // AM_CMSIS_REGS
// #### INTERNAL BEGIN ####
#if !APOLLO3_FPGA
// #### INTERNAL END ####

    //
    // Enable power control for the given device.
    //
    AM_REGa(PWRCTRL, DEVPWREN, | , am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable);

// #### INTERNAL BEGIN ####
#else
    //
    // Enable power control for the given device.
    //
    AM_REGa(PWRCTRL, DEVPWREN, | , am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable);

    am_hal_flash_delay(FLASH_CYCLES_US(10));
#endif // !APOLLO3_FPGA
// #### INTERNAL END ####

    for (uint32_t wait_usecs = 0; wait_usecs < AM_HAL_PWRCTRL_MAX_WFE; wait_usecs += 10)
    {
        am_hal_flash_delay(FLASH_CYCLES_US(10));

        if ((AM_REG(PWRCTRL, DEVPWRSTATUS) & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) > 0)
        {
            break;
        }
    }

    //
    // Check the device status.
    //
    if ((AM_REG(PWRCTRL, DEVPWRSTATUS) & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) > 0)
    {
        return AM_HAL_STATUS_SUCCESS;
    }
    else
    {
        return AM_HAL_STATUS_FAIL;
    }
#endif // AM_CMSIS_REGS
}

// ****************************************************************************
//
//  am_hal_pwrctrl_periph_disable()
//  Disable power for a peripheral.
//
// ****************************************************************************
uint32_t
am_hal_pwrctrl_periph_disable(am_hal_pwrctrl_periph_e ePeripheral)
{
// #### INTERNAL BEGIN ####
#if !APOLLO3_FPGA
// #### INTERNAL END ####

    //
    // Disable power domain for the given device.
    //
#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    PWRCTRL->DEVPWREN &= ~am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable;
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    AM_REGa(PWRCTRL, DEVPWREN, &, ~am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable);
#endif // AM_CMSIS_REGS

// #### INTERNAL BEGIN ####
#else
    //
    // Disable power domain for the given device.
    //
#if AM_CMSIS_REGS
    AM_CRITICAL_BEGIN
    PWRCTRL->DEVPWREN &= ~am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable;
    AM_CRITICAL_END
#else // AM_CMSIS_REGS
    AM_REGa(PWRCTRL, DEVPWREN, & , ~am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphEnable);
#endif // AM_CMSIS_REGS

    am_hal_flash_delay(FLASH_CYCLES_US(10));
#endif // !APOLLO3_FPGA
// #### INTERNAL END ####

    for (uint32_t wait_usecs = 0; wait_usecs < AM_HAL_PWRCTRL_MAX_WFE; wait_usecs += 10)
    {
        am_hal_flash_delay(FLASH_CYCLES_US(10));

#if AM_CMSIS_REGS
        if ( (PWRCTRL->DEVPWRSTATUS & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) == 0 )
        {
            break;
        }
#else // AM_CMSIS_REGS
        if ((AM_REG(PWRCTRL, DEVPWRSTATUS) & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) == 0)
        {
            break;
        }
#endif // AM_CMSIS_REGS
    }

    //
    // Check the device status.
    //
#if AM_CMSIS_REGS
    if ( ( PWRCTRL->DEVPWRSTATUS & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) == 0 )
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#else // AM_CMSIS_REGS
    if ((AM_REG(PWRCTRL, DEVPWRSTATUS) & am_hal_pwrctrl_peripheral_control[ePeripheral].ui32PeriphStatus) == 0)
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#endif // AM_CMSIS_REGS
    else
    {
        return AM_HAL_STATUS_FAIL;
    }
}

//*****************************************************************************
//
//! @brief Determine whether a peripheral is currently enabled.
//!
//! @param ePeripheral – The peripheral to enable.
//! @param pui32Enabled – Pointer to a ui32 that will return as 1 or 0.
//!
//! This function determines to the caller whether a given peripheral is
//! currently enabled or disabled.
//!
//! @return status - generic or interface specific status.
//
//*****************************************************************************
uint32_t
am_hal_pwrctrl_periph_enabled(am_hal_pwrctrl_periph_e ePeripheral,
                              uint32_t *pui32Enabled)
{
    uint32_t ui32Mask = 0;
    uint32_t ui32Enabled = 0;

    if ( pui32Enabled == NULL )
    {
        return AM_HAL_STATUS_INVALID_ARG;
    }

#if AM_CMSIS_REGS
    switch ( ePeripheral )
    {
        case AM_HAL_PWRCTRL_PERIPH_NONE:
        case AM_HAL_PWRCTRL_PERIPH_SCARD:
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOS:
        case AM_HAL_PWRCTRL_PERIPH_UART0:
        case AM_HAL_PWRCTRL_PERIPH_UART1:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_HCPA_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOM0:
        case AM_HAL_PWRCTRL_PERIPH_IOM1:
        case AM_HAL_PWRCTRL_PERIPH_IOM2:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_HCPB_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOM3:
        case AM_HAL_PWRCTRL_PERIPH_IOM4:
        case AM_HAL_PWRCTRL_PERIPH_IOM5:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_HCPC_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_ADC:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_PWRADC_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_MSPI:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_PWRMSPI_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_PDM:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_PWRPDM_Msk;
            break;
        case AM_HAL_PWRCTRL_PERIPH_BLEL:
            ui32Mask = PWRCTRL_DEVPWRSTATUS_BLEL_Msk;
            break;
        default:
            return AM_HAL_STATUS_FAIL;
    }

    if ( ui32Mask != 0 )
    {
        ui32Enabled = PWRCTRL->DEVPWRSTATUS & ui32Mask ? 1 : 0;
    }
#else // AM_CMSIS_REGS
    switch ( ePeripheral )
    {
        case AM_HAL_PWRCTRL_PERIPH_NONE:
        case AM_HAL_PWRCTRL_PERIPH_SCARD:
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOS:
        case AM_HAL_PWRCTRL_PERIPH_UART0:
        case AM_HAL_PWRCTRL_PERIPH_UART1:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_HCPA_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOM0:
        case AM_HAL_PWRCTRL_PERIPH_IOM1:
        case AM_HAL_PWRCTRL_PERIPH_IOM2:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_HCPB_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_IOM3:
        case AM_HAL_PWRCTRL_PERIPH_IOM4:
        case AM_HAL_PWRCTRL_PERIPH_IOM5:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_HCPC_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_ADC:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_PWRADC_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_MSPI:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_PWRMSPI_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_PDM:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_PWRPDM_M;
            break;
        case AM_HAL_PWRCTRL_PERIPH_BLEL:
            ui32Mask = AM_REG_PWRCTRL_DEVPWRSTATUS_BLEL_M;
            break;
        default:
            return AM_HAL_STATUS_FAIL;
    }

    if ( ui32Mask != 0 )
    {
        ui32Enabled = AM_REG(PWRCTRL, DEVPWRSTATUS) & ui32Mask ? 1 : 0;
    }
#endif // AM_CMSIS_REGS

    *pui32Enabled = ui32Enabled;

    return AM_HAL_STATUS_SUCCESS;
}



// ****************************************************************************
//
//  am_hal_pwrctrl_memory_enable()
//  Enable a configuration of memory.
//
// ****************************************************************************
uint32_t
am_hal_pwrctrl_memory_enable(am_hal_pwrctrl_mem_e eMemConfig)
{
    uint32_t ui32MemEnMask, ui32MemDisMask, ui32MemRegionMask, ui32MemStatusMask;
// #### INTERNAL BEGIN ####
#if 0
    uint32_t ui32MemEventMask;
#endif
// #### INTERNAL END ####

    ui32MemEnMask     =  am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryEnable;
    ui32MemDisMask    = ~am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryEnable;
// #### INTERNAL BEGIN ####
#if 0
    ui32MemEventMask  = am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryEvent;
#endif
// #### INTERNAL END ####
    ui32MemRegionMask = am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryMask;
    ui32MemStatusMask = am_hal_pwrctrl_memory_control[eMemConfig].ui32StatusMask;

    //
    // Disable unneeded memory. If nothing to be disabled, skip to save time.
    //
    // Note that a deliberate disable step using a disable mask is taken here
    // for 2 reasons: 1) To only affect the specified type of memory, and 2)
    // To avoid inadvertently disabling any memory currently being depended on.
    //
    if ( ui32MemDisMask != 0 )
    {
#if AM_CMSIS_REGS
        PWRCTRL->MEMPWREN &=
            ~(ui32MemDisMask & ui32MemRegionMask)                                   |
             (_VAL2FLD(PWRCTRL_MEMPWREN_DTCM, PWRCTRL_MEMPWREN_DTCM_GROUP0DTCM0)    |
              _VAL2FLD(PWRCTRL_MEMPWREN_FLASH0, PWRCTRL_MEMPWREN_FLASH0_EN));
#else // AM_CMSIS_REGS
        AM_REG(PWRCTRL, MEMPWREN) &= ~(ui32MemDisMask & ui32MemRegionMask) |
            (AM_REG_PWRCTRL_MEMPWREN_DTCM_GROUP0DTCM0 | AM_REG_PWRCTRL_MEMPWREN_FLASH0_EN);
#endif // AM_CMSIS_REGS
        am_hal_flash_delay(FLASH_CYCLES_US(1));
    }

// #### INTERNAL BEGIN ####
#if !APOLLO3_FPGA
#if 0
    uint32_t ui32Critical = 0;

    //
    // Clear any pending events.
    //
    ui32Critical = am_hal_interrupt_master_disable();   // Enter critical section protection.
    AM_ASM_SEV;
    AM_ASM_WFE;
    am_hal_interrupt_master_set(ui32Critical);          // Exit critical section.

    //
    // Set the event to trigger when device is enabled.
    //
    AM_REG(PWRCTRL,MEMPWREVENTEN) = ui32MemEventMask;
#endif
// #### INTERNAL END ####

    //
    // Enable the required memory.
    //
    if ( ui32MemEnMask != 0 )
    {
#if AM_CMSIS_REGS
        PWRCTRL->MEMPWREN |= ui32MemEnMask;
#else // AM_CMSIS_REGS
        AM_REG(PWRCTRL, MEMPWREN) |= ui32MemEnMask;
#endif // AM_CMSIS_REGS

        for (uint32_t wait_usecs = 0; wait_usecs < AM_HAL_PWRCTRL_MAX_WFE; wait_usecs += 10)
        {
            am_hal_flash_delay(FLASH_CYCLES_US(10));

// #### INTERNAL BEGIN ####
#if 0
            //
            // Execute Wait for Event with interrupts disabled.
            //
            ui32Critical = am_hal_interrupt_master_disable();   // Enter critical section protection.
            AM_ASM_WFE;
            am_hal_interrupt_master_set(ui32Critical);          // Exit critical section.
#endif
// #### INTERNAL END ####
#if AM_CMSIS_REGS
            if ( (PWRCTRL->MEMPWRSTATUS & ui32MemStatusMask) ==
                  am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryStatus )
            {
                break;
            }
#else // AM_CMSIS_REGS
            if ((AM_REG(PWRCTRL, MEMPWRSTATUS) & ui32MemStatusMask) == am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryStatus )
            {
                break;
            }
#endif // AM_CMSIS_REGS
        }
    }
// #### INTERNAL BEGIN ####
#else
    //
    // Enable the required memory.
    //
    if ( ui32MemEnMask != 0 )
    {
#if AM_CMSIS_REGS
        PWRCTRL->MEMPWREN |= ui32MemEnMask;
#else // AM_CMSIS_REGS
        AM_REG(PWRCTRL, MEMPWREN) |= ui32MemEnMask;
#endif // AM_CMSIS_REGS
    }

    am_hal_flash_delay(FLASH_CYCLES_US(10));
#endif // !APOLLO3_FPGA
// #### INTERNAL END ####

    //
    // Return status based on whether the power control memory status has reached the desired state.
    //
#if AM_CMSIS_REGS
    if ( ( PWRCTRL->MEMPWRSTATUS & ui32MemStatusMask) ==
           am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryStatus )
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#else // AM_CMSIS_REGS
    if ((AM_REG(PWRCTRL, MEMPWRSTATUS) & ui32MemStatusMask) == am_hal_pwrctrl_memory_control[eMemConfig].ui32MemoryStatus )
    {
        return AM_HAL_STATUS_SUCCESS;
    }
#endif // AM_CMSIS_REGS
    else
    {
        return AM_HAL_STATUS_FAIL;
    }
}

// ****************************************************************************
//
//  am_hal_pwrctrl_low_power_init()
//  Initialize system for low power configuration.
//
// ****************************************************************************
uint32_t
am_hal_pwrctrl_low_power_init(void)
{
    uint32_t      ui32Status;

#if AM_CMSIS_REGS
    //
    // Check if the BLE is already enabled.
    //
    if ( PWRCTRL->DEVPWRSTATUS_b.BLEL == 0)
    {
        //
        // First request the BLE feature and check that it was available and acknowledged.
        //
        MCUCTRL->FEATUREENABLE = MCUCTRL_FEATUREENABLE_BLEREQ_Msk;
        ui32Status = am_hal_flash_delay_status_check(10000,
                        (uint32_t)&MCUCTRL->FEATUREENABLE,
                        (MCUCTRL_FEATUREENABLE_BLEAVAIL_Msk |
                          MCUCTRL_FEATUREENABLE_BLEACK_Msk  |
                          MCUCTRL_FEATUREENABLE_BLEREQ_Msk),
                        (MCUCTRL_FEATUREENABLE_BLEAVAIL_Msk |
                         MCUCTRL_FEATUREENABLE_BLEACK_Msk   |
                         MCUCTRL_FEATUREENABLE_BLEREQ_Msk),
                         true);

        if (AM_HAL_STATUS_SUCCESS != ui32Status)
        {
            return AM_HAL_STATUS_TIMEOUT;
        }

        //
        // Next, enable the BLE Buck.
        //
        PWRCTRL->SUPPLYSRC |= _VAL2FLD(PWRCTRL_SUPPLYSRC_BLEBUCKEN,
                                       PWRCTRL_SUPPLYSRC_BLEBUCKEN_EN);

        //
        // Allow the buck to go to low power mode in BLE sleep.
        //
        PWRCTRL->MISC |= _VAL2FLD(PWRCTRL_MISC_MEMVRLPBLE,
                                  PWRCTRL_MISC_MEMVRLPBLE_EN);

        //
        // Check for Apollo3 A0 Silicon.
        //
        if ( APOLLO3_A0 )
        {
            // Disable SIMO Buck clkdiv because if ble is out of reset then the same bit divides the simobuck clk too agressively.
            MCUCTRL->SIMOBUCK4_b.SIMOBUCKCLKDIVSEL = 0x0;
            MCUCTRL->BLEBUCK2_b.BLEBUCKTONHITRIM   = 0xF;
            MCUCTRL->BLEBUCK2_b.BLEBUCKTONLOWTRIM  = 0xF;
        }
    }
#else // AM_CMSIS_REGS
    //
    // Check if the BLE is already enabled.
    //
    if (AM_BFR(PWRCTRL, DEVPWRSTATUS, BLEL) == 0)
    {
        //
        // First request the BLE feature and check that it was available and acknowledged.
        //
        AM_REG(MCUCTRL, FEATUREENABLE) = AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_M;
        ui32Status = am_hal_flash_delay_status_check(10000,
                                                     AM_REG_MCUCTRLn(0) + AM_REG_MCUCTRL_FEATUREENABLE_O,
                                                     (AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_M   |
                                                      AM_REG_MCUCTRL_FEATUREENABLE_BLEACK_M     |
                                                     AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_M),
                                                     (AM_REG_MCUCTRL_FEATUREENABLE_BLEAVAIL_M   |
                                                      AM_REG_MCUCTRL_FEATUREENABLE_BLEACK_M     |
                                                      AM_REG_MCUCTRL_FEATUREENABLE_BLEREQ_M),
                                                     true);

        if (AM_HAL_STATUS_SUCCESS != ui32Status)
        {
            return AM_HAL_STATUS_TIMEOUT;
        }

        //
        // Next, enable the BLE Buck.
        //
        AM_REG(PWRCTRL, SUPPLYSRC) |= AM_REG_PWRCTRL_SUPPLYSRC_BLEBUCKEN_EN;

        //
        // Allow the buck to go to low power mode in BLE sleep.
        //
        AM_REG(PWRCTRL, MISC) |= AM_REG_PWRCTRL_MISC_MEMVRLPBLE_EN;

        //
        // Check for Apollo3 A0 Silicon.
        //
        if ( APOLLO3_A0 )
        {
            // Disable SIMO Buck clkdiv because if ble is out of reset then the same bit divides the simobuck clk too agressively.
            AM_BFW(MCUCTRL, SIMOBUCK4, SIMOBUCKCLKDIVSEL, 0x0);
            AM_BFW(MCUCTRL, BLEBUCK2,  BLEBUCKTONHITRIM,  0xF);
            AM_BFW(MCUCTRL, BLEBUCK2,  BLEBUCKTONLOWTRIM, 0xF);
        }
    }
#endif // AM_CMSIS_REGS

    return AM_HAL_STATUS_SUCCESS;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
