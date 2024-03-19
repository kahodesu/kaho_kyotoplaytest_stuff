#include "SimpleTimer.h"

/////////////////////VARIABLES///////////////////////
const int initThreshold = 1000;  // when you want to start calculating values
const int loopDelay = 100; //how long you want the delay at the end of the loop
const int triggerEnd = 100;         //how long it might take
const int tapHoldThreshold = 350; //300

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
SimpleTimer tapHoldTimer; 
bool tapHoldFlag = false; 
bool holdingFlag = false;

void readMe(){ 
  value = analogRead(A0);
}


void tapHold() { 
  if (value >= initThreshold) { //if no contact
    if (!tapHoldTimer.isReady() && tapHoldFlag == true){ //first check if there was contact before
      //Serial.println("tap!");  
      Serial.write(1);
    }
  tapHoldFlag = false;
  return;
  }
  else if (value < initThreshold) { //if there is contact
    //Serial.println(value);
    if (tapHoldFlag == false) { //this happens once at the beginning of contact
      tapHoldTimer.reset();
      tapHoldTimer.setInterval(tapHoldThreshold);
      tapHoldFlag = true;
      //return;
      //Serial.println("timer started!"); 
    }
    else if (tapHoldFlag == true){
      if (tapHoldTimer.isReady()){
        //Serial.println("holding");
       Serial.write(2);
        return;       
      }
      //Serial.println("--");
      return;
    }
     
  } 
}


void setup() { //happens once at the beginning of the program. 
  Serial.begin(115200);
    pinMode(tablePin, INPUT); //table pads
}

void loop() { //happens over and over again 
  readMe();
  tapHold();
  delay(loopDelay); 
}
