/*
 * BUZ_interface.h
 *
 *  Created on: Jun 30, 2024
 *      Author: wily
 */

#ifndef BUZ_INTERFACE_H_
#define BUZ_INTERFACE_H_

typedef struct{
	u8 Port;
	u8 Pin;
	u8 Active_Statue;
}BUZ_Type;

void BUZ_Init  (BUZ_Type BUZ_Configration);
void BUZ_On    (BUZ_Type BUZ_Configration);
void BUZ_Off   (BUZ_Type BUZ_Configration);
void BUZ_Toggle(BUZ_Type BUZ_Configration);
u8 BUZ_GetValue(BUZ_Type BUZ_Configration);
#endif /* BUZ_INTERFACE_H_ */
