#include "MIDIUSB.h"
#include <arduino-timer.h>

auto timer = timer_create_default();
const int loop_length = 2000;


int centerDrawer = A0;   // center drawer
int leftDrawer = A1;   // left drawer
int rightDrawer = A2;   // right drawer
int CD = 0;  // variable to store the value coming from the sensor
int LD = 93;  // variable to store the value coming from the sensor
int RD = 0;  // variable to store the value coming from the sensor
int volume = 0;
int pitchBend = 0;
int lastRD = 0;

// void sendProgramChange(byte channel, byte program) {
//   midiEventPacket_t programChange = {0x0C, 0xC0 | channel, program, 0};
//   MidiUSB.sendMIDI(programChange);
//   MidiUSB.flush(); // Ensure the MIDI message is sent immediately
// }

void midiNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void midiNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void readMe(){
  // read the value from the sensor:

  CD = map(analogRead(centerDrawer), 0, 1023, 0, 220);
  if (CD >127)  CD=127;

  LD = map(analogRead(leftDrawer), 0, 1023, 93, 120);
  if (LD >97) LD =97;


  RD = map(analogRead(rightDrawer), 0, 1023, 0, 220);
  if (RD >127)  RD=127;

  // Serial.print("center drawer:");
  // Serial.print(CD);
  // Serial.print(" left drawer:");
  // Serial.print(LD);
  // Serial.print(" right drawer:");
  // Serial.println(RD);
}

bool run_samples(void *) {
  //Serial.println("playme!!)");
  midiNoteOn(0, LD, CD); // Melody on channel 0
  MidiUSB.flush();
  midiNoteOn(0, 98, RD); // Melody on channel 0
    MidiUSB.flush();
  return true; // repeat? true
}


void setup() {
  Serial.begin(115200);
  timer.every(loop_length, run_samples);
}

void loop() {
  readMe();
  timer.tick();
  delay(100);
}


