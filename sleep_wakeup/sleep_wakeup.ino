/*
  通过定时器功能唤醒深度睡眠（设置为5秒）
*/

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  (5)        //时间ESP32将转入休眠状态（以秒为单位）

RTC_DATA_ATTR int bootCount = 0;

/*
  Method to print the reason by which ESP32
  has been awaken from sleep
*/
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

void setup() {
  Serial.begin(115200);
  delay(1000); //花一些时间打开串行监视器
  //增加引导编号并在每次重启时打印
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();

  /*
    First we configure the wake up source
    We set our ESP32 to wake up every 5 seconds
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");

  /*
    Next we decide what all peripherals to shut down/keep on
    By default, ESP32 will automatically power down the peripherals
    not needed by the wakeup source, but if you want to be a poweruser
    this is for you. Read in detail at the API docs
    http://esp-idf.readthedocs.io/en/latest/api-reference/system/deep_sleep.html
    Left the line commented as an example of how to configure peripherals.
    The line below turns off all RTC peripherals in deep sleep.
  */
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  //Serial.println("Configured all RTC Peripherals to be powered down in sleep");

  /*
    Now that we have setup a wake cause and if needed setup the
    peripherals state in deep sleep, we can now start going to
    deep sleep.
    In the case that no wake up sources were provided but deep
    sleep was started, it will sleep forever unless hardware
    reset occurs.
  */
  Serial.println("要休眠了");
  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("这永远不会被打印");
}

void loop() {
 
}
