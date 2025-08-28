#include "header.h"
// SemaPhore handler
xSemaphoreHandle  binSemaphore;
/*
* Function Name : int main(void)
* Description   : This Function initializes UART, creates two FreeRTOS tasks
*/
int main(void)
{
	vSemaphoreCreateBinary(binSemaphore);
	// Initialize UART
	uart_init(9600);
	// config uart 0
	uartConfig();
	// Create Task A
	xTaskCreate(
							taskA,              // Function Name 
							"Task A",           // Task name
							128,                // Stack size (in words)
							NULL,               // Parameter
							1,                  // Priority
							NULL                // Task handle (not needed here)
		);
	
//		// Release semaphore
//		xSemaphoreGive(binSemaphore);
	   // Start the FreeRTOS scheduler
		 vTaskStartScheduler();
	  while(1);

}


