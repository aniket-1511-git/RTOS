/*
* Function name : void task_1(void* para)
* Description   : This Function to store elements in array 
*/
void task_1(void* para)
{
  //varrible for iterator 
  uint32_t i;
  // Array to store int 
  uint32_t valStore[100];
  while(1)
  {
    // loop to Iterate till 100
    for(i=0;i<100;i++)
    {
      valStore[i]=i+1;
    }   
    Serial.println(valStore[0]);
  }
}
void setup() {
  // Function to set baud rate 
  Serial.begin(96000);
  // Function to Display Task name 
   Serial.println("*********** FreeRTOs Memory demo ***********");
 // Function call to run task 1 in core zero
 xTaskCreatePinnedToCore(
      task_1,     // function to called
      "Mem demo", // Task name
      1024,          // stack size in byte
      NULL,          // Parameter to pass function 
      0,             // Task Priority
      NULL,          // Task handler
      0              // core no           
      ); 
}
void loop ()
{


}