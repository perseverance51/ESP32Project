/**
   BasicHTTPSClient.ino

*/

#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

// 测试HTTP请求用的URL
#define URL "http://www.weather.com.cn/data/sk/101250301.html"

//填写WIFI入网信息
const char* ssid     = "MERCURY_D268G";     // WIFI账户
const char* password = "pba5ayzk"; // WIFI密码

void setClock() {
  //对于我们东八区,8 * 3600,使用夏令时 
  configTime(8 * 3600, 0, "2.cn.pool.ntp.org", "1.cn.pool.ntp.org","3.cn.pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }
  Serial.println();
  struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出:2021-10-24 23:00:44 Sunday
}


void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
 for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
 //设置ESP32工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.println(" connected");

  setClock();  
}

void loop() {
      HTTPClient https;  
      Serial.print("[HTTPS] begin...\n");
      //配置请求地址。此处也可以不使用端口号和PATH而单纯的
  https.begin(URL); 
  Serial.print("URL: "); Serial.println(URL);
         //启动连接并发送HTTP请求
        int httpCode = https.GET();
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode); 
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
  
        https.end();

  Serial.println();
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
}
