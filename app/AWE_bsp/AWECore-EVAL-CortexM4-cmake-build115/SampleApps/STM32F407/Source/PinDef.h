/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     PinDef.h
********************************************************************************
*
*     Description:  GPIO Pin Definitions for AWE
*
*     Copyright:    DSP Concepts, Inc. (c) 2007 - 2016
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
*******************************************************************************/
#ifdef USE_GPIO

#define GPIO_DIR_INPUT 0
#define GPIO_DIR_OUTPUT 1

#define MAX_PINS 53

typedef struct
{
    GPIO_TypeDef* GPIOx;
    UINT32 GPIO_Pin;
    char szPinDesc[5];
}   PinInfoType;

PinInfoType InputPinMap[MAX_PINS] =
{
    {   GPIOA, 
        GPIO_PIN_0,
        "BTN",
    },
    
    {   GPIOA, 
        GPIO_PIN_1,
        "PA1",
    },    
   
    {   GPIOA, 
        GPIO_PIN_2,
        "PA2",
    },
    
    {   GPIOA, 
        GPIO_PIN_3,
        "PA3",
    },  
        
    {   GPIOA, 
        GPIO_PIN_8,
        "PA8",
    },  
        
    {   GPIOA, 
        GPIO_PIN_15,
        "PA15",
    },
            
    {   GPIOB, 
        GPIO_PIN_0,
        "PB0",
    },  
        
    {   GPIOB, 
        GPIO_PIN_1,
        "PB1",
    },
            
    {   GPIOB, 
        GPIO_PIN_4,
        "PB4",
    },  
        
    {   GPIOB, 
        GPIO_PIN_5,
        "PB5",
    },
            
    {   GPIOB, 
        GPIO_PIN_7,
        "PB7",
    },  
        
    {   GPIOB, 
        GPIO_PIN_8,
        "PB8",
    },
            
    {   GPIOB, 
        GPIO_PIN_11,
        "PB11",
    },  
        
    {   GPIOB, 
        GPIO_PIN_12,
        "PB12",
    },
            
    {   GPIOB, 
        GPIO_PIN_13,
        "PB13",
    },  
        
    {   GPIOB, 
        GPIO_PIN_14,
        "PB14",
    },
            
    {   GPIOB, 
        GPIO_PIN_15,
        "PB15",
    },
            
    {   GPIOC, 
        GPIO_PIN_1,
        "PC1",
    },
                
    {   GPIOC, 
        GPIO_PIN_2,
        "PC2",
    },
            
    {   GPIOC, 
        GPIO_PIN_4,
        "PC4",
    },
                
    {   GPIOC, 
        GPIO_PIN_5,
        "PC5",
    },
                    
    {   GPIOC, 
        GPIO_PIN_6,
        "PC6",
    },
           
    {   GPIOC, 
        GPIO_PIN_8,
        "PC8",
    },
                
    {   GPIOC, 
        GPIO_PIN_9,
        "PC9",
    },
                    
    {   GPIOC, 
        GPIO_PIN_11,
        "PC11",
    },
              
    {   GPIOC, 
        GPIO_PIN_13,
        "PC13",
    },
                
    {   GPIOC, 
        GPIO_PIN_14,
        "PC14",
    },
                    
    {   GPIOC, 
        GPIO_PIN_15,
        "PC15",
    },
                   
    {   GPIOD, 
        GPIO_PIN_0,
        "PD0",
    },
              
    {   GPIOD, 
        GPIO_PIN_1,
        "PD1",
    },
                
    {   GPIOD, 
        GPIO_PIN_2,
        "PD2",
    },
                    
    {   GPIOD, 
        GPIO_PIN_3,
        "PD3",
    },
                   
    {   GPIOD, 
        GPIO_PIN_6,
        "PD6",
    },
              
    {   GPIOD, 
        GPIO_PIN_7,
        "PD7",
    },
                
    {   GPIOD, 
        GPIO_PIN_8,
        "PD8",
    },
                    
    {   GPIOD, 
        GPIO_PIN_9,
        "PD9",
    },
                
    {   GPIOD, 
        GPIO_PIN_10,
        "PD10",
    },
                    
    {   GPIOD, 
        GPIO_PIN_11,
        "PD11",
    },
                    
    {   GPIOE, 
        GPIO_PIN_2,
        "PE2",
    },
                    
    {   GPIOE, 
        GPIO_PIN_4,
        "PE4",
    },
                    
    {   GPIOE, 
        GPIO_PIN_5,
        "PE5",
    },
                    
    {   GPIOE, 
        GPIO_PIN_6,
        "PE6",
    },
                    
    {   GPIOE, 
        GPIO_PIN_7,
        "PE7",
    },
                    
    {   GPIOE, 
        GPIO_PIN_8,
        "PE8",
    },
                    
    {   GPIOE, 
        GPIO_PIN_9,
        "PE9",
    },
                    
    {   GPIOE, 
        GPIO_PIN_10,
        "PE10",
    },
                    
    {   GPIOE, 
        GPIO_PIN_11,
        "PE11",
    },
                    
    {   GPIOE, 
        GPIO_PIN_12,
        "PE12",
    },
                    
    {   GPIOE, 
        GPIO_PIN_13,
        "PE13",
    },
                    
    {   GPIOE, 
        GPIO_PIN_14,
        "PE14",
    }, 
                    
    {   GPIOE, 
        GPIO_PIN_15,
        "PE15",
    }    
};

