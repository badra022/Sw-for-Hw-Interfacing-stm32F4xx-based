/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include"STD_types.h"
#include"MATH_macros.h"

#include "exti.h"

/************************************************************/
/*						FUNCTION DEFINITIONS				*/
/************************************************************/

void EXTI_enableInterruptChannel(u32 copy_u32channelNumber, triggerState_dtype trigger, channelPort_dtype port){

	if(trigger == RISING_EDGE){
		/* Rising trigger enabled */
		SET_BIT(EXTI_RTSR, copy_u32channelNumber);
	}
	if(trigger == FALLING_EDGE){
		/* Falling trigger enabled */
		SET_BIT(EXTI_FTSR, copy_u32channelNumber);
	}
	else if(trigger == BOTH){
		/* Falling and Rising trigger enabled */
		SET_BIT(EXTI_RTSR, copy_u32channelNumber);
		SET_BIT(EXTI_FTSR, copy_u32channelNumber);
	}

	/* Interrupt request from line copy_u32channelNumber is not masked */
	SET_BIT(EXTI_IMR, copy_u32channelNumber);

	/* enable SYSCFG peripheral clock to set the port selected through it */
	RCC_APB2ENR |= (1 << 14);

	/* set the port selected */
	SYSCFG->EXTICR[copy_u32channelNumber >> 2] = (port << (4 * (copy_u32channelNumber % 4)))
		| (SYSCFG->EXTICR[copy_u32channelNumber >> 2] & ~(0x0F << (4 * (copy_u32channelNumber % 4))));

}

void EXTI_disableInterruptChannel(u32 copy_u32channelNumber){
	/* Interrupt request from line copy_u32channelNumber is masked */
	CLR_BIT(EXTI_IMR, copy_u32channelNumber);

	/* reset triggers enabled */
	CLR_BIT(EXTI_RTSR, copy_u32channelNumber);
	CLR_BIT(EXTI_FTSR, copy_u32channelNumber);
}

void EXTI_SoftwareInterrupt(u32 copy_u32channelNumber){
	SET_BIT(EXTI_SWIER, copy_u32channelNumber);
}


u8 EXTI_getPendingBit(u32 copy_u32channelNumber){
	/* read the bit */
	u8 result = GET_BIT(EXTI_PR, copy_u32channelNumber);

	/* reset the pending flag to zero in case it was set */
	SET_BIT(EXTI_PR, copy_u32channelNumber);

	return result;
}
