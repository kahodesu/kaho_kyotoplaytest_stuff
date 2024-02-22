#include "SimpleTimer.h"

/////////////////////VARIABLES///////////////////////
const int initThreshold = 1014;  // when you want to start calculating values
const int loopDelay = 100; //how long you want the delay at the end of the loop
const int tapHoldThreshold = 300;

//pins
const int tablePin = A0; //the reading pin for the table
//const int resetPin = ; //the pin to reset the Arduino

short value = 0;

//timers
SimpleTimer tapHoldTimer; 
bool tapHoldFlag = false; 

void readMe(){ 
  value = analogRead(A0);
}

void tapHold() { 
  //NO CONTACT
  if (value >= initThreshold) {
    if (!tapHoldTimer.isReady() && tapHoldFlag == true){ //first check if there was contact before
      Serial.println("tap!");  
    }
  tapHoldFlag = false;
  return;
  }
  //  CONTACT 
  else if (value < initThreshold) { //if there is contact
    if (tapHoldFlag == false) { //this happens once at the beginning of contact
      tapHoldTimer.reset();
      tapHoldTimer.setInterval(tapHoldThreshold);
      tapHoldFlag = true;
      Serial.println("timer started!"); 
      return;
    }
    else if (tapHoldFlag == true){
      if (tapHoldTimer.isReady()){
        Serial.println("holding");
        return;
      }
      Serial.println("--");
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
