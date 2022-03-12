/*
 * DMA.h
 *
 *  Created on: Jan 7, 2022
 *      Author: galloul
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_

// Transfer types (single or burst)
#define SINGLE ((unsigned char)0x00)
#define BURST_4 ((unsigned char)0x01)
#define BURST_8 ((unsigned char)0x02)
#define BURST_16 ((unsigned char)0x03)

// Transfer size
#define BYTE ((unsigned char)0x00)
#define HALF_WORD ((unsigned char)0x01)
#define WORD ((unsigned char)0x02)

// Transfer mode (where P=Peripheral and M=Memory)
#define P2M ((unsigned char)0x00)
#define M2P ((unsigned char)0x01)
#define M2M ((unsigned char)0x02)


void DMA2_Enable_Clock(void);
void DMA2_Config(unsigned char CHSEL, unsigned int* SRC_ADR, unsigned int* DST_ADR, unsigned short int N_TFR,
				unsigned char TFR_SIZE, unsigned char TFR_MODE, unsigned char TFR_TYPE);
void DMA2_Start_TFR(void);
unsigned char Check_TC_Flag(void);
void Clear_TC_Flag(void);


#endif /* INC_DMA_H_ */
