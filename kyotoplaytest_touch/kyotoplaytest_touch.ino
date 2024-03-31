#include "MIDIUSB.h"
#include <arduino-timer.h>
#include "SimpleTimer.h"

auto timer = timer_create_default();
const int loopNotes[] = {1,2,3,4};
int loopNotesVelocity[] = {0, 0, 0, 0};
const int loop_length = 16000;
int loopCount = 0; //keeping track of how many times a loop has played

/////////////////////VARIABLES///////////////////////
const int initThreshold = 500;  // 600 start of playtest- when you want to start calculating values
//const int initThreshold = 800;  // when you want to start calculating values
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

#define NOTHING 0 //loopNotesVelocity[] = {0, 0, 0, 0};
#define INTRO 1 //loopNotesVelocity[] = {127, 0, 0, 0};
#define PICK 2 //loopNotesVelocity[] = {0, 127, 0, 0};
#define FLUTE 3 ////loopNotesVelocity[] = {0, 127, 127, 0};
#define EVERYTHING 4 //loopNotesVelocity[] = {0, 127, 127, 127};
#define FLUTEPLUS 5 //loopNotesVelocity[] = {0, 127, 127, 0};
#define JUSTFLUTE 6 //loopNotesVelocity[] = {0, 0, 127, 0};
int state =0;
bool holding = false;
void midiNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void midiNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

bool run_samples(void *) {
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED 
  for (int i = 0; i < 5; i++) {  
    midiNoteOn(0, loopNotes[i], loopNotesVelocity[i]); // Melody on channel 0
    MidiUSB.flush();
  }
  loopCount++; //loop count goes up once it's been played
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

      //Serial.println("tap!");  
      holding = true;
      midiNoteOn(0, random(10, 14), 60);
      MidiUSB.flush();
      return;
    }
    tapHoldFlag = false;
    if (loopCount>3){  
      state = 0;
      loopCount =0;
    }
    return;
  }
  //  CONTACT 
  else if (value < initThreshold) { //if there is contact
    //Serial.println(value);
    //Serial.print ("contact?");
    if (state == 0 || loopCount >2){
      if (state >6){
       state =0;  
      }
      else {
        if (holding ==true) 
        {
          state++;
          loopCount =1;
        }
      }
    }

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
          holding = true;
        //MidiUSB.flush();
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
  switch (state) {
    case NOTHING:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 0;
      loopNotesVelocity[2] = 0;
      loopNotesVelocity[3] = 0;
      break;

    case INTRO:
      loopNotesVelocity[0] = 127;
      loopNotesVelocity[1] = 0;
      loopNotesVelocity[2] = 0;
      loopNotesVelocity[3] = 0;
      break;

    case PICK:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 127;
      loopNotesVelocity[2] = 0;
      loopNotesVelocity[3] = 0;
      break;

    case FLUTE:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 127;
      loopNotesVelocity[2] = 0;
      loopNotesVelocity[3] = 127;
      break;

    case EVERYTHING:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 127;
      loopNotesVelocity[2] = 127;
      loopNotesVelocity[3] = 127;
      break;

    case FLUTEPLUS:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 127;
      loopNotesVelocity[2] = 127;
      loopNotesVelocity[3] = 0;
      break;

    case JUSTFLUTE:
      loopNotesVelocity[0] = 0;
      loopNotesVelocity[1] = 0;
      loopNotesVelocity[2] = 127;
      loopNotesVelocity[3] = 0;
      break;
  }
  tapHold();
  //==============for DEBUG

  // Serial.print ("HOLDING = ");
  // Serial.print (holding);
  // Serial.print ("value = ");
  // Serial.print (value);
  // Serial.print (" loop count = ");
  // Serial.print (loopCount);
  // Serial.print ("  state = " );
  // Serial.println (state);
  //==============
  delay(loopDelay);
  
  timer.tick();
 

  
  

  // #define NOTHING 0 //loopNotesVelocity[] = {0, 0, 0, 0};
  // #define INTRO 1 //loopNotesVelocity[] = {127, 0, 0, 0};
  // #define PICK 2 //loopNotesVelocity[] = {0, 127, 0, 0};
  // #define FLUTE 3 ////loopNotesVelocity[] = {0, 127, 127, 0};
  // #define EVERYTHING 4 //loopNotesVelocity[] = {0, 127, 127, 127};
  // #define FLUTEPLUS 5 //loopNotesVelocity[] = {0, 127, 127, 0};
  // #define JUSTFLUTE 5 //loopNotesVelocity[] = {0, 0, 127, 0};
}
