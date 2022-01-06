/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 3/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "MATH_macros.h"
#include "STD_types.h"
#include <math.h>

#include "gpio.h"
#include "uart.h"


/************************************************************/
/*						FUNCTION DEFINITIONS				*/
/************************************************************/

void USART1_voidInit(uartConfig_dtype* config_ptr){
	/* enable USART1 clock from the RCC */
	SET_BIT(RCC_APB2ENR, 4);

	USART1_CR1 = 0x0000;
	/* enable the uart */
	SET_BIT(USART1_CR1, 13);

	/* setup the baud rate */
	float64 UASRTDIV = (float64)(16000000) / (BAUDRATE * 8 * (2 - config_ptr->over_eight));
	u8 fraction = ceil((UASRTDIV - floor(UASRTDIV)) * (8 * (2 - config_ptr->over_eight)));
	u16 mantissa =  UASRTDIV;
	USART1_BRR = fraction | (mantissa << 4);

//	USART1_BRR = 0x683;

	USART1_CR2 = (config_ptr->stopBit << 12) | (config_ptr->clock_synch << 11)
			| (config_ptr->clock_polarity << 10) | (config_ptr->clock_phase << 9);

	USART1_CR1 |= (config_ptr->over_eight << 15) | (config_ptr->word_length << 12)
			| (config_ptr->parity.enable << 10) | (config_ptr->parity.type << 9) | (config_ptr->parity_error_interrupt << 8)
			| (config_ptr->transmission_complete_interrupt << 6) | (config_ptr->receive_complete_interrupt << 5)
			| (config_ptr->receiver << 2);
	USART1_CR1 |= (config_ptr->transmitter << 3);
}

void USART1_voidTransmitCharacter(u8 u8data){
	CLR_BIT(USART1_SR, 6);
	USART1_DR = u8data;

}

u8 USART1_u8ReceiveCharacter(void){
	return USART1_DR;
}

void USART1_voidSendString(u8* str){
	while(*str != '\0'){
		USART1_voidTransmitCharacter(*str);
		while(!GET_BIT(USART1_SR, 6)){}
		str++;
	}
	USART1_voidTransmitCharacter('\0');
}

void USART2_voidInit(uartConfig_dtype* config_ptr){
	/* enable USART1 clock from the RCC */
	SET_BIT(RCC_APB1ENR, 17);

	USART2_CR1 = 0x0000;
	/* enable the uart */
	SET_BIT(USART2_CR1, 13);

	/* setup the baud rate */
	float64 UASRTDIV = (16000000) / (BAUDRATE * 8 * (2 - config_ptr->over_eight));
	u8 fraction = ceil((UASRTDIV - floor(UASRTDIV)) * (8 * (2 - config_ptr->over_eight)));
	u16 mantissa =  ceil(UASRTDIV);
	USART2_BRR = fraction | (mantissa << 4);

//	USART2_BRR = 0x683;

	USART2_CR2 = (config_ptr->stopBit << 12) | (config_ptr->clock_synch << 11)
			| (config_ptr->clock_polarity << 10) | (config_ptr->clock_phase << 9);

	USART2_CR1 |= (config_ptr->over_eight << 15) | (config_ptr->word_length << 12)
			| (config_ptr->parity.enable << 10) | (config_ptr->parity.type << 9) | (config_ptr->parity_error_interrupt << 8)
			| (config_ptr->transmission_complete_interrupt << 6) | (config_ptr->receive_complete_interrupt << 5)
			| (config_ptr->receiver << 2);
	USART2_CR1 |= (config_ptr->transmitter << 3);
}

void USART2_voidTransmitCharacter(u8 u8data){
	CLR_BIT(USART2_SR, 6);
	USART2_DR = u8data;

}

u8 USART2_u8ReceiveCharacter(void){
	return USART2_DR;
}

void USART2_voidSendString(u8* str){

	while(*str != '\0'){
		USART2_voidTransmitCharacter(*str);
		while(!GET_BIT(USART2_SR, 6)){}
		str++;
	}
	USART2_voidTransmitCharacter('\0');
}
