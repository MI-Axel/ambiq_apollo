//*****************************************************************************
//
// Configure the device pins for different signals
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 4/22/2016 at 3:03:37 PM
// by TI PinMux version 
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "pinout.h"

//*****************************************************************************
//
//! \addtogroup pinout_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Configures the device pins for the customer specific usage.
//!
//! \return None.
//
//*****************************************************************************
void
PinoutSet(void)
{
    //
    // Enable Peripheral Clocks 
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOR);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOS);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOT);

    //
    // Configure the GPIO Pin Mux for PR4
    // for LCDDATA00
    //
    MAP_GPIOPinConfigure(GPIO_PR4_LCDDATA00);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PS5
    // for LCDDATA07
    //
    MAP_GPIOPinConfigure(GPIO_PS5_LCDDATA07);
    GPIOPinTypeLCD(GPIO_PORTS_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PJ6
    // for LCDAC
    //
    MAP_GPIOPinConfigure(GPIO_PJ6_LCDAC);
    GPIOPinTypeLCD(GPIO_PORTJ_BASE, GPIO_PIN_6);

    //
    // Configure the GPIO Pin Mux for PF7
    // for LCDDATA02
    //
    MAP_GPIOPinConfigure(GPIO_PF7_LCDDATA02);
    GPIOPinTypeLCD(GPIO_PORTF_BASE, GPIO_PIN_7);

    //
    // Configure the GPIO Pin Mux for PS4
    // for LCDDATA06
    //
    MAP_GPIOPinConfigure(GPIO_PS4_LCDDATA06);
    GPIOPinTypeLCD(GPIO_PORTS_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PR7
    // for LCDDATA05
    //
    MAP_GPIOPinConfigure(GPIO_PR7_LCDDATA05);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_7);

    //
    // Configure the GPIO Pin Mux for PR5
    // for LCDDATA01
    //
    MAP_GPIOPinConfigure(GPIO_PR5_LCDDATA01);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PR1
    // for LCDFP
    //
    MAP_GPIOPinConfigure(GPIO_PR1_LCDFP);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_1);

    //
    // Configure the GPIO Pin Mux for PR3
    // for LCDDATA03
    //
    MAP_GPIOPinConfigure(GPIO_PR3_LCDDATA03);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_3);

    //
    // Configure the GPIO Pin Mux for PR6
    // for LCDDATA04
    //
    MAP_GPIOPinConfigure(GPIO_PR6_LCDDATA04);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_6);

    //
    // Configure the GPIO Pin Mux for PR0
    // for LCDCP
    //
    MAP_GPIOPinConfigure(GPIO_PR0_LCDCP);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PR2
    // for LCDLP
    //
    MAP_GPIOPinConfigure(GPIO_PR2_LCDLP);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, GPIO_PIN_2);

    //
    // Configure the GPIO Pin Mux for PD4
    // for GPIO_PD4
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_4);
    MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0x0);

    //
    // Unlock the Port Pin and Set the Commit Bit
    //
    HWREG(GPIO_PORTE_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTE_BASE+GPIO_O_CR)   |= GPIO_PIN_7;
    HWREG(GPIO_PORTE_BASE+GPIO_O_LOCK) = 0x0;
    
    //
    // Configure the GPIO Pin Mux for PE7
    // for GPIO_PE7
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_7);
    MAP_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_7, 0x0);

    //
    // Configure the GPIO Pin Mux for PP7
    // for GPIO_PP7
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_7);
    MAP_GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_7, 0x0);

    //
    // Configure the GPIO Pin Mux for PT2
    // for GPIO_PT2
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTT_BASE, GPIO_PIN_2);
    MAP_GPIOPinWrite(GPIO_PORTT_BASE, GPIO_PIN_2, 0x0);

    //
    // Configure the GPIO Pin Mux for PT3
    // for GPIO_PT3
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTT_BASE, GPIO_PIN_3);
    MAP_GPIOPinWrite(GPIO_PORTT_BASE, GPIO_PIN_3, 0x0);

    //
    // Configure the GPIO Pin Mux for PF6
    // for GPIO_PF6
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_6);
    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_6, 0x0);

    //
    // Configure the GPIO Pin Mux for PB2
    // for T5CCP0
    //
    MAP_GPIOPinConfigure(GPIO_PB2_T5CCP0);
    MAP_GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_2);

    //
    // Configure the GPIO Pin Mux for PA0
    // for U0RX
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PA1
    // for U0TX
    //
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

