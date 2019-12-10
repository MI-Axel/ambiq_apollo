/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     BoardSetup.c
********************************************************************************
*
*     Description:  Setup board peripherals
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "usb_device.h"
#include "cs43l22.h"
#include <stdio.h>

I2C_HandleTypeDef hI2C1;
I2S_HandleTypeDef hI2S2;
I2S_HandleTypeDef hI2S3;
DMA_HandleTypeDef DMA_I2S2_RX;
DMA_HandleTypeDef DMA_I2S3_TX;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);

#if defined( __CC_ARM )

//-----------------------------------------------------------------------------
// METHOD:  fputc
// PURPOSE: Needed to make printf work to debug console
//-----------------------------------------------------------------------------
int fputc(int c, FILE *stream)
{
   return(ITM_SendChar(c) );

}   // End fputc

#endif


//-----------------------------------------------------------------------------
// METHOD:  SystemClock_Config
// PURPOSE: Configure the system clocks
//-----------------------------------------------------------------------------
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK   |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1  |
                                  RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 344;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    //STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported
    if (HAL_GetREVID() == 0x1001)
    {
        // Enable the Flash prefetch
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
    }

}   // End SystemClock_Config


//-----------------------------------------------------------------------------
// METHOD:  MX_I2C1_Init
// PURPOSE: Setup I2C to talk to the CODEC
//-----------------------------------------------------------------------------
void MX_I2C1_Init(void)
{
    hI2C1.Instance = I2C1;
    hI2C1.Init.ClockSpeed = 100000;
    hI2C1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hI2C1.Init.OwnAddress1 = 0;
    hI2C1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hI2C1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hI2C1.Init.OwnAddress2 = 0;
    hI2C1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hI2C1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hI2C1);

}   // End MX_I2C1_Init



//-----------------------------------------------------------------------------
// METHOD:  MX_I2S2_Init
// PURPOSE: Setup I2S for the MIC
//-----------------------------------------------------------------------------
void MX_I2S2_Init(void)
{
    __HAL_I2S_DISABLE(&hI2S2);

    hI2S2.Instance = SPI2;
    hI2S2.Init.Mode = I2S_MODE_MASTER_RX;
    hI2S2.Init.Standard = I2S_STANDARD_LSB;
    hI2S2.Init.DataFormat = I2S_DATAFORMAT_16B;
    hI2S2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    hI2S2.Init.AudioFreq = I2S_AUDIOFREQ_16K * 2;
    hI2S2.Init.CPOL  = I2S_CPOL_HIGH;
    hI2S2.Init.ClockSource = I2S_CLOCK_PLL;
    hI2S2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

    HAL_I2S_Init(&hI2S2);

}   // End MX_I2S3_Init


//-----------------------------------------------------------------------------
// METHOD:  MX_I2S3_Init
// PURPOSE: Setup I2S to the CODEC
//-----------------------------------------------------------------------------
void MX_I2S3_Init(void)
{
    __HAL_I2S_DISABLE(&hI2S3);

    hI2S3.Instance = SPI3;
    hI2S3.Init.Mode = I2S_MODE_MASTER_TX;
    hI2S3.Init.Standard = I2S_STANDARD_PHILIPS;
    hI2S3.Init.DataFormat = I2S_DATAFORMAT_16B_EXTENDED;
    hI2S3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hI2S3.Init.AudioFreq = I2S_AUDIOFREQ_48K;
    hI2S3.Init.CPOL = I2S_CPOL_LOW;
    hI2S3.Init.ClockSource = I2S_CLOCK_PLL;
    hI2S3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

    HAL_I2S_Init(&hI2S3);

}   // End MX_I2S3_Init


//-----------------------------------------------------------------------------
// METHOD:  MX_GPIO_Init
// PURPOSE: Setup I/O pins
//-----------------------------------------------------------------------------
void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();


    // CODEC Reset pin
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2S2 GPIO Configuration
    PB10      ------> CLK
    PC3       ------> DATA
    */
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /**I2S3 GPIO Configuration
    PA4      ------> I2S3_FRCLK
    PC7      ------> I2S3_MCK
    PC10     ------> I2S3_CK
    PC12     ------> I2S3_SD
    PC11     ------> I2S3_ext_SD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // LED4, LED3, LED5, LED6
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
    GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PDM_OUT_Pin */
    GPIO_InitStruct.Pin = PDM_OUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : BOOT1_Pin */
    GPIO_InitStruct.Pin = BOOT1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : CLK_IN_Pin */
    GPIO_InitStruct.Pin = CLK_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
    GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin
                          | Audio_RST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
    GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin
                          | Audio_RST_Pin, GPIO_PIN_RESET);

}   // End MX_GPIO_Init


//-----------------------------------------------------------------------------
// METHOD:  BoardInit
// PURPOSE: Setup board peripherals
//-----------------------------------------------------------------------------
void BoardInit(void)
{
    MX_I2C1_Init();

    MX_I2S2_Init();

    MX_I2S3_Init();

}   // End BoardInit

//-----------------------------------------------------------------------------
// METHOD:  CoreInit
// PURPOSE: Setup board peripherals
//-----------------------------------------------------------------------------
void CoreInit(void)
{
    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_USB_DEVICE_Init();

}   // End CoreInit
