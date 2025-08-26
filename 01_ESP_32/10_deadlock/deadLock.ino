
// semaphore handler
static SemaphoreHandle_t mutex_1;
static SemaphoreHandle_t mutex_2;
/*
* Function Name : void TaskA(void*para)
* Description   : This function Takes mutex_1 then mutex_2, does some work, and releases them.
*/
void TaskA(void*para)
{
  while(10){
     // Take mutex_1 first
    xSemaphoreTake(mutex_1, portMAX_DELAY);
    Serial.println("Task A took mutex 1");
    vTaskDelay(1 / portTICK_PERIOD_MS);
      // Then take mutex_2
    xSemaphoreTake(mutex_2, portMAX_DELAY);
    Serial.println("Task A took mutex 2");
    // Critical section
    Serial.println("Task A working ");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    // Release mutexes in reverse order
    xSemaphoreGive(mutex_2);
    xSemaphoreGive(mutex_1);

    Serial.println("Task A going to sleep");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
/*
* Function Name : void TaskB(void*para)
* Description   : This function Takes mutex_1 then mutex_2, does some work, and releases them.
*/
void TaskB(void*para)
{
  while(1){
    // Task B ALSO takes mutex_1 first
    xSemaphoreTake(mutex_1, portMAX_DELAY);
    Serial.println("Task B took mutex 1");
    vTaskDelay(1 / portTICK_PERIOD_MS);
    // Then takes mutex_2
    xSemaphoreTake(mutex_2, portMAX_DELAY);
    Serial.println("Task B took mutex 2");
    // Critical section
    Serial.println("Task B working");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    // Release mutexes
    xSemaphoreGive(mutex_2);
    xSemaphoreGive(mutex_1);

    Serial.println("Task B going to sleep");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
void setup() {
  Serial.begin(9600);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("===================== DeadLock in RTOS =====================");
  // Create mutexes
  mutex_1 = xSemaphoreCreateMutex();
  mutex_2 = xSemaphoreCreateMutex();
  // Create tasks pinned to Core 0
  xTaskCreatePinnedToCore(TaskA, "Task A", 1024, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskB, "Task B", 1024, NULL, 1, NULL, 0);
  // Delete setup tas
  vTaskDelete(NULL);
}

void loop() {}