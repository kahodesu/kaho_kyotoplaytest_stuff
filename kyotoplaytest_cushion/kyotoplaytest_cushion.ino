#include "MIDIUSB.h"

//ARM REST PINS
static const uint8_t lightPins[] = {A0, A1}; //P1: R, L, P2: R, L
int lightPinCount = 2;
int lightState[] = {0,0};

//CUSHIONS PINS
int cushionPins[] = {2,3,4,5,8,9,10,11}; //P1: RF, RB, LF, LB, P2: RF, RB, LF, LB
int cushionPinCount = 8;
int cushionState[] = {0,0,0,0,0,0,0,0};
int lastCushionState[] = {0,0,0,0,0,0,0,0};


//////////////CASES////////////////
#define REST 0 //
#define INTRO 1 //
#define MINIMAL 2 

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
  for (int thisPin = 0; thisPin < cushionPinCount; thisPin++) {
    pinMode(cushionPins[thisPin], OUTPUT);
  }
  for (int i = 0; i < lightPinCount; i++) { //or i <= 4
     pinMode(lightPins[i], INPUT);
  }
}

void loop() {
  // noteOn(0, 2, 127); // Melody on channel 0
  // MidiUSB.flush();
  // //Serial.println("boo");
  // delay(2000);

  //////////////////// HANDS CHECK! /////////////////////
  //read all the photo resistors
  for (int i = 0; i < lightPinCount; i++) { 
    lightState[i] = analogRead(lightPins[i]);
   // Serial.print ("light sensors:");
    //Serial.println(lightState[i]);
  }
  //if the arms are on the rests then this is where everything happens!!!!!!!
  if (lightState[0] < 10 && lightState[1] < 10 ){
    
    /////////// CHECK ALL THE CUSHIONS //////////////////
    for (int thisPin = 0; thisPin < cushionPinCount; thisPin++) {
      cushionState[thisPin] = digitalRead(cushionPins[thisPin]);
      if (lastCushionState[thisPin] == 0 && cushionState[thisPin] == 1) {
        //send midi signal to play sound 
        noteOn(0, thisPin, 127); // Melody on channel 0
        MidiUSB.flush();
        //delay(100);
      }
    }
  }
  for (int thisPin = 0; thisPin < cushionPinCount; thisPin++) {
    lastCushionState[thisPin] = cushionState[thisPin];
  }
 delay(100);
}

