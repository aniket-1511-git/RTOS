/* Macro defined for LED */
#define  LED_1 23
// Varriable for Mutex handler
static SemaphoreHandle_t mutexHandler;
/*
* Function Name : void ledBlink(void *para)
* Description   : this Function prints it on the serial monitor, and then continuously blinks *                  an LED
*/
void ledBlink(void *para)
{
  // Take the mutex 
  xSemaphoreTake(mutexHandler,portMAX_DELAY);
  uint32_t val = *(int *) para;
  // Release the mutex
  xSemaphoreGive(mutexHandler);
  // Print the received value to the serial monitor
  Serial.print("Data Received : ");
  Serial.println(val);
  while(1)
  {
    // Turn on LED 
    digitalWrite(LED_1, HIGH);
   // Wait for 500 milliseconds
    vTaskDelay(500 / portTICK_PERIOD_MS);
    // Turn off LED 
    digitalWrite(LED_1, LOW);
    // Wait for 500 milliseconds
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() 
{
  
  uint32_t delayVal;
  Serial.begin(9600);
  Serial.println("****************** RTOS Mutex ******************");
  // Set the LED pin as an output
  pinMode(LED_1, OUTPUT);
  Serial.println("Enter Value for Delay(MS)");
  // Wait until the user enters a value on Serial Monitor
  while(Serial.available()<= 0);
  // Read the integer input from the serial buffer
  delayVal = Serial.parseInt();
  Serial.print("Data Sent : ");
  Serial.println(delayVal);
  // Create a mutex  
  mutexHandler = xSemaphoreCreateMutex();
  // Function call to run task 1 in core zero
  xTaskCreatePinnedToCore(ledBlink,"Blink Led",1024,(void*)&delayVal,1,NULL,0);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  // Lock the mutex
  xSemaphoreTake(mutexHandler,portMAX_DELAY);
  Serial.println("Success..!");
}

void loop() {
}
