// Delay time for Task A in milliseconds
static const uint32_t task_0_delay = 500;

// Handle for binary semaphore
static SemaphoreHandle_t binSem;

/*
 * Function Name : void taskA(void *parameters)
 * Description   : Periodically gives the semaphore every 500 ms.
 *                 
 */
void taskA(void *parameters) {
  while (1) {
    // Release the semaphore
    xSemaphoreGive(binSem); 
    vTaskDelay(task_0_delay / portTICK_PERIOD_MS);
  }
}

/*
 * Function Name : void taskB(void *parameters)
 * Description   : Waits until Task A gives the semaphore. Once received,
 *               
 */
void taskB(void *parameters) {
  while (1) {
    // Waiting to acquire the semaphore from Task A
    Serial.println("[Task A] Waiting for semaphore...");
    
    // Take semaphore (block indefinitely until available)
    xSemaphoreTake(binSem, portMAX_DELAY); 
    
    Serial.println("[Task A] Semaphore received!");
  }
}

void setup() {
  Serial.begin(9600);   
  

  vTaskDelay(500 / portTICK_PERIOD_MS); 

  // Create a binary semaphore 
  binSem = xSemaphoreCreateBinary();

  // Create Task A to runs on Core 0
  xTaskCreatePinnedToCore(taskA, "Task A", 1024, NULL, 1, NULL, 0);

  // Create Task B to runs on Core 1
  xTaskCreatePinnedToCore(taskB, "Task B", 1024, NULL, 1, NULL, 1);


  vTaskDelete(NULL); 
}

// loop() is empty because tasks handle everything
void loop() {}
