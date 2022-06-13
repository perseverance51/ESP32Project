void setup() {

Serial.begin(115200);

Serial.print("setup() function running on core: ");

Serial.println(xPortGetCoreID());

}

void loop() {

Serial.print("loop() function running on core: ");

Serial.println(xPortGetCoreID());

}
