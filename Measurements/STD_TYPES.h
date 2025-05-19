/*
 * STD_TYPES.h
 *
 *  Created on: Jun 27, 2024
 *      Author: wily
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#define NULL 0
#define NULL_CHAR		  ('\0')

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)

typedef unsigned char         u8;          /*           0 .. 255              */
typedef signed char           s8;          /*        -128 .. +127             */
typedef unsigned short        u16;         /*           0 .. 65535            */
typedef signed short          s16;         /*      -32768 .. +32767           */
typedef unsigned long         u32;         /*           0 .. 4294967295       */
typedef signed long           s32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    u64;         /*       0 .. 18446744073709551615  */
typedef signed long long      s64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 f32;
typedef double                f64;

#define IDLE 			0
#define BUSY			1

#define OK           	0
#define NOK          	1
#define NULL_POINTER 	2
#define BUSY_STATE	 	3
#define TIMEOUT_STATE   4

#endif /* STD_TYPES_H_ */
