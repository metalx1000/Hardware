/***************************************************
Pinout for Arduino:
VCC - 5v
GND - GND
CS - pin #10
RESET - pin #9
AD - pin #8
SDA - pin #11
SCK - ping #13
LED - 3.3v


 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  //Rotate screen
  tft.setRotation(1);
  // tft print function!
  tftPrintTest();
  delay(500);


}

void loop() {
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}



void tftPrintTest() {
  tft.setRotation(1);
  String txt = "Films By Kris";
  tft.setTextWrap(false);
  //tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.println(txt);
  delay(500);
  tft.setTextColor(ST7735_WHITE);
  tft.println(txt);
  delay(500);
  tft.setTextColor(ST7735_YELLOW);
  tft.println(txt);
  delay(500);
  tft.setTextColor(ST7735_BLUE);
  tft.println(txt);
  delay(500);
  tft.setTextColor(ST7735_GREEN);
  tft.println(txt);
  delay(500);
  tft.setTextColor(ST7735_WHITE);
  tft.println("");
  tft.println("   DOT COM");
  delay(2000);  
}


