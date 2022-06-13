#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("");
}

uint64_t chipid;

void loop()
{
  chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
  Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
  Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

  Serial.printf("total heap size = %u\n",ESP.getHeapSize());
  Serial.printf("available heap = %u\n",ESP.getFreeHeap());
//  Serial.printf("lowest level of free heap since boot = %u\n",ESP.getMinFreeHeap());
//  Serial.printf("largest block of heap that can be allocated at once = %u\n",ESP.getMaxAllocHeap());

  Serial.printf("total Psram size = %u\n",ESP.getPsramSize());
  Serial.printf("available Psram = %u\n",ESP.getFreePsram());
  Serial.printf("lowest level of free Psram since boot = %u\n",ESP.getMinFreePsram());
  Serial.printf("largest block of Psram that can be allocated at once = %u\n",ESP.getMinFreePsram());

  Serial.printf("get Chip Revision = %u\n",ESP.getChipRevision());
  Serial.printf("getCpuFreqMHz = %u\n",ESP.getCpuFreqMHz());
  Serial.printf("get Cycle Count = %u\n",ESP.getCycleCount());
  Serial.printf("get SdkVersion = %s\n",ESP.getSdkVersion());

  delay(5000);
}
