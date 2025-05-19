/*
 * LED_interface.h
 *
 *  Created on: Jun 28, 2024
 *      Author: wily
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

typedef struct {
	u8 Port ;
	u8 Pin  ;
	u8 Active_Statue ;
}LED_Type;

void LED_Init  (LED_Type LED_Configration);
void LED_On    (LED_Type LED_Configration);
void LED_Off   (LED_Type LED_Configration);
void LED_Toggle(LED_Type LED_Configration);
u8 LED_GetValue(LED_Type LED_Configration);

#endif /* LED_INTERFACE_H_ */
