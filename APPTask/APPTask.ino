#define LED_BUILTIN (2)
//#include "sys/app_contorller.h"
    unsigned int previousMillis;        // 保存上一回的时间戳
    unsigned int  interval = 3000; // 日期时钟更新的时间间隔
//AppController *app_contorller; // APP控制器
//void wifi_auto_process()
//{
//    if (doDelayMillisTime(m_wifiClickInterval, m_preWifiClickMillis, false) == true)
//    {
//            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
//            Serial.print("Free heap: ");
//            Serial.println(ESP.getFreeHeap());
//            Serial.println(esp_get_free_heap_size());
//    }
//}
//boolean doDelayMillisTime(unsigned int interval, unsigned int previousMillis, boolean flag)
//{
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis >= interval)
//    {
//        previousMillis = currentMillis;
//        flag = !flag;
//    }
//    return flag ;
//}
void setup() {
Serial.begin(115200);
pinMode(LED_BUILTIN, OUTPUT);
   Serial.print("Free heap: ");
    Serial.println(esp_get_free_heap_size());
// app_contorller = new AppController(); // APP控制器
//    app_contorller->app_register(&media_app);
//    app_contorller->app_register(&weather_app);
//    app_contorller->app_register(&picture_app);
//    app_contorller->app_register(&screen_share_app);
//    app_contorller->app_register(&server_app);
}

void loop() {
//app_contorller->main_process(act_info); // 运行当前进程
//wifi_auto_process(); // 任务调度
 unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
            Serial.print("Free heap: ");
            Serial.println(ESP.getFreeHeap());//获取空闲堆
            Serial.println(esp_get_free_heap_size());//查询当前可用的堆内存大小
               Serial.println(ESP.getFlashChipMode());//dio
              Serial.println( ESP.getHeapSize()); //获取堆的容量
              Serial.println( ESP.getFlashChipSize());//16777216

      
    }
}
