#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
const char* ssid     = "MERCURY_D268G";     // your network SSID (name of wifi network)
const char* password = "pba5ayzk"; // your network password

const char*  server = "http://quan.suning.com/getSysTime.do";  // Server URL
//WebServer server(80);
WiFiClientSecure client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.println("\nStarting connection to server...");
 // client.setInsecure();//skip verification
  if (!client.connect(server, 80))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
//    client.println("GET http://quan.suning.com/getSysTime.do HTTP/1.1");
//    client.println("Host: http://quan.suning.com/getSysTime.do");
//    client.println("Connection: close");
//    client.println();
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.stop();
  }
}

void loop() {
  // do nothing
}
