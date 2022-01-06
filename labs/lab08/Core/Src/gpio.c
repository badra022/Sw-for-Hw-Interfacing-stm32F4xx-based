/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 24/11/2020			*************/
/*********** Version	: V01					*************/
/************************************************************/

#include "gpio.h"

void GPIO_Init( char port_id, unsigned int PIN_NO, unsigned int PIN_Dir, unsigned int Default_State, unsigned char Pulling_State)
{
	port_id -= 'A';
	//enable clock of port
	RCC_AHB1ENR |= (0x01 <<port_id);
	//configure moder register for pin direction
	switch(PIN_Dir)
	{
		case (INPUT):
				GPIO_MODER(port_id) &= ~(0x03 << 2*PIN_NO);
		break;
		case (OUTPUT):
				GPIO_MODER(port_id) |= (0x01 << 2*PIN_NO);
		break;
		case (ALTERNATE_FUN):
				GPIO_MODER(port_id) |= (0x02 << 2*PIN_NO);
		break;
		case (ANALOG):
				GPIO_MODER(port_id) |= (0x03 << 2*PIN_NO);
		break;
	}// end switch
	//configure default state
	switch(Default_State)
	{
		case(PUSH_PULL):
				GPIO_OTYPER(port_id) &= ~(0x01<<PIN_NO);
		break;
		case(OPEN_DRAIN):
				GPIO_OTYPER(port_id) |= (0x01<<PIN_NO);
		break;
	}//end switch

	GPIO_PUPDR(port_id) = (GPIO_PUPDR(port_id) & ~(0x3 << 2 * PIN_NO)) | (Pulling_State << 2 * PIN_NO);
}

unsigned char GPIO_WritePin(char port_id, unsigned int PIN_NO, unsigned int Data)
{
	port_id -= 'A';
	unsigned char result;
	if((GPIO_MODER(port_id) & (0x03 << 2*PIN_NO)) >> (2*PIN_NO) == 1)
	{
		 if(Data)
		 {
			 GPIO_ODR(port_id) |= (1<<PIN_NO);
		 }
		 else
		 {
			 GPIO_ODR(port_id) &= ~(1<<PIN_NO);
		 }
		result = OK;
	}
	else
	{
		result = NOK;
	}
	return result;
}

unsigned char GPIO_ReadPin(char port_id, unsigned int PIN_NO){
	port_id -= 'A';
	return (GPIO_IDR(port_id) & (1 << PIN_NO)) >> PIN_NO;
}

void GPIO_setAlternateFunction(char port_id, unsigned int PIN_NO, AF_dtype selected_function){
	port_id -= 'A';
	if(PIN_NO < 8){
		GPIO_AFRL(port_id) = (selected_function << (4 * PIN_NO)) | (GPIO_AFRL(port_id) & ~(0x0F << (4 * PIN_NO)));
	}
	else{
		GPIO_AFRH(port_id) = (selected_function << (4 * (PIN_NO - 8))) | (GPIO_AFRH(port_id) & ~(0x0F << (4 * (PIN_NO - 8))));
	}
}
