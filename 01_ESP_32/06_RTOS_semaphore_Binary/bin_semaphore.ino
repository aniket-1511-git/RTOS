// Binary semaphore Handler
static SemaphoreHandle_t binSema;
/*
* Function Name : void readBinSemaphore(void *parameter)
* Description   :This Function releases a binary semaphore, prints the received parameter value
*/
void readBinSemaphore(void *parameter)
{
  uint32_t val = *(int *) parameter;
  // Release the binary semaphore
  xSemaphoreGive(binSema);
  // Print the received value to the serial monitor
  Serial.print("Data Received : ");
  Serial.println(val);
  while(10);
}

void setup() {

  uint32_t delayVal;
  Serial.begin(9600);
  Serial.println("*************** RTOS Semaphore ***************");
  // Create binary Semaphore
  binSema =  xSemaphoreCreateBinary();
  Serial.println("Enter Value for Delay(MS)");
  // Wait until the user enters a value on Serial Monitor
  while(Serial.available()<= 0);
  // Read the integer input from the serial buffer
  delayVal = Serial.parseInt();
  Serial.print("Data Sent : ");
  Serial.println(delayVal);
  // Function call to run task 1 in core zero
  xTaskCreatePinnedToCore(readBinSemaphore,"read semaphore",1024,(void*)&delayVal,1,NULL,0);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  // wait till binary semaphore return
  xSemaphoreTake(binSema,portMAX_DELAY);
}

void loop() {
 
}
