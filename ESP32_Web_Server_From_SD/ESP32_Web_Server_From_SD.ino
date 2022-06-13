/*ESP32 Web Server with Files from microSD Card
 * 
 * 
 */
#ifdef ESP8266
#include <ESP8266WiFi.h> 
#include <ESPAsyncTCP.h>
#else
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "FS.h"
#endif
#include <ESPAsyncWebServer.h>
#include <SD.h> 
#include <SPI.h>
#ifdef ESP8266
#define SD_CS_pin           D8         // The pin on Wemos D1 Mini for SD Card Chip-Select
#else
#define SD_CS_pin           5        // Use pin 5 on MH-T Live ESP32 version of Wemos D1 Mini for SD Card Chip-Select
#endif                               // Use pin 13 on Wemos ESP32 Pro
// Replace with your network credentials
const char* ssid = "MERCURY_D268G";
const char* password = "pba5ayzk";
// Set LED GPIO
const int ledPin = 2;//板载led灯
// Stores LED state
String ledState;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void initSDCard(){

  if(!SD.begin(SD_CS_pin)){
    Serial.println("Card Mount Failed");
    return;
  }
#ifdef ESP32
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
#endif
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
//使用 % 来标识占位符,替换网页中的相关信息
// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
void setup() {
  Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
  initWiFi();
  initSDCard();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD , "/index.html", "text/html");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/style.css", "text/css");
  });
    // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SD,"/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SD, "/index.html", String(), false, processor);
  });
  //静态文件服务
  // 用户访问主页时，返回SD中index.html文件
 // server.serveStatic("/", SD, "index.html");
// 用户访问/时，默认返回将变成SPIFFS中/www/default.html文件
server.serveStatic("/", SD,  "/").setDefaultFile( "index.html");
// 设定缓存事件500秒，客户端获取过的文件将在客户端缓存500秒
// 500秒内需要已缓存的文件将直接使用缓存，不再从服务器获取
server.serveStatic("/", SD, "/").setCacheControl("max-age=500");
// 使用下面方式就可以随时更改Cache-Control
//AsyncStaticWebHandler* handler = &server.serveStatic("/", SD, "/").setCacheControl("max-age=600");
//handler->setCacheControl("max-age=30");

  server.begin();
}

void loop() {
  
}
