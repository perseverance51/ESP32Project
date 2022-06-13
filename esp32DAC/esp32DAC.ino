/*
@功能：ESP32输出两路DAC，实现两路两路呼吸灯
*/
#include <Arduino.h>
//#include <esp32-hal-dac.h>//DAC功能引用该库，可以不进行#include<>引用
 
//查看源码后得到，DAC引脚只能是这两个引脚
#define LED1 25
#define LED2 26
 
void setup(){
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
}
 
void loop()
{
  // 逐渐变亮
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 1)
  {
    dacWrite(LED1, dutyCycle);  // 输出DAC
    dacWrite(LED2, 255 - dutyCycle);  // 输出DAC
    delay(5);
  }
 
  // 逐渐变暗
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle = dutyCycle - 1)
  {
    dacWrite(LED1, dutyCycle);  // 输出DAC
    dacWrite(LED2, 255 - dutyCycle);  // 输出DAC
    delay(5);
  }
}
 
 
