/*
 * BIT_MATH.h
 *
 *  Created on: Jun 27, 2024
 *      Author: wily
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT) REG|=(1<<BIT)
#define CLR_BIT(REG,BIT) REG&=(~(1<<BIT))
#define TOG_BIT(REG,BIT) REG^=(1<<BIT)
#define RED_BIT(REG,BIT) (REG&(1<<BIT))>>BIT

#define IS_BIT_SET(REG,BIT) (REG&(1<<BIT))>>BIT
#define IS_BIT_CLR(REG,BIT)     !(REG&(1<<BIT))>>BIT



#endif /* BIT_MATH_H_ */
