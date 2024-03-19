#include "MIDIUSB.h"

// Melody notes and durations
//const int melodyNotes[] = {60, 62, 64, 65, 67, 65, 64, 62}; // C D E F G F E D
const int melodyNotes[] = {0, 1, 2, 3, 4, 1, 3, 3};
const int melodyDurations[] = {2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};

// Rhythm patterns (using MIDI note numbers for percussion)
// Note: 35 (Acoustic Bass Drum) or 36 (Bass Drum 1) can be used for a basic bass drum sound
const int rhythmNotes[] = {24, 24, 24, 24}; // Simple bass drum pattern
const int rhythmDurations[] = {1000, 1000, 1000, 1000}; // Rhythm durations
 
/////FUNCTIONS//////

void sendProgramChange(byte channel, byte program) {
  midiEventPacket_t programChange = {0x0C, 0xC0 | channel, program, 0};
  MidiUSB.sendMIDI(programChange);
  MidiUSB.flush(); // Ensure the MIDI message is sent immediately
}

void midiNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void midiNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void setup() {

  Serial.begin(115200);
  //sendProgramChange(3, 0);
}

void loop() {
  int melodyLength = sizeof(melodyNotes) / sizeof(int);
  int rhythmLength = sizeof(rhythmNotes) / sizeof(int);

  for (int i = 0; i < max(melodyLength, rhythmLength); i++) {
    if (i < melodyLength) {
      // Play melody note
     // sendProgramChange(0, 0);
      midiNoteOn(0, melodyNotes[i % melodyLength], 127); // Melody on channel 0
      MidiUSB.flush();
    }
    
    if (i < rhythmLength) {
      //sendProgramChange(3, 1);
      // Play rhythm note
      midiNoteOn(0, rhythmNotes[i % rhythmLength], 127); // Rhythm on channel 9 (10 in MIDI standard)
      MidiUSB.flush();
    }

    delay(min(melodyDurations[i % melodyLength], rhythmDurations[i % rhythmLength]));

    if (i < melodyLength) {
      // Stop melody note
      //sendProgramChange(0, 0);
      midiNoteOff(0, melodyNotes[i % melodyLength], 0);
      MidiUSB.flush();
    }
    
    if (i < rhythmLength) {
      // Stop rhythm note
      //sendProgramChange(3, 1);
      midiNoteOff(0, rhythmNotes[i % rhythmLength], 0);
      MidiUSB.flush();
    }

    // Adjust the delay to control the tempo and synchronization between melody and rhythm
    delay(250); // Short delay to separate the notes slightly
  }

  // Wait a bit before starting the loop over again
  delay(1000);
}
