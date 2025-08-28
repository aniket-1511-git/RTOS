#include "header.h"
/*
* Function Name : void ms_delay(int ms)
* Description   : This Function generate delay in milisec 
*                 
*/
void lcd_delay()
{
    unsigned int i;
    for(i=0;i<=2000;i++);
}
/*
* Function Name : void lcd_data(unsigned char data)
* Description   : This Function used to pass data on lcd display 
*                 
*/
void lcd_data(unsigned char data)
{
		 // Clear data lines
    IO1CLR=0xFF070000;
		// Send 8-bit data
    IO1SET=(data<<24);
		// Set RS pin
    IO1SET=bit(16); 
		// Clear RW pin
    IO1CLR=bit(17); 
		// Set EN pin
    IO1SET=bit(18);
		// Small delay
    lcd_delay();
		// Clear EN pin
    IO1CLR=bit(18);             
}
/*
* Function Name : void lcd_cmd(unsigned char data)
* Description   : This Function used to pass command on lcd display 
*                 
*/
void lcd_cmd(unsigned char cmd)
{
		// Clear data lines
    IO1CLR=0xFF070000;
		// Place 8-bit command
    IO1SET=(cmd<<24);
		// Clear RS pin
    IO1CLR=bit(16); 
		// Clear RW pin
    IO1CLR=bit(17);
		// Set EN pin
    IO1SET=bit(18);
		// Small delay
    lcd_delay();
		// Clear EN pin
    IO1CLR=bit(18);              
}
/*
* Function Name : void lcd_init(void)
* Description   : This Function used to Initialize lcd
*                 
*/
void lcd_init()
{
		// Set 8 bit mode
    lcd_cmd(0x38);
		// Display ON, Cursor ON
    lcd_cmd(0x0e);
		 // Clear Display
    lcd_cmd(0x01);
		// Entry Mode Set
    lcd_cmd(0x06);
		// Display ON, Cursor OFF
    lcd_cmd(0x0c);
		// set Cursor to beginning of first line
    lcd_cmd(0x80);
}
/*
* Function Name : void lcd_str(char *p)
* Description   : This Function used to send string on lcd
*                 
*/
void lcd_str( char *s)
{
		// Loop until null character '\0' 
    while(*s) {
				// Send current character to LCD, then move pointer to next character
        lcd_data(*s++);
    }
}
