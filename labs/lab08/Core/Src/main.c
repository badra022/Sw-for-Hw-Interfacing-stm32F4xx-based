/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 4/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

#include "MATH_macros.h"
#include "STD_types.h"

#include "gpio.h"
#include "nvic.h"
#include "uart.h"

void init_uart1_comm(void){

	/* setup RX, Tx pins */
	GPIO_Init('A', P9, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('A', P9, AF7);

	uartConfig_dtype Uart1_config;

	Uart1_config.parity.enable = DISABLE;
	Uart1_config.parity.type = EVEN;
	Uart1_config.over_eight = DISABLE;
	Uart1_config.clock_phase = FIRST_CLOCK;
	Uart1_config.clock_polarity = STEADY_LOW;
	Uart1_config.clock_synch = DISABLE;
	Uart1_config.parity_error_interrupt = DISABLE;
	Uart1_config.receive_complete_interrupt = DISABLE;
	Uart1_config.receiver = DISABLE;
	Uart1_config.stopBit = HALF_STOP_BIT;
	Uart1_config.word_length = EIGHT;
	Uart1_config.transmission_complete_interrupt = DISABLE;
	Uart1_config.transmitter = ENABLE;

	/* initiate the USART1 */
	USART1_voidInit(&Uart1_config);
}



int main(void) {
	init_uart1_comm();
	USART1_voidSendString((u8*)"Hello World!");

  while (1) {

  }
  return 0;
}
