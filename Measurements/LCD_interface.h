/*
 * LCD_interface.h
 *
 *  Created on: Jul 3, 2024
 *      Author: wily
 */

#ifndef LCD_LCD_INTERFACE_H_
#define LCD_LCD_INTERFACE_H_

#include "LCD_config.h"

#if LCD_MODE == 4
#define FOUR_BITS                     0x28

#elif LCD_MODE ==8
#define EIGHT_BITS                    0x38
#endif

#define lcd_DisplayOn_CursorOff       0x0c          // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn        0x0e          // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff      0x08          // turn display off
#define lcd_Clear                     0x01          //replace all characters with ASCII 'space'
#define lcd_EntryMode                 0x06          // shift cursor from left to right on read/write
#define lcd_Home                      0x02          // return cursor to first position on first line
#define lcd_CGRAM                     0x40          // the first Place/Address at CGRAM
#define lcd_SetCursor                 0x80          // set cursor position
#define lcd_FunctionReset             0x30          // reset the LCD

#define LCD_ROW_1   1
#define LCD_ROW_2   2

#define LCD_COL_1   1
#define LCD_COL_2   2
#define LCD_COL_3   3
#define LCD_COL_4   4
#define LCD_COL_5   5
#define LCD_COL_6   6
#define LCD_COL_7   7
#define LCD_COL_8   8
#define LCD_COL_9   9
#define LCD_COL_10  10
#define LCD_COL_11  11
#define LCD_COL_12  12
#define LCD_COL_13  13
#define LCD_COL_14  14
#define LCD_COL_15  15
#define LCD_COL_16  16

void LCD_Init                      ();
void LCD_SendData                  (u8 CopyData);
void LCD_SendCommand               ( u8 CopyCommand);
void LCD_SendString                ( const u8* CopyptrString);
void LCD_SendNumber                ( u64 CopyNumber);
void LCD_SetPosition               ( u8 CopyRow, u8 CopyCol );
void LCD_SendExtraChar             ( u8 CopyRow, u8 CopyCol );
void LCD_ClearScreen               ();
#endif /* LCD_LCD_INTERFACE_H_ */
