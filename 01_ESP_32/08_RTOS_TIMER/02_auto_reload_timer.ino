// Timer handler
static TimerHandle_t autoReloadTimer = NULL;
/*
* Function Name : void timerCallback(TimerHandle_t xTimer)
* Description   : This function is call back function of after timer completion 
*/
void timerCallback(TimerHandle_t xTimer)
{
  // print message if timer expired
  if((uint32_t)pvTimerGetTimerID(xTimer) == 1)
  {
    Serial.println("auto Reload Timer Expired");
  }
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("============= RTOS TIMER =============");
  // Create auto Reload Timer 
  autoReloadTimer = xTimerCreate(
                            "auto Reload Timer ",// Name of timer
                              1000 / portTICK_PERIOD_MS, // Period of timer 
                              pdTRUE,                   // Auto reload
                              (void*)1,                  // Timer ID
                              timerCallback);            // Call back function
  if(NULL == autoReloadTimer)
  {
    Serial.println("Could Not create one of the timers");
  }
  else
  {
    // Wait and print the messase 
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("================== Starting Timer ==================");
    // Start timer 
    xTimerStart(autoReloadTimer,portMAX_DELAY);
  }
   
}

void loop() {
  // put your main code here, to run repeatedly:

}
