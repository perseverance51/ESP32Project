//#include <Ticker.h>
//Ticker ticker;
#ifndef LED_BUILTIN
#define LED_BUILTIN 13 // ESP32 DOES NOT DEFINE LED_BUILTIN
#endif

float num2 = 623.95273;
void tick()
{
  //toggle state
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));     // set pin to the opposite state
//   Serial.println(PI);//直接打印PI常量的值：3.14
//      char jinoas[100];   //打印字符缓冲数组
//   char str[6];   //浮点类型转化存储缓冲数组
//   dtostrf(num2, 4,2, str);  // 4,2 表示转化的精度：623.95
//    sprintf(jinoas,"num2的值为:%s \t float:%.5f \t",str,num2);//num2的值为:623.95   float:623.95276
//    Serial.println(jinoas);
      static int i=0;
   int j=~(1<<i);
// Serial.printf("j= %d BIN= %\t",j);
  Serial.println(j, BIN);
 i++;
 i%=8;
   
}
void setup() {
  Serial.begin(112500);
  Serial.flush();//列队打印
  Serial.println("Start:");
  Serial.println();
   pinMode(LED_BUILTIN, OUTPUT);
//ticker.attach(6, tick);//每隔6秒板子led灯亮一下
 
}

void loop() {
     static int i=0;
   int j=~(1<<i);
   Serial.print("j=");
 Serial.println(j);
  Serial.print("BIN=");
  Serial.println(j, BIN);
 i++;
 i%=8;
 delay(5000);
}
