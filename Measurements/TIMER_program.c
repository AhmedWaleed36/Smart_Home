/*
 * TIMER_program.c
 *
 *  Created on: Jul 29, 2024
 *      Author: ahmed  waleed
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "TIMER_private.h"
#include"TIMER_config.h"
#include"TIMER_interface.h"

static void (*TIMERS_CallBackFunc[16])(void) = {NULL }; /* we have 8 interrupt sources in timer  */

void TIMER0_Init(void) {
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE
	/*initialize Ovf mode*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);
	/*Preload value*/
	TCNT0 = TIMER0_PRELOAD_VAL;
	/*Timer0 OVF Interrupt Enable*/
#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK, TIMSK_TOIE0);
#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE0);
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*initialize PHASE CORRECT PWM mode*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);
	/* OC0 MODE */
#if TIMER0_CTC_PWM_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#endif
	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL;
#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE
	/*initialize CTC mode*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL;
	/*Timer0 Compare Match Interrupt Enable*/
#if TIMER0_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE0);
#elif TIMER0_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE0);
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE
	/*initialize FAST PWM mode*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	/* OC0 MODE */
#if TIMER0_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#endif
	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL;

#endif
	/*Set the Required Prescaler*/
	TCCR0 &= TIMER_PRESCALER_MASK;
	TCCR0 |= TIMER0_PRESCALER;
}
/*----------------------------------------------------------------------------------------*/
void TIMER0_EnableINT(void) {
	SET_BIT(TIMSK, TIMSK_OCIE0);
}
/*----------------------------------------------------------------------------------------*/
void TIMER0_DisableINT(void) {
	CLR_BIT(TIMSK, TIMSK_OCIE0);
}
/*----------------------------------------------------------------------------------------*/
void TIMER0_SetPreload(u8 Copy_Preload) {
	TCNT0 = Copy_Preload;
}
/*----------------------------------------------------------------------------------------*/
void TIMER0_SetCTC(u8 Copy_CTC) {
	OCR0 = Copy_CTC;

}
/*----------------------------------------------------------------------------------------*/
u8   TIMER0_GetTimerCounterValue(void) {
	return TCNT0;
}
/*----------------------------------------------------------------------------------------*/
void TIMER0_SetPWMDutyCycle(u8 Copy_DutyCycle) {
#if TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER0_CTC_PWM_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		OCR0=Copy_DutyCycle*255;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		OCR0=(Copy_DutyCycle*255)/100;
	}
#elif TIMER0_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		OCR0 = (1-Copy_DutyCycle) * 255;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		OCR0 = ((1-Copy_DutyCycle) * 255) / 100;
	}
#endif
}

/*=======================================================================================
 ========================================================================================
 ======================================================================================== */

