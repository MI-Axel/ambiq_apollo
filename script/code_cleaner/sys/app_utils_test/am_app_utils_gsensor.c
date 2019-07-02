//*****************************************************************************
//
//! @file am_app_utils_gsensor.c
//!
//! @brief buzzer interface for Maya
//!
//! Functions for performing buzzer actions
//
//*****************************************************************************
#include "am_util.h"
#include "am_app_utils.h"

//*****************************************************************************
//
// Variables
//
//*****************************************************************************
#if configUSE_GSENSOR
static void* g_pGsensorIomHandle = NULL;

#define GSENSOR_IOM     1
#define GSENSOR_CS      0   //dummy, using I2C

#define GET_I2CADDR(cfg)    \
(((cfg) & 0x000FFF00) >> (8 + 1))

#define LIS2DW_MEMS_I2C_ADDRESS         0x30  // 0x33
#define LIS2DW_WHO_AM_I                 0x0F  // device identification register
#define LIS2DW_CTRL0                    0x1E

#define LIS2DW_WAKEUP_PIN               7

#define AM_DEVICES_LIS2DW_CTRL_REG1        0x20
#define AM_DEVICES_LIS2DW_CTRL_REG2        0x21
#define AM_DEVICES_LIS2DW_CTRL_REG3        0x22
#define AM_DEVICES_LIS2DW_CTRL_REG4        0x23
#define AM_DEVICES_LIS2DW_CTRL_REG5        0x24
#define AM_DEVICES_LIS2DW_CTRL_REG6        0x25

#define X0_plus     150
#define X0_minus    -150
#define Y0_plus     150
#define Y0_minus    -150
#define Z_max       (-1000+200)
#define Z_min       (-1000-200)  

#define mg_per_bit          0.244 // +- 2G
#define GSENSOR_QUITE_MS    (20*1000)//(1*60*1000) //MS unit
    
static TickType_t firstTick = 0;

//*****************************************************************************
//
// Configuration structure for the IO Master.
//
//*****************************************************************************
am_hal_iom_config_t g_sGsensorIomConfig =
{
    .eInterfaceMode       = AM_HAL_IOM_I2C_MODE,
    .ui32ClockFreq        = AM_HAL_IOM_1MHZ,
};

//
// IOM Configuration.
//
static am_hal_iom_config_t g_sGsensorIomI2CConfig =
{
    .eInterfaceMode       = AM_HAL_IOM_I2C_MODE,
    .ui32ClockFreq        = AM_HAL_IOM_400KHZ,
    .eSpiMode             = AM_HAL_IOM_SPI_MODE_0,
};

const am_hal_gpio_pincfg_t g_sGsensorWakePinConfig =
{
    .uFuncSel       = 3,
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
    .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
    .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN, //AM_HAL_GPIO_PIN_RDZERO_ZERO, //AM_HAL_GPIO_PIN_RDZERO_ZERO, //AM_HAL_GPIO_PIN_RDZERO_READPIN,
    .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO
};  

void gsensor_iom_slave_read(uint32_t offset, uint32_t *pBuf, uint32_t size)
{
    am_hal_iom_transfer_t Transaction;

    //
    // Set up the IOM transaction.
    //
    Transaction.ui8Priority     = 1;        // High priority for now.
    Transaction.eDirection      = AM_HAL_IOM_RX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = (offset & 0x0000FFFF);
    Transaction.ui32NumBytes    = size;
    Transaction.pui32RxBuffer   = (uint32_t *)pBuf;
  
    Transaction.uPeerInfo.ui32I2CDevAddr = GET_I2CADDR(AM_HAL_IOS_USE_I2C | AM_HAL_IOS_I2C_ADDRESS(LIS2DW_MEMS_I2C_ADDRESS));
    Transaction.ui8RepeatCount  = 0;
    Transaction.ui32PauseCondition = 0;
    Transaction.ui32StatusSetClr = 0;
    Transaction.bContinue       = false;

    //
    // Start the transaction.
    //
    //am_hal_iom_nonblocking_transfer(g_pGsensorIomHandle, &Transaction, NULL, NULL);

    am_hal_iom_blocking_transfer(g_pGsensorIomHandle, &Transaction); 
}

