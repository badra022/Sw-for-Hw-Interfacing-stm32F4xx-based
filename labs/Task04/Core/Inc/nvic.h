/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

/************************************************************/
/*			GUARD FILE TO PREVENT MULTIPLE INCLUSION		*/
/************************************************************/
#ifndef	_NVIC_INTERFACE_H_
#define	_NVIC_INTERFACE_H_

/* 0xE000E100 Base address */

#define NVIC_PERIPHERAL_BASE	0xE000E100

typedef struct{
	u32 ISER[128];
	u32 ICER[128];
	u32 ISPR[128];
	u32 ICPR[128];
	u32 IABR[128];
	u32 RESERVED[128];
	u8 IPR;
}NVIC_dtype;

#define NVIC		((volatile NVIC_dtype*)(NVIC_PERIPHERAL_BASE))

/************************************************************/
/*						FUNCTION PROTOTYPES					*/
/************************************************************/

void NVIC_voidEnableInterrupt(u8 copy_u8IntNumber);
void NVIC_voidDisableInterrupt(u8 copy_u8IntNumber);
void NVIC_voidSetPendingFlag(u8 copy_u8IntNumber);
void NVIC_voidResetPendingFlag(u8 copy_u8IntNumber);
u8 	 NVIC_voidGetActiveFlag(u8 copy_u8IntNumber);

#endif
