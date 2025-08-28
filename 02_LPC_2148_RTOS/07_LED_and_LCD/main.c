#include "header.h"
/*
* Function Name : int main(void)
* Description   : This Function init PORT0 and PORT 1 LCD and create task for LED Blink and LCD Scroll
*/
int main(void)
{
		// Configure all pins of PORT0 and PORT1 as output
    IO0DIR = IO1DIR = 0xFFFFFFFF;   
    // Initialize LCD 
    lcd_init();                     
    // Create FreeRTOS Task 1 
    xTaskCreate(
        lcdScroll,                  // Task function
        "lcd scroll",               // Task name 
        1000,                       // Stack size
        NULL,                       // Task input parameter 
        1,                          // Priority
        NULL                        // Task handle
    );
    
    // Create FreeRTOS Task 2 
    xTaskCreate(
        taskLEDBlink,               // Task function
        "led blink",                // Task name
        1000,                       // Stack size 
        NULL,                       // Task input parameter 
        1,                          // Priority 
        NULL                        // Handle 
    );
    // Start FreeRTOS scheduler 
    vTaskStartScheduler();          

}





