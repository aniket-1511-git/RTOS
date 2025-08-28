#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits "Task A running" over UART every 1 second.
*/
void taskA(void *parameter)
{
    while(1)
    {
				// Send message
        uart_stringTransmit("Task A running\r\n");
				// Delay for 10 ticks			
        vTaskDelay(1);                           
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
				// Send message
        uart_stringTransmit("Task B running\r\n"); 
				// Delay for 1000 ticks
        vTaskDelay(1);                           
    }
}
