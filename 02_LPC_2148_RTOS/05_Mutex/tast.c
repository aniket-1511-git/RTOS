#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits "Task A running" over UART every 1 second.
*/

void taskA(void *parameter)
{
    while(1)
    {
			xSemaphoreTake(mutexHandler,portMAX_DELAY);
			// Send message
			uart_stringTransmit("Task A Running \r\n");	
			xSemaphoreGive( mutexHandler );
			vTaskDelay(5);
    }
}

/*
* Function Name : void taskB(void *parameter)
* Description   : Periodically transmits "Task B running" over UART every 1 second.
*/

void taskB(void *parameter)
{
  while(1)
    {
			xSemaphoreTake(mutexHandler,portMAX_DELAY);
			// Send message
			uart_stringTransmit("Task B Running \r\n");
			xSemaphoreGive( mutexHandler );			
			vTaskDelay(5);
    }
}


