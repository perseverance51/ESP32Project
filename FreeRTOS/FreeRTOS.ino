/* 保存数据的结构*/
typedef struct{
  int sender;
  char *msg;
}Data;
 
/* 这个变量保持队列句柄 */
xQueueHandle xQueue;
TaskHandle_t xTask1;
TaskHandle_t xTask2;
void setup() {
 
  Serial.begin(112500);
  /* 创建队列，其大小可包含5个元素Data */
  xQueue = xQueueCreate(5, sizeof(Data));
 
  xTaskCreatePinnedToCore(
      sendTask,           
      "sendTask",        /* 任务名称. */10000,                    /* 任务的堆栈大小 */NULL,                     /* 任务的参数 */1,                        /* 任务的优先级 */
      &xTask1,                /* 跟踪创建的任务的任务句柄 */0);                    /* pin任务到核心0 */
  xTaskCreatePinnedToCore(
      receiveTask,           
      "receiveTask",        
      10000,                    
      NULL,                    
      1,                        
      &xTask2,            
      1);                
}
 
void loop() {
 
}
 
void sendTask( void * parameter )
{
  /*保持发送数据的状态 */
  BaseType_t xStatus;
  /* 阻止任务的时间，直到队列有空闲空间 */
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  /* 创建要发送的数据 */
  Data data;
  /* sender 1的id为1 */
  data.sender = 1;
  for(;;){
    Serial.print("sendTask run on core ");
    /* 获取任务被固定到 */
    Serial.print(xTaskGetAffinity(xTask1));
    Serial.println(" is sending data");
    data.msg = (char *)malloc(20);
    memset(data.msg, 0, 20);
    memcpy(data.msg, "hello world", strlen("hello world"));
    /* 将数据发送到队列前面*/
    xStatus = xQueueSendToFront( xQueue, &data, xTicksToWait );
    /* 检查发送是否正常 */if( xStatus == pdPASS ) {
      /* 增加发送方1 */
      Serial.println("sendTask sent data");
    }
    /* 我们在这里延迟，以便receiveTask有机会接收数据 */
    delay(1000);
  }
  vTaskDelete( NULL );
}
 
void receiveTask( void * parameter )
{
  /*保持接收数据的状态 */
  BaseType_t xStatus;
  /* 阻止任务的时间，直到数据可用 */
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  Data data;
  for(;;){
    /*从队列接收数据 */
    xStatus = xQueueReceive( xQueue, &data, xTicksToWait );
    /* 检查接收是否正常 */
    if(xStatus == pdPASS){
      Serial.print("receiveTask run on core ");
      /*获取任务固定的核心 */
      Serial.print(xTaskGetAffinity(xTask2));
      /* 将数据打印到终端*/
      Serial.print(" got data: ");
      Serial.print("sender = ");
      Serial.print(data.sender);
      Serial.print(" msg = ");
      Serial.println(data.msg);
      free(data.msg);
    }
  }
  vTaskDelete( NULL );
}
