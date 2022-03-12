/*
 * DMA.c
 *
 *  Created on: Jan 7, 2022
 *      Author: galloul
 */

#include "DMA.h"

#define DMA_REG(BASE_ADDRESS,REG_OFFSET) (*((unsigned int *)(BASE_ADDRESS+REG_OFFSET)))

#define RCC ((unsigned int)0x40023800)
#define RCC_AHB1ENR DMA_REG(RCC, 0x30)

#define DMA2 ((unsigned int)0x40026400)

#define DMA2_LISR DMA_REG(DMA2, 0x00)
#define DMA2_HISR DMA_REG(DMA2, 0x04)
#define DMA2_LIFCR DMA_REG(DMA2, 0x08)
#define DMA2_HIFCR DMA_REG(DMA2, 0x0C)
#define DMA2_S0CR DMA_REG(DMA2, 0x10)
#define DMA2_S0NDTR DMA_REG(DMA2, 0x14)
#define DMA2_S0PAR DMA_REG(DMA2, 0x18)
#define DMA2_S0M0AR DMA_REG(DMA2, 0x1C)
#define DMA2_S0M1AR DMA_REG(DMA2, 0x20)
#define DMA2_S0FCR DMA_REG(DMA2, 0x24)



void DMA2_Enable_Clock(void)
{
	RCC_AHB1ENR |= (0x01 << 22); //Enable clock for DMA2 by setting pin 22 in RCC_AHB1ENR
}

void DMA2_Config(unsigned char CHSEL, unsigned int* SRC_ADR, unsigned int* DST_ADR, unsigned short int N_TFR,
				unsigned char TFR_SIZE, unsigned char TFR_MODE, unsigned char TFR_TYPE)
{

	DMA2_S0CR &= ~(0x07 << 25); // Clear 25-27 pins CHSEL[2:0]
	DMA2_S0CR |= (CHSEL << 25); // Choosing the channel (CHSEL)

	DMA2_S0CR &= ~(0x03 << 23); // Clear 23-24 pins MBURST[1:0] (Memory burst transfer configuration)
	DMA2_S0CR |= (TFR_TYPE << 23); // Choosing memory transfer type

	DMA2_S0CR &= ~(0x03 << 21); // Clear 21-22 pins PBURST[1:0] (Peripheral burst transfer configuration)
	DMA2_S0CR |= (TFR_TYPE << 21); // Choosing peripheral transfer type

	DMA2_S0CR |= (0x03 << 16); //set priority to be very high

	DMA2_S0CR &= ~(0x01 << 15); // Set peripheral increment offset size to be linked with PSIZE

	DMA2_S0CR &= ~(0x03 << 13); // Clear 13-14 pins MSIZE[1:0] (Memory data size)
	DMA2_S0CR |= (TFR_SIZE << 13); // Set Memory data size

	DMA2_S0CR &= ~(0x03 << 11); // Clear 11-12 pins PSIZE[1:0] (Peripheral data size)
	DMA2_S0CR |= (TFR_SIZE << 11); // Set Peripheral data size

	DMA2_S0CR |= (0x01 << 10); // Set Memory address pointer to be incremented after each data transfer
							   // (increment is done according to MSIZE)

	DMA2_S0CR |= (0x01 << 9); // Set Peripheral address pointer to be incremented after each data transfer
							  // (increment is done according to PSIZE)

	DMA2_S0CR &= ~(0x03 << 6); // Clear 6-7 pins DIR[1:0] (Data transfer direction)
	DMA2_S0CR |= (TFR_MODE << 6); // Set Data transfer direction

	DMA2_S0CR |= (0x01 << 4); // Enable Transfer complete interrupt



	DMA2_S0NDTR = 0; // Clear 0-15 pins NDT[15:0] (Number of data items to transfer)
	DMA2_S0NDTR |= (N_TFR); // Set Number of data items to transfer



	DMA2_S0PAR = 0; // Clear 0-31 pins PAR[31:0] (Peripheral address)
	DMA2_S0PAR = SRC_ADR; // Set Source address

	DMA2_S0M0AR = 0; // Clear 0-31 pins M0A[31:0] (Memory 0 address)
	DMA2_S0M0AR = DST_ADR; // Set Destination address



	DMA2_S0FCR |= (0x01 << 2); // Disable direct mode (already disabled by HW in case of M2M mode)

	DMA2_S0FCR &= ~(0x03); // Clear 0-1 pins FTH[1:0] FIFO threshold selection
	DMA2_S0FCR |= (0x01); // Set FIFO threshold selection to be 1/2 full FIFO

}

void DMA2_Start_TFR(void)
{
	DMA2_LIFCR = 0xFFFFFFFF; // Clear event flags in LIFCR and HIFCR
	DMA2_HIFCR = 0xFFFFFFFF;

	DMA2_S0CR |= 0x01; // Enable Stream0 on DMA2

}

unsigned char Check_TC_Flag(void)
{
	unsigned char state;
	state = (DMA2_LISR & (0x01 << 5)) >> 5; // Get the state of the transfer complete interrupt flag of stream0
	return state;
}

void Clear_TC_Flag(void)
{
	DMA2_LIFCR |= (0x01 << 5); // Clear transfer complete interrupt flag of stream0
}
