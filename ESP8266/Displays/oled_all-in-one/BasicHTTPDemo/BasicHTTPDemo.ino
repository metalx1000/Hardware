//Code by Kris Occhipinti
//http://filmsbykris.com
//Wed Sep  6 10:11:16 EDT 2017
//License GPLv3
// Include the correct display library
// For a connection via I2C using Wire include

#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <ESP8266WiFi.h>

const char* ssid     = "....";
const char* password = "....";

const char* host = "filmsbykris.com";
String url = "/scripts/esp/msgs/oled1.php";

// or #include "SH1106.h" alis for `#include "SH1106Wire.h"`
// For a connection via I2C using brzo_i2c (must be installed) include
// #include <brzo_i2c.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Brzo.h"
// #include "SH1106Brzo.h"
// For a connection via SPI include
// #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// #include "SH1106SPi.h"

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5,4);

// SH1106 display(0x3c, 5,4);

int xpos = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println(); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);

  display.clear();  // clear the display
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(0,24,"Connecting");
}

void drawDemo() {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    //check if it has a message line
    if(line.indexOf("ESPMSG:") > 0){
      //removed line header
      line.remove(0, 8);
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.setTextAlignment(TEXT_ALIGN_LEFT); // The coordinates define the center of the screen!
      display.drawString(0,0, line);

      //draw moving cursor at bottom of display
      display.setFont(ArialMT_Plain_24);
      display.setTextAlignment(TEXT_ALIGN_LEFT); // The coordinates define the center of the screen!
      display.drawString(xpos%128,40,"-");
      display.display();
    }
  }
  
  Serial.println();
  Serial.println("closing connection");

}

void loop() {
  //display.clear();  // clear the display
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  drawDemo();
  xpos = xpos + 2;
}


