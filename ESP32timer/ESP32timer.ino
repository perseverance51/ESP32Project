/*
   重复计时器（定时器可以通过连接到 PIN 0 的按钮停止）
  接线说明： 按键接4
*/

//停止按钮连接到 D4 (IO4)
#define BTN_STOP_ALARM    (4)

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void IRAM_ATTR onTimer() {
  // 增加计数器并设置 ISR 的时间
  portENTER_CRITICAL_ISR(&timerMux);
  isrCounter++;
  lastIsrAt = millis();
  portEXIT_CRITICAL_ISR(&timerMux);
  // 给出一个我们可以在循环中检查的信号量
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // 如果要切换输出，在此处使用数字读/写是安全的
}

void setup() {
  Serial.begin(115200);

  // 将 BTN_STOP_ALARM 设置为输入上拉模式
  pinMode(BTN_STOP_ALARM, INPUT_PULLUP);
//digitalWrite(BTN_STOP_ALARM,LOW);
  // 创建信号量以在计时器触发时通知我们
  timerSemaphore = xSemaphoreCreateBinary();

  // 使用 4 的第一个计时器（从零开始计数）。
  // 为预分频器设置 80 分频器（更多信息请参见 ESP32 技术参考手册）信息）。
  timer = timerBegin(0, 80, true);

  // 将计时器功能附加到我们的计时器。
  timerAttachInterrupt(timer, &onTimer, true);

  //  定时器设置
  //每秒调用一次 onTimer 函数（值以微秒为单位）。
  // 是否重装载,重复闹钟（第三个参数）
  timerAlarmWrite(timer, 1000000ul, true);

  // 使能定时器
  timerAlarmEnable(timer);
}

void loop() {
  //如果计时器已触发
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) {
    uint32_t isrCount = 0, isrTime = 0;
    // 读取中断计数和时间
    portENTER_CRITICAL(&timerMux);
    isrCount = isrCounter;
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);
    //打印出来
    Serial.print("onTimer no. ");
    Serial.print(isrCount);
    Serial.print(" at ");
    Serial.print(isrTime);
    Serial.println(" ms");
  }
  // 如果按钮被按下
  if (digitalRead(BTN_STOP_ALARM) == LOW ) {
    Serial.println("取消计数，Stop");
    // 如果计时器仍在运行
    if (timer) {
      // 停止并释放计时器
      timerEnd(timer);
      timer = NULL;
    }
  }
}