void TIMER1_Init(void){
#if TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_NORMAL_MODE
	/*Initialize Normal mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);
	/*Preload value*/
	TCNT1 = TIMER1_PRELOAD_VAL;
	/* OVF Interrupt Enable*/
	#if TIMER1_OVERFLOW_INTERRUPT==DISABLE
	CLR_BIT(TIMSK, TIMSK_TOIE1);
	#elif TIMER1_OVERFLOW_INTERRUPT==ENABLE
	SET_BIT(TIMSK, TIMSK_TOIE1);
	#endif
/*=======================================================================================*/
#elif TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_CTC_OCR1A_MODE ||	TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_CTC_ICR1_MODE
	/*Initialize CTC mode*/
	#if TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_CTC_OCR1A_MODE
		CLR_BIT(TCCR1A, TCCR1A_WGM10);
		CLR_BIT(TCCR1A, TCCR1A_WGM11);
		SET_BIT(TCCR1B, TCCR1B_WGM12);
		CLR_BIT(TCCR1B, TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_CTC_ICR1_MODE
		CLR_BIT(TCCR1A, TCCR1A_WGM10);
		CLR_BIT(TCCR1A, TCCR1A_WGM11);
		SET_BIT(TCCR1B, TCCR1B_WGM12);
		SET_BIT(TCCR1B, TCCR1B_WGM13);
	#endif
	/*CTC values*/
	OCR1A = TIMER1_CTCA_VAL ;
	OCR1B = TIMER1_CTCB_VAL ;
	#if TIMER1_WAVEFORM_GENERATION_MODE==TIMER1_CTC_ICR1_MODE
		ICR1 = TIMER1_ICR1_VAL ;
		#if TIMER1_ICR_EDGE == RISING_EDGE
			SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING_EDGE
			CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		#endif
	#endif
	/*Set OCR1A mode*/
	#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_OC_TOGGEL
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_OC_LOW
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_OC_HIGH
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#endif

	/*Set OCR1B mode*/
	#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_OC_TOGGEL
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_OC_LOW
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_OC_HIGH
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#endif

	/* CTC Interrupt Enable*/
	#if TIMER1_CTCA_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
	#elif TIMER1_CTCA_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
	#endif

	#if TIMER1_CTCB_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
	#elif TIMER1_CTCB_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
	#endif
	/*===================================================================================*/
#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE) ||(TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE)
	/*Set Waveform generation mode as PWM modes */
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#endif
	/*Set the require CTC Values*/
	OCR1A = TIMER1_CTCA_VAL ;
	OCR1B = TIMER1_CTCB_VAL ;

	/*Set ICR1*/
	#if ((TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE))
		ICR1 = TIMER1_ICR1_VAL ;

		#if TIMER1_ICR_EDGE == RISING_EDGE
			SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING_EDGE
			CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		#endif
	#endif

	/*Set OCR1A mode*/
	#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#endif

	/*Set OCR1B mode*/
	#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#endif

	/* PWM Interrupts Enable*/
	#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_TOIE1) ;
	#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_TOIE1) ;
	#endif

	#if TIMER1_CTCA_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
	#elif TIMER1_CTCA_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
	#endif

	#if TIMER1_CTCB_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
	#elif TIMER1_CTCB_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
	#endif

	#if TIMER1_ICR_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_TICIE1) ;
	#elif TIMER1_ICR_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_TICIE1) ;
	#endif

#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE)

	/*Set Waveform generation mode as PWM modes */
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#endif

	/*Set the require CTC Values*/
	OCR1A = TIMER1_CTCA_VAL ;
	OCR1B = TIMER1_CTCB_VAL ;

	/*Set ICR1*/
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
		ICR1 = TIMER1_ICR1_VAL ;

		#if TIMER1_ICR_EDGE == RISING_EDGE
			SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING_EDGE
			CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		#endif
	#endif

	/*Set OCR1A mode*/
	#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
	#endif

	/*Set OCR1B mode*/
	#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
	#endif

	/*Timer1 PWM Interrupt Enable*/
	#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_TOIE1) ;
	#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_TOIE1) ;
	#endif

	#if TIMER1_CTCA_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
	#elif TIMER1_CTCA_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
	#endif

	#if TIMER1_CTCB_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
	#elif TIMER1_CTCB_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
	#endif

	#if TIMER1_ICR_INTERRUPT == DISABLE
		CLR_BIT(TIMSK , TIMSK_TICIE1) ;
	#elif TIMER1_ICR_INTERRUPT == ENABLE
		SET_BIT(TIMSK , TIMSK_TICIE1) ;
	#endif
#endif

	/*Set the Required Prescaler*/
	TCCR1B &= TIMER_PRESCALER_MASK ;
	TCCR1B |= TIMER1_PRESCALER ;


}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetPreload (u16 Copy_Preload){
	TCNT1 = Copy_Preload;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetCTCA (u16 Copy_CTCA) {
	OCR1A = Copy_CTCA;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetCTCB (u16 Copy_CTCB) {
	OCR1B = Copy_CTCB;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetICR1 (u16 Copy_ICR1){
	ICR1 = Copy_ICR1;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetPWMDutyCycleOC1A (u16 Copy_DutyCycle) {
#if (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE)
#if TIMER1_OCR1A_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER1_OCR1A_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		OCR1A=Copy_DutyCycle*65535;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		OCR1A=(Copy_DutyCycle*65535)/100;
	}
#elif TIMER1_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER1_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		OCR1A = (1-Copy_DutyCycle) * 65535;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		OCR1A = ((1-Copy_DutyCycle) * 65535) / 100;
	}
#endif
#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE)
#if TIMER1_OCR1A_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER1_OCR1A_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		ICR1=Copy_DutyCycle*65535;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		ICR1=(Copy_DutyCycle*65535)/100;
	}
#elif TIMER1_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER1_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		ICR1 = (1-Copy_DutyCycle) * 65535;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		ICR1 = ((1-Copy_DutyCycle) * 65535) / 100;
	}
#endif
#endif
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_SetPWMDutyCycleOC1B (u16 Copy_DutyCycle) {
#if (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE)
#if TIMER1_OCR1A_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER1_OCR1A_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		OCR1B=Copy_DutyCycle*65535;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		OCR1B=(Copy_DutyCycle*65535)/100;
	}
#elif TIMER1_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER1_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		OCR1B = (1-Copy_DutyCycle) * 65535;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		OCR1B = ((1-Copy_DutyCycle) * 65535) / 100;
	}
#endif
#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE)
#if TIMER1_OCR1A_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER1_OCR1A_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		ICR1=Copy_DutyCycle*65535;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		ICR1=(Copy_DutyCycle*65535)/100;
	}
