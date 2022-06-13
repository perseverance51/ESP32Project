#include <ESP8266WiFi.h>
#include <espnow.h>

//注意这里填写对方的MAC
uint8_t esp_1_address[] = {0xF4, 0xCF, 0xA2, 0xD7, 0xD0, 0x40};//NODE1模块1的mac地址
//uint8_t esp_2_address[] = {0x84, 0xCC, 0xA8, 0xA9, 0x00, 0x36};//WEMOS模块2的mac地址
//uint8_t esp_3_address[] = {0x8C, 0xAA, 0xB5, 0x0D, 0x80, 0x7C};//模块3的mac地址

//NODE:0xF4, 0xCF, 0xA2, 0xD7, 0xD0, 0x40
//WEMOS:84:CC:A8:A9:00:36

//Callback when data is sent
//发送信息时的回调函数，每次发送信息会自动调用该函数
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) 
{
  //Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0)//信息发送成功时
  {
    //打印接收方的mac地址
    Serial.print("deliver data to:  ");
    for(int i = 0; i < 5; ++i)
    {
      Serial.printf("%x:", *(mac_addr + i));
    }
    Serial.printf("%x", *(mac_addr + 5));
    Serial.println(" ");
    //Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// Callback when data is received
//接收信息时的回调函数，每次接收信息会自动调用该函数
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) 
{
  //在此处先通过mac地址判断是哪一个设备发送的数据，再进行数据解析（在主控中写代码时）
  //或者只是使用memcpy函数存储数据，在主函数中处理（类似于DMA的形式）
  //打印发送方的mac地址
  Serial.print("receive data from:  ");
  for(int i = 0; i < 5; ++i)
  {
    Serial.printf("%x:", *(mac + i));
  }
  Serial.printf("%x", *(mac + 5));
  Serial.println(" ");
  /*
  Serial.print("Bytes received: ");
  Serial.println(len);
  */
  //打印接收到的数据
  for(int i = 0; i < len; ++i)
  {
    Serial.printf("%c", *(incomingData + i));  
  }
  Serial.println(" ");
}

void setup() {

  Serial.begin(115200);//初始化串口，设置其波特率为115200
  
  WiFi.mode(WIFI_STA);//设置WIFI模式为STA
  WiFi.disconnect();//断开WIFI连接
  
  // Init ESP-NOW
  if (esp_now_init() != 0)//初始化espnow
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else
  {
    Serial.println("esp_now init success");
  }

  // Set ESP-NOW Role
  //双向通信时需要设定角色为 ESP_NOW_ROLE_COMBO
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  //执行完这个函数，每次发送数据就会自动调用回调函数了
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  //与模块2和3配对
  esp_now_add_peer(esp_1_address, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
//  esp_now_add_peer(esp_2_address, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
 // esp_now_add_peer(esp_3_address, ESP_NOW_ROLE_COMBO, 2, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  //执行完这个函数，每次接收数据就会自动调用回调函数了
  esp_now_register_recv_cb(OnDataRecv);
}

uint8_t data_to_send[] = {"test from esp8266_1 Wemos D1"};//要发送的数据

void loop() 
{
    // Send message via ESP-NOW
    //向模块2和3发送数据
     esp_now_send(esp_1_address, data_to_send, sizeof(data_to_send));
//    esp_now_send(esp_2_address, data_to_send, sizeof(data_to_send));
//    esp_now_send(esp_3_address, data_to_send, sizeof(data_to_send));
    delay(500);
}
