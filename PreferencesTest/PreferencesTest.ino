#include <Arduino.h>
#include <Preferences.h>

void setup() {
    Serial.begin(115200);
    Serial.println();
    delay(2000);

    Preferences prefs;
    prefs.begin("test",false);
    Serial.println(prefs.freeEntries());//获取空余nvs空间

        size_t num = prefs.putString("name", "perseverance9527"); // 获取当前命名空间中的键名为"name"的值
                                                        // 如果没有该元素则返回默认值"555"
        Serial.printf("name: %d\n\n", num);
        Serial.println(prefs.freeEntries());
       Serial.printf("name: %s\n\n", prefs.getString("name").c_str());
        prefs.end();
       // delay(5000);
      //  ESP.restart();

}

void loop() {
      Preferences prefs;
      prefs.begin("test",true);
      Serial.println(prefs.freeEntries());//获取空余nvs空间
       Serial.printf("name: %s\n\n", prefs.getString("name").c_str());
        prefs.end();
        delay(5000);
  
  }
