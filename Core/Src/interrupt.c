/*
 * interrupt.c
 *
 *  Created on: Dec 24, 2021
 *      Author: galloul
 */

#include "interrupt.h"

#define EXTI_REG(BASE_ADDRESS,REG_OFFSET) (*((unsigned int *)(BASE_ADDRESS+REG_OFFSET)))

#define RCC ((unsigned int)0x40023800)
#define RCC_APB2ENR EXTI_REG(RCC, 0x44)

#define SYSCFG ((unsigned int)0x40013800)
#define SYSCFG_EXTICR1 EXTI_REG(SYSCFG, 0x08)

#define EXTI ((unsigned int)0x40013C00)
#define EXTI_IMR EXTI_REG(EXTI, 0x00)
#define EXTI_RTSR EXTI_REG(EXTI, 0x08)
#define EXTI_FTSR EXTI_REG(EXTI, 0x0C)
#define EXTI_PR EXTI_REG(EXTI, 0x14)

#define NVIC ((unsigned int)0xE000E100)
//#define NVIC_ISER0 EXTI_REG(NVIC, 0x00)
#define NVIC_ICER0 EXTI_REG(NVIC, 0x180)
//#define NVIC_ISER1 EXTI_REG(NVIC, 0x04)


#define NVIC_ISER(ID) EXTI_REG(NVIC, ISER_Offset[ID])
unsigned int ISER_Offset[2]={0x00 , 0x04};



void SYSCFG_EnableClock(void)
{
	RCC_APB2ENR |= (0x01 << 0xE);
}

void EXTI_Enable(unsigned char PIN_NUM)
{
	SYSCFG_EXTICR1 &= ~(0x1 << (4 * PIN_NUM));
}

void EXTI_Unmask(unsigned char PIN_NUM)
{
	EXTI_IMR |= (0x1 << (PIN_NUM));
}

void EXTI_Trigger_Selection(unsigned char SELECTION_TYPE, unsigned char PIN_NUM)
{
	if (SELECTION_TYPE == RISING)
	{
		EXTI_RTSR |= (0x1 << (PIN_NUM));
	}
	else if (SELECTION_TYPE == FALLING)
	{
		EXTI_FTSR |= (0x1 << (PIN_NUM));
	}
}

void NVIC_Enable(unsigned char REG_ID, unsigned char LINE)
{

	NVIC_ISER(REG_ID) |= (0x1 << (LINE));
}

void EXTI_Clear(unsigned char PIN_NUM)
{
	EXTI_PR |= (0x1 << (PIN_NUM));
}
