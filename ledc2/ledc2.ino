#include <Arduino.h>

/* 设置led输出引脚号 */
uint8_t led_pin = 2;

void setup() 
{            
  Serial.begin(115200);
  delay(10); 

  /* 1. 使用ledc通道1，设置频率为2kHz，分辨率为8位 */
  double f = ledcSetup(1, 2000, 8);  
  Serial.print("F=");Serial.println(f); /* 打印实际设置的频率*/

  /* 2. 将LED引脚绑定到ledc通道1 */
  ledcAttachPin(led_pin, 1);

  /* 3. 设置ledc通道占空比为128/256=50% */
  ledcWrite(1, 32);
}

void loop() 
{
  delay(100);
}
