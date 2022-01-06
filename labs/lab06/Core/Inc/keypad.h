/*
 * keypad.h
 *
 *  Created on: Dec 27, 2019
 *      Author: badra069
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/

#define N_COL				3
#define N_ROW				4
#define KEYPAD_PORT 		'B'
#define KEYPAD_START_PIN	0
/************************************************FUNCTIONS PROTOTYPES**********************************************/
void KEYPAD_init(void);
void Keypad_manage(void);
unsigned char Keypad_GetKey(void);
void Keypad_setCallBack(void (*func)(void));


#endif /* KEYPAD_H_ */
