#include <Arduino.h>

int freq = 1000;    // 频率
int channel = 0;    // 通道
int resolution = 8;   // 分辨率

const int led = 2;
void setup()
{
  /* 1. 使用ledc通道1，设置频率为1kHz，分辨率为10位 */
  ledcSetup(channel, freq, resolution); // 设置通道
  ledcAttachPin(led, channel);  // 将通道与对应的引脚连接
}

void loop()
{
  // 逐渐变亮
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 5)
  {
    ledcWrite(channel, dutyCycle);  // 输出PWM
    delay(20);
  }

  // 逐渐变暗
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle = dutyCycle - 5)
  {
    ledcWrite(channel, dutyCycle);  // 输出PWM
    delay(20);
  }
}
