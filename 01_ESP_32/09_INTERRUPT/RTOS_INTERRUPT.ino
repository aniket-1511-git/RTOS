#include "esp_timer.h"

// LED Pins 
static const int ledPin = 2;
// Timer Handler 
esp_timer_handle_t timer = NULL;


// Interrupt Service Routines 
/*
* Function Name : void IRAM_ATTR onTimer(void* arg)
* Description   : This Function executes when timer reaches max
*/
void IRAM_ATTR onTimer(void* arg)
{
  // Read the current state of the LED pin
  int pinStatus = digitalRead(ledPin);
  // Toggle the LED pin
  digitalWrite(ledPin,!pinStatus);
}
void setup()
{
  // LED pin Configuration
  pinMode(ledPin,OUTPUT);
   // Define the timer configuration structure
  esp_timer_create_args_t timer_args= {
    .callback =  &onTimer,            // Function to cal
    .arg = NULL,                      // Argument to pass to the callback
    .dispatch_method = ESP_TIMER_TASK,// Run the callback in the timer
    .name = "Blink LED"               // Name of the timer
  };
  // Create the timer 
  esp_timer_create(&timer_args,&timer);
  // Start the timer to call the callback every 1 second
  esp_timer_start_periodic(timer,1000000);
}
void loop()
{
  
}