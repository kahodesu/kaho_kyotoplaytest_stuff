/* PROOF OF CONCEPT FOR KYOTOPLAYTEST INSTALLATION*/ 

#include "MIDIUSB.h"
//int sv = 0;
// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {

  // Serial.println(sv);
  // delay(100);

  // Serial.println("Sending note on");
  // noteOn(0, sv, 64);   // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(500);
  // Serial.println("Sending note off");
  // noteOff(0, sv, 64);  // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(500); 
  
// sv = sv + 1;

//for (int i = 30; i <= 39; i++) {
  Serial.println("Sending note on");
  noteOn(0, 37, 64);   // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(1000);
  Serial.println("Sending note off");
  noteOff(0, 37, 64);  // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(1500);

    Serial.println("Sending note on");
  noteOn(0, 54, 50);   // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(500);
  Serial.println("Sending note off");
  noteOff(0, 54, 50);  // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(1500);
  

  //controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}