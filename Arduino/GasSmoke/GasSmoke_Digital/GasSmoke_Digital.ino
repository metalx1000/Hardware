/* GAS Sensor MQ-2
This sensor detects flammable gasses
the board has four pins
connect AO to Arduino pin A0
connect DO to Arduino pin 2
connect Gnd to Arduino Gnd
connect Vcc to Arduino 5 volts
*/

int sensorPin = A0; // select the input pin for the potentiometer
int DOPin = 2; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
int ledPin =13;

void setup() {
// declare the ledPin as an OUTPUT:
pinMode(DOPin, INPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}


void loop() {
// read the value from the sensor:
sensorValue = analogRead(sensorPin);
Serial.print("Analog Output = ");
Serial.println(sensorValue);
// turn the ledPin on if triggered
//
if (digitalRead(DOPin) ==HIGH){
digitalWrite(ledPin, LOW);
Serial.println("Digital Output = OFF");
}
else {
digitalWrite(ledPin, HIGH);
Serial.println("Digital Output = ON");
}
delay(1000);
}
