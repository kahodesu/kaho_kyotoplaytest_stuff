////////////////////////////////////////////////////////////////////////////////////////
//                                TOUCH by Kaho Abe                                   //
// this code is for the kyotoplaytest installation                                    //
// reference circuit: https://www.instructables.com/Make-a-Musical-Bench-1/           //
//                                                                                    //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////LIBRARIES///////////////////////
#include "Timer.h"
#include "MIDIUSB.h"

/////////////////////VARIABLES///////////////////////
const int initThreshold = 1014;  // when you want to start calculating values
const int loopDelay = 10; //how long you want the delay at the end of the loop
const int triggerEnd = 100;         //how long it might take

//threshholds for loop modes
const int introThreshold = 1000;
const int moodThreshold = 900;
const int harmonicThreshold = 800;
const int fillThreshold = 600;
const int secretThreshold = 0;// 0 to 599

//pins
const int tablePin = A0; //the reading pin for the table
const int seat1Pin = 22; //the pin for the cushion
const int seat2Pin = 23; //the pin for the other cushion
//const int resetPin = ; //the pin to reset the Arduino

int seat1State = 0;
int seat2State = 0; 
short value = 0;
bool lastContactState = false; 

//timers
Timer tapHoldTimer(1000); 
bool tapHoldFlag = false; 

//LOOP MODE. Loops I need: intro, mood, harmonic, fill, outro
#define NOTHING 0
#define INTRO 1
#define MOOD 2
#define HARMONIC 3
#define FILL 4
#define OUTRO 5
#define SECRET 6

int loopMode = NOTHING;

///////////////////// FUNCTIONS ///////////////////////
void timer() {
//https://github.com/sstaub/Timer installed this... 
//probably need two kind of timers

// ---- timer for the ending the experience when it is abandoned
//if the seats were occupied but are no longer occupied, 
//and a certain amount of time has passed
//then go to outro and shut down sound
//reset arduino

//--- timer for ending when engaged for a long time in a holding state
//Also if there is a long hold and the long hold continues
//go thru all the stages
//and then if it's is past a max then go to outro and shut down sound
//reset arduino
//i think this part has to do with a certain total amount of time in a long hold maybe? 
}


//function to see how much free memory there is available on chip
//i am worried about running out of memory and if i need to set up a reset program after each use, etc. 
// FOR DEBUGGING - uncomment later! //
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

//function to read all the sensors
void readMe(){ 
  value = analogRead(A0);
  seat1State = digitalRead(seat1Pin);
  seat2State = digitalRead(seat2Pin);
  
  // FOR DEBUGGING - uncomment later! //
  Serial.print("seats: " + seat1State);
  Serial.print("\t" + seat2State);
  Serial.print("\t sensor: " + value); // to see what the values are in serial monitor
  Serial.print("\t");

  Serial.print("Free RAM: ");
  Serial.println(freeRam());
}

//function returns true if both people are sitting
bool sittingState() { //for this to be true both cushions have to be sat upon
  if (seat1State == 1 && seat2State == 1){
    return true;
  }
  else {
    return false;
  }
}

// function checks if it is a tap or a hold
// fuck, i need to figure out a way of recognizing if it is a tap or hold
void tapHold() { 
   if (value < initThreshold) { //if there is contact
    if ( tapHoldFlag == false) { //this happens at the beginning
      tapHoldFlag = true;
      tapHoldTimer.start();
    }    
    else {
      if(timer.state() == STOPPED) {
        //it is a hold;
      }
  else { //if there is no contact
     


  }
      //check the timer is still going on
      //otherwise it is a tap!
    }
  
  
   }

   
    //during the first time, start timer
    //if it's the second time then just keep in mind what was happening before
    //if status changes before time runs out then it's a tap
    //otherwise it is a hold. 
   
  }

  // first recognize when there is initial contact/circuit
  // start a timer
  // just need to know last loop had contact and then checks for contact this time around
  // if it  is still in contact after timer is done then it is a hold
  // otherwise it is a tap
  // reset 

}


///////////////////// SETUP ///////////////////////
void setup() { //happens once at the beginning of the program. 
  Serial.begin(115200);
  pinMode(tablePin, INPUT); //table pads
  pinMode(seat1Pin, INPUT); //cushion 1 
  pinMode(seat2Pin, INPUT); //cushion 2
}
///////////////////// LOOP ///////////////////////
void loop() { //happens over and over again 
  readMe();
 // if (value < initThreshold) 
  delay(loopDelay);  //

  //Remember the contact State for next time
  lastContactState = sittingState();
}