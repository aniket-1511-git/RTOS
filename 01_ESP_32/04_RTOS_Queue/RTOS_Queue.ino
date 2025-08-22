// Queue handler
static QueueHandle_t msgQueue;
/* Macro defined for Queue len */
#define  queue_len 10
/*
* Function Name : void readQueueData(void * para)
* Description   : Function to read data fomr Queue
*/
void readQueueData(void * para)
{
  // Varriable to read data from Queue
  uint32_t qData;
  while(1)
  {
    // see if there's data in the queue
    if(xQueueReceive(msgQueue, (void*)&qData,0 ) == pdTRUE)
    {
      // function to send data to Serial 
      Serial.print(qData);
      Serial.print(" ");
    }
    vTaskDelay(1000 /portTICK_PERIOD_MS);
  }
}
/*
* Function Name : void readQueueData(void * para)
* Description   : Function to read data fomr Queue
*/
void writeQueueData(void * para)
{
  // Varriable to write data in Queue
  uint32_t qData;
  while(1)
  {
    qData++;
    // see if there's data in the queue
    if(xQueueSend(msgQueue, (void*)&qData,10 ) != pdTRUE)
    {
      Serial.println();
      Serial.println("Queue Full ...!");
    }
    // function for delay
    vTaskDelay(500 /portTICK_PERIOD_MS);
  }
}
void setup() {
  // Function to set baud rate 
  Serial.begin(9600);
  // Function to Display Task name 
  Serial.println("*********** FreeRTOs Queue demo ***********");

  // Function to create queue
  msgQueue = xQueueCreate(queue_len,sizeof(int));
 // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      readQueueData,     // function to called
      "Read Queue data",     // Task name
      1500,          // stack size in byte
      NULL,          // Parameter to pass function 
      0,             // Task Priority
      NULL,          // Task handler
      0              // core no           
      );
       // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      writeQueueData,     // function to called
      "write Queue data ",     // Task name
      1500,          // stack size in byte
      NULL,          // Parameter to pass function 
      1,             // Task Priority
      NULL,          // Task handler
      1              // core no           
      );  
}
void loop ()
{


}
