#include "header.h"
/*
* Function Name : void lcdScroll(void *s)
* Description   :  this function to scroll data on LCD
*/
void lcdScroll(void *s)
{
		// Set cursor at 1st line
    lcd_cmd(0x80);
	 // Print string on LCD
    lcd_str(" WELCOME");
    while(1) {
				// Command to Shift data to right
        lcd_cmd(0x1C);
				// Small delay
        vTaskDelay(1);
    }
}

/*
* Function Name : void taskLEDBlink(void *s)
* Description   :  This functio  Blinks LEDs
*/
void taskLEDBlink(void *s)
{
    while(1) {
				// LEDs ON
        IO0SET=0xff00;
				// Small delay
        vTaskDelay(1);
				// LEDs OFF
        IO0CLR=0xff00;
				// Small delay
        vTaskDelay(1);
    }
}

