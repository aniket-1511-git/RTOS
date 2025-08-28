#include <LPC214X.H>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


/* defined macro set or clear bit  */
#define bit(x) (1<<x)

/* defined macro register select pin of LCD*/
#define RS (1<<17)
/* defined macro for read write pin of LCD */
#define RW (1<<18)
/* defined macro for enable pin of LCD */
#define EN (1<<19) 

void lcdScroll(void *s); // Function to perform LCD scrolling
void taskLEDBlink(void *s); // Function to perform lED blinking

void lcd_init(void);            // Function to // Initialize LCD
void lcd_cmd(unsigned char );// Function to send command to LCD
void lcd_data(unsigned char );// Function to send data on LCD
void lcd_str(char *);// Function to send string on LCD
void ms_delay(int ms); // Function to delay



