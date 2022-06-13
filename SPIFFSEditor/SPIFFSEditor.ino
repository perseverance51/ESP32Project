/*
 * 登录页面
 * http://192.168.0.118/edit
 */
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h> //引入相应库
#include <SPIFFSEditor.h> //引入相应库
  #include "FS.h"
  #include <SD.h> 
#include <SPI.h>
#define SD_CS_pin    (5) 
const char *ssid = "MERCURY_D268G";
const char *password = "pba5ayzk";

AsyncWebServer server(80); //声明WebServer对象

const char* http_username = "admin";
const char* http_password = "123456";
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
void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
  initSDCard();
  SPIFFS.begin(true);

  server.addHandler(new SPIFFSEditor(SPIFFS, http_username,http_password));

  server.begin(); //启动服务器

  Serial.println("Web server started");
}

void loop(){}
