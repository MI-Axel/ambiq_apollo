//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
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
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

/*******************************************************************************
*
********************************************************************************
*     am_app_KWS_isr_handler.c
********************************************************************************
*
*     Description: isr handlers file and related low power driver
*
*******************************************************************************/
#include "usr_include.h"
//*****************************************************************************
//
// CTRL Button GPIO ISR
//
//*****************************************************************************
#if 0
void
am_app_button_3_handler(void)
{
    // disable button interrupt so switch bouncing has no effect
    am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
    // ISR will be enabled again in the task function 
    am_app_utils_task_send_fromISR(AM_APP_ISR_GPIO, AM_APP_TASK_BUTTON, 
                                    AM_APP_MESSAGE_SHORT, CTRL_BUTTON3, NULL);
    // ISR will be enabled again in the task function 
}

void
am_app_button_2_handler(void)
{
    // disable button interrupt so switch bouncing has no effect
    am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    am_app_utils_task_send_fromISR(AM_APP_ISR_GPIO, AM_APP_TASK_BUTTON, 
                                    AM_APP_MESSAGE_SHORT, CTRL_BUTTON2, NULL);

}
#endif    // 0

//*****************************************************************************
//
// WOS ISR
//
//*****************************************************************************
#if VOS_configUSE_WOS
void
am_app_WOS_handler(void)
{
    if(g_ui16WOSActiveFlag == 0) 
    {
	    g_ui16WOSActiveFlag = 20;
	    am_app_KWD_WOS_pdm_enable();
    }
    else
	    g_ui16WOSActiveFlag = 20;
}
#endif    // VOS_configUSE_WOS

//*****************************************************************************
//
// Sleep Button GPIO ISR
//
//*****************************************************************************
#if USE_SLEEP_BUTTON
void
sleep_button_handler(void)
{
    wsfMsgHdr_t *pMsg;
  
    if(deepsleep_status == 0) {
      //am_hal_gpio_out_bit_clear(WOS_MODE_PIN);
      // Disable the GPIO Wake interrupt.
  
#if USE_WAKE_ON_SOUND
        am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(WOS_WAKE1_PIN));
        am_hal_gpio_pin_config(WOS_WAKE1_PIN, AM_HAL_GPIO_OUTPUT);
#endif    // USE_WAKE_ON_SOUND
  
      // disable pdm clock and set PDM clock pin Low to save power
      am_hal_pdm_disable();
  
      am_hal_gpio_pin_config(PDM_DATA, AM_HAL_PIN_DISABLE);  // Disable PDM data pin
  
      //Power Down PDM interface to further reduce power
      am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PDM);
  
      if ((pMsg = WsfMsgAlloc(sizeof(wsfMsgHdr_t))) != NULL)
      {
        pMsg->event = AMDTP_DEEP_SLEEP_IND; // Lewis : Need to fix!! FIT_DEEP_SLEEP_IND;
        pMsg->param = 0;
        pMsg->status = 0;
        WsfMsgSend(amdtpHandlerId, pMsg);
      }
    }
    else 
    {
        APP_TRACE_INFO0("Power on\n");
        HciDrvRadioBoot(0);
        DmDevReset();
  
        //Power Down PDM interface to further reduce power
        am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PDM);
    
        am_hal_gpio_pin_config(PDM_DATA, PDM_DATA_PIN_CFG);  // Enable PDM data pin
    
        //
        // Configure the PDM module
        //
        PDMregConfig();
    
        //
        // Make sure interrupts are clear
        //
        AM_REG(PDM, INTCLR) = 0x7;
        AM_REG(PDM, FLUSH) = 0x1;                       // Reset FIFO pointers
    
        //
        // Enable interrupts PDM
        //
        am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);  //NVIC setting
        am_hal_pdm_int_enable(AM_HAL_PDM_INT_FIFO | AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF);
        am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_PDM, AM_HAL_INTERRUPT_PRIORITY(4));
    
        // enable pdm clock
        am_hal_pdm_enable();
    
        deepsleep_status = 0;
  }
}
#endif    // USE_SLEEP_BUTTON

