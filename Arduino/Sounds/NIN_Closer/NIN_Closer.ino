/*
  NIN Closer
 GPLv3 - August 17th, 2016
 Plays The Medoly from the end of Closer by Trent Reznor
 Created by Kris Occhipinti
 
 Based on code by Tom Igoe
 Connect Speaker to Pin#8 and Ground on your Arduino  

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_C4, NOTE_C3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 1, 2, 1, 2, 1, 4, 4, 4, 4, 1
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 11; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
