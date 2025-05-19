/*
 * GPIO_program.c
 *
 *  Created on: Jun 27, 2024
 *      Author: wily
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void GPIO_SetPinDirection(u8 Copy_PORT, u8 Copy_PIN, u8 Copy_Direction) {
	if (Copy_Direction == PIN_OUTPUT) {
		switch (Copy_PORT) {
		case PORTA_ID:
			SET_BIT(DDRA, Copy_PIN);
			break;
		case PORTB_ID:
			SET_BIT(DDRB, Copy_PIN);
			break;
		case PORTC_ID:
			SET_BIT(DDRC, Copy_PIN);
			break;
		case PORTD_ID:
			SET_BIT(DDRD, Copy_PIN);
			break;
		}
	} else if (Copy_Direction == PIN_INPUT) {
		switch (Copy_PORT) {
		case PORTA_ID:
			CLR_BIT(DDRA, Copy_PIN);
			break;
		case PORTB_ID:
			CLR_BIT(DDRB, Copy_PIN);
			break;
		case PORTC_ID:
			CLR_BIT(DDRC, Copy_PIN);
			break;
		case PORTD_ID:
			CLR_BIT(DDRD, Copy_PIN);
			break;
		}
	}
}
void GPIO_SetPinValue(u8 Copy_PORT, u8 Copy_PIN, u8 Copy_Value) {
	if (Copy_Value == LOGIC_HIGH) {
		switch (Copy_PORT) {
		case PORTA_ID:
			SET_BIT(PORTA, Copy_PIN);
			break;
		case PORTB_ID:
			SET_BIT(PORTB, Copy_PIN);
			break;
		case PORTC_ID:
			SET_BIT(PORTC, Copy_PIN);
			break;
		case PORTD_ID:
			SET_BIT(PORTD, Copy_PIN);
			break;
		}
	} else if (Copy_Value == LOGIC_LOW) {
		switch (Copy_PORT) {
		case PORTA_ID:
			CLR_BIT(PORTA, Copy_PIN);
			break;
		case PORTB_ID:
			CLR_BIT(PORTB, Copy_PIN);
			break;
		case PORTC_ID:
			CLR_BIT(PORTC, Copy_PIN);
			break;
		case PORTD_ID:
			CLR_BIT(PORTD, Copy_PIN);
			break;
		}
	}
}
u8 GPIO_GetPinValue(u8 Copy_PORT, u8 Copy_PIN) {
	u8 LOC_Statues = 0;
	switch (Copy_PORT) {
	case PORTA_ID:
		LOC_Statues = RED_BIT(PINA, Copy_PIN);
		break;
	case PORTB_ID:
		LOC_Statues = RED_BIT(PINB, Copy_PIN);
		break;
	case PORTC_ID:
		LOC_Statues = RED_BIT(PINC, Copy_PIN);
		break;
	case PORTD_ID:
		LOC_Statues = RED_BIT(PIND, Copy_PIN);
		break;
	}
	return LOC_Statues;
}
void GPIO_TogglePinValue(u8 Copy_PORT, u8 Copy_PIN) {
	switch (Copy_PORT) {
	case PORTA_ID:
		TOG_BIT(PORTA, Copy_PIN);
		break;
	case PORTB_ID:
		TOG_BIT(PORTB, Copy_PIN);
		break;
	case PORTC_ID:
		TOG_BIT(PORTC, Copy_PIN);
		break;
	case PORTD_ID:
		TOG_BIT(PORTD, Copy_PIN);
		break;
	}
}
void GPIO_SetPortDirection(u8 Copy_PORT, u8 Copy_Direction) {
	if (Copy_Direction == PORT_OUTPUT) {
		switch (Copy_PORT) {
		case PORTA_ID:
			DDRA = PORT_OUTPUT;
			break;
		case PORTB_ID:
			DDRB = PORT_OUTPUT;
			break;
		case PORTC_ID:
			DDRC = PORT_OUTPUT;
			break;
		case PORTD_ID:
			DDRD = PORT_OUTPUT;
			;
			break;
		}
	} else if (Copy_Direction == PORT_INPUT) {
		switch (Copy_PORT) {
		case PORTA_ID:
			DDRA = PORT_INPUT;
			break;
		case PORTB_ID:
			DDRB = PORT_INPUT;
			break;
		case PORTC_ID:
			DDRC = PORT_INPUT;
			break;
		case PORTD_ID:
			DDRD = PORT_INPUT;
			break;
		}
	}
}
void GPIO_WritePortValue(u8 Copy_PORT, u8 Copy_Value) {
	switch (Copy_PORT) {
	case PORTA_ID:
		PORTA = Copy_Value;
		break;
	case PORTB_ID:
		PORTB = Copy_Value;
		break;
	case PORTC_ID:
		PORTC = Copy_Value;
		break;
	case PORTD_ID:
		PORTD = Copy_Value;
		break;
	}
}
u8 GPIO_ReadPortValue(u8 Copy_PORT) {
	u8 LOC_Statues = 0;
	switch (Copy_PORT) {
	case PORTA_ID:
		LOC_Statues = PINA;
		break;
	case PORTB_ID:
		LOC_Statues = PINB;
		break;
	case PORTC_ID:
		LOC_Statues = PINC;
		break;
	case PORTD_ID:
		LOC_Statues = PIND;
		break;
	}
	return LOC_Statues;
}
void GPIO_WriteLowNibbleValue(u8 Copy_PORT, u8 Copy_Value) {
	Copy_Value &= 0x0f;
	switch (Copy_PORT) {
	case PORTA_ID:
		PORTA &= 0xf0;
		PORTA |= Copy_Value;
		break;
	case PORTB_ID:
		PORTB &= 0xf0;
		PORTB |= Copy_Value;
		break;
	case PORTC_ID:
		PORTC &= 0xf0;
		PORTC |= Copy_Value;
		break;
	case PORTD_ID:
		PORTD &= 0xf0;
		PORTD |= Copy_Value;
		break;
	}
}
void GPIO_WriteHighNibbleValue(u8 Copy_PORT, u8 Copy_Value) {
	Copy_Value = (Copy_Value << 4);
	switch (Copy_PORT) {
	case PORTA_ID:
		PORTA &= 0x0f;
		PORTA |= Copy_Value;
		break;
	case PORTB_ID:
		PORTB &= 0x0f;
		PORTB |= Copy_Value;
		break;
	case PORTC_ID:
		PORTC &= 0x0f;
		PORTC |= Copy_Value;
		break;
	case PORTD_ID:
		PORTD &= 0x0f;
		PORTD |= Copy_Value;
		break;
	}
}
void GPIO_SetLowNibbleDirection(u8 Copy_PORT , u8 Copy_Direction){
		switch (Copy_PORT) {
		case PORTA_ID:
			DDRA &= 0xf0;
			DDRA |= Copy_Direction;
			break;
		case PORTB_ID:
			DDRB &= 0xf0;
			DDRB |= Copy_Direction;
			break;
		case PORTC_ID:
			DDRC &= 0xf0;
			DDRC |= Copy_Direction;
			break;
		case PORTD_ID:
			DDRD &= 0xf0;
			DDRD |=Copy_Direction;
			break;
}}
void GPIO_SetHighNibbleDirection(u8 Copy_PORT, u8 Copy_Direction){
	switch (Copy_PORT) {
	case PORTA_ID:
		DDRA &= 0x0f;
		DDRA |= Copy_Direction;
		break;
	case PORTB_ID:
		DDRB &= 0x0f;
		DDRB |= Copy_Direction;
		break;
	case PORTC_ID:
		DDRC &= 0x0f;
		DDRC |= Copy_Direction;
		break;
	case PORTD_ID:
		DDRD &= 0x0f;
		DDRD |=Copy_Direction;
		break;
}
}
