#include "MIDIUSB.h"
#include <arduino-timer.h>
#include "SimpleTimer.h"

auto timer = timer_create_default();
const int melodyNotes[] = {0, 1, 2, 3, 4};
const int melodyVelocity[] = {0, 0, 0, 0, 0};
const int loopNotes[] = {0, 1, 2, 3, 4};
const int loopNotesVelocity[] = {127, 127, 127, 127, 127};
const int loop_length = 12000;

/////////////////////VARIABLES///////////////////////
const int initThreshold = 600;  // when you want to start calculating values
const int loopDelay = 100; //how long you want the delay at the end of the loop

const int triggerEnd = 100;         //how long it might take
const int tapHoldThreshold = 300; //300


//pins
const int tablePin = A0; //the reading pin for the table
//const int resetPin = ; //the pin to reset the Arduino

short value = 0;

//timers
SimpleTimer tapHoldTimer; 
bool tapHoldFlag = false; 

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

void readMe(){ 
  value = analogRead(A0);
  //Serial.println(value);
}

void tapHold() { 
  //NO CONTACT

  if (value >= initThreshold) {
    if (!tapHoldTimer.isReady() && tapHoldFlag == true){ //first check if there was contact before

      //================Serial.println("tap!");  


    }
  tapHoldFlag = false;
  return;
  }
  //  CONTACT 
  else if (value < initThreshold) { //if there is contact
    //Serial.println(value);
    if (tapHoldFlag == false) { //this happens once at the beginning of contact
      tapHoldTimer.reset();
      tapHoldTimer.setInterval(tapHoldThreshold);
      tapHoldFlag = true;
      //return;
      //Serial.println("timer started!"); 

      //=============Serial.println("timer started!"); 
      return;

    }
    else if (tapHoldFlag == true){
      if (tapHoldTimer.isReady()){
        //==============Serial.println("holding");
       midiNoteOn(0, melodyNotes[2], melodyVelocity[127]); // Melody on channel 0
        MidiUSB.flush();
       midiNoteOn(0, melodyNotes[3], melodyVelocity[127]); // Melody on channel 0
        MidiUSB.flush();
        return;       
      }

      return;
    }
     
  } 
}

void setup() { //happens once at the beginning of the program. 
  Serial.begin(115200);
  pinMode(tablePin, INPUT); //table pads
  timer.every(loop_length, run_samples);
}

void loop() { //happens over and over again 
  readMe();
  tapHold();
  timer.tick();
  delay(loopDelay); 
}
