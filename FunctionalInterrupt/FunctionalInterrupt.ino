/*
 测试功能中断
  接线说明： 按键1接16，按键2接17
*/

#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include "Button.h"
#define BUTTON1 16
#define BUTTON2 17

Button button1(BUTTON1);
Button button2(BUTTON2);


void setup() {
    Serial.begin(115200);
}

void loop() {
        button1.checkPressed();
        button2.checkPressed();
}
