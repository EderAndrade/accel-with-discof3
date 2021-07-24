
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_gpio.h
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 12/03/2021
  * @brief  : Header of GPIO driver
   *****************************************************************************
*/
#ifdef GPIO_ENABLED

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_DRV_GPIO_H
#define __EA_DRV_GPIO_H

/* Includes ------------------------------------------------------------------*/  
// STMicroelectronics
#include "stm32f3xx_hal.h"
/* Define --------------------------------------------------------------------*/
#define NUM_OF_IOS  (uint8_t)8

/* DEFINING PORT AND PINS FOR THE DIGITAL I/Os USED --------------------------*/

/* OUTPUTS -------------------------------------------------------------------*/
/* LEDs of STM32F3-DISCO board ************************************************/
#define BLUE_LED_Pin            GPIO_PIN_8
#define BLUE_LED_GPIO_Port      GPIOE
#define RED_LED_Pin             GPIO_PIN_9
#define RED_LED_GPIO_Port       GPIOE
#define ORANGE_LED_Pin          GPIO_PIN_10
#define ORANGE_LED_GPIO_Port    GPIOE
#define GREEN_LED_Pin           GPIO_PIN_11
#define GREEN_LED_GPIO_Port     GPIOE
#define BLUE_LEDE12_Pin         GPIO_PIN_12
#define BLUE_LEDE12_GPIO_Port   GPIOE
#define RED_LEDE13_Pin          GPIO_PIN_13
#define RED_LEDE13_GPIO_Port    GPIOE
#define ORANGE_LEDE14_Pin       GPIO_PIN_14
#define ORANGE_LEDE14_GPIO_Port GPIOE
#define GREEN_LEDE15_Pin        GPIO_PIN_15
#define GREEN_LEDE15_GPIO_Port  GPIOE
/*----------------------------------------------------------------------------*/

/* INPUTS --------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
// These values helps to understand the code
typedef enum
{                       
    /* Output *****************************************************************/
	eLedBlue1 = 0   ,
    eLedRed1        ,
    eLedOrange1     ,
    eLedGreen1      ,
    eLedBlue2       ,
    eLedRed2        ,
    eLedOrange2     ,
    eLedGreen2      ,    
    /* Input ******************************************************************/
      
}e_gpio_t;

// This struct combines port and pin in one location
typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t         pin;        
    
}st_gpio_pin_t;

// Struct that retains all information about GPIOs of application
typedef struct
{
    /* Flags ******************************************************************/
    uint8_t FlagEnable;                 // State of peripheral
    
    /* Variables **************************************************************/
	GPIO_PinState State[NUM_OF_IOS];	// Vector of GPIOs values stored
    
    /* Function Pointers ******************************************************/
    int8_t  (*Open) (void);                        
    int8_t  (*Close)(void);                    
    int8_t  (*Write)(e_gpio_t, GPIO_PinState);              
    int8_t  (*Read) (e_gpio_t);               
    
}st_gpio_t;

/* Public objects ------------------------------------------------------------*/
extern st_gpio_t GPIO;

#endif /* __EA_DRV_GPIO_H */
#endif /* GPIO_ENABLED */
/*****************************END OF FILE**************************************/