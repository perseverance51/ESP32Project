/**
 * ESP32 HTTP GET方式获取网络数据

 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

//填写WIFI入网信息
const char* ssid     = "MERCURY_D268G";     // WIFI账户
const char* password = "pba5ayzk"; // WIFI密码

void setup() {

    Serial.begin(115200);
    Serial.println();

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }
/* 开始访问指定服务器地址，获取数据  */
  Serial.print("Connected to ");
  Serial.println(ssid);
        HTTPClient http;//创建 WiFiClient 实例化对象
        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("http://quan.suning.com/getSysTime.do"); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET("http://quan.suning.com/getSysTime.do");//PUT请求

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
}

void loop() {
    delay(5000);
}
