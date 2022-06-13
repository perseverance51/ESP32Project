// 演示如何在wifi和蓝牙模式之间切换，或者同时使用
// 按键绑定在GPIO 0 和 GND之间，模式也随之按下而切换

#include "WiFi.h"
#define STA_SSID "MERCURY_D268G"
#define STA_PASS "pba5ayzk"
#define AP_SSID  "Esp32"
const int touchPin = 4; 
const int ledPin = 2;
const uint8_t threshold = 20;
enum { STEP_BTON, STEP_BTOFF, STEP_STA, STEP_AP, STEP_AP_STA, STEP_OFF, STEP_BT_STA, STEP_END };  //枚举，即别名   
//没有指定值的枚举元素，其值为前一元素加 1。也就说 STEP_BTON 的值为 0，STEP_BTOFF 的值为 1...
void setup() {
    Serial.begin(115200);
  //  pinMode(touchPin, INPUT_PULLUP);  //触摸引脚4，输入模式
    pinMode (ledPin, OUTPUT);
    WiFi.onEvent(WiFiEvent);
    Serial.print("ESP32 SDK: ");
    Serial.println(ESP.getSdkVersion());
    Serial.println("按下按键切换至下一模式");
}

void loop() {
 
    uint8_t touchValue =  touchRead(touchPin);    //unsigned char
    if(touchValue < threshold){       //如果本次引脚电平不等于前次
        onButton();
    }
}

void onButton(){
  static uint32_t step = STEP_BTON;
  switch(step){
    case STEP_BTON://BT only
      Serial.println("** 启动蓝牙");
      btStart();
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_BTOFF://ALL Off
      Serial.println("** 关闭蓝牙");
      btStop();
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_STA://STA Only
      Serial.println("** 启动wifi站点模式");
      WiFi.begin(STA_SSID, STA_PASS);       //连接wifi
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_AP://AP Only
      Serial.println("** 关闭wifi站点模式");
      WiFi.mode(WIFI_AP);
      Serial.println("** 开启AP模式");
      WiFi.softAP(AP_SSID);                 //初始化AP，wifi名字为AP_SSID
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_AP_STA://AP+STA
      Serial.println("** 启动wifi站点模式");
      WiFi.begin(STA_SSID, STA_PASS);
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_OFF://All Off
      Serial.println("** wifi关闭");
      WiFi.mode(WIFI_OFF);
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_BT_STA://BT+STA
      Serial.println("** 启动 wifi站点模式+蓝牙");
      WiFi.begin(STA_SSID, STA_PASS);
      btStart();
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    case STEP_END://All Off
      Serial.println("** 关闭 wifi站点模式+蓝牙");
      WiFi.mode(WIFI_OFF);
      btStop();
      digitalWrite(ledPin,!digitalRead(ledPin));
    break;
    
    default:
    break;
  }
  if(step == STEP_END){
    step = STEP_BTON;
  } else {
    step++;
  }
  
  //抖动消除
  delay(100);
}

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        case SYSTEM_EVENT_AP_START:
            Serial.println("AP Started");
            WiFi.softAPsetHostname(AP_SSID);
            break;
        case SYSTEM_EVENT_AP_STOP:
            Serial.println("AP Stopped");
            break;
        case SYSTEM_EVENT_STA_START:
            Serial.println("STA Started");
            WiFi.setHostname(AP_SSID);
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            Serial.println("STA Connected");
            WiFi.enableIpV6();
            break;
        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            Serial.print("STA IPv6: ");
            Serial.println(WiFi.localIPv6());
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("STA IPv4: ");
            Serial.println(WiFi.localIP());
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("STA Disconnected");
            break;
        case SYSTEM_EVENT_STA_STOP:
            Serial.println("STA Stopped");
            break;
        default:
            break;
    }
}
