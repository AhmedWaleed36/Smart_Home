/*
 * ADC_interface.h
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3


#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

#define ADC_CH_MASK			    0b11100000
#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7

#define ADC_SINGLE_CONVERSION   0
#define ADC_AUTO_TRIGGER   		1

#define ADC_Auto_MASK			0b00011111
#define ADC_FREE_RUNNING        0
#define ADC_ANALOG_COMPARATOR   1
#define ADC_EXTI0               2
#define ADC_TIM0_CTC            3
#define ADC_TIM0_OVF            4
#define ADC_TIM1_CTC_CHANNEL_B  5
#define ADC_TIM1_OVF            6
#define ADC_TIM1_ICU            7

#define ADC_PRE_MASK			0b11111000
#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7

void ADC_Init         (void);
void ADC_Enable           (void);
void ADC_Disable          (void);
void ADC_InterruptEnable  (void);
void ADC_InterruptDisable (void);
void   ADC_GetResultSingle        ( u8 Copy_Channel , u16* Copy_Result                                         );
void   ADC_StartConversionInterrupt( u8 Copy_Channel , u16* Copy_Result , void(*Copy_pvNotificationFunc)(void) );
//u8   ADC_StartChainAsynch     ( Chain_t * Copy_Chain);


#endif /* ADC_INTERFACE_H_ */
