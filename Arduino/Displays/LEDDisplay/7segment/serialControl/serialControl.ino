#include "LedControl.h"
String inString = "";
int pos = 0;
// Arduino Pin 12 to DIN, 11 to Clk, 10 to LOAD, no.of devices is 1
LedControl lc = LedControl(12,11,10,1);
void setup() {
    Serial.begin(115200);
    // Initialize the MAX7219 device
    lc.shutdown(0, false); // Enable display
    lc.setIntensity(0, 10); // Set brightness level (0 is min, 15 is max)
    lc.clearDisplay(0); // Clear display register
    for (int i = 0; i < 8; i++) {
        lc.setDigit(0, i, i + 1, false);
    }
}
void loop() {

    // send data only when you receive data:
    if (Serial.available() > 0) {
        int inChar = Serial.read();
        if (isDigit(inChar)) {
            inString = (char) inChar;
        }

        if (inChar == '\n') {
            int x = inString.toInt();
            Serial.print("I received: ");
            Serial.println(x);
            lc.setDigit(0, pos, x, false);
            pos++;
            if (pos > 7) {
                pos = 0;
            }
        }
    }
}

//To connect through Linux Shell
//stty raw -echo < /dev/ttyUSB0 #activate connection
//while [ 1 ];do for i in `seq 0 9`;do for x in `seq 0 9`;do echo $i > /dev/ttyUSB0;sleep .05;done;done;done #this loops through all digits