PinInfoType OutputPinMap[MAX_PINS] =
{ 
    {   GPIOD, 
        GPIO_PIN_15,
        "LED6",
    },

    {   GPIOD, 
        GPIO_PIN_13,
        "LED3",
    },

    {   GPIOD, 
        GPIO_PIN_14,
        "LED5",
    },
    
    {   GPIOA, 
        GPIO_PIN_1,
        "PA1",
    },
    
    {   GPIOA, 
        GPIO_PIN_2,
        "PA2",
    },
    
    {   GPIOA, 
        GPIO_PIN_3,
        "PA3",
    },  
            
    {   GPIOA, 
        GPIO_PIN_8,
        "PA8",
    },  
        
    {   GPIOA, 
        GPIO_PIN_15,
        "PA15",
    },
        
    {   GPIOB, 
        GPIO_PIN_0,
        "PB0",
    },  
        
    {   GPIOB, 
        GPIO_PIN_1,
        "PB1",
    },
            
    {   GPIOB, 
        GPIO_PIN_4,
        "PB4",
    },  
        
    {   GPIOB, 
        GPIO_PIN_5,
        "PB5",
    },
            
    {   GPIOB, 
        GPIO_PIN_7,
        "PB7",
    },  
        
    {   GPIOB, 
        GPIO_PIN_8,
        "PB8",
    },
            
    {   GPIOB, 
        GPIO_PIN_11,
        "PB11",
    },  
        
    {   GPIOB, 
        GPIO_PIN_12,
        "PB12",
    },
            
    {   GPIOB, 
        GPIO_PIN_13,
        "PB13",
    },  
        
    {   GPIOB, 
        GPIO_PIN_14,
        "PB14",
    },
            
    {   GPIOB, 
        GPIO_PIN_15,
        "PB15",
    },
            
    {   GPIOC, 
        GPIO_PIN_1,
        "PC1",
    },
                
    {   GPIOC, 
        GPIO_PIN_2,
        "PC2",
    },
            
    {   GPIOC, 
        GPIO_PIN_4,
        "PC4",
    },
                
    {   GPIOC, 
        GPIO_PIN_5,
        "PC5",
    },
                    
    {   GPIOC, 
        GPIO_PIN_6,
        "PC6",
    },
           
    {   GPIOC, 
        GPIO_PIN_8,
        "PC8",
    },
                
    {   GPIOC, 
        GPIO_PIN_9,
        "PC9",
    },
                    
    {   GPIOC, 
        GPIO_PIN_11,
        "PC11",
    },
              
    {   GPIOC, 
        GPIO_PIN_13,
        "PC13",
    },
                
    {   GPIOC, 
        GPIO_PIN_14,
        "PC14",
    },
                    
    {   GPIOC, 
        GPIO_PIN_15,
        "PC15",
    },
                   
    {   GPIOD, 
        GPIO_PIN_0,
        "PD0",
    },
              
    {   GPIOD, 
        GPIO_PIN_1,
        "PD1",
    },
                
    {   GPIOD, 
        GPIO_PIN_2,
        "PD2",
    },
                    
    {   GPIOD, 
        GPIO_PIN_3,
        "PD3",
    },
                   
    {   GPIOD, 
        GPIO_PIN_6,
        "PD6",
    },
              
    {   GPIOD, 
        GPIO_PIN_7,
        "PD7",
    },
                
    {   GPIOD, 
        GPIO_PIN_8,
        "PD8",
    },
                    
    {   GPIOD, 
        GPIO_PIN_9,
        "PD9",
    },
                
    {   GPIOD, 
        GPIO_PIN_10,
        "PD10",
    },
                    
    {   GPIOD, 
        GPIO_PIN_11,
        "PD11",
    },
                    
    {   GPIOE, 
        GPIO_PIN_2,
        "PE2",
    },
                    
    {   GPIOE, 
        GPIO_PIN_4,
        "PE4",
    },
                    
    {   GPIOE, 
        GPIO_PIN_5,
        "PE5",
    },
                    
    {   GPIOE, 
        GPIO_PIN_6,
        "PE6",
    },
                    
    {   GPIOE, 
        GPIO_PIN_7,
        "PE7",
    },
                    
    {   GPIOE, 
        GPIO_PIN_8,
        "PE8",
    },
                    
    {   GPIOE, 
        GPIO_PIN_9,
        "PE9",
    },
                    
    {   GPIOE, 
        GPIO_PIN_10,
        "PE10",
    },
                    
    {   GPIOE, 
        GPIO_PIN_11,
        "PE11",
    },
                    
    {   GPIOE, 
        GPIO_PIN_12,
        "PE12",
    },
                    
    {   GPIOE, 
        GPIO_PIN_13,
        "PE13",
    },
                    
    {   GPIOE, 
        GPIO_PIN_14,
        "PE14",
    }, 
                    
    {   GPIOE, 
        GPIO_PIN_15,
        "PE15",
    }    
}; 

#endif
