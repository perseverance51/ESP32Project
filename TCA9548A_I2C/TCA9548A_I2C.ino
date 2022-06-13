
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//#include <Adafruit_SH1106.h>
#include <Adafruit_SH110X.h>



#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.println(bus);
}
 
void setup() {
  Serial.begin(115200);
 Serial.println("Realy");
  // Start I2C communication with the Multiplexer
  Wire.begin();
  delay(2000);
  // Init OLED display on bus number 2
     TCA9548A(0);
    display.begin(i2c_Address, true); // Address 0x3C default
    delay(500);
  // Clear the buffer
  display.clearDisplay();

}
 
void loop() {
  
    TCA9548A(0);
  display.clearDisplay();
  display.setTextSize(1);
//  display.setTextColor(WHITE);
display.setTextColor(SH110X_WHITE);
  display.setCursor(5, 10);
  // Display static text
  display.println("Persevverance");
  display.display(); 
  delay(2000);
    display.clearDisplay();
}
