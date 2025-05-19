/*
 * LED_interface.c
 *
 *  Created on: Jun 28, 2024
 *      Author: wily
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LED_interface.h"

void LED_Init(LED_Type LED_Configration) {

	GPIO_SetPinDirection(LED_Configration.Port, LED_Configration.Pin,
			PIN_OUTPUT);

}
void LED_On(LED_Type LED_Configration) {
	if (LED_Configration.Active_Statue == ACTIVE_HIGH) {
		GPIO_SetPinValue(LED_Configration.Port, LED_Configration.Pin,
				LOGIC_HIGH);
	} else if (LED_Configration.Active_Statue == ACTIVE_LOW) {
		GPIO_SetPinValue(LED_Configration.Port, LED_Configration.Pin,
				LOGIC_LOW);
	}

}
void LED_Off(LED_Type LED_Configration) {
	if (LED_Configration.Active_Statue == ACTIVE_HIGH) {
		GPIO_SetPinValue(LED_Configration.Port, LED_Configration.Pin,
				LOGIC_LOW);
	} else if (LED_Configration.Active_Statue == ACTIVE_LOW) {
		GPIO_SetPinValue(LED_Configration.Port, LED_Configration.Pin,
				LOGIC_HIGH);
	}

}
void LED_Toggle(LED_Type LED_Configration) {
	GPIO_TogglePinValue(LED_Configration.Port, LED_Configration.Pin);

}
u8 LED_GetValue(LED_Type LED_Configration) {
	u8 LOC_Statues =0;
	LOC_Statues= GPIO_GetPinValue(LED_Configration.Port, LED_Configration.Pin);
	return LOC_Statues;
}
