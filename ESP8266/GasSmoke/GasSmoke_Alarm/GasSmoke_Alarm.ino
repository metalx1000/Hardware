/* GAS Sensor MQ-2 Module for ESP8266
This sensor detects flammable gasses
the board has four pins
connect DO to Arduino pin 2
connect Gnd to Arduino Gnd
connect Vcc to Arduino 5 volts
Digital Pins can only be High/Low(on/off)
So we don't know how much Smoke/Gas is in the sensor,
but we can set a threshold and send an alert.
threshold will be set by potentiometer screw on board
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = ".....";
const char* password = ".....";

ESP8266WebServer server(80);

int sensorPin = A0; // select the input pin for the potentiometer
int DOPin = 2; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
String alert = "OFF"; //sets to 1 if Gas/Smoke detected

void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html>\
<html>\
<head>\
<script src='https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js'></script>\
<script>\
$(document).ready(function(){\
setInterval(function(){\
$.get('alert',function(data){\
$('h1').html(data);\
});\
}, 1000);\
});\
</script>\
</head>\
<body>\
<h1>OFF</h1>\
</body>\
</html>");
}

void handleNotFound(){
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

}

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(DOPin, INPUT);
  Serial.begin(9600);

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

  server.on("/alert", [](){
    server.send(200, "text/plain", alert);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  //check sensor
  if (digitalRead(DOPin) ==HIGH){
    alert = "OFF"; //reset if smoke/gas clears
    Serial.println("Digital Output = OFF");
  }
  else {
    alert = "ON"; //set to "ON" (true/high) if smoke/gas detected
    Serial.println("Digital Output = ON");
  }
  //Webserver
  server.handleClient();
  delay(1000);
}
