/*
 * LCD_program.c
 *
 *  Created on: Jul 3, 2024
 *      Author: wily
 */
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_interface.h"

void LCD_Init() {

#if LCD_MODE ==8
	_delay_ms(50);
	GPIO_SetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RW, PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_EN, PIN_OUTPUT);
	// Return Home
	LCD_SendCommand(lcd_Home);
	_delay_ms(1);
	// Function Set 8 BIT
	LCD_SendCommand(EIGHT_BITS);
	_delay_ms(1);
	//Display ON / Cursor OFF
	LCD_SendCommand(lcd_DisplayOn_CursorOff);
	_delay_ms(1);
	//Clear Screen
	LCD_ClearScreen();
	LCD_SendCommand(lcd_EntryMode);
	_delay_ms(1);
#elif LCD_MODE ==4

	_delay_ms(50);
	GPIO_SetHighNibbleDirection(LCD_DATA_PORT, H_NIBBLE_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RW, PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_EN, PIN_OUTPUT);
	// Return Home
	LCD_SendCommand(lcd_Home);
	_delay_ms(30);
	// Function Set 4 BIT
	LCD_SendCommand(FOUR_BITS);
	_delay_ms(1);
	//Display ON / Cursor OFF
	LCD_SendCommand(lcd_DisplayOn_CursorOff);
	_delay_ms(1);
	//Clear Screen
	LCD_ClearScreen();
	LCD_SendCommand(lcd_EntryMode);
	_delay_ms(1);

#endif
}
void LCD_SendData(u8 CopyData) {
#if LCD_MODE ==8
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, LOGIC_HIGH);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW, LOGIC_LOW);

	GPIO_WritePortValue(LCD_DATA_PORT, CopyData);
	LCD_fallingEdge();
#elif LCD_MODE ==4
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, LOGIC_HIGH);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW, LOGIC_LOW);

	GPIO_WriteHighNibbleValue(LCD_DATA_PORT, CopyData >> 4);
	LCD_fallingEdge();
	GPIO_WriteHighNibbleValue(LCD_DATA_PORT, CopyData);
	LCD_fallingEdge();
#endif
	_delay_ms(1);
}

void LCD_SendCommand(u8 CopyCommand) {
#if LCD_MODE ==8
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, LOGIC_LOW);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW, LOGIC_LOW);
	GPIO_WritePortValue(LCD_DATA_PORT, CopyCommand);
	LCD_fallingEdge();
#elif LCD_MODE ==4
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, LOGIC_LOW);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW, LOGIC_LOW);
	GPIO_WriteHighNibbleValue(LCD_DATA_PORT, CopyCommand >> 4);
	LCD_fallingEdge();
	GPIO_WriteHighNibbleValue(LCD_DATA_PORT, CopyCommand);
	LCD_fallingEdge();
#endif
	_delay_ms(1);
}
void LCD_SendString(const u8* CopyptrString) {
	u8 LOC_ITERATOR = 0;
	while (CopyptrString[LOC_ITERATOR] != '\0') {
		LCD_SendData(CopyptrString[LOC_ITERATOR]);
		LOC_ITERATOR++;
	}
}
void LCD_SendNumber(u64 CopyNumber) {
	u64 LOC_u64Reversed = 1;
	if (CopyNumber == 0) {
		LCD_SendData('0');
	}

	else {

		while (CopyNumber != 0) {

			LOC_u64Reversed = (LOC_u64Reversed * 10) + (CopyNumber % 10);
			CopyNumber /= 10;

		}
		while (LOC_u64Reversed != 1) {

			LCD_SendData((LOC_u64Reversed % 10) + 48);
			LOC_u64Reversed /= 10;

		}

	}
}
void LCD_SetPosition(u8 CopyRow, u8 CopyCol) {
	if (CopyCol < 1 || CopyCol > 16 || CopyRow < 1 || CopyRow > 2) {
		LCD_SendCommand(lcd_SetCursor);
	} else if (1 == CopyRow) {
		LCD_SendCommand(lcd_SetCursor + (CopyCol - 1));
	} else if (2 == CopyRow) {
		LCD_SendCommand(lcd_SetCursor + (64) + (CopyCol - 1));
	}
	_delay_ms(1);
}
void LCD_SendExtraChar(u8 CopyRow, u8 CopyCol) {

}

void LCD_ClearScreen() {
	LCD_SendCommand(lcd_Clear);
	_delay_ms(10);
}

static void LCD_fallingEdge() {
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN, LOGIC_LOW);
	_delay_ms(1);
}
