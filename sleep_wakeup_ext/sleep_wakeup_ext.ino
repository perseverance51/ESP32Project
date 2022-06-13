/*
  深度睡眠与外部唤醒（这里使用10K下拉按钮到 GPIO 4）
*/

#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 十六进制

RTC_DATA_ATTR int bootCount = 0;

//打印 ESP32 从深度睡眠中醒来的原因
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("使用 RTC_IO 的外部信号引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("使用 RTC_CNTL 的外部信号引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("定时器引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("触摸板引起的唤醒"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("ULP 程序引起的唤醒"); break;
    default : Serial.printf("唤醒不是由深度睡眠引起的: %d\n", wakeup_reason); break;
  }
}

void setup(){
  Serial.begin(115200);
  delay(1000); //花一些时间打开串行监视器
  //增加引导编号并在每次重启时打印
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //也打印 ESP32 和触摸板的唤醒原因
  print_wakeup_reason();

  /*
  First we configure the wake up source
  We set our ESP32 to wake up for an external trigger.
  There are two types for ESP32, ext0 and ext1 .
  ext0 uses RTC_IO to wakeup thus requires RTC peripherals
  to be on while ext1 uses RTC Controller so doesnt need
  peripherals to be powered on.
  Note that using internal pullups/pulldowns also requires
  RTC peripherals to be turned on.
  */
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,1); //1 = High, 0 = Low

  //If you were to use ext1, you would use it like
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  //将进入睡眠
  Serial.println("要休眠了");
  esp_deep_sleep_start();
  Serial.println("这永远不会被打印");
}

void loop(){
}
