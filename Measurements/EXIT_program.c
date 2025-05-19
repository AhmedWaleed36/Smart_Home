/*
 * EXIT_program.c
 *
 *  Created on: Jul 4, 2024
 *      Author: wily
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//#include "GPIO_interface.h"

#include "EXIT_private.h"
#include "EXIT_config.h"
#include "EXIT_interface.h"

void (*EXTI_CallBack[3])(void) = {NULL};

void EXTI_Init() {
	CLR_BIT(MCUCR_REG,0);
	CLR_BIT(MCUCR_REG,1);
	CLR_BIT(MCUCR_REG,2);
	CLR_BIT(MCUCR_REG,3);




#if     EXTI0_MODE == EXTI_ON_CHANGE
	MCUCR_REG|=EXTI_ON_CHANGE;
#elif   EXTI0_MODE == EXTI_LOW_LEVEL
	MCUCR_REG|=EXTI_LOW_LEVEL;
#elif   EXTI0_MODE == EXTI_FALLING_EDGE
	MCUCR_REG|=EXTI_FALLING_EDGE;
#elif   EXTI0_MODE == EXTI_RISING_EDGE
	MCUCR_REG|=EXTI_RISING_EDGE;
#endif

#if 	EXTI1_MODE == EXTI_ON_CHANGE
	MCUCR_REG|=(EXTI_ON_CHANGE<<2);
#elif 	EXTI1_MODE == EXTI_LOW_LEVEL
	MCUCR_REG|=(EXTI_LOW_LEVEL<<2);
#elif	EXTI1_MODE == EXTI_FALLING_EDGE
	MCUCR_REG|=(EXTI_FALLING_EDGE<<2);
#elif 	EXTI1_MODE == EXTI_RISING_EDGE
	MCUCR_REG|=(EXTI_RISING_EDGE<<2);
#endif

#if 	EXTI2_MODE == EXTI_INT2_FALLING_EDGE
		CLR_BIT(MCUCSR_REG,6);
#elif 	EXTI2_MODE == EXTI_INT2_RISING_EDGE
		SET_BIT(MCUCSR_REG,6);
#endif

#if 	EXTI_INT0_INIT_STATE  ==  EXTI_Disable_State
	CLR_BIT(GICR_REG,6);
#elif  EXTI_INT0_INIT_STATE  ==  EXTI_Enable_State
	SET_BIT(GICR_REG,6);
#endif

#if 	EXTI_INT1_INIT_STATE  ==  EXTI_Disable_State
	CLR_BIT(GICR_REG,7);
#elif  EXTI_INT1_INIT_STATE  ==  EXTI_Enable_State
	SET_BIT(GICR_REG,7);
#endif
#if 	EXTI_INT2_INIT_STATE  ==  EXTI_Disable_State
	CLR_BIT(GICR_REG,5);
#elif  EXTI_INT2_INIT_STATE  ==  EXTI_Enable_State
	SET_BIT(GICR_REG,5);
#endif

SET_BIT(GIFR_REG,5);
SET_BIT(GIFR_REG,6);
SET_BIT(GIFR_REG,7);
}

void EXTI_EnableGlobalInterrupt   (void){
	SET_BIT(SREG_REG,7);
}
void EXTI_DisableGlobalInterrupt (void){
	CLR_BIT(SREG_REG,7);
}

void EXTI_EnableInterrupt0() {
	SET_BIT(GICR_REG,6);
}
void EXTI_DisableInterrupt0() {
	CLR_BIT(GICR_REG,6);
}
void EXTI_EnableInterrupt1() {
	SET_BIT(GICR_REG,7);
}
void EXTI_DisableInterrupt1() {
	CLR_BIT(GICR_REG,7);
}
void EXTI_EnableInterrupt2() {
	SET_BIT(GICR_REG,5);
}
void EXTI_DisableInterrupt2() {
	CLR_BIT(GICR_REG,5);
}

void EXTI_ClearFlag(u8 CopyEXTILine) {
	SET_BIT(GIFR_REG, CopyEXTILine);
}
void EXTI_SetCallBack0       ( void (*Copy_pvoidCallBack) (void) ){
	// EXTILine 0 , 1 , 2
	if (Copy_pvoidCallBack != NULL) {

		EXTI_CallBack[0] = Copy_pvoidCallBack;

	}
}
void EXTI_SetCallBack1       ( void (*Copy_pvoidCallBack) (void) ){
	// EXTILine 0 , 1 , 2
	if (Copy_pvoidCallBack != NULL) {

		EXTI_CallBack[1] = Copy_pvoidCallBack;

	}
}
void EXTI_SetCallBack2       ( void (*Copy_pvoidCallBack) (void) ){
	// EXTILine 0 , 1 , 2
	if (Copy_pvoidCallBack != NULL) {

		EXTI_CallBack[2] = Copy_pvoidCallBack;

	}
}

// ISR

void __vector_1(void) __attribute__((signal,used));
void __vector_1(void) {
	if (EXTI_CallBack[0] != NULL) {

		EXTI_CallBack[0](); /*  Call The Global Pointer to ISR   */
		EXTI_ClearFlag( 6);

	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void) {

	if (EXTI_CallBack[1] != NULL) {

		EXTI_CallBack[1]();
		EXTI_ClearFlag( 7);

	}

}

void __vector_3(void) __attribute__((signal));
void __vector_3(void) {

	if (EXTI_CallBack[2] !=NULL) {

		EXTI_CallBack[2]();
		EXTI_ClearFlag( 5);

	}

}
