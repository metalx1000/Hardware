/*
 * ESP Code for 1.8" TFT SPI Display
 * This code is not working correctly yet.
 * Use the Adafruit_ILI9340 that came with this code
 * at the time of writing this the Adafruit_ILI9340 lib 
 * that is supplied by Arduino doesn't work at all
 * (although maybe it does by the time you are reading this)
 * 
 * Pinout:
 * LED - 3.3V
 * SCK - D5 - GPIO #14
 * SDA - D7 - GPIO #13
 * AO - D4 - GPIO #02 
 * RESET - RST
 * CS - D1 - GPIO #5
 * GND - GND
 * VCC - 3.3V
 */
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define _sclk 14
#define _miso 12
#define _mosi 13
#define _cs 15
#define _dc 2
#define _rst 4

// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

void setup() {
  Serial.begin(9600);
  
  Serial.println("Adafruit 2.2\" SPI TFT Test!"); 
  
  tft.begin();
  //testFillScreen();
  delay(2000);
}

void loop(void) {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(2000);
  }
  //testFillScreen();
}


unsigned long testFillScreen() {
  tft.fillScreen(ILI9340_BLACK);
  tft.fillScreen(ILI9340_RED);
  tft.fillScreen(ILI9340_GREEN);
  tft.fillScreen(ILI9340_BLUE);
  tft.fillScreen(ILI9340_BLACK);
}

unsigned long testText() {
  tft.fillScreen(ILI9340_BLACK);;
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9340_RED);  tft.setTextSize(2);
  tft.println("Films By Kris!");
    tft.setTextColor(ILI9340_GREEN);  tft.setTextSize(1);
  tft.println("Is this Backwards?");

}

