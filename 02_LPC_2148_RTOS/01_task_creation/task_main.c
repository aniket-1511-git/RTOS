#include "header.h"
/*
* Function Name : int main(void)
* Description   : This Function initializes UART, creates two FreeRTOS tasks
*/
int main(void)
{
	// Initialize UART
	uart_init(9600);
	// Create Task A
	xTaskCreate(
							taskA,              // Function Name 
							"Task A",           // Task name
							128,                // Stack size (in words)
							NULL,               // Parameter
							1,                  // Priority
							NULL                // Task handle (not needed here)
		);
	// Create Task B
		xTaskCreate(
							taskB,              // Function Name 
							"Task B",           // Task name
							128,                // Stack size (in words)
							NULL,               // Parameter
							0,                  // Priority
							NULL                // Task handle (not needed here)
		);
	// Start the FreeRTOS scheduler
	vTaskStartScheduler();
}







