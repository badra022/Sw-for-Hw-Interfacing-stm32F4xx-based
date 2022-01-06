/*
 * GPIO.h
 *
 *  Created on: Nov 24, 2021
 *      Author: ADVINTIC
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f401xc.h"

//write result
#define OK  ((unsigned char)0)
#define NOK ((unsigned char)1)

//mode types
#define INPUT ((unsigned int)0x00)
#define OUTPUT ((unsigned int)0x01)
#define ALTERNATE_FUN ((unsigned int)0x02)
#define ANALOG ((unsigned int)0x03)

//output modes
#define PUSH_PULL ((unsigned int)0x00)
#define OPEN_DRAIN ((unsigned int)0x01)

#define PULL_UP		((unsigned char)0x01)
#define PULL_DOWN	((unsigned char)0x02)
#define NO_PULLING	((unsigned char)0x00)

void GPIO_Init( char Port, unsigned int PIN_NO, unsigned int PIN_Dir, unsigned int Default_State, unsigned char Pulling_State);
unsigned char GPIO_WritePin(char Port, unsigned int PIN_NO, unsigned int Data);
unsigned char GPIO_ReadPin(char Port, unsigned int PIN_NO);


#endif /* INC_GPIO_H_ */
