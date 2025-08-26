TickType_t cs_wait = 250;   // Critical section duration in ms
TickType_t med_wait = 5000; // Medium task work duration in ms

static SemaphoreHandle_t lock; // Mutex handle for synchronization

/*
* Function Name : void taskLow(void *parameters)w
* Description   : Low priority task that tries to take the lock,
*                
*/
void taskLow(void *parameters) {
  TickType_t timestamp;
  while (1) 
  {
    Serial.println("Task Low trying to take lock...");
    // Record current time before trying to acquire the mutex
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Block indefinitely until lock is acquired
    xSemaphoreTake(lock, portMAX_DELAY);

    Serial.println("Task Low got lock.");
    // Print how long it waited to acquire the lock
    Serial.println((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);

    // Hold lock for 'cs_wait' ms (busy wait loop, not vTaskDelay)
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

    Serial.println("Task Low release lock.");
    // Release lock
    xSemaphoreGive(lock);

    // Sleep for 500 ms before trying again
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

/*
* Function Name : void taskMid(void *parameters)
* Description   : Medium priority task that does some busy work
*          
*/
void taskMid(void *parameters) {
  TickType_t timestamp;
  while (1) 
  {
    Serial.println("Task Mid doing some work...");

    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Simulate workload for 'med_wait' ms
    while ((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < med_wait);

    Serial.println("Task Mid done!");
    // Yield for 500 ms before next cycle
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

/*
* Function Name : void taskHigh(void *parameters)
* Description   : High priority task that tries to take the lock,
*                
*/
void taskHigh(void *parameters) {
  TickType_t timestamp;
  while (1) 
  {
    Serial.println("Task High trying to take lock...");
    // Record current time before trying to acquire the mutex
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Block indefinitely until lock is acquired
    xSemaphoreTake(lock, portMAX_DELAY);

    Serial.println("Task High got lock. ");
    // Print how long it waited to acquire the lock
    Serial.println((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);

    // Hold lock for 'cs_wait' ms (busy wait loop)
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

    Serial.println("Task High release lock.");
    // Release lock
    xSemaphoreGive(lock);

    // Sleep for 500 ms before trying again
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);
  vTaskDelay(1000 / portTICK_PERIOD_MS); // Allow Serial to initialize
  Serial.println();

  // Create a mutex for synchronization
  lock = xSemaphoreCreateMutex();

  // Create tasks with different priorities pinned to Core 1
  xTaskCreatePinnedToCore(taskLow, "Task Low", 1024, NULL, 1, NULL, 1);
  vTaskDelay(1 / portTICK_PERIOD_MS); // Small delay to ensure order
  xTaskCreatePinnedToCore(taskHigh, "Task High", 1024, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(taskMid, "Task Mid", 1024, NULL, 2, NULL, 1);

  // Delete setup task (no longer needed)
  vTaskDelete(NULL);
}

void loop() {
  // Empty loop since all work is done in FreeRTOS tasks
}
