/*
看门狗定时器：当GPIO 4当接地超过3s，系统判断程序跑飞，强制重启。
  接线说明： 按键接D4--GPIO4
*/

#include "esp_system.h"

const int button = 4;         //用于触发延迟的0接脚
const int wdtTimeout = 1000;  //触发看门狗的时间（以毫秒为单位）
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("running setup");

  pinMode(button, INPUT_PULLUP);                    //初始化控制引脚
  timer = timerBegin(0, 80, true);                  //初始化定时器 定时器编号0，分频数 80，是否是累加模式：true
  timerAttachInterrupt(timer, &resetModule, true);  //附加回调
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //设置定时器
  timerAlarmEnable(timer);                          //开启中断
}

void loop() {
  Serial.println("running main loop");

  timerWrite(timer, 0); //重置定时器（饲料看门狗）
  long loopTime = millis();
  //按下按钮时，最多延迟 3 秒触发定时器
  while (!digitalRead(button)) {
    Serial.println("button pressed");
    delay(500);
  }
  delay(1000); //模拟工作
  loopTime = millis() - loopTime;

  Serial.print("loop time is = ");
  Serial.println(loopTime); //应该在 3000 以下
}
