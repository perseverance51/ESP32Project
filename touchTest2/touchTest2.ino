/**
 * 功能：使用ESP32的触摸按键
 * 触摸传感器通道 管脚
          T0  GPIO4
          T1  GPIO0
          T2  GPIO2
          T3  MTDO
          T4  MTCK
          T5  MTDI
          T6  MTMS
          T7  GPIO27
          T8  32K_XN
          T9  32K_XP
 */
#include <WiFi.h>
#define led 2
const unsigned char touchPin = 4; 
const uint8_t threshold = 20;
unsigned char Trg =0;
unsigned char Cont =0;
uint8_t  CNT =0;
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Interrupt Test");
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);//板载led灯
  //touchAttachInterrupt(T0, gotTouch, 40);//其中40为阈值，当通道T0上的值<40时，会触发中断
}
 
void loop() {
   uint8_t touchValue =  touchRead(touchPin);    //unsigned char
   uint8_t   STATE =0;
   Trg = 0;
    if(touchValue < threshold){       //如果感应值大于阈值，就触发
    //    Serial.printf("touch_pad_read: %d ,led= %d \n",touchValue,digitalRead(led));  // Touch0 通道是 GPIO 4.
        STATE =1;
      Trg = STATE & (STATE ^ Cont);   // 按键触发为1     
      }
     if(Trg){
      digitalWrite(led,HIGH);
     // Serial.println("短按...");
        }   
     if(Cont & STATE){
       CNT++;       // 计数 
       if(CNT > 100){
        digitalWrite(led,LOW);
        Serial.println("长按条件触发...");
        CNT = 0;
        }
     }
       Cont = STATE;                     // 长按触发为1
  }
void onButton(){ 
  digitalWrite(led,!digitalRead(led));
Serial.printf("touch_pad_read: %d ,led= %d \n",touchRead(T0),digitalRead(led));  // Touch0 通道是 GPIO 4.

  delay(80);
}
