/*
 * EXIT_interface.h
 *
 *  Created on: Jul 4, 2024
 *      Author: wily
 */

#ifndef EXIT_INTERFACE_H_
#define EXIT_INTERFACE_H_

#define EXTI_LINE0   6
#define EXTI_LINE1   7
#define EXTI_LINE2   5

#define EXTI_LOW_LEVEL     0
#define EXTI_ON_CHANGE     1
#define EXTI_FALLING_EDGE  2
#define EXTI_RISING_EDGE   3

#define 	EXTI_INT2_FALLING_EDGE  0
#define 	EXTI_INT2_RISING_EDGE   1


#define		EXTI_Enable_State		1
#define		EXTI_Disable_State		0



void EXTI_Init    	        (void);
//void EXTI_SetSignalLatch    ( u8 CopySenseMode , u8 CopyEXTILine);
void EXTI_EnableGlobalInterrupt   ( void);
void EXTI_DisableGlobalInterrupt ( void);

void EXTI_EnableInterrupt0   ( void);
void EXTI_DisableInterrupt0 (void);

void EXTI_EnableInterrupt1   ( void);
void EXTI_DisableInterrupt1 ( void);

void EXTI_EnableInterrupt2  ( void);
void EXTI_DisableInterrupt2 ( void);

void EXTI_ClearFlag         ( u8 CopyEXTILine);
void EXTI_SetCallBack0      ( void (*Copy_pvoidCallBack) (void) );
void EXTI_SetCallBack1      ( void (*Copy_pvoidCallBack) (void) );
void EXTI_SetCallBack2      ( void (*Copy_pvoidCallBack) (void) );


#endif /* EXIT_INTERFACE_H_ */
