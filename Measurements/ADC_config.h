/*
 * ADC_config.h
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/*
 Options:-
 	 1-AREF
 	 2-AVCC
 	 3-INTERNAL_2_56

 */

#define ADC_VREF  INTERNAL_2_56

/*
  Options :
 	 1-RIGHT_ADJUSTMENT
 	 2-LEFT_ADJUSTMENT

  */

#define ADC_ADJUSTMENT RIGHT_ADJUSTMENT

/*
 Options:-
 	 1-ADC_CHANNEL0
 	 2-ADC_CHANNEL1
 	 3-ADC_CHANNEL2
 	 4-ADC_CHANNEL3
 	 5-ADC_CHANNEL4
 	 6-ADC_CHANNEL5
 	 7-ADC_CHANNEL6
 	 8-ADC_CHANNEL7


 */
#define ADC_CHANNEL  ADC_CHANNEL0
/*
 Options:-
 	 1-ADC_SINGLE_CONVERSION
 	 2-ADC_AUTO_TRIGGER

 */
#define ADC_TRIGGERING_SOURCE  ADC_SINGLE_CONVERSION

/*
 Options:-
 	 1-ADC_FREE_RUNNING
 	 2-ADC_ANALOG_COMPARATOR
 	 3-ADC_EXTI0
 	 4-ADC_TIM0_CTC
 	 5-ADC_TIM0_OVF
 	 6-ADC_TIM1_CTC_CHANNEL_B
 	 7-ADC_TIM1_OVF
 	 8-ADC_TIM1_ICU

 */

#define ADC_TRIGGERING_MODE  ADC_FREE_RUNNING

/*
 Options:-
 	 1-ADC_PRE_2
 	 2-ADC_PRE_4
 	 3-ADC_PRE_8
 	 4-ADC_PRE_16
 	 5-ADC_PRE_32
 	 6-ADC_PRE_64
 	 7-ADC_PRE_128

 */

#define  ADC_PRESCALLER   ADC_PRE_8
#define  ADC_TIMEOUT      50000

#endif /* ADC_CONFIG_H_ */
