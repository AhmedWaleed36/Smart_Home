/*
 * EXIT_private.h
 *
 *  Created on: Jul 4, 2024
 *      Author: wily
 */

#ifndef EXIT_PRIVATE_H_
#define EXIT_PRIVATE_H_

#define SREG_REG 	   *((volatile u8 *)0x5F)
#define MCUCR_REG	   *((volatile u8 *)0x55)
#define MCUCSR_REG	   *((volatile u8 *)0x54)
#define GICR_REG  	   *((volatile u8 *)0x5B)
#define GIFR_REG 	   *((volatile u8 *)0x5A)


#endif /* EXIT_PRIVATE_H_ */
