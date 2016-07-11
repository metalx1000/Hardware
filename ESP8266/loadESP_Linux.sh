#!/bin/bash
#ESP8266 Basic Arduino IDE setup
#pin layout diagram
xdg-open "http://www.cnx-software.com/wp-content/uploads/2015/10/NodeMCU_v0.9_Pinout.png"
#Instructions from
xdg-open "http://www.whatimade.today/esp8266-easiest-way-to-program-so-far/"

#download the latest IDE - https://www.arduino.cc/en/Main/Software
wget "https://downloads.arduino.cc/arduino-1.6.9-linux64.tar.xz" -O arduinoIDE.tar.xz

#extract
tar xf arduinoIDE.tar.xz
cd arduino-*

echo "Go to File --> Preferences and add the link http://arduino.esp8266.com/stable/package_esp8266com_index.json to the Additional Boards Manager URLS."
echo "Then Go to Tools --> Board --> Boards manager and search for esp"
./arduino

./.arduino15/packages/esp8266/hardware/esp8266/2.3.0/cores/esp8266/
#Pin 16 is the on board LED
#The default Blink program example for the ESP8266 has the wrong pin set for this model
####Hold Down Flash button on board until uploading starts###