void gsensor_iom_slave_write(uint32_t offset, uint32_t *pBuf, uint32_t size)
{
    am_hal_iom_transfer_t Transaction;

    //
    // Set up the IOM transaction.
    //
    Transaction.ui8Priority     = 1;        // High priority for now.
    Transaction.eDirection      = AM_HAL_IOM_TX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = (offset & 0x0000FFFF);
    Transaction.ui32NumBytes    = size;
    Transaction.pui32TxBuffer   = (uint32_t *)pBuf;
  
    Transaction.uPeerInfo.ui32I2CDevAddr = GET_I2CADDR(AM_HAL_IOS_USE_I2C | AM_HAL_IOS_I2C_ADDRESS(LIS2DW_MEMS_I2C_ADDRESS));
    Transaction.ui8RepeatCount  = 0;
    Transaction.ui32PauseCondition = 0;
    Transaction.ui32StatusSetClr = 0;
    Transaction.bContinue       = false;

    //
    // Start the transaction.
    //
    //am_hal_iom_nonblocking_transfer(g_pGsensorIomHandle, &Transaction, NULL, NULL);
    
    uint32_t ui32Status = am_hal_iom_blocking_transfer(g_pGsensorIomHandle, &Transaction);

}

void gsensor_reg_block_write(uint8_t ui8StartRegister, uint32_t *pui32Values, uint32_t ui32NumBytes)
{
    uint8_t ui8Offset;

    // for I2C multiple data write.
    ui8Offset = 0x80 | ui8StartRegister;
        
    //am_hal_iom_i2c_write(psDevice->ui32IOMModule,
    //                     psDevice->ui32ChipSelect,
    //                     pui32Values, ui32NumBytes,
    //                     AM_HAL_IOM_OFFSET(ui8Offset));
    gsensor_iom_slave_write(ui8Offset, pui32Values, ui32NumBytes);    
}

void gsensor_wakeup_pin_handle()
{
    uint32_t ui32PinState;

    am_hal_gpio_state_read(LIS2DW_WAKEUP_PIN, AM_HAL_GPIO_INPUT_READ, &ui32PinState);

    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
    
    //am_app_utils_task_send_fromISR(AM_APP_ISR_GPIO, AM_APP_TASK_GSENSOR, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);   
}

void gsensor_wakeup_button_init(void)
{
    am_hal_gpio_pinconfig(LIS2DW_WAKEUP_PIN, g_sGsensorWakePinConfig);
    //am_hal_gpio_interrupt_register(LIS2DW_WAKEUP_PIN, gsensor_wakeup_pin_handle);
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));

    //am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
    
    NVIC_SetPriority(GPIO_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
    NVIC_EnableIRQ(GPIO_IRQn);
    
}

void am_app_util_gsensor_config(void)
{
    uint8_t sRegBuffer[6];
    uint32_t  ui32Temp;
        
    ui32Temp = 0x20; //0x70;//0x63;
    gsensor_iom_slave_write(0x34, &ui32Temp, 1 ); // WAKE_UP_THS // THS x (FS 2g/2^6) 
    
    ui32Temp = 0x60;//0x15;//0x11;
    gsensor_iom_slave_write(0x35, &ui32Temp, 1);  // WAKE_UP_DUR
    
    ui32Temp = 0x20;
    gsensor_iom_slave_write(0x3f, &ui32Temp, 1); //CTRL7: bit6: INT2_ON_INT1, bit5:INTERRUPTS_ENABLE

    // software reset,the procedure can take 5us 
    ui32Temp = 0x0C;
    gsensor_iom_slave_write(0x21, &ui32Temp, 1); 

    am_util_delay_us(8);   
     
    sRegBuffer[0] = 0x20;     // CTRL_REG1  #100hz
    sRegBuffer[1] = 0x00;     // CTRL_REG2
    sRegBuffer[2] = 0x00;     // CTRL_REG3
    sRegBuffer[3] = 0x20;     // CTRL_REG4
    sRegBuffer[4] = 0x00;     // CTRL_REG5
    sRegBuffer[5] = 0x04;     // CTRL_REG6  #FS 2 g LOW_NOISE enabled

#if 0
    gsensor_reg_block_write(AM_DEVICES_LIS2DW_CTRL_REG1, (uint32_t *)sRegBuffer, 6);
#else    // 0
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG1, (uint32_t *)&sRegBuffer[0], 1);
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG2, (uint32_t *)&sRegBuffer[1], 1);
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG3, (uint32_t *)&sRegBuffer[2], 1);
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG4, (uint32_t *)&sRegBuffer[3], 1);
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG5, (uint32_t *)&sRegBuffer[4], 1);
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG6, (uint32_t *)&sRegBuffer[5], 1);
#endif    // 0
    
