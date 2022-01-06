/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#define _EXTI0_VECTOR_IRQ		6
#define _EXTI1_VECTOR_IRQ		7
#define _EXTI2_VECTOR_IRQ		8
#define _EXTI3_VECTOR_IRQ		9
#define _EXTI4_VECTOR_IRQ		10

#define EXTI_BASE_ADDRESS		0x40013C00
#define SYSCFG_BASE_ADDRESS		0x40013800

#define EXTI_IMR		*((volatile u32* )(EXTI_BASE_ADDRESS + 0x00))
#define EXTI_EMR		*((volatile u32* )(EXTI_BASE_ADDRESS + 0x04))
#define EXTI_RTSR		*((volatile u32* )(EXTI_BASE_ADDRESS + 0x08))
#define EXTI_FTSR		*((volatile u32* )(EXTI_BASE_ADDRESS + 0x0C))
#define EXTI_SWIER		*((volatile u32* )(EXTI_BASE_ADDRESS + 0x10))
#define EXTI_PR			*((volatile u32* )(EXTI_BASE_ADDRESS + 0x14))

typedef struct{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 RESERVED[2];
	u32 CMPCR;
}SYSCFG_dtype;

#define SYSCFG	((volatile SYSCFG_dtype*)(SYSCFG_BASE_ADDRESS))
#define RCC_APB2ENR		*((volatile u32*)(0x40023800 + 0x44))

typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	BOTH,
}triggerState_dtype;

typedef enum{
	PA = 0,
	PB = 1,
	PC = 2,
	PD = 3,
	PE = 4,
	PH = 7,
}channelPort_dtype;

void EXTI_enableInterruptChannel(u32 copy_u32channelNumber, triggerState_dtype trigger, channelPort_dtype port);
void EXTI_disableInterruptChannel(u32 copy_u32channelNumber);
void EXTI_SoftwareInterrupt(u32 copy_u32channelNumber);
u8 EXTI_getPendingBit(u32 copy_u32channelNumber);

#endif /* INC_EXTI_H_ */
