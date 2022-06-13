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

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Interrupt Test");
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);//板载led灯
  touchAttachInterrupt(T0, gotTouch, 40);//其中40为阈值，当通道T0上的值<40时，会触发中断
}
 
void loop() {}
void gotTouch(){ 
  digitalWrite(led,!digitalRead(led));
  Serial.printf("touch_pad_read: %d ,led= %d \n",touchRead(T0),digitalRead(led));  // Touch0 通道是 GPIO 4.
  delay(80);
}
