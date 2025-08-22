
// Message to display on serial terminal 
char message[] = "Welcome to RTOS with ESP32";
// task 1 Handler 
static TaskHandle_t taskH1=NULL;
// task 2 Handler 
static TaskHandle_t taskH2=NULL;
/*
* Function name : void task_1(void* para)
* Description   : This Function to display Message on serial terimal
*/
void task_1(void* para)
{
  // length of String and iterator 
  uint32_t mLen = strlen(message),i;
  while(1)
  {
    // loop to Iterate till message length
    for(i=0;i<mLen;i++)
    {
      // Function to print char by char on serial terminal
      Serial.print(message[i]);
    }
    // Function to print next line on serial terminal
     Serial.println();
     // Function to Delay generation 
    vTaskDelay(1000 /portTICK_PERIOD_MS);
   
  }
}
/*
* Function name : void task_2(void* para)
* Description   : This Function to display '*'  on serial terimal
*/
void task_2(void* para)
{
  while(1)
  {
    // Function to print 
    Serial.print('*');
    // Function to Delay generation 
    vTaskDelay(100/ portTICK_PERIOD_MS);
  }

}
void setup() {
  // Function to set baud rate 
  Serial.begin(300);
  // Function to Display Task name 
   Serial.println("*********** FreeRTOs Task ***********");
 // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      task_1,     // function to called
      "MESSAGE PRINT", // Task name
      1024,          // stack size in byte
      NULL,          // Parameter to pass function 
      0,             // Task Priority
      &taskH1,          // Task handler
      0              // core no           
      );
 // Function call to run task 2 in core zero
 xTaskCreatePinnedToCore(
      task_2,     // function to called
      "* Print",  // Task name
      1024,          // stack size in byte
      NULL,          // Parameter to pass function 
      1,             // Task Priority
      &taskH1,          // Task handler
      1              // core no           
      );
}

void loop() {

  for(int i =0;i<3;i++)
  {
    // function to suspend task 2
    vTaskSuspend(taskH2);
    // Function to Delay generation 
    vTaskDelay(2000/ portTICK_PERIOD_MS);
    // function to resume task 2
    vTaskResume(taskH2);
    // Function to Delay generation 
    vTaskDelay(2000/ portTICK_PERIOD_MS);
  
  }
  // Check if the task handle is valid 
  if(taskH1 !=NULL)
  {
    // Delete the task 
    vTaskDelete(taskH1);
    // Set the handle to NULL to avoid dangling pointers
    taskH1 = NULL;
  }
}
