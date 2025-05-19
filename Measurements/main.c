/*
 * main.c
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define MCUCSR *((volatile u8*)0x55)
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"
#include "LCD_interface.h"
#include "BUZ_interface.h"
#include "LED_interface.h"
#include "SERVO_interface.h"
#include "EXIT_interface.h"

u16 Result;
u16 LDR;
u16 LDR_value;
u16 value;
u8 flame;
u8 rain;
u8 motion;

BUZ_Type buz = { PORTD_ID, PIN3_ID, ACTIVE_HIGH };
LED_Type led = { PORTB_ID, PIN0_ID, ACTIVE_HIGH };

void main() {
	MCUCSR |= (1 << 7);
	MCUCSR |= (1 << 7);  // Needs to be written twice within four clock cycles

	GPIO_SetPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT); //==> Flame sensor
	GPIO_SetPinDirection(PORTD_ID, PIN1_ID, PIN_INPUT); //==> Rain sensor
	GPIO_SetPinDirection(PORTD_ID, PIN0_ID, PIN_INPUT); // ==> Motion sensor


	GPIO_SetPinDirection(PORTD_ID,PIN4_ID,PIN_OUTPUT); // Rain Servo
	GPIO_SetPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT); // Motion Servo


	BUZ_Init(buz);
	LED_Init(led);
	ADC_Init();
	LCD_Init();

	TIMER1_Init();

	ADC_Enable();
	GIE_Enable();

	LCD_SendString("T=");
	while (1) {
		value = 0;
		LDR_value = 0;
		for (int i = 0; i < 10; i++)
		{
			ADC_GetResultSingle(ADC_CHANNEL0, &Result);
			value += ((((u16) Result * 2560ul) / 1023ul) / 10ul);
		}
		for (int i = 0; i < 10; i++)
		{
			ADC_GetResultSingle(ADC_CHANNEL1, &LDR);
			LDR_value += ((((u16) LDR * 2560ul) / 1023ul));
		}

		value /= 10;
		LDR_value /= 10;

		flame = GPIO_GetPinValue(PORTD_ID, PIN2_ID);
		rain = GPIO_GetPinValue(PORTD_ID, PIN1_ID);
		motion = GPIO_GetPinValue(PORTD_ID, PIN0_ID);

		LCD_SetPosition(LCD_ROW_1, LCD_COL_3);

		if (LDR_value > 1500) {
			LED_On(led);
		}
		else
		{
			LED_Off(led);
		}

		if (value >= 100)
		{
			LCD_SendString(" ");
			LCD_SendNumber(value);
			LCD_SendData('C');
		}
		else if (value > 10 && value < 100)
		{
			LCD_SendString("  ");
			LCD_SendNumber(value);
			LCD_SendData('C');
		}
		else if (value < 10)
		{
			LCD_SendString("   ");
			LCD_SendNumber(value);
			LCD_SendData('C');
		}

		if (flame)
		{
			LCD_SetPosition(LCD_ROW_2, LCD_COL_1);
			LCD_SendString("Fire!!!");
			BUZ_On(buz);
		}
		else
		{
			LCD_SetPosition(LCD_ROW_2, LCD_COL_1);
			LCD_SendString("       ");
			BUZ_Off(buz);
		}

		if (rain == 0)
		{
			LCD_SetPosition(LCD_ROW_1, LCD_COL_9);
			LCD_SendString("Raining!");
			TIMER1_SetCTCB(2000);
		}

		else
		{
			LCD_SetPosition(LCD_ROW_1, LCD_COL_9);
			TIMER1_SetCTCB(500);
			LCD_SendString("        ");
		}

		if (motion)
		{
			LCD_SetPosition(LCD_ROW_2, LCD_COL_9);
			LCD_SendString("D_Opened");
			TIMER1_SetCTCA(2300);
		} else
		{
			LCD_SetPosition(LCD_ROW_2, LCD_COL_9);
			LCD_SendString("D_Closed          ");

			TIMER1_SetCTCA(500);
		}
	}

}
