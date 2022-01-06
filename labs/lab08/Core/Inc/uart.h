/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 3/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

/************************************************************/
/*			GUARD FILE TO PREVENT MULTIPLE INCLUSION		*/
/************************************************************/
#ifndef INC_UART_H_
#define INC_UART_H_

#define BAUDRATE		9600


#define USART1_BASE_ADDRESS			0x40011000
#define USART2_BASE_ADDRESS			0x40004400
#define USART6_BASE_ADDRESS			0x40011400

#define USART1_SR		*((volatile u32*)(USART1_BASE_ADDRESS + 0x00))
#define USART1_DR		*((volatile u32*)(USART1_BASE_ADDRESS + 0x04))
#define USART1_BRR		*((volatile u32*)(USART1_BASE_ADDRESS + 0x08))
#define USART1_CR1		*((volatile u32*)(USART1_BASE_ADDRESS + 0x0C))
#define USART1_CR2		*((volatile u32*)(USART1_BASE_ADDRESS + 0x10))
#define USART1_CR3		*((volatile u32*)(USART1_BASE_ADDRESS + 0x14))
#define USART1_GTPR		*((volatile u32*)(USART1_BASE_ADDRESS + 0x18))

#define USART2_SR		*((volatile u32*)(USART2_BASE_ADDRESS + 0x00))
#define USART2_DR		*((volatile u32*)(USART2_BASE_ADDRESS + 0x04))
#define USART2_BRR		*((volatile u32*)(USART2_BASE_ADDRESS + 0x08))
#define USART2_CR1		*((volatile u32*)(USART2_BASE_ADDRESS + 0x0C))
#define USART2_CR2		*((volatile u32*)(USART2_BASE_ADDRESS + 0x10))
#define USART2_CR3		*((volatile u32*)(USART2_BASE_ADDRESS + 0x14))
#define USART2_GTPR		*((volatile u32*)(USART2_BASE_ADDRESS + 0x18))

#define USART6_SR		*((volatile u32*)(USART6_BASE_ADDRESS + 0x00))
#define USART6_DR		*((volatile u32*)(USART6_BASE_ADDRESS + 0x04))
#define USART6_BRR		*((volatile u32*)(USART6_BASE_ADDRESS + 0x08))
#define USART6_CR1		*((volatile u32*)(USART6_BASE_ADDRESS + 0x0C))
#define USART6_CR2		*((volatile u32*)(USART6_BASE_ADDRESS + 0x10))
#define USART6_CR3		*((volatile u32*)(USART6_BASE_ADDRESS + 0x14))
#define USART6_GTPR		*((volatile u32*)(USART6_BASE_ADDRESS + 0x18))

#define RCC_APB2ENR		*((volatile u32*)(0x40023800 + 0x44))
#define RCC_APB1ENR		*((volatile u32*)(0x40023800 + 0x40))

typedef enum{
	EIGHT,
	NINE,
}wordLenght_dtype;

typedef enum{
	EVEN,
	ODD,
}paritySelection_dtype;

typedef struct{
	u8 enable;						/*	ENABLE, DISABLE */
	paritySelection_dtype type;		/* EVEN, ODD */
}parity_dtype;

typedef enum{
	ONE_STOP_BIT,
	HALF_STOP_BIT,
	TWO_STOP_BIT,
	ONE_AND_HALF_STOP_BIT,
}stopBit_dtype;

typedef enum{
	STEADY_LOW,
	STEADY_HIGH,
}clockPolarity_dtype;

typedef enum{
	FIRST_CLOCK,
	SECOND_CLOCK,
}clockPhase_dtype;

typedef struct{
	parity_dtype parity;			/* (ENABLE, ODD), (ENABLE, EVEN), (DISABLE, xx) */
	u8 over_eight;					/*  ENABLE, DISABLE */
	wordLenght_dtype word_length;	/*  EIGHT , NINE */
	u8 transmission_complete_interrupt;		/* ENABLE, DISABLE */
	u8 receive_complete_interrupt;			/* ENABLE, DISABLE */
	u8 parity_error_interrupt;				/* ENABLE, DISABLE */
	u8 transmitter;							/* ENABLE, DISABLE */
	u8 receiver;							/* ENABLE, DISABLE */
	u8 clock_synch;							/* ENABLE, DISABLE */
	stopBit_dtype stopBit;					/* ONE_STOP_BIT */
	clockPolarity_dtype clock_polarity;		/* STEADY_LOW, STEADY_HIGH */
	clockPhase_dtype clock_phase;			/* FIRST_CLOCK, SECOND_CLOCK */
}uartConfig_dtype;

/************************************************************/
/*						FUNCTION PROTOTYPES					*/
/************************************************************/
void USART1_voidInit(uartConfig_dtype* config_ptr);
void USART1_voidTransmitCharacter(u8 u8data);
u8 USART1_u8ReceiveCharacter(void);
void USART1_voidSendString(u8* str);

void USART2_voidInit(uartConfig_dtype* config_ptr);
void USART2_voidTransmitCharacter(u8 u8data);
u8 USART2_u8ReceiveCharacter(void);
void USART2_voidSendString(u8* str);

#endif /* INC_UART_H_ */
