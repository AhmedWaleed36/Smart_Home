/*
 * BUZ_program.h
 *
 *  Created on: Jun 30, 2024
 *      Author: wily
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "BUZ_interface.h"

void BUZ_Init(BUZ_Type BUZ_Configration) {

	GPIO_SetPinDirection(BUZ_Configration.Port, BUZ_Configration.Pin,
	PIN_OUTPUT);

}
void BUZ_On(BUZ_Type BUZ_Configration) {
	if (BUZ_Configration.Active_Statue == ACTIVE_HIGH) {
		GPIO_SetPinValue(BUZ_Configration.Port, BUZ_Configration.Pin,
		LOGIC_HIGH);
	} else if (BUZ_Configration.Active_Statue == ACTIVE_LOW) {
		GPIO_SetPinValue(BUZ_Configration.Port, BUZ_Configration.Pin,
		LOGIC_LOW);
	}

}
void BUZ_Off(BUZ_Type BUZ_Configration) {
	if (BUZ_Configration.Active_Statue == ACTIVE_HIGH) {
		GPIO_SetPinValue(BUZ_Configration.Port, BUZ_Configration.Pin,
		LOGIC_LOW);
	} else if (BUZ_Configration.Active_Statue == ACTIVE_LOW) {
		GPIO_SetPinValue(BUZ_Configration.Port, BUZ_Configration.Pin,
		LOGIC_HIGH);
	}

}
void BUZ_Toggle(BUZ_Type BUZ_Configration) {
	GPIO_TogglePinValue(BUZ_Configration.Port, BUZ_Configration.Pin);

}

