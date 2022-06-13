/*          Soft SPI 
 *  [ESP32 IO26 – CS MICROSD]
    [ESP32 IO14 – MOSI MICROSD]
    [ESP32 IO13 – MISO MICROSD]
    [ESP32 IO27 – SCK MICROSD]
    [ESP32 GND – GND MICROSD]
    [VIN – VCC MICROSD]

    Hard SPI
 * MICROSD CS    -    ESP32 IO5
  MICROSD SCK   -     ESP32 IO18
  MICROSD MOSI  -    ESP32 IO23
  MICROSD MISO   -   ESP32 IO19
  MICROSD Vcc   -      ESP32 VIN
  MICROSD GND   -    ESP32 GND
 * 
 */
#include <mySD.h>

File root;

void setup()
{
  Serial.begin(115200);

  Serial.print("Initializing SD card...");
  /* initialize SD library with Soft SPI pins, if using Hard SPI replace with this SD.begin()*/
  //if (!SD.begin(26, 14, 13, 27)) {
    if (!SD.begin()) { 
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  /* Begin at the root "/" */
  root = SD.open("/");
  if (root) {    
    printDirectory(root, 0);
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  /* open "test.txt" for writing */
  root = SD.open("test.txt", FILE_WRITE);
  /* if open succesfully -> root != NULL 
    then write string "Hello world!" to it
  */
  if (root) {
    root.println("Hello world!");
    root.flush();
   /* close the file */
    root.close();
  } else {
    /* if the file open error, print an error */
    Serial.println("error opening test.txt");
  }
  delay(1000);
  /* after writing then reopen the file and read it */
  root = SD.open("test.txt");
  if (root) {    
    /* read from the file until there's nothing else in it */
    while (root.available()) {
      /* read the file and print to Terminal */
      Serial.write(root.read());
    }
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  
  Serial.println("done!");
}

void loop()
{
}

void printDirectory(File dir, int numTabs) {
  
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the name
     Serial.print(entry.name());
     /* Recurse for directories, otherwise print the file size */
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       /* files have sizes, directories do not */
       Serial.print("\t\t");
       Serial.println(entry.size());
     }
     entry.close();
   }
}