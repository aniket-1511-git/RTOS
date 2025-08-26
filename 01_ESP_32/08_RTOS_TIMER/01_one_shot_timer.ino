// Timer handler
static TimerHandle_t oneShotTimer = NULL;
/*
* Function Name : void timerCallback(TimerHandle_t xTimer)
* Description   : This function is call back function of after timer completion 
*/
void timerCallback(TimerHandle_t xTimer)
{
  Serial.println("One shot Timer Expired");
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("============= RTOS TIMER =============");
  // Create one shot timer 
  oneShotTimer = xTimerCreate(
                            "One Shot Timer",// Name of timer
                              2000 / portTICK_PERIOD_MS, // Period of timer 
                              pdFALSE,                   // Auto reload
                              (void*)0,                  // Timer ID
                              timerCallback);            // Call back function
  if(NULL == oneShotTimer)
  {
    Serial.println("Could Not create one of the timers");
  }
  else
  {
    // Wait and print the messase 
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("================== Starting Timer ==================");
    // Start timer 
    xTimerStart(oneShotTimer,portMAX_DELAY);
  }
   
}

void loop() {
  // put your main code here, to run repeatedly:

}
