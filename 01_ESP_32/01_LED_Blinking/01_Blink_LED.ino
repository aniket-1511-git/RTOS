/* Macro Defined for LED 1 */
#define LED_1 22
/* Macro Defined for LED 2 */
#define LED_2 12


/*
* Function name : void blinkLed1(void* para)
* Description   : This Function Blink the LED_1
*/
void blinkLed1(void* para)
{
  while(1)
  {
    // Function call to On led
    digitalWrite(LED_1, HIGH);
    // Function Call for delay 
    vTaskDelay(500 /portTICK_PERIOD_MS);
    // Function call to Off led
    digitalWrite(LED_1, LOW);
     // Function Call for delay 
    vTaskDelay(500 /portTICK_PERIOD_MS);
    Serial.println("Task One Running in Core Zero ");
  }
}
/*
* Function name : void blinkLed2(void* para)
* Description   : This Function Blink the LED_2
*/
void blinkLed2(void* para)
{
  while(1)
  {
    // Function call to On led
    digitalWrite(LED_2, HIGH);
    // Function Call for delay 
    vTaskDelay(500 /portTICK_PERIOD_MS);
    // Function call to Off led
    digitalWrite(LED_2, LOW);
     // Function Call for delay 
    vTaskDelay(500 /portTICK_PERIOD_MS);
    Serial.println("Task Two Running in Core One ");
  }
}
void setup() {
  Serial.begin(9600);
// Function Call set LED1 State
 pinMode(LED_1, OUTPUT);
// Function Call set LED2 State
 pinMode(LED_2, OUTPUT);
 // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      blinkLed1,     // function to called
      "Blink LED 1", // Task name
      1024,          // stack size in byte
      NULL,          // Parameter to pass function 
      1,             // Task Priority
      NULL,          // Task handler
      0              // core no           
      );
 // Function call to run task 2 in core zero
 xTaskCreatePinnedToCore(
      blinkLed2,     // function to called
      "Blink LED 2", // Task name
      1024,          // stack size in byte
      NULL,          // Parameter to pass function 
      1,             // Task Priority
      NULL,          // Task handler
      1              // core no           
      );
}

void loop() {
  // put your main code here, to run repeatedly:

}
