#include "header.h"

/*
* Function name      : void uart_init(uint16_t brate_u16)
* Description        : this function Initializes UART0 with specified baud rate, data length, and 
*                      TXD0/RXD0 pin configuration       
*/
void uart_init(uint16_t brate_u16)
{
	// Variables to store calculated PCLK freq and UART divisor latch value
	uint32_t pclk,dlab_val;
	// Array storing possible Peripheral Clock (PCLK) values in MHz
	int32_t vpbdiv[]={15,60,30,15};
	// Calculate Peripheral Clock in Hz based on VPBDIV setting
	pclk = vpbdiv[VPBDIV]*1000000-1;
	// Calculate UART Divisor Latch value using formula: PCLK / (16 × baud rate)
	dlab_val = pclk/(brate_u16*16);
	// Configure TXD0 and RXD0 for UART0 function
	PINSEL0 = 0x05;
	// enble u0lcr register for baud rate setting and assigned word length
	U0LCR = 0x83;
	// store lowwe 8 bits of baud rate in u0dll register
	U0DLL = (dlab_val &0xFF);
	// store upper 8 bits of baud rate in u0dlm registerregister
	U0DLM = ((dlab_val>>8) &0xFF);
	// enable UART0 for normal operation
	U0LCR = 0x03;
}
/*
* Function name      : void uart_charTransmit(uint8_t data_u8)
* Description        : this function designed to Transmits a single character via UART0 
*/
void uart_charTransmit(uint8_t data_u8)
{
	// store data into u0thr register
	U0THR = data_u8;
	// Wait until the THRE flag is set
	while(0 == THRE_U8 );
}

/* 
* Function name      : uint8_t uart_charReceive(void)
* Description        : this function designed to Receive a single character via UART0                            
*/
uint8_t uart_charReceive(void)
{
	// Wait until the RDR flag is set
	while(0 == RDR_U8 );
	// returing the received data in u0rbr register
	return U0RBR;
}
/* 
* Function name      : void uart_stringReceive(uint8_t *stringData_u8,uint8_t stringLen_u8)
* Description        : this function designed to Receive a string via UART0                    
*/
void uart_stringReceive(uint8_t *stringData_u8,uint8_t stringLen_u8)
{
	// Variables to store index of last received char 
	uint8_t i;
	// loop to iterate untill getting enter key or max string len
	for(i=0;i<stringLen_u8;i++)
	{
		// Wait until the RDR flag is set
		while(0 == RDR_U8 );
		// store the received data in string 
		stringData_u8[i] = U0RBR;
		// checking last receive char is enter key 
		if('\r' == stringData_u8[i])
		{
			// store the null char in string 
			stringData_u8[i] = '\0';
			// breaking loop
			break;
		}
	}
}
/* 
* Function name      : void uart_stringTransmit(uint8_t *stringData_u8)
* Description        : this function designed to transmit a string via UART0 
*/                  
void uart_stringTransmit(uint8_t *stringData_u8)
{
	// loop iterate untill null char
	while(*stringData_u8)
	{
		// store data into u0thr register
		U0THR = *stringData_u8;
		// Wait until the THRE flag is set
	  while(0 == THRE_U8 );
		// incrementing pointer 
		stringData_u8++;
	}
}





