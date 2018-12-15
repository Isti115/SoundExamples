/*
  Simple MIDI player for SoftwareSerial

  Generates a series of MIDI notes.
   The melody is Steve Reich's "Piano phase"

  Uses SoftwareSerial for MIDI, so will work on any 
  328 or 32U4-based board (e.g. Uno, Leonardo, Micro, Yún)
 
  Circuit:
    connect TX of SoftwareSerial (pin 3) to TX pin of MIDI jack
 
  created 13 Feb 2017
  modified 13 Dec 2018
  by Tom Igoe
*/

#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2, 3); // 2 is RX, 3 is TX

int bpm = 72;  // beats per minute
// duration of a beat in ms
float beatDuration = 60.0 / bpm * 1000;   

// the melody sequence:
int melody[] = {64, 66, 71, 73, 74, 66, 64, 73, 71, 66, 74, 73};
// which note of the melody to play:
int thisNote = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // initialize MIDI serial:
  midiSerial.begin(31250);
}

void loop() {
  // play a note from the melody:
  midiCommand(0x90, melody[thisNote], 127);
  // all the notes in this are sixteenth notes, 
  // which is 1/4 of a beat, so:
  int noteDuration = beatDuration / 4;
  // I like when the note is on 60% of the note time:
  delay(noteDuration);
  // turn the note off:
  midiCommand(0x80, melody[thisNote], 127);
  // increment the note number for next time through the loop:
  thisNote++;
  // keep the note in the range from 0 - 12 using modulo:
  thisNote = thisNote % 12;
}

// send a 3-byte midi message
void midiCommand(byte cmd, byte data1, byte  data2) {
  midiSerial.write(cmd);     // command byte (should be > 127)
  midiSerial.write(data1);   // data byte 1 (should be < 128)
  midiSerial.write(data2);   // data byte 2 (should be < 128)
}
