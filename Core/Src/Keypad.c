/*
 * Author : Mohamed Galloul
 * Date   : 9/12/2021
 * Version: 1.0.0
 */
#include "Keypad.h"
#include "GPIO.h"
#include "main.h"

static int pressed_key;
static char state=RELEASED;
static int keys_arr[4][3] =  {{1, 2, 3},
							   {4, 5, 6},
							   {7, 8, 9},
							   {0, 0, 0}};


void Keypad_init(void){

	GPIO_EnableClock(0);

	//Set pins 1,2,3 in keypad to be pins 0,1,2 in port 'A'
	for (int i = 0; i < 3; i++) {
		GPIO_Init(0, i, OUTPUT, PUSH_PULL);
	}

	//Set pins A,B,C,D in keypad to be pins 3,4,5,6 in port 'A'
	for (int i = 3; i < 7; i++) {
		GPIO_Init(0, i, INPUT, PULL_UP);
	}
}


void Keypad_manage(void){

	if (state == RELEASED){

		//Iterate over each column in the keypad to capture the first pressed key
		for(int j=0; j < 3; j++){

			//Set the current column to 0 capture the first pressed key.
			GPIO_WritePin(0, j, 0);

			//Iterate over each row in the keypad to capture the first pressed key
			for(int i=0; i < 4; i++){

				if(GPIO_ReadPin(0, i+3) == 0){
					/*
					Set the state to be PRESSED and get first pressed key,
					to prevent any other keys from interrupting the function,
					before executing KeypadCallouts_KeyPressNotificaton() function.
					*/
					pressed_key = keys_arr[i][j];
					state = PRESSED;
					GPIO_WritePin(0, j, 1);
					KeypadCallouts_KeyPressNotificaton();
				}
			}

			//Set the current column back to 1 before setting the next column to 0
			GPIO_WritePin(0, j, 1);
		}
	}

}


int Keypad_GetKey(void){

	if (state == PRESSED){

		state = RELEASED;
		return pressed_key;
	}

	else
		return -1;
}
