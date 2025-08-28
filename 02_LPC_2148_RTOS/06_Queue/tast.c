#include "header.h"
/*
* Function Name : void taskA(void *parameter)
* Description   : Periodically transmits data in queue
*/

void taskA(void *parameter)
{
		// data to send into the queue
		char sendData[26]="Welcome to Queue tutorial",i;
		// Send message
		uart_stringTransmit("\r\nTask A Writing data in Queue \r\n");
		// Variable to store queue send status
		portBASE_TYPE queSendStatus;
    while(1)
    {
				
			for(i=0;i<26;i++)
			{
				// Send each character to the queue
				queSendStatus = xQueueSendToBack(queue,&sendData[i],0);
			}
			// Check if the data was sent
			if(pdPASS != queSendStatus)
			{
				// Send message
				uart_stringTransmit("\r\nTask A Sent data \r\n");
				// Delay 
				vTaskDelay(10);
				// Send message
				uart_stringTransmit("\r\nTask B Received Data\r\n");
				vTaskDelay(10);
			}
			
    }
}

/*
* Function Name : void taskB(void *parameter)
* Description   : Periodically read the data form queue transmit over UART 
*/

void taskB(void *parameter)
{
	// Variable to store one character received
	char receivedData;
	// Variable to store queue receive status
	portBASE_TYPE queRecStatus;

  while(1)
    {
			// Read the data form queue
			queRecStatus = xQueueReceive(queue,&receivedData,100);	
			// Check if data was successfully received
			if(queRecStatus == pdPASS)
			{
				// Transmit the received character over UART
				uart_charTransmit(receivedData);
			}
    }
}


