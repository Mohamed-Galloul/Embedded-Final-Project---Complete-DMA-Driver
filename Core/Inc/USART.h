/*
 * USART.h
 *
 *  Created on: Jan 1, 2022
 *      Author: galloul
 */

#ifndef INC_USART_H_
#define INC_USART_H_

void USART2_EnableClock(void);
void USART_Enable(void);
void Write_USART_DR(unsigned char data);
unsigned char Read_USART_DR(void);
unsigned char Read_TC_Bit(void);
void Clear_TC_Bit(void);


#endif /* INC_USART_H_ */
