#include <BLEDevice.h>

// Server回调函数声明
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("现在有设备接入~");
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("现在有设备断开连接~");
      // 在有设备接入后Advertising广播会被停止，所以要在设备断开连接时重新开启广播
      // 不然的话只有重启ESP32后才能重新搜索到
      pServer->startAdvertising(); //该行效果同 BLEDevice::startAdvertising();
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println();

  BLEDevice::init("ESP32-BLE");
  BLEServer *pServer = BLEDevice::createServer(); // 创建服务器
  pServer->setCallbacks(new MyServerCallbacks()); // 绑定回调函数
  BLEDevice::startAdvertising();
}

void loop() {}
