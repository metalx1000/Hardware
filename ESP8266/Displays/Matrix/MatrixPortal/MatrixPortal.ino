/*
   Captive Port Dot Matrix By Kris Occhipinti - http://filmsbykris.com 08/26/2016
   Original Captive Portal by: M. Ray Burnette 20150831
   See Notes tab for original code references and compile requirements
*/
#include <MaxMatrix.h>
#include <pgmspace.h>
#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>
#include "chars.h"

const int led = 2;
 

int data = 12;    // DIN pin of MAX7219 module - D6
int load = 13;    // CS pin of MAX7219 module  - D7
int clock = 15;  // CLK pin of MAX7219 module  - D8
 
int maxInUse = 2;  //how many MAX7219 are connected
 
MaxMatrix m(data, load, clock, maxInUse); // define Library
 
byte buffer[10];
 
char* string1 = "    Ember to Mission Control   ";  // Default Scrolling Text


const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

/* Set these to your desired credentials. */
const char *ssid = "Matrix";
//const char *password = "...";

String responseHTML = ""
                      
                      "<!DOCTYPE html><html><head><title>Virus Detected</title><meta name='viewport' content='width=device-width, initial-scale=1.0'></head>\n"
                      "<body><h1>Your Computer Is Now Infected!!!</h1><p>You are Welcome.</p></body>\n"
                      "<script>alert('Virus Found');</script>\n"
                      "</html>\n";




void updateText() {

}

void portal(){
  //webServer.send(200, "text/html", responseHTML);
  digitalWrite(led, 1);
  
  if (webServer.args() > 0 ) {
    for ( uint8_t i = 0; i < webServer.args(); i++ ) {
      if (webServer.argName(i) == "msg") {
        strcpy (string1,webServer.arg(i).c_str());

        webServer.send(200, "text/plain", webServer.arg(i));
      }
    }
  } else{
    string1="    Mission Control to Ember   ";
    webServer.send(200, "text/plain", "");
  }

  digitalWrite(led, 0);  
}

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound(portal);

  
  webServer.on("/update", updateText);
  
  webServer.begin();

  m.init(); // module MAX7219
  m.setIntensity(5); // LED Intensity 0-15
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
}

void loop() {
  dnsServer.processNextRequest();
  byte c;
  delay(100);
  m.shiftLeft(false, true);
  printStringWithShift(string1, 100);  // Send scrolling Text
  webServer.handleClient();
}


// Put extracted character on Display
void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(maxInUse*8, 0, buffer);
  m.setColumn(maxInUse*8 + buffer[0], 0);
  
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
    webServer.handleClient();
  }
  
}
 
// Extract characters from Scrolling text
void printStringWithShift(char* s, int shift_speed){
  while (*s != 0){
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
