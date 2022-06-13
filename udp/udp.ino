#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#ifndef STASSID
#define STASSID "MERCURY_D268G"
#define STAPSK  "pba5ayzk"
#endif

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,


WiFiUDP Udp;


char hex_str[]  = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};//每次发过来的数据

uint8_t hex_list[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x5, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}; //16进制的数

//查询列表的返回
uint8_t check_char (char temp_) {
  for (int x = 0 ; x < 16 ; x++)
    if (temp_ == hex_str[x])
    {
      return hex_list[x];
      break;
    }

}



void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);


  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("IP:"));
  display.println(WiFi.localIP());
  display.setTextSize(2);
  display.print(F("PORT:"));
  display.println(localPort);
  display.display();
}
int index_l = 0;
int rows = 0;
void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
                  ESP.getFreeHeap());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    for (int x  = 0; x < n ; x++)
    {
      if ( packetBuffer[x] == '*') {
        Serial.println("recv start:");
        display.clearDisplay();
        index_l = 0 ;
        rows = 0 ;
      }

      else  if ( packetBuffer[x] == '#') {
        Serial.println("over");
        display.display();
        index_l = 0 ;
        rows = 0 ;
      }
      else {
        char t = check_char (packetBuffer[x]);
        for  (int y = 0 ; y < 4 ; y++)
        {
          if (index_l == 128) {
            index_l = 0;
            rows++;
          }
          int point = 0;
          if ( t << (4 + y) >> 7 & 1) {
            point = 1;
          }
          display.drawPixel (index_l, rows, point);
          index_l ++;

        }
      }
    }
  }
}

/*
  test (shell/netcat):
  --------------------
    nc -u 192.168.esp.address 8888
*/
