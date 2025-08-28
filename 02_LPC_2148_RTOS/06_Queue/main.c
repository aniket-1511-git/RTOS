#include "header.h"
// Queue handler
xQueueHandle queue;
/*
* Function Name : int main(void)
* Description   : This Function initializes UART, creates two FreeRTOS tasks
*/
int main(void)
{
	// creating Quue
	  queue = xQueueCreate(26,sizeof(char));

	// Initialize UART
	uart_init(9600);
	if(NULL != queue)
	{
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
									1,                  // Priority
									NULL                // Task handle (not needed here)
				);
		// Start the FreeRTOS scheduler
		vTaskStartScheduler();
	}
	  
	  while(1);

}


