
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_log.c
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : API of log
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "stdint.h"
#include "stdio.h"
#include "string.h"
// Eder Andrade driver library
#ifndef TERMINAL_ENABLED
	#include "ea_drv_uart.h"
#endif
#include "ea_api_accel.h"
// API library
#include "ea_api_log.h"

/*******************************************************************************
							HOW TO USE THIS API
********************************************************************************

1. 	First, you should include in your .c file the "ea_api_log.h" file.

2.  Call ea_api_log_init() to initialize the driver;

3.  Call ea_api_log_print() to print the battery value over UART.

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
#define LOG_API_OK      (int8_t) 0
#define LOG_API_ERROR   (int8_t)-1

/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/    
int8_t  ea_api_log_init     (void);// Initialize log API
int8_t  ea_api_log_deinit   (void);// Deinitialize log API
int8_t  ea_api_log_print    (void);// Print the log about battery

/* Public objects ------------------------------------------------------------*/
/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : ea_api_log_init    
  * @brief      : Init. UART driver
  * @pre-cond.  : SysClk function and ADC driver opened
  * @post-cond. : Log driver init. and ready to be used
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_init(void)
{
    // Init. battery driver
    if(ea_api_accel_init() != 0)
    {
        return LOG_API_ERROR;
    }
	// OK
	return LOG_API_OK;	
}

/**
  * @Func       : ea_api_log_deinit    
  * @brief      : Deinitializes log driver
  * @pre-cond.  : ea_api_log_init
  * @post-cond. : Log API deinit.
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_deinit(void)
{
    // Deinit. battery driver
    if(ea_api_accel_reset() != 0)
    {
        return LOG_API_ERROR;
    }    
	// OK
	return LOG_API_OK;	
}

/**
  * @Func       : ea_api_log_print    
  * @brief      : Print battery value over UART
  * @pre-cond.  : ea_api_accel_init() called
  * @post-cond. : Accelerometer values over IAR terminal or UART hardware
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_print(void)
{ 	
	#ifdef TERMINAL_ENABLED
		// If user wants to user IAR terminal
		int16_t iAccelXyz[3] = {0}, iX = 0, iY = 0, iZ = 0; 
		ea_api_accel_get_xyz(iAccelXyz);
		iX = iAccelXyz[0];
		iY = iAccelXyz[1];
		iZ = iAccelXyz[2];		
		
		// Using IAR terminal
		printf("[LOG] X axis: %3d\r\n", iX);
		printf("[LOG] Y axis: %3d\r\n", iY);
		printf("[LOG] Z axis: %3d\r\n", iZ);
		return 0;
	#elif	
 		// Using UART hardware
		char ucVet[32] = {0}; 
		sprintf((char*)ucVet, "[LOG] X axis: %3d\r\n", (int)I2C.uiXyz[eAxisX]); 
    	return UART.Write(ucVet, strlen((const char*)ucVet));
	#endif	
}
/*****************************END OF FILE**************************************/
