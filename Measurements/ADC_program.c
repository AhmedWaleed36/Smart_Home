/*
 * ADC_program.c
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_ConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* ADC_NotificationFunc)(void)= NULL;




void ADC_Init(void) {
	/*Select the voltage reference*/
#if	ADC_VREF == AREF
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);

#elif	ADC_VREF == AVCC
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
#elif	ADC_VREF == INTERNAL_2_56
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#endif

	/*Set Left Adjust Result*/
#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
	CLR_BIT(ADMUX, ADLAR);

#elif	ADC_ADJUSTMENT == LEFT_ADJUSTMENT
	SET_BIT(ADMUX,ADLAR);
#endif

	/*Set Trigger source */
#if	ADC_TRIGGERING_SOURCE ==  ADC_SINGLE_CONVERSION
	CLR_BIT(ADCSRA, ADATE);
#elif	ADC_TRIGGERING_SOURCE ==  ADC_AUTO_TRIGGER
	SET_BIT(ADCSRA,ADATE);
	SFIOR&=ADC_Auto_MASK;
	SFIOR|=ADC_TRIGGERING_MODE;
#endif

	/*Set Prescaler Value*/
	ADCSRA &= ADC_PRE_MASK;
	ADCSRA |= ADC_PRESCALLER;

	CLR_BIT(ADCSRA, ADEN);
	CLR_BIT(ADCSRA, ADIE);

}
void ADC_Enable(void) {
	SET_BIT(ADCSRA, ADEN);
}
void ADC_Disable(void) {
	CLR_BIT(ADCSRA, ADEN);
}
void ADC_InterruptEnable(void) {
	SET_BIT(ADCSRA, ADIE);
}
void ADC_InterruptDisable(void) {
	CLR_BIT(ADCSRA, ADIE);
}
void ADC_GetResultSingle(u8 Copy_Channel, u16* Copy_Result) {
	u32 Local_TimeoutCounter = 0;
	if (Copy_Result != NULL) {

		/*Set required channel*/
		ADMUX &= ADC_CH_MASK;
		ADMUX |= Copy_Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA, ADSC);

		/*Waiting until the conversion is complete*/
		while (((RED_BIT(ADCSRA, ADIF)) == 0) && (Local_TimeoutCounter < ADC_TIMEOUT))
		{
			Local_TimeoutCounter++;
		}
		if (Local_TimeoutCounter <= ADC_TIMEOUT) {
			/*Clear the interrupt flag*/
			SET_BIT(ADCSRA, ADIF);
			/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			*Copy_Result = (ADCL | (ADCH << 8));

		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			*Copy_Result = (ADCL>>6 | (ADCH << 2));

		#endif
		}
	}

}
void ADC_StartConversionInterrupt(u8 Copy_Channel, u16* Copy_Result,void (*Copy_NotificationFunc)(void)) {

		if ((Copy_Result != NULL) && (Copy_NotificationFunc != NULL))
		{

				/*Initialize the global result pointer*/
				ADC_ConversionResult = Copy_Result;

				/*Initialize the global notification function pointer*/
				ADC_NotificationFunc= Copy_NotificationFunc;

				/*Set required channel*/
				ADMUX &= ADC_CH_MASK ;
				ADMUX |= Copy_Channel ;

				/*Start Conversion*/
				SET_BIT(ADCSRA , ADSC) ;

				/*ADC Conversion Complete Interrupt Enable*/
				SET_BIT(ADCSRA , ADIE) ;

		}


}
void __vector_16(void) __attribute__((signal,used));
void __vector_16(void) {
			/*Return Conversion Result*/
					#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
						* ADC_ConversionResult = (ADCL|(ADCH << 8))  ;

					#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
						*ADC_AsynchConversionResult = (ADCL>>6 | (ADCH << 2)) ;

					#endif

			/*Call Notification Function*/
			ADC_NotificationFunc() ;
			SET_BIT(ADCSRA,ADIF);
			/*Disable the Conversion Complete Interrupt*/
//			CLR_BIT(ADCSRA , ADIE) ;
}