#if 0   
    uint32_t ui32Temp1 = 0xff , ui32Temp2 = 0xFF, ui32Temp3 = 0xFF, ui32Temp4 = 0xFF, ui32Temp5 = 0xFF, ui32Temp6 = 0xFF;
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG1, &ui32Temp1, 1 );
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG2, &ui32Temp2, 1 );
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG3, &ui32Temp3, 1 );
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG4, &ui32Temp4, 1 );
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG5, &ui32Temp5, 1 );
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG6, &ui32Temp6, 1 );
    
    gsensor_iom_slave_read(AM_DEVICES_LIS2DW_CTRL_REG1, &ui32Temp1, 1 );
#endif    // 0
}

void am_app_util_gsensor_init(void)
{
    am_hal_iom_initialize(GSENSOR_IOM, &g_pGsensorIomHandle);
    am_hal_iom_power_ctrl(g_pGsensorIomHandle, AM_HAL_SYSCTRL_WAKE, false);
    am_hal_iom_configure(g_pGsensorIomHandle, &g_sGsensorIomI2CConfig);
//    am_hal_iom_interrupt_enable(g_pGsensorIomHandle, AM_HAL_IOM_INT_THR | AM_HAL_IOM_INT_CMDCMP);
    am_hal_iom_enable(g_pGsensorIomHandle);

    am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM1_SCL,  g_AM_BSP_GPIO_IOM1_SCL);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_IOM1_SDA,  g_AM_BSP_GPIO_IOM1_SDA);


#if 1
    am_hal_gpio_pinconfig(LIS2DW_WAKEUP_PIN, g_sGsensorWakePinConfig);
    //am_hal_gpio_interrupt_register(LIS2DW_WAKEUP_PIN, gsensor_wakeup_pin_handle);
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
#endif    // 1
    am_app_util_gsensor_config();
    
    am_util_delay_ms(50);
}


