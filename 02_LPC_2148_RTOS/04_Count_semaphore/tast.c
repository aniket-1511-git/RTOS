#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits "Task A running" over UART every 1 second.
*/

void taskA(void *parameter)
{
    while(1)
    {
				if(NULL != countSemaphore)
			{
				// Take semaphore
				if((xSemaphoreTake(countSemaphore,portMAX_DELAY))== pdTRUE)
				{
					// Send message
					uart_stringTransmit("Task A Take semaphore\r\n");	
				}
			}
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
			if(NULL != countSemaphore)
			{
				// Take semaphore
				if((xSemaphoreTake(countSemaphore,portMAX_DELAY))== pdTRUE)
				{
					// Send message
					uart_stringTransmit("Task B Take semaphore\r\n");	
				}
			}
			
    }
}


