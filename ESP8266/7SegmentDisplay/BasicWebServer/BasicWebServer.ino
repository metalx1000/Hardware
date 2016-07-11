#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "LedControl.h"
// Arduino Pin 5 to DIN, 4 to Clk, 2 to LOAD, no.of devices is 1
LedControl lc = LedControl(5, 4, 2, 1);

const char* ssid = "Station 47";
const char* password = "nnfdla47";

ESP8266WebServer server(80);

const int led = 13;

void msg(int p,char m){
  //lc.clearDisplay(0); // Clear dsplay register
  lc.setChar(0, p, m, false);
}

void digits2screen(){
    lc.clearDisplay(0); // Clear dsplay register
    //serChar needs single ' not double "
    lc.setChar(0, 6, 'E', false);
    lc.setDigit(0, 5, 5, false);
    lc.setChar(0, 4, 'P', false);
    lc.setDigit(0, 3, 8, false);
    lc.setDigit(0, 2, 2, false);
    lc.setDigit(0, 1, 6, false);
    lc.setDigit(0, 0, 6, false);
}

void handleRoot() {
  lc.clearDisplay(0);
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "msg") {
        server.send(200, "text/plain", server.arg(i));
      }if (server.argName(i) == "char") {
        String a = server.arg(i);
        server.send(200, "text/plain", a);
        int pos = 0;
        for(int p = a.length() - 1; p >=  0; p--){
          msg(pos,a.charAt(p));
          pos++;
        }
      }
    }
  } else{
    digitalWrite(led, 1);
    server.send(200, "text/plain", "hello from esp8266!");
    digitalWrite(led, 0);
    digits2screen();
  }
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
  
}

void setup(void){
  // Initialize the MAX7219 device
  lc.shutdown(0, false); // Enable display
  lc.setIntensity(0, 10); // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0); // Clear dsplay register
    
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
