/*
   ESP8266 Blink by Simon Peter
   Blink the blue LED on the ESP-01 module
   This example code is in the public domain
   
   The blue LED on the ESP-01 module is connected to GPIO1 
   (which is also the TXD pin; so we cannot use Serial.print() at the same time)
   
   Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
   Modified for relay by Kris Occhipinti http://filmsbykris.com
*/

const int Relay = 5;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(Relay, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   
  digitalWrite(Relay, LOW);         
                                    
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);  
  digitalWrite(Relay, HIGH);  
  delay(2000);                      
}
