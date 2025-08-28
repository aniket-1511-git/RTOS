#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : This function waits to take a counting semaphore and, sends data on UART
*/

void taskA(void *parameter)
{
    while(1)
    {
				// check if count semaphore is null or not
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
* Description   : This function waits to take a counting semaphore and, sends data on UART
*/

void taskB(void *parameter)
{
    while(1)
    {
			// check if count semaphore is null or not
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


