/*
 * Author : Mohamed Galloul
 * Date   : 1/1/2022
 * Version: 1.0.0
 */
#include "GPIO.h"
#include "interrupt.h"
#include "USART.h"
#include "DMA.h"

void DMA2_Stream0_IRQHandler(void);
void Print_Message(void);
void delay_ms(int ms);


unsigned int SRC_array [100] = {};
unsigned int DST_array [100] = {};

unsigned char Message[] = "Memory to Memory transfer is done!";


int main(void) {

		// Enable clock for Port A
		GPIO_EnableClock(0);

		// Set PA0  to be OUTPUT with PUSH_PULL mode, and connected to the testing LED
		GPIO_Init(0, 0, OUTPUT, PUSH_PULL);

		// Set PA2  to be ALTERNATIVE_FUN (USART2) with PUSH_PULL mode, connected to the RXD pin in the virtual terminal
		GPIO_Init(0, 2, ALTERNATE_FUN, PUSH_PULL);
		// Enable USART2 clock
		USART2_EnableClock();


		// Initialize both SRC and DST arrays
		for (int i = 0; i < 100; ++i)
		{
			SRC_array[i] = 100 * (i+1);
			DST_array[i] = 0;
		}

		// Enable clock for DMA2
		DMA2_Enable_Clock();

		/* Configure DMA2 by sending the address of both the SRC and DST arrays, size of both arrays,
		 * Transfer Size as word (32 bits), Transfer Mode as memory to memory,
		 * and Transfer Type as single.
		 */
		DMA2_Config(0, SRC_array, DST_array, 100, WORD, M2M, SINGLE);

		// Start transfer
		DMA2_Start_TFR();


		// Enable DMA2_Stream0 Interrupt in register NVIC_ISER1 pin 24
		NVIC_Enable(1, 24);

  while (1) {

  }

  return 0;
}


void DMA2_Stream0_IRQHandler(void)
{

	unsigned char state = Check_TC_Flag();
	if (state) {
		GPIO_WritePin(0, 0, DST_array[99]); // Make sure that the value on the last element of DST_array is not 0 anymore, by Setting the LED
		Print_Message(); // Print the Success Message
		Clear_TC_Flag(); // clear the transfer complete bit for stream0
	}

}


void Print_Message(void)
{
	/* Enable USART2, as a transmitter that transmits data of 8 bit length,
	 * at a baud rate of 9600 and 1 stop bit
	 * (which is the same baud rate and number of stop bits for the virtual terminal on Proteus)
	 */
	USART_Enable();

	unsigned int Message_Size = sizeof(Message)/sizeof(Message[0]);

	// Iterate over each Character on the array and print it on the terminal
	for (int i = 0; i < Message_Size-1; i++)
	{

		Write_USART_DR(Message[i]); // print the current character
		while(Read_TC_Bit() == 0){} // wait until current character is sent by polling on the TC flag
		Clear_TC_Bit(); // Clear the TC flag to send the next character
		delay_ms(1); // wait for 1ms before sending again
	}
}


void delay_ms(int ms) {
  unsigned int i;
  for (i = 0; i < ms *1000; i++) {
  }
}

