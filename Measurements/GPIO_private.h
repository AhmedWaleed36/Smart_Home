/*
 * GPIO_private.h
 *
 *  Created on: Jun 27, 2024
 *  Author: wily
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/* GROUPA */
#define PORTA *((volatile u8*)0x3B)
#define DDRA *((volatile u8*)0x3A)
#define PINA *((volatile u8*)0x39)

/* GROUPB */
#define PORTB *((volatile u8*)0x38)
#define DDRB *((volatile u8*)0x37)
#define PINB *((volatile u8*)0x36)

/* GROUPC */
#define PORTC *((volatile u8*)0x35)
#define DDRC *((volatile u8*)0x34)
#define PINC *((volatile u8*)0x33)

/* GROUPD */
#define PORTD *((volatile u8*)0x32)
#define DDRD *((volatile u8*)0x31)
#define PIND *((volatile u8*)0x30)


#endif /* GPIO_PRIVATE_H_ */
