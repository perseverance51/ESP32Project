/*******************************************************
            ESP32 使用内部霍尔传感器
   功能：使用内部霍尔传感器获取磁场强度的值打印到串口监视器
   引脚：

 *******************************************************/
const int LED = 2;
const int LIMIT = 0;
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  //guarda o valor lido do sensor hall
  int measurement = 0;
  measurement = hallRead();
   Serial.print("Hall sensor measurement: ");
  Serial.println(measurement);
  if (measurement < LIMIT) {//数值小于0，点亮板载led灯
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  delay(1000);
}
