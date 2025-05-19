/*
 * GPIO_interface.h
 *
 *  Created on: Jun 27, 2024
 *      Author: wily
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/* Directions */

#define PIN_INPUT		0
#define PIN_OUTPUT		1
#define PORT_INPUT		0
#define PORT_OUTPUT		255
#define L_NIBBLE_INPUT		0x00
#define L_NIBBLE_OUTPUT		0x0f
#define H_NIBBLE_INPUT		0x00
#define H_NIBBLE_OUTPUT		0xf0
#define ACTIVE_HIGH     1
#define ACTIVE_LOW      0


/* Ports */

#define PORTA_ID		0
#define PORTB_ID		1
#define PORTC_ID		2
#define PORTD_ID		3

/* Pins */

#define PIN0_ID			0
#define PIN1_ID			1
#define PIN2_ID			2
#define PIN3_ID			3
#define PIN4_ID			4
#define PIN5_ID			5
#define PIN6_ID			6
#define PIN7_ID			7

/* Functions Prototypes */

void GPIO_SetPinDirection(u8 Copy_PORT ,u8 Copy_PIN, u8 Copy_Direction);
void GPIO_SetPinValue(u8 Copy_PORT ,u8 Copy_PIN, u8 Copy_Value);
u8 GPIO_GetPinValue(u8 Copy_PORT ,u8 Copy_PIN);
void GPIO_TogglePinValue( u8 Copy_PORT , u8 Copy_PIN );

void GPIO_SetPortDirection( u8 Copy_PORT , u8 Copy_Direction );
void GPIO_WritePortValue( u8 Copy_PORT , u8 Copy_Value );
u8 GPIO_ReadPortValue( u8 Copy_PORT );

void GPIO_SetLowNibbleDirection(u8 Copy_PORT , u8 Copy_Direction);
void GPIO_SetHighNibbleDirection(u8 Copy_PORT , u8 Copy_Direction);
void GPIO_WriteLowNibbleValue( u8 Copy_PORT , u8 Copy_Value );
void GPIO_WriteHighNibbleValue( u8 Copy_PORT , u8 Copy_Value );


#endif /* GPIO_INTERFACE_H_ */
