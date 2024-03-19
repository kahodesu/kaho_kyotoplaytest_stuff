#include "SimpleTimer.h"

/////////////////////VARIABLES///////////////////////
const int initThreshold = 1000;  // when you want to start calculating values
const int loopDelay = 100; //how long you want the delay at the end of the loop
<<<<<<< HEAD
const int triggerEnd = 100;         //how long it might take
const int tapHoldThreshold = 350; //300
=======
const int tapHoldThreshold = 300;
>>>>>>> c07cbefe830ce26db0787f13c5391f5d0ce9cbf1

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
<<<<<<< HEAD
      //Serial.println("tap!");  
      Serial.write(1);
=======
      Serial.println("tap!");  
>>>>>>> c07cbefe830ce26db0787f13c5391f5d0ce9cbf1
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
<<<<<<< HEAD
      //return;
      //Serial.println("timer started!"); 
=======
      Serial.println("timer started!"); 
      return;
>>>>>>> c07cbefe830ce26db0787f13c5391f5d0ce9cbf1
    }
    else if (tapHoldFlag == true){
      if (tapHoldTimer.isReady()){
        //Serial.println("holding");
       Serial.write(2);
        return;       
      }
<<<<<<< HEAD
      //Serial.println("--");
=======
      Serial.println("--");
>>>>>>> c07cbefe830ce26db0787f13c5391f5d0ce9cbf1
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
