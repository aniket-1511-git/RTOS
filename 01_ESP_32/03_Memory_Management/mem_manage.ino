// Varriable to store data for serial terminal
char *MsgBuff = NULL;
// Flag to send status to task 2
volatile uint8_t flag = 0;
// Macro defined to size of Buffer
#define msgBufferSize 30
/*
* Function name : void task_2(void* para)
* Description   : This Function to read the status from task1 and display data and free dynamic memory
*/
void task_1readData(void* para) 
{
  // varrible to store data and char form serial terminal
  char mBuff[msgBufferSize],ch;

  // Varrible for iterator
  uint8_t i=0;
  while(1)
  {
    // Check if data is available on the Serial port
    while(Serial.available())
    {
      if(i< msgBufferSize )
      {
       
        // Read a character from Serial and store it in buffer
        mBuff[i] = Serial.read();
        // Check if the received character is a newline
        if('\n' == mBuff[i])
        {
          // Null-terminate the string
          mBuff[i]='\0';
          // Function to print free memory Before malloc
        Serial.print("Heap Size Before malloc : ");
        Serial.println(xPortGetFreeHeapSize());
          // Allocate memory for MsgBuff dynamically
          MsgBuff = (char*) pvPortMalloc(sizeof(char)*i+1);
          // Copy the string from mBuff to MsgBuff
          strcpy(MsgBuff,mBuff);
          // Set flag 
          flag = 1;
          // Reset index
          i=-1;
       }
       // Increment buffer index
        i++;
      }
        // Buffer overflow condition
      else 
      {

        // Set flag 
        flag = 1;
        // Reset index
        i = 0;
      }
    }
  }
   // Function For delay
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
/*
* Function name : void task_2writeData(void* para)
* Description   : This Function to read the status from task1 and display data and free dynamic memory
*/
void task_2writeData(void* para)
{
  while(1)
  {
      if(1== flag )
      {
        // Function to print received message  
        Serial.println(MsgBuff);
        // Function to print free memory After malloc
        Serial.print("Heap Size After malloc : ");
        Serial.println(xPortGetFreeHeapSize());
        // Function to Free 
        vPortFree(MsgBuff);
        // Reset buffer as null
        MsgBuff = NULL;
        // Function For delay
        vTaskDelay(100 /portTICK_PERIOD_MS);
        flag = 0;
      }
  }
}
void setup() {
  // Function to set baud rate 
  Serial.begin(9600);
  // Function to Display Task name 
   Serial.println("*********** FreeRTOs Memory demo ***********");
  Serial.println("Enter String...");
 // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      task_1readData,     // function to called
      "Read string",     // Task name
      1500,          // stack size in byte
      NULL,          // Parameter to pass function 
      0,             // Task Priority
      NULL,          // Task handler
      0              // core no           
      );
       // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      task_2writeData,     // function to called
      "write string ",     // Task name
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