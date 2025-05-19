/*
 * EXIT_config.h
 *
 *  Created on: Jul 4, 2024
 *      Author: wily
 */

#ifndef EXIT_CONFIG_H_
#define EXIT_CONFIG_H_

/*
 Options :-

 	 1-EXTI_FALLING_EDGE
 	 2-EXTI_RISING_EDGE
 	 3-EXTI_LOW_LEVEL
 	 4-EXTI_ON_CHANGE

 */

#define EXTI0_MODE  EXTI_RISING_EDGE



#define EXTI1_MODE  EXTI_FALLING_EDGE




#define EXTI2_MODE  EXTI_INT2_FALLING_EDGE


#define EXTI_INT0_INIT_STATE    EXTI_Disable_State
#define EXTI_INT1_INIT_STATE    EXTI_Disable_State
#define EXTI_INT2_INIT_STATE    EXTI_Disable_State



#endif /* EXIT_CONFIG_H_ */
