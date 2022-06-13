/*

  深度睡眠触摸唤醒(触摸T0唤醒)
*/

#define Threshold 40 //数值越大，灵敏度更高

RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

//打印 ESP32 从深度睡眠中醒来的原因
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("使用 RTC_IO 的外部信号引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("使用 RTC_CNTL 的外部信号引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("定时器引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("触摸板引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("ULP 程序引起的唤醒"); break;
    default : Serial.printf("唤醒不是由深度睡眠引起的: %d\n", wakeup_reason); break;
  }
}

//打印 ESP32 从深度睡眠中醒来的原因
void print_wakeup_touchpad() {
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  switch (touchPin)
  {
    case 0  : Serial.println("在 GPIO 4 上检测到触摸"); break;
    case 1  : Serial.println("在 GPIO 0 上检测到触摸"); break;
    case 2  : Serial.println("在 GPIO 2 上检测到触摸"); break;
    case 3  : Serial.println("在 GPIO 15 上检测到触摸"); break;
    case 4  : Serial.println("在 GPIO 13 上检测到触摸"); break;
    case 5  : Serial.println("在 GPIO 12 上检测到触摸"); break;
    case 6  : Serial.println("在 GPIO 14 上检测到触摸"); break;
    case 7  : Serial.println("在 GPIO 27 上检测到触摸"); break;
    case 8  : Serial.println("在 GPIO 33 上检测到触摸"); break;
    case 9  : Serial.println("在 GPIO 32 上检测到触摸"); break;
    default : Serial.println("唤醒不是通过触摸板"); break;
  }
}

void callback() {
  //占位符回调函数
}

void setup() {
  Serial.begin(115200);
  delay(1000); //花一些时间打开串行监视器

  //增加引导编号并在每次重启时打印
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //也打印 ESP32 和触摸板的唤醒原因
  print_wakeup_reason();
  print_wakeup_touchpad();

  //在触摸板D4 (GPIO4) 上设置中断,用于触摸唤醒
  touchAttachInterrupt(T0, callback, Threshold);

  //将触摸板配置为唤醒源
  esp_sleep_enable_touchpad_wakeup();

  //现在去睡觉
  Serial.println(" 要休眠了");
  esp_deep_sleep_start();
  Serial.println("这永远不会被打印");
}

void loop() {
  //这永远不会到达
}
