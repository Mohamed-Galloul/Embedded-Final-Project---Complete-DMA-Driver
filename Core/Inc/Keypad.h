/*
 * Author : Mohamed Galloul
 * Date   : 9/12/2021
 * Version: 1.0.0
 */

#ifndef KEYPAD_H
#define KEYPAD_H


#define PRESSED ((char)0x00)
#define RELEASED ((char)0x01)

void Keypad_init(void);
void Keypad_manage(void);
int Keypad_GetKey(void);



#endif /* KEYPAD_H */