#elif TIMER1_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER1_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		ICR1 = (1-Copy_DutyCycle) * 65535;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		ICR1 = ((1-Copy_DutyCycle) * 65535) / 100;
	}
#endif
#endif
}
/*----------------------------------------------------------------------------------------*/
u16  TIMER1_GetTimerCounterValue (void) {
	u16 i;
	i=TCNT1;
	return i;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_ICUInitEnable(){
	/* Set trigger source as rising edge Initially  */
	#if (TIMER_u8_ICP_INIT_STATE == TIMER_u8_ICP_RAISING_EDGE)
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	#elif(TIMER_u8_ICP_INIT_STATE == TIMER_u8_ICP_FALLING_EDGE)
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	#endif

	/* Enable Interrupt of ICU */
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_ICUSetTriggerEdge(u8 Copy_Edge){
	if (Copy_Edge == TIMER_ICP_RAISING_EDGE) {
		SET_BIT(TCCR1B, TCCR1B_ICES1);
	}
	else if (Copy_Edge == TIMER_ICP_FALLING_EDGE) {
		CLR_BIT(TCCR1B, TCCR1B_ICES1);
	}
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_ICUEnableInterrupt(){
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_ICUDisableInterrupt(){
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}
/*----------------------------------------------------------------------------------------*/
u16  TIMER1_GetICR(){
	u16 i;
	i=ICR1;
	return i;
}
/*----------------------------------------------------------------------------------------*/
void TIMER1_WDTSleep()
{
	/* CLear The Prescaler bits  */
	WDTCR &= WDT_PS_MASKING ;
	/* Set The required prescaller */
	WDTCR |= WDT_PRESCALER ;
}
/*----------------------------------------------------------------------------------------*/
void TIMER_WDTEnable ()
{
	SET_BIT (WDTCR , WDTCR_WDE);
}
/*----------------------------------------------------------------------------------------*/
void TIMER_WDTDisable ()
{
	/* Set Bit 3&4 at the same CLK cycle  */
	WDTCR |= 0b00011000 ;
	/* WDTCR_WDE = 0 */
	/* I don't care for any value in this Reg Cuz I want to Disable */
	WDTCR = 0 ;
}

/*=======================================================================================
 ========================================================================================
 ======================================================================================== */

void TIMER2_Init(void) {
#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

	/*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR2 , TCCR2_WGM20);
	CLR_BIT(TCCR2 , TCCR2_WGM21);

	/*Set the Required Preload Value*/
	TCNT2 = TIMER2_PRELOAD_VAL;

	/*Timer2 Overflow Interrupt Enable*/
#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE2);
#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE2);
#endif

#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*initialize PHASE CORRECT PWM mode*/
	SET_BIT(TCCR2, TCCR2_WGM20);
	CLR_BIT(TCCR2, TCCR2_WGM21);
	/* OC0 MODE */
#if TIMER2_CTC_PWM_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#elif TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#endif
	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VAL;
#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

	/*Initialize Waveform Generation Mode as CTC Mode*/
	CLR_BIT(TCCR2 , TCCR2_WGM20);
	SET_BIT(TCCR2 , TCCR2_WGM21);

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VAL;

	/*Timer2 Compare Match Interrupt Enable*/
#if TIMER2_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE2);
#elif TIMER2_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE2);
#endif

#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE
	/*initialize FAST PWM mode*/
	SET_BIT(TCCR2, TCCR2_WGM20);
	SET_BIT(TCCR2, TCCR2_WGM21);
	/* OC0 MODE */
#if TIMER0_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#elif TIMER0_CTC_PWM_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#endif
	/*Set the Required CTC Value*/
	OCR2 = TIMER0_CTC_VAL;
#endif

	/*Set the Required Prescaler*/
	TCCR2 &= TIMER_PRESCALER_MASK;
	TCCR2 |= TIMER2_PRESCALER;
}
/*----------------------------------------------------------------------------------------*/
void TIMER2_EnableINT(void) {
	SET_BIT(TIMSK , TIMSK_OCIE2);
}
/*----------------------------------------------------------------------------------------*/
void TIMER2_DisableINT(void) {
	CLR_BIT(TIMSK , TIMSK_OCIE2);
}
/*----------------------------------------------------------------------------------------*/
void TIMER2_SetPreload(u8 Copy_Preload) {
	TCNT2 = Copy_Preload;
}
/*----------------------------------------------------------------------------------------*/
void TIMER2_SetCTC(u8 Copy_CTC) {
	if(Copy_CTC>255 )Copy_CTC=(Copy_CTC/1024)*255;
	OCR2 = Copy_CTC;

}
/*----------------------------------------------------------------------------------------*/
u8   TIMER2_GetTimerCounterValue(void) {
	return TCNT2;
}
/*----------------------------------------------------------------------------------------*/
void TIMER2_SetPWMDutyCycle (u8 Copy_DutyCycle){
#if TIMER2_CTC_PWM_MODE==TIMER_SET_ON_CTC_CLR_ON_TOP || TIMER2_CTC_PWM_MODE==TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
	if(Copy_DutyCycle>=0 && Copy_DutyCycle<=1) {
		OCR2=Copy_DutyCycle*255;
	}
	else if(Copy_DutyCycle>=0 && Copy_DutyCycle<=100) {
		OCR2=(Copy_DutyCycle*255)/100;
	}
#elif TIMER2_CTC_PWM_MODE==TIMER_CLR_ON_CTC_SET_ON_TOP || TIMER2_CTC_PWM_MODE==TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
	if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 1) {
		OCR2 = (1-Copy_DutyCycle) * 255;
	} else if (Copy_DutyCycle >= 0 && Copy_DutyCycle <= 100) {
		OCR2 = ((1-Copy_DutyCycle) * 255) / 100;
	}
#endif
}

/*=======================================================================================
 ========================================================================================
 ======================================================================================== */

void TIMER_SetCallBack(void (*Copy_CallBackFunc)(void), u8 Copy_VectorID) {

	if (Copy_CallBackFunc != NULL) {
		TIMERS_CallBackFunc[Copy_VectorID] = Copy_CallBackFunc;
	}

}
/*TIMER0 Normal Mode ISR*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void) {
	if (TIMERS_CallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL) {
		TIMERS_CallBackFunc[TIMER0_OVF_VECTOR_ID]();
	}
}

/*TIMER0 CTC Mode ISR*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void) {
	if (TIMERS_CallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL) {
		TIMERS_CallBackFunc[TIMER0_CTC_VECTOR_ID]();
	}
}
/*TIMER1 Normal Mode ISR*/
void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{
	if (TIMERS_CallBackFunc[TIMER1_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER1_OVF_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCB Mode ISR*/
void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	if (TIMERS_CallBackFunc[TIMER1_CTCB_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER1_CTCB_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCA Mode ISR*/
void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{
	if (TIMERS_CallBackFunc[TIMER1_CTCA_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER1_CTCA_VECTOR_ID]() ;
	}
}

/*TIMER1 ICU ISR*/
void __vector_6 (void)		__attribute__((signal)) ;
void __vector_6 (void)
{
	if (TIMERS_CallBackFunc[TIMER1_ICU_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER1_ICU_VECTOR_ID]() ;
	}
}

/*TIMER2 Normal Mode ISR*/
void __vector_5(void) __attribute__((signal));
void __vector_5(void) {
	if (TIMERS_CallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL) {
		TIMERS_CallBackFunc[TIMER2_OVF_VECTOR_ID]();
	}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4(void) __attribute__((signal));
void __vector_4(void) {
	if (TIMERS_CallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL) {
		TIMERS_CallBackFunc[TIMER2_CTC_VECTOR_ID]();
	}
}
