// Macro defined for LED
#define LED_Pin 2
// Timer handler
static TimerHandle_t oneShotTimer = NULL;
/*
* Function Name : void timerCallback(TimerHandle_t xTimer)
* Description   : This function is call back function of after timer completion 
*/
void timerCallback(TimerHandle_t xTimer)
{
  digitalWrite(LED_Pin,LOW);
  Serial.println("LED OFF");
   Serial.println("One shot Timer Expired");
}
/*
* Function Name : void timerCallback(TimerHandle_t xTimer)
* Description   : This function is call back function of after timer completion 
*/
void blinkBackLight(void *para)
{
  char c ;
  while(1)
  {
    if(Serial.available()>0)
    {
      Serial.println("================== Enter Data ==================");
      c = Serial.read();
      Serial.println(c);
      digitalWrite(LED_Pin,HIGH);
      Serial.println("LED ON ");
      Serial.println("================== Starting Timer ==================");
      // Start timer 
      xTimerStart(oneShotTimer,portMAX_DELAY);
    }
  }
}
void setup() {
  
  pinMode(LED_Pin,OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("============= RTOS TIMER =============");
  // Create one shot Timer 
  oneShotTimer = xTimerCreate("one shot Timer ",// Name of timer
                              1000 / portTICK_PERIOD_MS, // Period of timer 
                              pdFALSE,                   // Auto reload
                              (void*)0,                  // Timer ID
                              timerCallback);            // Call back function

  xTaskCreatePinnedToCore(blinkBackLight,"Blink back light", 1024,NULL, 1,NULL,0);
  vTaskDelete(NULL); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
