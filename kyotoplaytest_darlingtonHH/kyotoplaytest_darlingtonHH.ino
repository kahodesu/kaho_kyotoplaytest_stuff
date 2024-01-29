////////////////////////////////////////////////////////////////////////////////////////
//                                TOUCH by Kaho Abe                                   //                     
// this code is for the kyotoplaytest installation                                    //
// reference: https://arduino.stackexchange.com/questions/16150/human-circuit-trigger //
////////////////////////////////////////////////////////////////////////////////////////


/////////////////////VARIABLES///////////////////////
const short triggerThreshold = 10;// Lower is more sensitive;
const int triggerEnd = 100; //how long it might take 

///////////////////// FUNCTIONS ///////////////////////
void startmeup() {
 //MIDI code to play droning bass
 //the longer it runs the more it builds
}

void startmeup() {
 //MIDI code to play droning bass

}

///////////////////// SETUP ///////////////////////
void setup() {
  pinMode(A0, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
  delay(1);
}
///////////////////// LOOP ///////////////////////
void loop() {
  short value = analogRead(A0);
  //Serial.print(value);
  Serial.println(value);
  //digitalWrite(A5, (value > triggerThreshold) ? HIGH : LOW);
  delay(100);// 10ms;
}