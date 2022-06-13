#include <Arduino.h>
#include "SD.h"

void setup()
{
  Serial.begin(115200);
  if (!SD.begin())
  {
    Serial.print(".");
  }
  Serial.println("SD card Ready!");
  Serial.printf("SD.cardSize = %lld \r\n", SD.cardSize());
  Serial.printf("SD.totalBytes = %lld \r\n", SD.totalBytes());
  Serial.printf("SD.usedBytes = %lld \r\n", SD.usedBytes());
  Serial.printf("SD.cardType = %d \r\n", SD.cardType());
  Serial.printf("is there /test.txt? :%d \r\n", SD.exists("/sd/doc1/test.txt"));
  Serial.println(SD.mkdir("/doc1"));
  Serial.printf("is there /doc1? :%d \r\n", SD.exists("/doc1"));
  Serial.printf("is there /test.txt? :%d \r\n", SD.exists("/test.txt"));
  File file = SD.open("/test.txt", FILE_WRITE);
  Serial.printf("is there /test.txt? :%d \r\n", SD.exists("/test.txt"));
  file.printf("hello!!!");
  file.close();
  file = SD.open("/test.txt", FILE_READ);
  Serial.println(file.readString());
  file.close();
  Serial.printf("is there /doc1/test1.txt? :%d \r\n", SD.exists("/doc1/test1.txt"));
  File file2 = SD.open("/doc1/test1.txt", FILE_WRITE);
  Serial.printf("is there /doc1/test1.txt? :%d \r\n", SD.exists("/doc1/test1.txt"));
  file2.printf("hello!!!");
  file2.close();
  file2 = SD.open("/test.txt", FILE_READ);
  Serial.println(file2.readString());
  file2.close();
  SD.end();
}

void loop()
{
}