void am_app_util_gsensor_power_down(void)
{
    uint32_t ui32Temp;
    
    // software reset
    ui32Temp = 0x44;
    gsensor_iom_slave_write(0x21, &ui32Temp, 1);
    am_util_delay_ms(50);

    // write 0x00 to CTRL1 to enter power down mode
    ui32Temp = 0x00;
    gsensor_iom_slave_write(0x20, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x20, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL1 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL2 to enter power down mode
    ui32Temp = 0x10;
    gsensor_iom_slave_write(0x21, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x21, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL2 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL3 to enter power down mode
    ui32Temp = 0x2a;
    gsensor_iom_slave_write(0x22, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x22, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL3 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL4 to enter power down mode
    ui32Temp = 0x00;
    gsensor_iom_slave_write(0x23, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x23, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL4 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL5 to enter power down mode
    ui32Temp = 0x00;
    gsensor_iom_slave_write(0x24, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x24, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL5 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL6 to enter power down mode
    ui32Temp = 0x00;
    gsensor_iom_slave_write(0x25, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x25, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL6 = 0x%02x. \n", ui32Temp);

    // write 0x00 to CTRL7 to enter power down mode
    ui32Temp = 0x40;
    gsensor_iom_slave_write(0x3f, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x3f, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("CTRL7 = 0x%02x. \n", ui32Temp);

    // write 0x00 to WAKE_UP_THS to enter power down mode
    ui32Temp = 0x40;
    gsensor_iom_slave_write(0x34, &ui32Temp, 1);

    ui32Temp = 0x55;
    gsensor_iom_slave_read(0x34, &ui32Temp, 1);
    AM_APP_LOG_DEBUG("WAKE_UP_THS = 0x%02x. \n", ui32Temp);

//    ui32Temp = 0x0a;
//    gsensor_iom_slave_write(0x22, &ui32Temp, 1);
//
//    ui32Temp = 0x0b;
//    gsensor_iom_slave_write(0x22, &ui32Temp, 1);

    am_util_delay_ms(50);
    uint8_t result[6];
    gsensor_iom_slave_read(0x28, (uint32_t *)&result[0], 1);
    gsensor_iom_slave_read(0x29, (uint32_t *)&result[1], 1);
    gsensor_iom_slave_read(0x2a, (uint32_t *)&result[2], 1);
    gsensor_iom_slave_read(0x2b, (uint32_t *)&result[3], 1);
    gsensor_iom_slave_read(0x2c, (uint32_t *)&result[4], 1);
    gsensor_iom_slave_read(0x2d, (uint32_t *)&result[5], 1);

    AM_APP_LOG_DEBUG("Lis3mdl X0=%X, X1=%X, Y0=%X, Y1= %X, Z0=%X, Z1=%X\n", result[0], result[1], result[2], result[3], result[4], result[5]);

    am_hal_iom_power_ctrl(g_pGsensorIomHandle, AM_HAL_SYSCTRL_DEEPSLEEP, false);
}


void am_app_util_gsensor_system_power_off(void)
{
    //
    // Disable all interrupts
    //
    // am_hal_interrupt_master_disable();

    for(uint8_t i = 0; i < 32; i++)
    {
        NVIC_DisableIRQ(i);         // disable all IRQs
        NVIC_ClearPendingIRQ(i);    // clear all pending IRQs
    }
    
    //
    // Suspend all tasks
    // 
    vTaskSuspendAll();

    //
    // Stop Stimer
    //
    am_hal_stimer_int_clear(AM_HAL_STIMER_INT_COMPAREA);
    am_hal_stimer_int_disable(AM_HAL_STIMER_INT_COMPAREA);
    am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR |AM_HAL_STIMER_CFG_FREEZE);

    //
    // Turn off peripherals
    //
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOS);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM2);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM3);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM4);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM5);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_ADC);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_SCARD);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_MSPI);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_PDM);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_BLEL);

    //
    // Turn OFF Flash1
    //
    if ( am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEM_FLASH_512K) )
    {
    }

    //
    // Power down SRAM
    //
    
    //PWRCTRL->MEMPWDINSLEEP_b.SRAMPWDSLP = PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER32K;


    // GPIO12 (PDMC) set to low
    am_hal_gpio_pinconfig(PDM_CLK, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(PDM_CLK, AM_HAL_GPIO_OUTPUT_CLEAR);

    // GPIO38 (nSPK_POWER) set to low
    am_hal_gpio_pinconfig(BUZZER_CAP_PWR_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);

    // IOM1 I2C IOs output high
    am_hal_gpio_pinconfig(8, g_AM_HAL_GPIO_OUTPUT);    // scl
    am_hal_gpio_pinconfig(9, g_AM_HAL_GPIO_OUTPUT);    // sda
    am_hal_gpio_pinconfig(7, g_AM_HAL_GPIO_OUTPUT);    // int1
    am_hal_gpio_state_write(8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(9, AM_HAL_GPIO_OUTPUT_SET);
    //am_hal_gpio_state_write(7, AM_HAL_GPIO_OUTPUT_CLEAR);

    // Disable all other GPIOs
    am_hal_gpio_pinconfig(LED_D1, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D2, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D3, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D4, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D5, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D6, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D7, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D8, g_AM_HAL_GPIO_DISABLE);

    am_hal_gpio_pinconfig(CTRL_BUTTON2, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(PDM_DATA, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(4, g_AM_HAL_GPIO_DISABLE);    // wake
    am_hal_gpio_pinconfig(49, g_AM_HAL_GPIO_DISABLE);   // mode
    am_hal_gpio_pinconfig(7, g_AM_HAL_GPIO_DISABLE);    // int1
//    am_hal_gpio_pinconfig(8, g_AM_HAL_GPIO_DISABLE);    // scl
//    am_hal_gpio_pinconfig(9, g_AM_HAL_GPIO_DISABLE);    // sda
    am_hal_gpio_pinconfig(17, g_AM_HAL_GPIO_DISABLE);   // optional button
    am_hal_gpio_pinconfig(22, g_AM_HAL_GPIO_DISABLE);   // tx0
    am_hal_gpio_pinconfig(23, g_AM_HAL_GPIO_DISABLE);   // rx0
    am_hal_gpio_pinconfig(33, g_AM_HAL_GPIO_DISABLE);   // amic audio out
    am_hal_gpio_pinconfig(41, g_AM_HAL_GPIO_DISABLE);   // swo
    
    
#if 0
    am_hal_gpio_pinconfig(0, g_AM_HAL_GPIO_DISABLE);
    am_hal_clkgen_clkout_enable(false, AM_HAL_CLKGEN_CLKOUT_XTAL_32768);
#endif    // 0
    
    //
    // enable only button interrupt
    //
}

void am_app_util_gsensor_resetTick()
{
    firstTick = 0;
}    

void am_app_util_gsensor_powerdown()
{
    am_app_util_buzzer_power_down();

    am_util_delay_ms(100);  
    //am_hal_interrupt_master_disable();

    am_app_util_gsensor_system_power_off();

    gsensor_wakeup_button_init();
    

    //am_util_delay_ms(10);
    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

    // do not enable interrupt here, since we turned off SRAM
    // reset the system and start over
    //am_hal_flash_delay(FLASH_CYCLES_US(100000));
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(LIS2DW_WAKEUP_PIN));
    am_hal_stimer_config(0x0);
    am_hal_reset_control(AM_HAL_RESET_CONTROL_SWPOI, NULL);

    while(1);
}

void am_app_gsensor_button2_init(void)
{
    const am_hal_gpio_pincfg_t CFG_CTRL_BUTTON =
    {
        .uFuncSel       = 3,
        .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
        .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
        .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
        .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_BOTH,
        .ePullup        = AM_HAL_GPIO_PIN_PULLUP_WEAK,
    };

    am_hal_gpio_pinconfig(CTRL_BUTTON2, CFG_CTRL_BUTTON);

    NVIC_SetPriority(GPIO_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    NVIC_EnableIRQ(GPIO_IRQn);
}

void am_app_gsensor_button2_process()
{
    if (NULL == g_pGsensorIomHandle)
        return;

    //am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    
    am_app_utils_task_send_fromISR(AM_APP_ISR_GPIO, AM_APP_TASK_GSENSOR, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);

}

void am_app_util_gsensor_button2_disble_handler()
{
    xTimerStop(am_KWD_timers[AM_APP_TIMER_GSENSOR_PERIOD], 0);
    //xTimerDelete(am_KWD_timers[AM_APP_TIMER_GSENSOR_PERIOD], 0);

    // write 0x00 to CTRL1 to enter power down mode
    uint32_t ui32Temp = 0x00;
    gsensor_iom_slave_write(AM_DEVICES_LIS2DW_CTRL_REG1, &ui32Temp, 1); 

    if (g_pGsensorIomHandle != NULL)
    {

        am_bsp_iom_pins_disable(GSENSOR_IOM, AM_HAL_IOM_I2C_MODE);

        //
        // Disable the IOM.
        //
        am_hal_iom_disable(g_pGsensorIomHandle);

        //
        // Disable power to and uninitialize the IOM instance.
        //
        am_hal_iom_power_ctrl(g_pGsensorIomHandle, AM_HAL_SYSCTRL_DEEPSLEEP, false);

        am_hal_iom_uninitialize(g_pGsensorIomHandle);
    }

    g_pGsensorIomHandle = NULL;
    
}


int32_t complement(uint8_t high, uint8_t low)
{
    uint8_t hi = high;
    uint16_t value = (uint16_t)(hi << 8) + low;
    
    if((value & 0x8000) != 0)   
    {
        uint16_t nValue = (~value) + 0x1;
        return (nValue* mg_per_bit/4) * ((int32_t)(-1));
    }
  
    return (value * mg_per_bit/4);
}


void am_app_util_gsensor_process(void)
{
    bool bStill = false;
    uint8_t result[6];
    int32_t xAxis, yAxis, zAxis;
    
    gsensor_iom_slave_read(0x28, (uint32_t *)&result[0], 1);
    gsensor_iom_slave_read(0x29, (uint32_t *)&result[1], 1);
    gsensor_iom_slave_read(0x2a, (uint32_t *)&result[2], 1);
    gsensor_iom_slave_read(0x2b, (uint32_t *)&result[3], 1);
    gsensor_iom_slave_read(0x2c, (uint32_t *)&result[4], 1);
    gsensor_iom_slave_read(0x2d, (uint32_t *)&result[5], 1);

    xAxis = complement(result[1], result[0]);
    yAxis = complement(result[3], result[2]);
    zAxis = complement(result[5], result[4]);  
    
    AM_APP_LOG_DEBUG("Lis3mdl X=%d, Y=%d, Z=%d\n", xAxis, yAxis, zAxis);

    if ((xAxis < X0_plus) && (xAxis > X0_minus) && (yAxis < Y0_plus) && (yAxis > Y0_minus) && (zAxis < Z_max) && (zAxis > Z_min))
        bStill = true;

    // 
    if (bStill)
    {
        if (firstTick == 0)
            firstTick = xTaskGetTickCount();
        
        TickType_t xTickNow = xTaskGetTickCount();
        
        if( ((xTickNow - firstTick)/portTICK_PERIOD_MS) >=  GSENSOR_QUITE_MS) 
            am_app_utils_task_send_fromISR(AM_APP_TASK_GSENSOR, AM_APP_TASK_GSENSOR, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
    }
    else
    {
        firstTick = 0;
    }
    
    //configASSERT(bStill == true);
    //am_app_utils_task_send_xTicksToWait(AM_APP_TASK_GSENSOR, AM_APP_TASK_GSENSOR, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL, pdMS_TO_TICKS( 20000 ));
    
}

void am_app_KWD_timer_gsensor_period_callback(TimerHandle_t xTimer)
{
    // am_app_utils_task_send(AM_APP_TASK_GSENSOR, AM_APP_TASK_GSENSOR, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
    
    am_app_util_gsensor_process();
}
#endif    // configUSE_GSENSOR
