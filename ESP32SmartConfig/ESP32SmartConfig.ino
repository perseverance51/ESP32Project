#include <WiFi.h>
#include <esp_wifi.h>     //用于esp_wifi_restore() 删除保存的wifi信息

#define LED_BUILTIN  (2)    //板载led灯
#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"
const unsigned long interval = 6000UL;//设置更新频率
unsigned long previousMillis = 0;
bool ledState = false;

void SmartConfig()
{ 
  // WiFi.mode(WIFI_AP_STA);
   WiFi.mode(WIFI_STA);
   Serial.println("\r\n wait for smartconfig....");
   WiFi.beginSmartConfig();
     while(1)
   {
    Serial.print(".");
    delay(500);
    if ( WiFi.smartConfigDone())
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s\r\n",WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n",WiFi.psk().c_str());    
      break;      
    }
   } 
}
bool AutoConfig()
{
  WiFi.begin();
  for (int i=0; i<20; i++)
  {
    int wstatus = WiFi.status();
    if (wstatus == WL_CONNECTED )  
       {  
          Serial.println("wifi smartConfig success");
          Serial.printf("SSID:%s",WiFi.SSID().c_str());
          Serial.printf(",PWS:%s\r\n",WiFi.psk().c_str());
          Serial.print("localIP:");
          Serial.println(WiFi.localIP());
          Serial.print(",GateIP:");
          Serial.println(WiFi.gatewayIP()); 
          esp_wifi_set_storage(WIFI_STORAGE_RAM);//自动保存wifi信息
          WiFi.setAutoConnect(true);  // 设置自动连接      
          return true;
       }
       else
       {
          Serial.print("WIFI AutoConfig Waiting ....");
          Serial.println(wstatus);
          delay(1000);
       }   
  }
  Serial.println("Wifi autoconfig faild!");
  return false;
  }
void setup() {
  Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);//板载led灯作为指示
 delay(100);
   if (!AutoConfig())
  {
   SmartConfig();
  }  
 configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
 // esp_wifi_restore();  //删除保存的wifi信息
  
}
 
void loop() {  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
     ledState = !ledState;//状态翻转
     digitalWrite(LED_BUILTIN, ledState);
     struct tm timeInfo; //声明一个结构体
  if (!getLocalTime(&timeInfo))
  { //一定要加这个条件判断，否则内存溢出
    Serial.println("Failed to obtain time");
  }
   Serial.println(&timeInfo, "%F %T %A"); 
        previousMillis = currentMillis;
}
 
}

//删除保存的wifi信息,并使LED闪烁5次
void restoreWiFi(){
       delay(500);
       esp_wifi_restore();  //删除保存的wifi信息
       Serial.println("连接信息已清空,准备重启设备..");

  }
