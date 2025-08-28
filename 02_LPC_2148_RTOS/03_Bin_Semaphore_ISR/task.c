#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits "Task A running" over UART every 1 second.
*/

void taskA(void *parameter)
{
    while(1)
    {
			// Take semaphore
			if((xSemaphoreTake(binSemaphore,portMAX_DELAY))== pdTRUE)
			{
				// Send message
        uart_stringTransmit("Task A Take semaphore\r\n");	
			}
    }
}

