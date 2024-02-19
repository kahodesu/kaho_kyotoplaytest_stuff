////////////////////////////////////////////////////////////////////////////////////////
//                                AnalogCheck by Kaho Abe                             //
// this code is for the kyotoplaytest installation                                    //
// to use to check sensors and switches in project                                    //
////////////////////////////////////////////////////////////////////////////////////////


/////////////////////VARIABLES///////////////////////
const int initThreshold = 1014;  // when you want to start calculating values
const int loopDelay = 10; //how long you want the delay at the end of the loop

//pins
const int tablePin = A0; //the reading pin for the table
const int seat1Pin = 22; //the pin for the cushion
const int seat2Pin = 23; //the pin for the other cushion
//const int resetPin = ; //the pin to reset the Arduino

int seat1State = 0;
int seat2State = 0; 
short value = 0;

///////////////////// FUNCTIONS ///////////////////////

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

}