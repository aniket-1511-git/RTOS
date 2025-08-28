#include "header.h"
/*
* Function Name : void uartReceiveInterrupt(void)
* Description   : ISR function to execute after the uart interrupt come 
*/
void uartReceiveInterrupt(void)__irq
{
  unsigned char r;
	// Flag to indicate if a higher priority task
  static portBASE_TYPE interrupttask;
	// Initialize the flag 
  interrupttask=pdFALSE;
  // Check if UART0 Receive Data Available
  if(U0IIR&0x04) {
		// Read received data
    r=U0RBR;
		// Send message over UART
    uart_stringTransmit("Received Data : ");
		
    U0THR=r;
		// Wait until Transmit Holding Register
		while(!(U0LSR&0x20));	
    uart_stringTransmit("\r\nGoing to give semaphore\r\n");
		// Give semaphore from ISR to unblock
    xSemaphoreGiveFromISR(countSemaphore,&interrupttask);	
    uart_stringTransmit("Semaphore has given\r\n");
  }
	// Clear interrupt in VIC
  VICVectAddr = 0x00;
}
/*
* Function Name : void uartConfig(void)
* Description   : configure the uart interrupt
*/
void uartConfig(void)
{
	// Enable UART0 transmitter
	U0TER=(1<<7);
	//enables uart receive identification interrupt
	U0IER=0x01;  
	//selecting as irq
  VICIntSelect=0x0000;     
	//enable uart0
  VICIntEnable|=0x0040;   
	//assigning address
  VICVectAddr2=(unsigned long int)uartReceiveInterrupt;  
	//need to assign slot no of interrupt source which has been activate
  VICVectCntl2|=0x26;  
	
}

