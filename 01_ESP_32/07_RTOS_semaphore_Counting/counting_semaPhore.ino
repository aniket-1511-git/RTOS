// Size of circular buffer
enum {bufferSize = 5};
// producer no of task
static const int prod_tasks = 5;
// Customer no of task
static const int cons_tasks = 2;
// producer writes to circular buffer
static const int num_writes = 3;
// Globle Varribles
// Shared Buffer
static int buf[bufferSize];
// buffer Writing index
static int headBuf = 0;
// buffer reading index
static int tailBuf = 0;
// semaphore handle
static SemaphoreHandle_t binSem;
static SemaphoreHandle_t mutex;
static SemaphoreHandle_t semEmpty;
static SemaphoreHandle_t semFilled;
/*
* Function Name : void readProducer(void *parameters) 
* Description   : this function to write given number of times to shared buffer
*/
void readProducer(void *parameters) 
{
   //  copy received parameter in to local varriable
  int num = *(int *)parameters;
  // Release the binary semaphore
  xSemaphoreGive(binSem);
  for (int i = 0; i < num_writes; i++) {
    // Wait until there is at least one empty 
    xSemaphoreTake(semEmpty, portMAX_DELAY);
    //  Acquire the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);
    // Store the no in buffer
    buf[headBuf] = num;
    headBuf = (headBuf + 1) % bufferSize;
   // Release the mutex
    xSemaphoreGive(mutex);
    // Release the Semaphore
    xSemaphoreGive(semFilled);
  }
  vTaskDelete(NULL);
}

void writeConsumer(void *parameters) {
  int val;
  while (1) {
    // Wait until there is at least one filled slot in the buffer
    xSemaphoreTake(semFilled, portMAX_DELAY);
    // Acquire the mutex to get exclusive access to the shared buffer
    xSemaphoreTake(mutex, portMAX_DELAY);
    // Read the value from the buffer
    val = buf[tailBuf];
    tailBuf = (tailBuf + 1) % bufferSize;
    // print to serial
    Serial.println(val);
    // Release the mutex
    xSemaphoreGive(mutex);
     // Release the Semaphore
    xSemaphoreGive(semEmpty);
  }
}

void setup() {
  char task_name[12];
  Serial.begin(9600);
  Serial.println("======================= RTOS SEMAPHORE =======================");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  // Create a binary semaphore
  binSem = xSemaphoreCreateBinary();
  // Create a mutex 
  mutex = xSemaphoreCreateMutex();
  // Create a counting semaphore
  semEmpty = xSemaphoreCreateCounting(bufferSize, bufferSize);
  // Create a counting
  semFilled = xSemaphoreCreateCounting(bufferSize, 0);

  for (int i = 0; i < prod_tasks; i++) {
    sprintf(task_name, "Producer %i", i);
    // Create a producer task pinned to core 0
    xTaskCreatePinnedToCore(readProducer, task_name, 1024, (void *)&i, 1, NULL, 0);
    // Wait until the created producer task signals it's ready
    xSemaphoreTake(binSem, portMAX_DELAY);
  }

  for (int i = 0; i < cons_tasks; i++) {
    sprintf(task_name, "Consumer %i", i);
    // Create a consumer task pinned to core 1
    xTaskCreatePinnedToCore(writeConsumer, task_name, 1024,NULL, 1, NULL, 1);
  }
  // Locks and immediately unlocks the mutex
  xSemaphoreTake(mutex, portMAX_DELAY); 
  xSemaphoreGive(mutex);
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}