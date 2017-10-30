/*
 * Basic Wemos Pushbutton WebClient
 * Part of the software package: https://github.com/metalx1000/Hardware
 * Code by Kris Occhipinti
 * https://filmsbykris.com
 * copyright October 2017
 * Licensed under the GPLv3
 * https://www.gnu.org/licenses/gpl-3.0.txt
 * 
 * 
 *  This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */


#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;


const int buttonPin = 0;     // D3 on Wemos is GPIO0
const int ledPin =  2;       // D4 on the Wemos is the builtin LED - GPIO2
int t = 0;                   // Prevents false presses by counting loops while button is pressed
int tl = 50;                // Number of loops before button is pressed
int d = 1000;                //delay between presses to prevent triggering more than once
int buttonState = 0;         // variable for reading the pushbutton status

//URL to connect to
String url = "http://192.168.1.150:8080/cgi-bin/test.cgi";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("castle", "5987cb800f");
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);    

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void sendPress(){
  Serial.print("Requesting URL: ");
  Serial.println(url);
  HTTPClient http;

  http.begin(url); //HTTP
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    Serial.println("Connected...");

    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("The Server says:");
      Serial.print(payload);
    }
  } else {
    String errorCode = http.errorToString(httpCode).c_str();
    Serial.println(errorCode);
  }

  http.end();  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if button is pressed.
  //button not pressed
  if (buttonState == HIGH) {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
    t=0;
    //Serial.println("High");
    //button pressed
  } else {
    //if button is pressed for long enough then trigger
    if(t == tl){
      // turn LED on:
      digitalWrite(ledPin, LOW);
      Serial.println("Button Pressed");
      //Connect to server
      sendPress();
      delay(d);
    }else{
      //count loops while button is pressed
      t++;
    }
  }

}
