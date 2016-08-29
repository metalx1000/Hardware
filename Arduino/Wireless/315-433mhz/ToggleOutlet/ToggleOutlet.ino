/*
  Example for different sending methods
  For Zapp Outlet Plugs
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  mySwitch.setPulseLength(185);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {


  /* Same switch as above, but using decimal code */
  mySwitch.send(89347, 24);
  delay(1000);  
  mySwitch.send(89356, 24);
  delay(1000);  


}
