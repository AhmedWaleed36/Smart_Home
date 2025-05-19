/*
 * GIE_program.c
 *
 *  Created on: Jul 5, 2024
 *      Author: wily
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_private.h"

void GIE_Enable ()
{
	SET_BIT (SREG , SREG_I) ;
}

void GIE_Disable ()
{
	CLR_BIT (SREG , SREG_I) ;
}
