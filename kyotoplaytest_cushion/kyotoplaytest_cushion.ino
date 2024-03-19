//ARM REST PINS
static const uint8_t lightPins[] = {A0, A1, A2, A3}; //P1: R, L, P2: R, L
int lightPinCount = 4;
int lightState[] = {0,0,0,0};

//CUSHIONS PINS
int cushionPins[] = {2,3,4,5,8,9,10,11}; //P1: RF, RB, LF, LB, P2: RF, RB, LF, LB
int cushionPinCount = 8;
int cushionState[] = {0,0,0,0,0,0,0,0};


//////////////CASES////////////////
#define REST 0 //
#define INTRO 1 //
#define MINIMAL 2 //
#define FILLED 3 // 
#define CLIMACTIC 4

void setup() {
  for (int thisPin = 0; thisPin < cushionPinCount; thisPin++) {
    pinMode(cushionPins[thisPin], OUTPUT);
  }
  for (int i = 0; i < lightPinCount; i++) { //or i <= 4
     pinMode(lightPins[i], INPUT);
  }
}

void loop() {

  //////////////////// HANDS CHECK! /////////////////////
  //read all the photo resistors
  for (int i = 0; i < lightPinCount; i++) { 
    lightState[i] = analogRead(lightPins[i]);
  }
  //if the arms are on the rests then this is where everything happens!!!!!!!
  if (lightState[0] >5 && lightState[1] >5 && lightState[2 >5 && lightState[3] >5 ){
    
    /////////// CHECK ALL THE CUSHIONS //////////////////
    for (int thisPin = 0; thisPin < cushionPinCount; thisPin++) {
      cushionState[thisPin] = digitalRead(buttonPin);
    }

    // do something different depending on the range value:
    switch (state) {
      case REST:  // nothing should be happening and cushions should be completely deactivated
        Serial.println("dark");
        break;
      case INTRO:  //cushions should still be deactivated, but the arm rests should have triggered a beat 
        Serial.println("dim");
        break;
      case MINIMAL:  // accomapniment starts, cushions should be able to trigger sounds/melody
        Serial.println("medium");
        break;
      case FILLED:  // more exciting loops
        Serial.println("bright");
        break;
      case CLIMACTIC:  // the most climactic loop
        Serial.println("bright");
        break;
    }

  }
  //if the hands are not on the rests, then demote the state to eventually go to REST state
  else {
    if (state>0) state --; //demote the state if the hands have left the rests, eventually it will turn off
  }
}

