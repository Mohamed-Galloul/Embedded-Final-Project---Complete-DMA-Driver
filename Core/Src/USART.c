/*
 * USART.c
 *
 *  Created on: Jan 1, 2022
 *      Author: galloul
 */

#include "USART.h"


#define USART_REG(BASE_ADDRESS,REG_OFFSET) (*((unsigned int *)(BASE_ADDRESS+REG_OFFSET)))

#define RCC ((unsigned int)0x40023800)
#define RCC_APB1ENR USART_REG(RCC, 0x40)
//
#define USART2 ((unsigned int)0x40004400)

#define USART2_SR USART_REG(USART2, 0x00)
#define USART2_DR USART_REG(USART2, 0x04)
#define USART2_BRR USART_REG(USART2, 0x08)
#define USART2_CR1 USART_REG(USART2, 0x0C)
#define USART2_CR2 USART_REG(USART2, 0x10)
#define USART2_CR3 USART_REG(USART2, 0x14)
#define USART2_GTPR USART_REG(USART2, 0x18)


void USART2_EnableClock(void)
{
	RCC_APB1ENR |= (0x01 << 0x11); //enable pin17 --> enable USART2
}

void USART_Enable(void)
{
	USART2_CR1 |= (0x01 << 0x0D); //to enable USART
	USART2_CR1 &= ~(0x01 << 0x0C); //for wordlength of 8 bits
	USART2_CR1 |= (0x01 << 0x03); //to enable transmitting
	USART2_BRR |= 0x0682; //for baud rate of 9600
	USART2_CR2 &= ~(0x03 << 0x0C); //for 1 stop bits

}

void Write_USART_DR(unsigned char data)
{
	USART2_DR &= ~(0xFF);
	USART2_DR |= (data);
}

unsigned char Read_USART_DR(void)
{
	unsigned char data = USART2_DR & 0xFF;
	return data;
}

unsigned char Read_TC_Bit(void)
{
	unsigned char TC = (USART2_SR & (0x01 << 0x06)) >> 0x06;
	return TC;
}

void Clear_TC_Bit(void)
{
	USART2_SR &= ~(0x01 << 0x06);
}


