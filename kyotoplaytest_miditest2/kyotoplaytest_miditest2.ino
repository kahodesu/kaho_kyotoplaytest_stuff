//Test to show that all loops can be run at once from Arduino and then kept on a timer to be triggered when the loop is over. It sounds suprisingly seamless. 

#include "MIDIUSB.h"
#include <arduino-timer.h>

auto timer = timer_create_default();
const int melodyNotes[] = {0, 1, 2, 3, 4};
const int melodyVelocity[] = {0, 0, 0, 0, 0};
const int loop_length = 12000;


/////FUNCTIONS//////

// void sendProgramChange(byte channel, byte program) {
//   midiEventPacket_t programChange = {0x0C, 0xC0 | channel, program, 0};
//   MidiUSB.sendMIDI(programChange);
//   MidiUSB.flush(); // Ensure the MIDI message is sent immediately
// }
// 
void midiNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void midiNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

bool run_samples(void *) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED 
  for (int i = 0; i < 5; i++) {
  
  midiNoteOn(0, melodyNotes[i], melodyVelocity[i]); // Melody on channel 0
  MidiUSB.flush();
  }
  return true; // repeat? true
}

void setup() {
  Serial.begin(115200);
  timer.every(loop_length, run_samples);
}

void loop() {
  timer.tick();
}
