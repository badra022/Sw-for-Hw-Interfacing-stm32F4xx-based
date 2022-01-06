/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include"STD_types.h"
#include"MATH_macros.h"

#include "nvic.h"

/************************************************************/
/*						FUNCTION DEFINITIONS				*/
/************************************************************/

/***************************************************************************/
/****	Brief	:	enables the ext interrupt by the NVIC 				****/
/**** 	Return	:	None												****/
/****	param	:	bit number that corresponds to the ext peri			****/
/***************************************************************************/
void NVIC_voidEnableInterrupt(u8 copy_u8IntNumber)
{
	NVIC->ISER[copy_u8IntNumber >> 5] = 1 << (copy_u8IntNumber & 0x001F);
}

/***************************************************************************/
/****	Brief	:	disables the ext interrupt by the NVIC		 		****/
/**** 	Return	:	None												****/
/****	param	:	bit number that corresponds to the ext peri			****/
/***************************************************************************/
void NVIC_voidDisableInterrupt(u8 copy_u8IntNumber)
{
	NVIC->ICER[copy_u8IntNumber >> 5] = 1 << (copy_u8IntNumber & 0x001F);
}

/***************************************************************************/
/****	Brief	:	set the pending flag for the ext interrupt by NVIC	****/
/**** 	Return	:	None												****/
/****	param	:	bit number that corresponds to the ext peri			****/
/***************************************************************************/
void NVIC_voidSetPendingFlag(u8 copy_u8IntNumber)
{
	NVIC->ISPR[copy_u8IntNumber >> 5] = 1 << (copy_u8IntNumber & 0x001F);
}

/***************************************************************************/
/****	Brief	:	reset the pending flag for the ext interrupt by NVIC****/
/**** 	Return	:	None												****/
/****	param	:	bit number that corresponds to the ext peri			****/
/***************************************************************************/
void NVIC_voidResetPendingFlag(u8 copy_u8IntNumber)
{
	NVIC->ICPR[copy_u8IntNumber >> 5] = 1 << (copy_u8IntNumber & 0x001F);
}

u8 NVIC_voidGetActiveFlag(u8 copy_u8IntNumber)
{
	return (NVIC->IABR[copy_u8IntNumber >> 5] & (1 << (copy_u8IntNumber & 0x001F)))?1:0;
}
