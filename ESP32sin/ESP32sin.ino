/*
@功能：ESP32输出两路DAC，输出正玄波
*/
#include <Arduino.h>
//#include <esp32-hal-dac.h>//DAC功能引用该库，可以不进行#include<>引用
#define uPi 3.14
#define uMaxValue 255

unsigned char uPoints = 0;
unsigned char sin_tab[]="";

void getsin()
{
  float x, uAng;
  uAng=360.000/uPoints;
  for(int i=0;i<uPoints;i++){
    x=uAng*i;
    x=x*(uPi/180); // 弧度=角度*（π/180）
    sin_tab[i]=(uMaxValue/2)*sin(x)+(uMaxValue/2);
    Serial.printf("sin tab[%d]: %f\n", i, sin_tab[i]);
    // dacWrite(25, 100);  //25,26 就是两个DAC引脚，后面的值取值范围时0-255，具体输出电压是  200/255*电源电压，200就是你填入的值
  }
}


void setup() {
  Serial.begin(115200); 

}

void loop() {
  getsin();
for(int i=0; i<uPoints; i++){
  dacWrite(25, sin_tab[i]);    
}
}
