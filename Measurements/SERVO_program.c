/*
 * SERVO_program.c
 *
 *  Created on: Sep 8, 2024
 *      Author: ahmed  waleed
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SERVO_config.h"
#include "TIMER_interface.h"

/* with setting the PWM period to 20ms (50HZ) with a Fosc = 1000000 and the prescaller to 1  ------>  then ICR1 = 19999 */
/* with setting the PWM period to 20ms (50HZ) with a Fosc = 8000000 and the prescaller to 64  ------>  then ICR1 = 2499 */

void SERVO_SetDegreeOC1A(s8 Copy_degree){
u16 oc;
#if FOC==1000000 && PRESCALER==1
oc = 1499+((500)*(Copy_degree/90.0));
#elif  FOC==8000000 && PRESCALER==64
oc = 187-(63)*(Copy_degree/90.0);
#endif
TIMER1_SetCTCA(oc);
}
void SERVO_SetDegreeOC1B(s8 Copy_degree){
u16 oc=0;
#if FOC==1000000 && PRESCALER==1
oc = 1499+((500)*(Copy_degree/90.0));
#elif  FOC==8000000 && PRESCALER==64
oc = 187-(63)*(Copy_degree/90.0);
#endif
TIMER1_SetCTCB(oc);
}
