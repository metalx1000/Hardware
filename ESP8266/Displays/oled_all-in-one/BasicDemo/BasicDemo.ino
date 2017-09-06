// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

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
    
  Serial.println(); 

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
}

void drawDemo() {
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER); // The coordinates define the center of the screen!
  display.drawString(xpos%725/2-100,0,"Hello World");

  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT); // The coordinates define the center of the screen!
  display.drawString(0,24,"FilmsByKris.com");

  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_LEFT); // The coordinates define the center of the screen!
  display.drawString(xpos%128,40,"-");
}

void loop() {
  display.clear();  // clear the display
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  drawDemo();
  display.display();
  delay(10);
  xpos = xpos + 2;
}


