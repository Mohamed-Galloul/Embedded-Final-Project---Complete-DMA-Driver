/*
 * interrupt.h
 *
 *  Created on: Dec 24, 2021
 *      Author: galloul
 */

#ifndef INC_INTERRUPT_H_
#define INC_INTERRUPT_H_


#define RISING ((unsigned char)1)
#define FALLING ((unsigned char)0)

void SYSCFG_EnableClock(void);
void EXTI_Enable(unsigned char PIN_NUM);
void EXTI_Unmask(unsigned char PIN_NUM);
void EXTI_Trigger_Selection(unsigned char SELECTION_TYPE, unsigned char PIN_NUM);
void NVIC_Enable(unsigned char REG_ID, unsigned char LINE);
void EXTI_Clear(unsigned char PIN_NUM);



#endif /* INC_INTERRUPT_H_ */
