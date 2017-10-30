const int buttonPin = 0;     // D3 on Wemos is GPIO0
const int ledPin =  2;       // D4 on the Wemos is the builtin LED - GPIO2
int t = 0;                   // Prevents false presses by counting loops while button is pressed
int tl = 50;                // Number of loops before button is pressed
int d = 1000;                //delay between presses to prevent triggering more than once

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(115200);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
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
      delay(d);
    }else{
      t++;
    }
  }

  
}
