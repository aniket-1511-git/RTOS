#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits "Task A running" over UART 
*/

void taskA(void *parameter)
{
    while(1)
    {
			// mutex lock
			xSemaphoreTake(mutexHandler,portMAX_DELAY);
			// Send message
			uart_stringTransmit("Task A Running \r\n");	
			// mutex release
			xSemaphoreGive( mutexHandler );
			// Delay 
			vTaskDelay(5);
    }
}

/*
* Function Name : void taskB(void *parameter)
* Description   : Periodically transmits "Task B running" over UART 
*/

void taskB(void *parameter)
{
  while(1)
    {
			// mutex lock
			xSemaphoreTake(mutexHandler,portMAX_DELAY);
			// Send message
			uart_stringTransmit("Task B Running \r\n");
			// mutex release
			xSemaphoreGive( mutexHandler );	
		// Delay 			
			vTaskDelay(5);
    }
}


