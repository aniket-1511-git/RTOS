#include <LPC214X.H>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
// SemaPhore handler
extern xSemaphoreHandle  countSemaphore;
/* defined macro for transmitter holding register empty  */
#define THRE_U8 ((U0LSR>>5)&1)

/* defined macro for receiver data ready */
#define RDR_U8  (U0LSR&1)
	 

void uart_init(uint16_t );            	     // Function to Initializes uart 0
void uart_charTransmit(uint8_t);             // Fucntion to Transmit char via uart0
uint8_t uart_charReceive(void);              // Fucntion to Receive char via uart0
void uart_stringTransmit(uint8_t *);	     // Fucntion to Transmit string via uart0
void uart_stringReceive(uint8_t *,uint8_t);  // Fucntion to Receive string via uart0
void uartConfig(void);

void taskA(void *parameter); // Function to perform task A
void taskB(void *parameter); // Function to perform task B


