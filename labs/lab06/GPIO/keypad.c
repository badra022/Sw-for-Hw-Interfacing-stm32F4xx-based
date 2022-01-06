/*
 * keypad.c
 *
 *  Created on: Dec 27, 2019
 *      Author: badra069
 */
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include "GPIO.h"
#include"keypad.h"
static unsigned char current_key;
void (*KeypadCallouts_KeyPressNotificaton)(void) = (void*)0;
/*************************************PRIVATE FUNCTIONS DECLARATION**************************************/
#if(N_COL == 3)
static unsigned char KEYPAD_4x3_adjustKeyNumber(unsigned char a_number);
#elif(N_COL == 4)
static unsigned char KEYPAD_4x4_adjustKeyNumber(unsigned char a_number);
#endif
void KEYPAD_init(void)
{
	for(unsigned char i = 0; i < 3; i++){
		GPIO_Init(KEYPAD_PORT, KEYPAD_START_PIN + i, OUTPUT, PUSH_PULL, NO_PULLING);
	}

	for(unsigned char i = 4; i < 8; i++){
		GPIO_Init(KEYPAD_PORT, KEYPAD_START_PIN + i, INPUT, PUSH_PULL, PULL_UP);
	}
}

void Keypad_setCallBack(void (*func)(void)){
	KeypadCallouts_KeyPressNotificaton = func;
}

unsigned char Keypad_GetKey(void){
	return current_key;
}

void Keypad_manage(void)
{
	unsigned char row , col;		/*to hold the current location in the keypad*/
	while(1)
	{		/*looping till entering the key*/
		for(col = 0 ; col < N_COL ; col++)
		{
			for(unsigned char i = 0; i < 3; i++)
			{
				GPIO_WritePin(KEYPAD_PORT, KEYPAD_START_PIN + i, (i == col)?0: 1);
			}
			/*test the column with outing 0 in it and reading rows*/
			for(row = 0 ; row < N_ROW ; row++)
			{
				if(GPIO_ReadPin(KEYPAD_PORT, KEYPAD_START_PIN + row + 4) == 0)
				{
					for(int j = 0; j < 50000; j++){}		/* for debouncing */

					if(GPIO_ReadPin(KEYPAD_PORT, KEYPAD_START_PIN + row + 4) == 0)
					{
						/*waiting for the user to move his hand from the button*/
						while(GPIO_ReadPin(KEYPAD_PORT, KEYPAD_START_PIN + row + 4) == 0){};

						#if(N_COL == 3)
						current_key = KEYPAD_4x3_adjustKeyNumber(row*N_COL + col + 1);
						KeypadCallouts_KeyPressNotificaton();
						/*call the local function that return the key*/
						#elif(N_COL == 4)
						current_key = KEYPAD_4x4_adjustKeyNumber(row*N_COL + col + 1);
						KeypadCallouts_KeyPressNotificaton();
						/*call the local function that return the key*/
						#endif
					}
				}
			}
		}
	}
}
#if(N_COL == 3)
static unsigned char KEYPAD_4x3_adjustKeyNumber(unsigned char a_number)
{
	switch(a_number)
	{
	case 1 : return 1;
				break;
	case 2 : return 2;
				break;
	case 3 : return 3;
				break;
	case 4 : return 4;
				break;
	case 5 : return 5;
				break;
	case 6 : return 6;
				break;
	case 7 : return 7;
				break;
	case 8 : return 8;
				break;
	case 9 : return 9;
				break;
	case 11: return 0;
				break;
	}
	return 0xFF;
}
#elif(N_COL == 4)
static unsigned char KEYPAD_4x4_adjustKeyNumber(unsigned char a_number)
{
	switch(a_number)
	{
	case 1 : return 7;
				break;
	case 2 : return 8;
				break;
	case 3 : return 9;
				break;
	case 5 : return 4;
				break;
	case 6 : return 5;
				break;
	case 7 : return 6;
				break;
	case 9 : return 1;
				break;
	case 10: return 2;
				break;
	case 11: return 3;
				break;
	case 12: return '-';
				break;
	case 14: return 0;
				break;
	}
	return 0xFF;
}
#endif
