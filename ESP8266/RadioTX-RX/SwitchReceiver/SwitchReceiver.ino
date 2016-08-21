/*
  Code by Kris Occhipinti
  Flip switch on RF signal
  GPLv3 August 21, 2016
  http://filmsbykris.com
  Based on library https://github.com/sui77/rc-switch/

  Switch output GPIO#13 - D7
  RF recevier GPIO#0 - D3
  
*/


#include <RCSwitch.h>
int pinSW = 13; //Our Swith ESP D7
int led = 16;

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(pinSW, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Welcome");
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is D3 or GPIO pin #0
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      if(mySwitch.getReceivedValue() == 89347){
        Serial.println("Unlock");
        digitalWrite(pinSW, HIGH);
        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(2000);              // wait for a second
        digitalWrite(pinSW, LOW);
        digitalWrite(led, LOW);// turn the LED off by making the voltage LOW
        delay(1000);
      }
    }

    mySwitch.resetAvailable();
  }
}
