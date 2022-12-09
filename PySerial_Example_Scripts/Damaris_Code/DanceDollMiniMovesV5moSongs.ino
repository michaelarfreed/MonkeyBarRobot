
#include <Servo.h>

Servo myservo1;  //right  up/down  -->4  3rd from left
Servo myservo2;  //right  open/closed  -->2  1st pin from left
Servo myservo3;  //left   up/down   --> 5   right pin
Servo myservo4;  //left   open/closed  --->3 2nd pin from left

unsigned long currentMillis;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long prevSubMillis = 0; 
unsigned long prevSwayMillis = 0; 
unsigned long motorTimer = 0;
unsigned long subTimer = 0;
unsigned long nowSubTime = 0;
unsigned long swayTimer = 0;
unsigned long nowSwayTime = 0;
unsigned long nowMotorTime = 0;
unsigned long nowArmTime = 0;
unsigned long armTimer = 0;
const long interval = 1500; 
const long subInterval = 1500; 
const long sOffset = 100;
int subDone = 1;
int swaySpeed = 0;
//int swayInterval = 20; 
int swayDone = 1;
int minArmDelay = 10;
int e1 = 0;
int e2 = 0;
int e3 = 0;
int e4 = 0;
int maxError = 0;

int pos = 90;
int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int pos4 = 90;
int target1 = 10;
int target2 = 10;
int target3 = 10;
int target4 = 10;
int currentDir = 90;
int currentPos = 0;
int servoIncrementDelay = 10;
int oldDance = 0;
int newDance = 1;
int CurrentDanceStep = 1;
int NewDanceStep = 1;
int newDir = 0;
int newMove = 0;
int moveChange = 0;
int dirChange = 0;
int dirIncrement = 0;
int moveIncrement = 0;
int newSong = 1;
int oldSong = 1;
int NewSongStep = 1;
int songRequest = 25;  //--> update this
int songRequest1 = 1;
int songRequest2 = 1;
int qfrequency = 700;
//int SwayState = LOW; 

int motorMode = 0;
// 0 = stop, 1=left,2=right,3=forward,4=back
//motorPins
int ledPins[] = {
  10, 9, 8, 7, 6, 1
};       // an array of pin numbers to which LEDs are attached
int pinCount = 6; 
int SwayState = LOW;             // SwayState used to set the LED
unsigned long previousSwayMillis = 0;        // will store last time LED was updated
const long swayInterval = 450;  


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  //MotorPin setup
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }

//  // Set the speed to start, from 0 (off) to 255 (max speed)
//  myMotor->setSpeed(150);  myMotor->run(FORWARD);  myMotor->run(RELEASE);
//  myOtherMotor->setSpeed(150);  myOtherMotor->run(FORWARD);  myOtherMotor->run(RELEASE);
 motorMode = 0;
  myservo1.attach(4);
  myservo2.attach(2);
  myservo3.attach(5);
  myservo4.attach(3); 
  myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos2);
    myservo3.write(pos3);
    myservo4.write(pos4);
    motorTimer = millis(); //reset the timer
    previousMillis = millis(); //reset the timer 
     armTimer = millis();
    swayTimer = millis();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  uint8_t i;
  if(Serial.available() > 1){
    songRequest1 = Serial.read() - '0';
    songRequest2 = Serial.read() - '0';
    songRequest = ( songRequest1 *10) + songRequest2;
  }

   if (songRequest == 21){
    fire();
  } else if (songRequest == 22 ) {
    applause();
  } else if (songRequest == 23 ) {
    rock();
  } else if (songRequest == 24) {
    better();
  } else if (songRequest == 25) {
    findyourthing();
  } else if (songRequest == 26 ) {
    titan();
  } else if (songRequest == 27 ) {
    Great();
  } else if (songRequest == 28 ) {
    Cheap();
  } else if (songRequest == 14 ) {
    price();
  } else if (songRequest == 10 ) {
    Add();
   } else if (songRequest == 11) {
    Roar();    
  } else if (songRequest == 12 ) {
    holdhand();
  } else if (songRequest == 13 ) {
    airplane();
   } else if (songRequest == 19) {
    first2();
  } else if (songRequest == 16) {
    DontWorryBeHappy();
  } else if (songRequest == 18) {
    worrything();
  } else if (songRequest == 15) {
    ymca();
  } else if (songRequest == 17) {
    turnlove();
  } else if (songRequest == 20) {
    WorryChild();
  } else {
    //Roar();
    //Cheap();
    //DontWorryBeHappy();
    //Great();
    testPattern();
  }
//testPattern();

  //currentMillis = millis();   // Feet Refresh Timer

  
  currentMillis = millis();   //Arm Refresh Timer
  nowArmTime = currentMillis - armTimer ;
  if ( nowArmTime > servoIncrementDelay ){
    armTimer = millis(); //reset the timer
    servoIncrement();
  }

  //unsigned long currentMillis = millis();

  if (currentMillis - previousSwayMillis >=swayInterval) {
    // save the last time you blinked the LED
    previousSwayMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (SwayState == LOW) {
      SwayState = HIGH;
      leftTurn();
    } else {
      SwayState = LOW;
      rightTurn();
    }
  }
  //sway();
  //Repeat Motor pattern according to MotorTimer
// 0 = stop, 1=left,2=right,3=forward,4=back
//  currentMillis = millis();
//  nowMotorTime = currentMillis - motorTimer ;
//  if ( nowMotorTime < 10 ){  stopTurn(); target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
//  } else if ( nowMotorTime <  5000 ){ dSub(27,13,23,17); sway(); //arm up 
//  } else if ( nowMotorTime <  9000 ){ dSub(23,12,23,15); sway(); //arm out
//  } else if ( nowMotorTime <  12000 ){dSub(27,13,23,12); sway();  //arm down
//  } else if ( nowMotorTime <  16000 ){dSub(23,12,23,15); sway(); 
//  } else if ( nowMotorTime <  19000 ){dSub(26,14,24,16); sway(); 
//  } else if ( nowMotorTime <  22000 ){dSub(27,13,26,13);  sway(); 
//  } else if ( nowMotorTime <  27000 ){dSub(26,14,24,16);   sway(); 
//  } else {
//    motorTimer = millis(); //reset the timer
//  }
//  servoIncrement(); 
}

void sway(){
//  if (swayDone == 1) {    swayTimer = millis();    swayDone = 0;
//  } 
//  currentMillis = millis();
//  nowSwayTime = currentMillis - swayTimer ;
//  if ( nowSwayTime < 2 ){  stopTurn();  //doesnt have time to get here!
//  } else if ( nowSubTime <  300 ){ leftTurn();   swaySpeed = 75;
//  } else if ( nowSubTime <  500 ){ leftTurn();   swaySpeed = 40;
//  } else if ( nowSubTime <  1000 ){ stopTurn();  swaySpeed = 0;
//  } else if ( nowSubTime <  1300 ){ rightTurn(); swaySpeed = 75;
//  } else if ( nowSubTime <  1600 ){ rightTurn(); swaySpeed = 40;
//  } else if ( nowSubTime <  2000 ){ stopTurn(); swaySpeed = 0;
//  } else {
//    swayTimer = millis(); //reset the timer
//    swayDone = 1;
//  }
}

//void sway(){
//  if (swayDone == 1) {    swayTimer = millis();    swayDone = 0;
//  } 
//  currentMillis = millis();
//  nowSwayTime = currentMillis - swayTimer ;
//  if ( nowSwayTime < 2 ){  stopTurn();  //doesnt have time to get here!
//  } else if ( nowSubTime <  200 ){ leftTurn();   swaySpeed = 75;
//  } else if ( nowSubTime <  400 ){ rightTurn();   swaySpeed = 75;
//  } else if ( nowSubTime <  600 ){ leftTurn();  swaySpeed = 75;
//  } else if ( nowSubTime <  800 ){ rightTurn(); swaySpeed = 75;
//  } else if ( nowSubTime <  1000 ){ stopTurn(); swaySpeed = 0;
//  } else if ( nowSubTime <  2000 ){ stopTurn(); swaySpeed = 0;
//  } else {
//    swayTimer = millis(); //reset the timer
//    swayDone = 1;
//  }
//}


void simpleSway( int Angle1, int Angle2){
  //sway();
}
void simpleMove( int Angle1, int Distance1){
  //sway();
}


void turnlove(){
  newSong = 17;
  qfrequency = 487;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2000 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(60 , 90 );
} else if ( nowMotorTime < ( 3950 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(60 , 90 );
} else if ( nowMotorTime < ( 5900 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 7850 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 9800 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 11750 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13700 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 15650 + sOffset) ) {d4Sub(  21,11,21,11 , 27,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17600 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 19550 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 21500 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 23450 + sOffset) ) {d4Sub(  25,12,27,17 , 27,17,22,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 25400 + sOffset) ) {d8Sub(  28,11,28,17 , 28,11,28,17 ); simpleSway(70 , 80 );
} else if ( nowMotorTime < ( 27350 + sOffset) ) {d8Sub(  28,11,28,17 , 28,11,28,17 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 29300 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 31250 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33200 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 35150 + sOffset) ) {d8Sub(  23,19,23,15 , 23,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37100 + sOffset) ) {d4Sub(  24,13,29,13 , 23,14,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 39050 + sOffset) ) {d4Sub(  24,13,29,13 , 23,14,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41000 + sOffset) ) {d4Sub(  24,13,29,13 , 23,14,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 42950 + sOffset) ) {d4Sub(  24,13,29,13 , 23,14,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43925 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 44900 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45875 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 46850 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47825 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48800 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49775 + sOffset) ) {d8Sub(  29,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 50750 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 52700 + sOffset) ) {d4Sub(  25,12,22,15 , 25,12,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54650 + sOffset) ) {d4Sub(  22,15,22,15 , 22,15,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55625 + sOffset) ) {d8Sub(  29,19,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56600 + sOffset) ) {d8Sub(  28,18,21,11 , 28,18,21,11 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 57575 + sOffset) ) {d8Sub(  23,11,23,14 , 23,11,23,14 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 59525 + sOffset) ) {d4Sub(  25,12,22,15 , 25,12,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61475 + sOffset) ) {d4Sub(  22,15,22,15 , 22,15,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62450 + sOffset) ) {d8Sub(  29,19,27,17 , 25,15,27,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 63425 + sOffset) ) {d8Sub(  28,18,21,11 , 28,18,21,11 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 65375 + sOffset) ) {d8Sub(  23,11,23,14 , 23,11,23,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 67325 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 69275 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71225 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73175 + sOffset) ) {d4Sub(  24,14,24,14 , 27,17,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 75125 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77075 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79025 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80975 + sOffset) ) {d4Sub(  25,12,27,17 , 27,17,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82925 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 84875 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 86825 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88775 + sOffset) ) {d4Sub(  21,11,21,11 , 27,17,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 90725 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 92675 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 94625 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 96575 + sOffset) ) {d4Sub(  25,12,27,17 , 27,17,22,15 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 98525 + sOffset) ) {d8Sub(  28,11,28,17 , 28,11,28,17 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 100475 + sOffset) ) {d4Sub(  28,11,28,17 , 28,11,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 102425 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104375 + sOffset) ) {d8Sub(  23,12,23,13 , 23,19,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 105350 + sOffset) ) {d8Sub(  21,13,25,13 , 23,15,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 106325 + sOffset) ) {d8Sub(  23,11,23,15 , 25,13,28,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 107300 + sOffset) ) {d8Sub(  21,13,25,13 , 23,15,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108275 + sOffset) ) {d8Sub(  23,11,23,15 , 25,13,28,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 109250 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110225 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 111200 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112175 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113150 + sOffset) ) {d8Sub(  29,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 114125 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 115100 + sOffset) ) {d8Sub(  29,12,23,13 , 22,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 116075 + sOffset) ) {d8Sub(  29,12,23,13 , 22,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117050 + sOffset) ) {d8Sub(  29,12,23,13 , 22,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118025 + sOffset) ) {d8Sub(  29,12,23,13 , 22,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119000 + sOffset) ) {d8Sub(  29,19,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119975 + sOffset) ) {d8Sub(  28,18,21,11 , 28,18,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120950 + sOffset) ) {d8Sub(  23,11,23,14 , 23,11,23,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 122900 + sOffset) ) {d4Sub(  25,12,22,15 , 25,12,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124850 + sOffset) ) {d4Sub(  22,15,22,15 , 22,15,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125825 + sOffset) ) {d8Sub(  29,19,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126800 + sOffset) ) {d8Sub(  28,18,21,11 , 28,18,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 127775 + sOffset) ) {d8Sub(  29,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 128750 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 129725 + sOffset) ) {d8Sub(  22,15,23,13 , 29,16,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130700 + sOffset) ) {d8Sub(  25,12,23,13 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 131675 + sOffset) ) {d8Sub(  22,15,23,13 , 29,16,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132650 + sOffset) ) {d8Sub(  25,12,23,13 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 133625 + sOffset) ) {d8Sub(  22,15,23,13 , 29,16,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134600 + sOffset) ) {d8Sub(  25,12,23,13 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135575 + sOffset) ) {d8Sub(  22,15,23,13 , 29,16,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 136550 + sOffset) ) {d8Sub(  25,12,23,13 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137525 + sOffset) ) {d8Sub(  24,18,26,15 , 23,19,25,12 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 138500 + sOffset) ) {d8Sub(  24,14,25,16 , 29,13,22,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 139475 + sOffset) ) {d8Sub(  24,18,26,15 , 23,19,25,12 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 140450 + sOffset) ) {d8Sub(  24,14,25,16 , 29,13,22,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 141425 + sOffset) ) {d8Sub(  24,18,26,15 , 23,19,25,12 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 142400 + sOffset) ) {d8Sub(  24,14,25,16 , 29,13,22,15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 143375 + sOffset) ) {d8Sub(  25,15,25,16 , 26,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144350 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 146300 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 148250 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150200 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 152150 + sOffset) ) {d4Sub(  21,11,21,11 , 27,17,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 154100 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156050 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 158000 + sOffset) ) {d4Sub(  23,19,23,17 , 29,12,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 159950 + sOffset) ) {d4Sub(  25,12,27,17 , 22,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 161900 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 163850 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 165800 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 167750 + sOffset) ) {d4Sub(  21,11,24,14 , 27,17,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 169700 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 171650 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 173600 + sOffset) ) {d8Sub(  23,11,23,18 , 23,15,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175550 + sOffset) ) {d4Sub(  25,12,27,17 , 22,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177500 + sOffset) ) {d8Sub(  25,18,25,11 , 25,18,25,11 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 179450 + sOffset) ) {d8Sub(  25,18,25,11 , 25,18,25,11 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 181400 + sOffset) ) {d8Sub(  23,19,23,15 , 23,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 183350 + sOffset) ) {d8Sub(  23,19,23,15 , 23,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184325 + sOffset) ) {d8Sub(  21,13,28,13 , 25,17,29,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 185300 + sOffset) ) {d8Sub(  23,11,23,18 , 27,15,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186275 + sOffset) ) {d8Sub(  21,13,28,13 , 25,17,29,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 188225 + sOffset) ) {d8Sub(  23,11,23,18 , 27,15,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 189200 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 190175 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 191150 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192125 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 193100 + sOffset) ) {d8Sub(  21,12,22,12 , 23,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194075 + sOffset) ) {d8Sub(  23,13,22,12 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195050 + sOffset) ) {d8Sub(  29,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 196025 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 197000 + sOffset) ) {d4Sub(  22,12,22,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 197975 + sOffset) ) {d4Sub(  22,12,22,12 , 22,12,22,12 ); simpleSway(90 , 90 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void Add(){
  newSong = 10;
  qfrequency = 736;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 4688 + sOffset) ) {d4Sub(  24,14,22,12 , 26,16,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 8376 + sOffset) ) {d4Sub(  24,14,26,16 , 23,12,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12064 + sOffset) ) {d4Sub(  22,19,21,12 , 25,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 15752 + sOffset) ) {d4Sub(  24,14,26,16 , 23,12,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 19440 + sOffset) ) {d4Sub(  23,13,23,16 , 29,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 23128 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 26816 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30504 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34192 + sOffset) ) {d4Sub(  26,16,21,11 , 23,13,26,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37880 + sOffset) ) {d4Sub(  25,16,26,15 , 25,16,25,16 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 41568 + sOffset) ) {d4Sub(  26,16,22,12 , 27,17,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45256 + sOffset) ) {d4Sub(  25,16,26,15 , 25,16,25,16 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 47456 + sOffset) ) {d4Sub(  26,16,22,12 , 27,17,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49656 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 51856 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 54056 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56256 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58456 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 60656 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 62856 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65056 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 67256 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(20 , 140 );
} else if ( nowMotorTime < ( 69456 + sOffset) ) {d4Sub(  22,12,27,17 , 21,11,23,13 ); simpleSway(20 , 140 );
} else if ( nowMotorTime < ( 71656 + sOffset) ) {d4Sub(  21,11,23,13 , 27,17,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75344 + sOffset) ) {d4Sub(  28,18,21,11 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79032 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82720 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 86408 + sOffset) ) {d4Sub(  26,16,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90096 + sOffset) ) {d4Sub(  26,16,21,11 , 23,13,26,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93784 + sOffset) ) {d4Sub(  25,16,26,15 , 25,16,25,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 97472 + sOffset) ) {d4Sub(  26,16,22,12 , 27,17,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 101160 + sOffset) ) {d4Sub(  25,16,26,15 , 25,16,25,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 102160 + sOffset) ) {d4Sub(  26,16,22,12 , 27,17,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104360 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 106560 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 108760 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110960 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113160 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 115360 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 117560 + sOffset) ) {d4Sub(  21,11,27,17 , 21,11,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119760 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121960 + sOffset) ) {d4Sub(  23,15,23,16 , 25,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124160 + sOffset) ) { d8Sub(  22,15,23,13 , 25,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126360 + sOffset) ) {d4Sub(  22,15,22,15 , 25,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 128560 + sOffset) ) { d8Sub(  22,15,23,13 , 25,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130760 + sOffset) ) {d4Sub(  22,15,22,15 , 25,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132960 + sOffset) ) { d8Sub(  22,15,23,13 , 25,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135160 + sOffset) ) {d4Sub(  22,15,22,15 , 25,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137360 + sOffset) ) { d8Sub(  22,15,23,13 , 25,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139560 + sOffset) ) {d4Sub(  22,15,22,15 , 25,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141760 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}


void DontWorryBeHappy(){
  newSong = 16;
  qfrequency = 860;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  } else if ( nowMotorTime <  ( sOffset) ){ d2Sub(23,13,23,13); simpleSway( 80,  100); 
  } else if ( nowMotorTime <  (5500 + sOffset) ){ d2Sub(27,13,23,17); simpleMove( 130, 30); 
  } else if ( nowMotorTime <  (9000 + sOffset) ){ d2Sub(23,12,23,15);  simpleSway( 90,  140);
  } else if ( nowMotorTime <  (12500 + sOffset) ){d2Sub(27,13,23,17); simpleMove( 50, 40); 
  } else if ( nowMotorTime <  (16000 + sOffset) ){d2Sub(23,12,23,15); simpleSway( 90,  40);
  } else if ( nowMotorTime <  (19500 + sOffset) ){d2Sub(26,14,24,16); //sway(90,110);
  } else if ( nowMotorTime <  (23000 + sOffset) ){d2Sub(27,13,26,13); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (26500 + sOffset) ){d2Sub(26,14,24,16); //sway(70,110);
  } else if ( nowMotorTime <  (30000 + sOffset) ){d2Sub(27,13,26,13); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (33500 + sOffset) ){d2Sub(23,13,27,17); //sway(70,110);
  } else if ( nowMotorTime <  (40500 + sOffset) ){d2Sub(25,15,22,12); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (44000 + sOffset) ){d2Sub(26,14,24,16); //sway(70,110);
  } else if ( nowMotorTime <  (51000 + sOffset) ){d2Sub(27,13,26,13); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (54500 + sOffset) ){d2Sub(25,15,22,12); //sway(70,110);
  } else if ( nowMotorTime <  (58000 + sOffset) ){d2Sub(26,14,24,16); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (61500 + sOffset) ){d2Sub(27,13,23,17); simpleSway(70,110);
  } else if ( nowMotorTime <  (65000 + sOffset) ){d2Sub(23,12,23,15); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (68500 + sOffset) ){d2Sub(27,13,23,17); simpleSway(70,110);
  } else if ( nowMotorTime <  (72000 + sOffset) ){d2Sub(23,12,23,15); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (75500 + sOffset) ){d2Sub(27,13,26,13); simpleSway(70,110);
  } else if ( nowMotorTime <  (79000 + sOffset) ){d2Sub(26,14,24,16); simpleSway( 60,  120);
  } else if ( nowMotorTime <  (82500 + sOffset) ){ d2Sub(27,13,26,13); simpleSway(70,110);
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void first2(){
  newSong = 19;
  qfrequency = 588;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(26,16,26,16); //doesnt have time to get here!
  } else if ( nowMotorTime < ( 6000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(85 , 95 );
} else if ( nowMotorTime < ( 10000 + sOffset) ) { d2Sub(  23,16,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 14000 + sOffset) ) { d2Sub(  23,13,26 , 13 ); simpleSway(75 , 105 );
} else if ( nowMotorTime < ( 18000 + sOffset) ) { d2Sub(  26,17,22 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22000 + sOffset) ) { d2Sub(  27,14,24 , 17 ); simpleSway(75 , 105 );
} else if ( nowMotorTime < ( 26000 + sOffset) ) { d2Sub(  26,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 30000 + sOffset) ) { d2Sub(  27,17,27 , 17 ); simpleSway(85 , 95 );
} else if ( nowMotorTime < ( 33000 + sOffset) ) { d2Sub(  25,15,25 , 15 ); simpleSway(80 , 90 );
} else if ( nowMotorTime < ( 36000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 39000 + sOffset) ) { d2Sub(  23,11,23 , 11 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 42000 + sOffset) ) { d2Sub(  23,17,23 , 17 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 44000 + sOffset) ) { d2Sub(  23,14,23 , 13 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 46000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(100 , 80 );
} else if ( nowMotorTime < ( 48000 + sOffset) ) { d2Sub(  26,14,25 , 15 ); simpleSway(100 , 80 );
} else if ( nowMotorTime < ( 50000 + sOffset) ) { d2Sub(  24,16,25 , 15 ); simpleSway(100 , 80 );
} else if ( nowMotorTime < ( 52000 + sOffset) ) { d2Sub(  26,14,25 , 15 ); simpleSway(100 , 80 );
} else if ( nowMotorTime < ( 54000 + sOffset) ) { d2Sub(  24,16,25 , 15 ); simpleSway(100 , 80 );
} else if ( nowMotorTime < ( 60000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62000 + sOffset) ) { d2Sub(  26,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 64000 + sOffset) ) { d2Sub(  24,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66000 + sOffset) ) { d2Sub(  26,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68000 + sOffset) ) { d2Sub(  24,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75000 + sOffset) ) { d2Sub(  23,14,23 , 14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 78000 + sOffset) ) { d2Sub(  27,17,22 , 12 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 82000 + sOffset) ) { d2Sub(  24,16,24 , 16 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 86000 + sOffset) ) { d2Sub(  27,17,22 , 12 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 90000 + sOffset) ) { d2Sub(  24,16,24 , 16 ); simpleSway(20 , 40 );
} else if ( nowMotorTime < ( 93000 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 99000 + sOffset) ) { d2Sub(  23,14,23 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100000 + sOffset) ) { d2Sub(  23,17,23 , 17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104000 + sOffset) ) { d2Sub(  23,15,23 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108000 + sOffset) ) { d2Sub(  25,15,25 , 15 ); simpleSway(40 , 140 );
} else if ( nowMotorTime < ( 115000 + sOffset) ) { d2Sub(  24,14,25 , 15 ); simpleSway(40 , 140 );
} else if ( nowMotorTime < ( 123000 + sOffset) ) { d2Sub(  23,11,23 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137000 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144000 + sOffset) ) { d2Sub(  23,16,21 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156000 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 159000 + sOffset) ) { d2Sub(  23,14,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 160000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 163000 + sOffset) ) { d2Sub(  23,17,23 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 167000 + sOffset) ) { d2Sub(  23,15,23 , 11 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void holdhand(){
  newSong = 12;
  qfrequency = 489;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2956 + sOffset) ) {d4Sub(  23,16,23,16 , 23,13,23,13 ); simpleSway(140 , 90 );
} else if ( nowMotorTime < ( 4912 + sOffset) ) {d4Sub(  23,11,23,11 , 23,17,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 6868 + sOffset) ) {d4Sub(  23,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 8824 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 10780 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 12736 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 14692 + sOffset) ) {d4Sub(  23,12,23,12 , 22,12,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 16648 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 18604 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 20560 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 22516 + sOffset) ) {d4Sub(  26,16,26,16 , 23,15,23,15 ); simpleMove(120 , 20 );
} else if ( nowMotorTime < ( 24472 + sOffset) ) {d4Sub(  26,16,26,16 , 23,14,23,17 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 26428 + sOffset) ) {d4Sub(  23,17,23,17 , 23,17,23,17 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 28384 + sOffset) ) {d4Sub(  23,12,23,12 , 23,13,23,13 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 30340 + sOffset) ) {d4Sub(  26,16,26,16 , 23,15,23,15 ); simpleMove(120 , 20 );
} else if ( nowMotorTime < ( 32296 + sOffset) ) {d4Sub(  26,16,26,16 , 23,14,23,17 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 34252 + sOffset) ) {d4Sub(  23,17,23,17 , 23,17,23,17 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 36208 + sOffset) ) {d4Sub(  23,12,23,12 , 23,13,23,13 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 38164 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 40120 + sOffset) ) {d4Sub(  27,13,25,13 , 27,13,27,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 42076 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 44032 + sOffset) ) {d4Sub(  25,15,22,12 , 26,16,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 45988 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 47944 + sOffset) ) {d4Sub(  27,13,25,13 , 27,13,27,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 49900 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 51856 + sOffset) ) {d4Sub(  25,15,22,12 , 26,16,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 53812 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55768 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57724 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59680 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61636 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63592.0000000001 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65548 + sOffset) ) {d4Sub(  27,17,27,17 , 23,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 67504 + sOffset) ) {d4Sub(  26,16,22,12 , 22,12,24,14 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 69460 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71416 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73372 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75328 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77284 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79240 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 81196 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 83152 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 85108 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 87064 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 89020 + sOffset) ) {d4Sub(  23,12,23,12 , 22,12,22,12 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 90976 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 92932 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 94888 + sOffset) ) {d4Sub(  29,13,29,13 , 23,19,23,19 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 96844.0000000001 + sOffset) ) {d4Sub(  26,16,26,16 , 23,15,23,15 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 98800.0000000001 + sOffset) ) {d4Sub(  26,16,26,16 , 23,14,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 100756 + sOffset) ) {d4Sub(  23,17,23,17 , 23,17,23,17 ); simpleMove(120 , 20 );
} else if ( nowMotorTime < ( 102712 + sOffset) ) {d4Sub(  23,12,23,12 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 104668 + sOffset) ) {d4Sub(  26,16,26,16 , 23,15,23,15 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 106624 + sOffset) ) {d4Sub(  26,16,26,16 , 23,14,23,17 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 108580 + sOffset) ) {d4Sub(  23,17,23,17 , 23,17,23,17 ); simpleMove(120 , 20 );
} else if ( nowMotorTime < ( 110536 + sOffset) ) {d4Sub(  23,12,23,12 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 112492 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 114448 + sOffset) ) {d4Sub(  27,13,25,13 , 27,13,27,13 ); simpleMove(90 , 30 );
} else if ( nowMotorTime < ( 116404 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 118360 + sOffset) ) {d4Sub(  25,15,22,12 , 26,16,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 120316 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 122272 + sOffset) ) {d4Sub(  27,13,25,13 , 27,13,27,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 124228 + sOffset) ) {d4Sub(  23,17,23,15 , 23,17,23,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 126184 + sOffset) ) {d4Sub(  25,15,22,12 , 26,16,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 128140 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 130096 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 132052 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134008 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135964 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137920 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139876 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141832 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 143788 + sOffset) ) {d4Sub(  27,17,27,17 , 23,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 145744 + sOffset) ) {d4Sub(  26,16,22,12 , 22,12,24,14 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 147700 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 149656 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151612 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 153568 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 155524 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 157480 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 159436 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 161392 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 163348 + sOffset) ) {d4Sub(  25,17,25,12 , 28,12,28,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 165304 + sOffset) ) {d4Sub(  27,17,29,17 , 22,15,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 167260 + sOffset) ) {d4Sub(  21,11,28,18 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 169216 + sOffset) ) {d4Sub(  23,13,23,14 , 23,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 171172 + sOffset) ) {d4Sub(  23,13,24,13 , 27,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173128 + sOffset) ) {d4Sub(  23,12,23,16 , 23,13,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175084 + sOffset) ) {d4Sub(  23,13,23,11 , 23,17,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177040 + sOffset) ) {d4Sub(  25,17,25,12 , 28,12,28,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178996 + sOffset) ) {d4Sub(  27,17,29,17 , 22,15,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180952 + sOffset) ) {d4Sub(  21,11,28,18 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182908 + sOffset) ) {d4Sub(  23,13,23,14 , 23,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184864 + sOffset) ) {d4Sub(  23,13,24,13 , 27,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186820 + sOffset) ) {d4Sub(  23,14,23,12 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 188776 + sOffset) ) {d4Sub(  24,13,22,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 190732 + sOffset) ) {d4Sub(  23,13,21,11 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192688 + sOffset) ) {d4Sub(  29,19,25,15 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194644 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 196600 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 198556 + sOffset) ) {d4Sub(  25,11,21,15 , 25,18,25,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 200512 + sOffset) ) {d4Sub(  21,15,25,11 , 28,15,21,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 202468 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 204424 + sOffset) ) {d4Sub(  22,12,28,18 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 206380 + sOffset) ) {d4Sub(  27,17,27,17 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 208336 + sOffset) ) {d4Sub(  26,16,22,12 , 22,12,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 210292 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 212248 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 214204 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 216160 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 218116 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 220072 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 222028 + sOffset) ) {d4Sub(  29,16,26,19 , 29,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 223006 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 224962 + sOffset) ) {d8Sub(  23,13,23,11 , 23,11,23,11 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void airplane(){
  newSong = 13;
  qfrequency = 350;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2401 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 3802 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 5203 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 6604 + sOffset) ) {d4Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 8005 + sOffset) ) {d4Sub(  28,13,21,13 , 28,13,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 9406 + sOffset) ) {d4Sub(  23,11,23,11 , 23,11,23,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 10807 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12208 + sOffset) ) {d4Sub(  23,17,23,17 , 23,11,23,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13609 + sOffset) ) {d4Sub(  27,12,27,12 , 21,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 15010 + sOffset) ) {d4Sub(  22,17,22,17 , 26,11,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 16411 + sOffset) ) {d4Sub(  27,12,27,12 , 21,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17112 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17812 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 18513 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 19213 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 19914 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20614 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22015 + sOffset) ) {d4Sub(  29,19,29,19 , 26,16,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 23416 + sOffset) ) {d4Sub(  23,17,23,17 , 23,11,23,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 24817 + sOffset) ) {d4Sub(  27,12,27,12 , 21,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 26218 + sOffset) ) {d4Sub(  22,17,22,17 , 26,11,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 27619 + sOffset) ) {d4Sub(  27,12,27,12 , 21,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 28320 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 29020 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 29721 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30421 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 31122 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 31822 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33223 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34624 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 36025 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37426 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 38827 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 40228 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41629 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43030 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 44431 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45832 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47233 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48634 + sOffset) ) {d4Sub(  26,16,26,16 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 50035 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51436 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52837 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54238 + sOffset) ) {d4Sub(  26,16,23,13 , 28,18,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55639 + sOffset) ) {d4Sub(  22,12,22,12 , 29,19,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57040 + sOffset) ) {d4Sub(  22,12,22,12 , 29,19,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58441 + sOffset) ) {d4Sub(  22,12,22,12 , 29,19,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59842 + sOffset) ) {d4Sub(  22,12,22,12 , 29,19,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61243 + sOffset) ) {d4Sub(  23,18,23,11 , 23,17,23,12 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void ymca(){
  newSong = 15;
  qfrequency = 471;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 7;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2884 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 4834 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 6784 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 7759 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 8734 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 9709 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 10684 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 11659 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12634 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13609 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 14584 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 15559 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 16534 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17509 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 18484 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20434 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22384 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 23359 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 24334 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 25309 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 26284 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 27259 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 28234 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 29209 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30184 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 31159 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 32134 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33109 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34084 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 36034 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37984 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 39934 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41884 + sOffset) ) {d4Sub(  27,17,24,14 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43834 + sOffset) ) {d4Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45784 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47734 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49684 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51634 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53584 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55534 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57484 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59434 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61384 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63334 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65284 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 67234 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 69184 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71134 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72109 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73084 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74059 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75034 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 76009 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 76984 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77959 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 78934 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79909 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80884 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 81859 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82834 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 84784 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 86734 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 87709 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88684 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 89659 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90634 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 91609 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 92584 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93559 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 94534 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95509 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 96484 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 97459 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98434 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100384 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 102334 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104284 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 106234 + sOffset) ) {d4Sub(  27,17,24,14 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108184 + sOffset) ) {d4Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110134 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112084 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 114034 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115984 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117934 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119884 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121834 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 123784 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125734 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 127684 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 129634 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 131584 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 133534 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135484 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 136459 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137434 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 138409 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139384 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 140359 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141334 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 142309 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 143284 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144259 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145234 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 146209 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 147184 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 149134 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151084 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 152059 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 153034 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 154009 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 154984 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 155959 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156934 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 157909 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 158884 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 159859 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 160834 + sOffset) ) {d8Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 161809 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 162784 + sOffset) ) {d8Sub(  23,13,23,12 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 164734 + sOffset) ) {d8Sub(  23,13,22,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 166684 + sOffset) ) {d4Sub(  27,13,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 168634 + sOffset) ) {d4Sub(  27,12,27,12 , 27,12,27,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 170584 + sOffset) ) {d4Sub(  27,17,24,14 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 172534 + sOffset) ) {d4Sub(  27,15,25,17 , 27,15,25,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174484 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 176434 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178384 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180334 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182284 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184234 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186184 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 188134 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 190084 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192034 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 193984 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195934 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 197884 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 199834 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 201784 + sOffset) ) {d4Sub(  28,13,23,18 , 28,13,23,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203734 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 205684 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 207634 + sOffset) ) {d4Sub(  24,14,24,14 , 29,19,21,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 209584 + sOffset) ) {d4Sub(  28,18,28,18 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 211534 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 213484 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}
void worrything(){
  newSong = 18;
  qfrequency = 480;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 9;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2920 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 4840 + sOffset) ) {d4Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 6760 + sOffset) ) {d4Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 8680 + sOffset) ) {d4Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 10600 + sOffset) ) {d4Sub(  23,12,23,14 , 23,11,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12520 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 14440 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 16360 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 18280 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 20200 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 22120 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 24040 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 25960 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 27880 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 29800 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 31720 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33640 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 35560 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37480 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 39400 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41320 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43240 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45160 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47080 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49000 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 50920 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52840 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54760 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56680 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58600 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 60520 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 62440 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 64360 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 66280 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 68200 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 70120 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 72040 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 73960 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 75880 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 77800 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 79720 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 81640 + sOffset) ) {d4Sub(  25,15,26,16 , 25,15,29,19 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 83560 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 85480 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 87400 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 89320 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 91240 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93160 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95080 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 97000 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98920 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100840 + sOffset) ) {d4Sub(  23,13,25,12 , 23,13,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 102760 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104680 + sOffset) ) {d4Sub(  24,14,23,13 , 24,14,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 106600 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108520 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110440 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112360 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 114280 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 116200 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118120 + sOffset) ) {d4Sub(  22,12,25,15 , 22,12,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120040 + sOffset) ) {d4Sub(  22,12,25,15 , 29,19,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121960 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 123880 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 125800 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 127720 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 129640 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 131560 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 133480 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 135400 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 137320 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 139240 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 141160 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 143080 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 145000 + sOffset) ) {d4Sub(  25,15,26,16 , 25,15,29,19 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 146920 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 148840 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 150760 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 152680 + sOffset) ) {d4Sub(  23,12,23,11 , 22,13,21,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 154600 + sOffset) ) {d8Sub(  23,11,29,18 , 23,11,29,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156520 + sOffset) ) {d8Sub(  21,13,28,19 , 21,13,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 158440 + sOffset) ) {d8Sub(  23,11,29,18 , 23,11,29,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 160360 + sOffset) ) {d8Sub(  21,13,28,19 , 21,13,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 162280 + sOffset) ) {d4Sub(  24,14,26,16 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 164200 + sOffset) ) {d4Sub(  24,14,26,16 , 22,12,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 166120 + sOffset) ) {d4Sub(  24,14,26,16 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 168040 + sOffset) ) {d4Sub(  24,14,26,16 , 22,12,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 169960 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 171880 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173800 + sOffset) ) {d8Sub(  22,17,22,16 , 22,17,22,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175720 + sOffset) ) {d8Sub(  22,17,22,16 , 22,17,22,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177640 + sOffset) ) {d8Sub(  22,17,22,16 , 22,17,22,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179560 + sOffset) ) {d8Sub(  22,17,22,16 , 22,17,22,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181480 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 183400 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 185320 + sOffset) ) {d8Sub(  27,17,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187240 + sOffset) ) {d8Sub(  27,17,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 189160 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,22,12 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 191080 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,22,12 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 193000 + sOffset) ) {d8Sub(  27,17,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194920 + sOffset) ) {d8Sub(  27,17,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 196840 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,22,12 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 198760 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,22,12 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 200680 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 202600 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 204520 + sOffset) ) {d4Sub(  23,13,23,13 , 27,17,27,17 ); simpleSway(50 , 60 );
} else if ( nowMotorTime < ( 206440 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,21,11 ); simpleSway(120 , 130 );
} else if ( nowMotorTime < ( 208360 + sOffset) ) {d4Sub(  25,15,26,16 , 25,15,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 210280 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 212200 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 214120 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}
void WorryChild(){
  newSong = 20;
  qfrequency = 466;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  10 ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 1965 + sOffset) ) {d4Sub(  23,13,23,13 , 23,15,23,18 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 3830 + sOffset) ) {d4Sub(  23,18,23,18 , 23,18,23,18 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 5695 + sOffset) ) {d4Sub(  23,18,23,15 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 7560 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 9425 + sOffset) ) {d4Sub(  23,15,23,18 , 23,11,23,14 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 11290 + sOffset) ) {d4Sub(  23,14,23,11 , 23,18,23,15 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 13155 + sOffset) ) {d4Sub(  25,13,28,13 , 21,13,24,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 15020 + sOffset) ) {d4Sub(  24,13,21,13 , 28,13,25,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 16885 + sOffset) ) {d4Sub(  23,15,23,18 , 23,11,23,14 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 18750 + sOffset) ) {d4Sub(  23,14,23,11 , 23,18,23,15 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 20615 + sOffset) ) {d4Sub(  25,13,28,13 , 21,13,24,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 22480 + sOffset) ) {d4Sub(  24,13,21,13 , 28,13,25,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 24345 + sOffset) ) {d4Sub(  23,19,23,15 , 23,18,23,11 ); simpleSway(110 , 70 );
} else if ( nowMotorTime < ( 26210 + sOffset) ) {d4Sub(  23,11,23,18 , 23,17,23,15 ); simpleSway(110 , 70 );
} else if ( nowMotorTime < ( 28075 + sOffset) ) {d4Sub(  29,13,25,13 , 28,13,21,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 29940 + sOffset) ) {d4Sub(  21,13,28,13 , 27,13,25,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 31805 + sOffset) ) {d4Sub(  23,19,23,15 , 23,18,23,11 ); simpleSway(110 , 70 );
} else if ( nowMotorTime < ( 33670 + sOffset) ) {d4Sub(  23,11,23,18 , 23,17,23,15 ); simpleSway(110 , 70 );
} else if ( nowMotorTime < ( 35535 + sOffset) ) {d4Sub(  29,13,25,13 , 28,13,21,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 37400 + sOffset) ) {d4Sub(  21,13,28,13 , 27,13,25,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 38333 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 39265 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 40198 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 41130 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 42063 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 42995 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43928 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 44860 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45793 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 46725 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47658 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48590 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49523 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 50455 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51388 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52320 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53252 + sOffset) ) {d8Sub(  26,16,23,13 , 27,17,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54185 + sOffset) ) {d8Sub(  21,11,21,11 , 21,11,21,11 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 55117 + sOffset) ) {d8Sub(  21,11,21,17 , 21,13,21,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 56050 + sOffset) ) {d8Sub(  21,13,27,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56982 + sOffset) ) {d8Sub(  23,13,27,17 , 24,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57915 + sOffset) ) {d8Sub(  24,14,24,14 , 24,14,24,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 58847 + sOffset) ) {d8Sub(  22,12,22,12 , 22,12,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 59780 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 60712 + sOffset) ) {d8Sub(  26,16,23,13 , 27,17,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61645 + sOffset) ) {d8Sub(  21,11,21,11 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62577 + sOffset) ) {d8Sub(  21,11,21,17 , 21,13,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63510 + sOffset) ) {d8Sub(  21,13,27,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 64442 + sOffset) ) {d8Sub(  23,13,27,17 , 24,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65375 + sOffset) ) {d8Sub(  24,14,24,14 , 24,14,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66307 + sOffset) ) {d8Sub(  22,12,22,12 , 22,12,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 67240 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68172 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 69105 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70037 + sOffset) ) {d8Sub(  23,17,23,12 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70970 + sOffset) ) {d8Sub(  27,13,22,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71902 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72835 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73767 + sOffset) ) {d8Sub(  23,17,23,12 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74700 + sOffset) ) {d8Sub(  27,13,22,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75632 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 76565 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77497 + sOffset) ) {d8Sub(  23,17,23,12 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 78430 + sOffset) ) {d8Sub(  27,13,22,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79362 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80295 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 81227 + sOffset) ) {d8Sub(  23,17,23,12 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82160 + sOffset) ) {d8Sub(  27,13,22,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 83092 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 84025 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 84957 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 85890 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 86822 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 87755 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 88687 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 89620 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 90552 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 91485 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 92417 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 93350 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 94282 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 95215 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 96147 + sOffset) ) {d8Sub(  23,13,27,17 , 27,17,21,11 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 97080 + sOffset) ) {d8Sub(  21,11,21,11 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 98012 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 98945 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 99877 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 100810 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 102675 + sOffset) ) {d4Sub(  23,15,23,18 , 23,11,23,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104540 + sOffset) ) {d4Sub(  23,14,23,11 , 23,18,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 106405 + sOffset) ) {d4Sub(  25,13,28,13 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108270 + sOffset) ) {d4Sub(  24,13,21,13 , 28,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110135 + sOffset) ) {d4Sub(  23,15,23,18 , 23,11,23,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112000 + sOffset) ) {d4Sub(  23,14,23,11 , 23,18,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113865 + sOffset) ) {d4Sub(  25,13,28,13 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115730 + sOffset) ) {d4Sub(  24,13,21,13 , 28,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117595 + sOffset) ) {d4Sub(  23,19,23,15 , 23,18,23,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119460 + sOffset) ) {d4Sub(  23,11,23,18 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121325 + sOffset) ) {d4Sub(  29,13,25,13 , 28,13,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 123190 + sOffset) ) {d4Sub(  21,13,28,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125055 + sOffset) ) {d4Sub(  23,19,23,15 , 23,18,23,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126920 + sOffset) ) {d4Sub(  23,11,23,18 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 128785 + sOffset) ) {d4Sub(  29,13,25,13 , 28,13,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130650 + sOffset) ) {d4Sub(  21,13,28,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 131583 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 132515 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 133448 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134380 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135313 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 136245 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137178 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 138110 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139043 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139975 + sOffset) ) {d8Sub(  23,16,23,13 , 23,16,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 140908 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141840 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 142773 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 143705 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144638 + sOffset) ) {d8Sub(  23,13,25,15 , 21,11,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145570 + sOffset) ) {d8Sub(  28,18,21,11 , 24,14,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 146503 + sOffset) ) {d8Sub(  26,16,23,13 , 27,17,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 147435 + sOffset) ) {d8Sub(  21,11,21,11 , 21,11,21,11 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 148368 + sOffset) ) {d8Sub(  21,11,21,17 , 21,13,21,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 149300 + sOffset) ) {d8Sub(  21,13,27,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150233 + sOffset) ) {d8Sub(  23,13,27,17 , 24,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151165 + sOffset) ) {d8Sub(  24,14,24,14 , 24,14,24,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 152098 + sOffset) ) {d8Sub(  22,12,22,12 , 22,12,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 153030 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 153963 + sOffset) ) {d8Sub(  26,16,23,13 , 27,17,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 154895 + sOffset) ) {d8Sub(  21,11,21,11 , 21,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 155828 + sOffset) ) {d8Sub(  21,11,21,17 , 21,13,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156760 + sOffset) ) {d8Sub(  21,13,27,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 157693 + sOffset) ) {d8Sub(  23,13,27,17 , 24,11,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 158625 + sOffset) ) {d8Sub(  24,14,24,14 , 24,14,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 159558 + sOffset) ) {d8Sub(  22,12,22,12 , 22,12,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 160490 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 161423 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 162355 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 163288 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 164220 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 165153 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 166085 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 167018 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 167950 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 168883 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 169815 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 170748 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 171680 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 172613 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173545 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174478 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175410 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 176343 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177275 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178208 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179140 + sOffset) ) {d8Sub(  23,17,23,12 , 23,17,23,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180073 + sOffset) ) {d8Sub(  27,13,22,13 , 27,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181005 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181938 + sOffset) ) {d8Sub(  28,11,27,17 , 21,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182870 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 183803 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 184735 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 185668 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 186600 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 187533 + sOffset) ) {d8Sub(  27,17,27,17 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 188465 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 189398 + sOffset) ) {d8Sub(  21,11,27,17 , 21,11,27,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 190330 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 191263 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192195 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 193128 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194060 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194993 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195925 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 196858 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 197790 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 198723 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 199655 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 200588 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 201520 + sOffset) ) {d8Sub(  23,14,23,12 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 202453 + sOffset) ) {d8Sub(  24,13,22,13 , 27,13,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203385 + sOffset) ) {d8Sub(  23,13,29,19 , 25,15,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 204318 + sOffset) ) {d8Sub(  21,11,24,14 , 22,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 205250 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 206183 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 206183 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}


void rock(){
  newSong = 23;
  qfrequency = 473;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  10 ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 3427 + sOffset) ) {d4Sub(  24,16,28,19 , 24,16,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 5354 + sOffset) ) {d4Sub(  29,18,26,14 , 24,16,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 7281 + sOffset) ) {d4Sub(  24,16,26,14 , 29,16,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 9208 + sOffset) ) {d4Sub(  24,16,28,19 , 24,16,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 11135 + sOffset) ) {d4Sub(  29,18,26,14 , 24,16,28,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13062 + sOffset) ) {d4Sub(  24,16,26,14 , 29,16,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 14026 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 14989 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 16916 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17880 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 18843 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20770 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 21734 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22697 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 24624 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 25588 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 26551 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 28478 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 29442 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30405 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 32332 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33296 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34259 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 36186 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 38113 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 40040 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 41967 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 43894 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 45821 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 46785 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 47748 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48712 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49675 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 50639 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51602 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52566 + sOffset) ) {d8Sub(  22,13,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53529 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54493 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55456 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56420 + sOffset) ) {d8Sub(  23,13,26,19 , 22,15,24,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57383 + sOffset) ) {d8Sub(  21,11,28,14 , 25,12,29,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58347 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 59310 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 60274 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 61237 + sOffset) ) {d8Sub(  22,13,22,13 , 23,12,23,12 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 62201 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 63164 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 64128 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 65091 + sOffset) ) {d8Sub(  23,13,26,19 , 22,15,24,18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 66055 + sOffset) ) {d8Sub(  21,11,28,14 , 25,12,29,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 67018 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 67982 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68945 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 69909 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70872 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71836 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72799 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73763 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74726 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75690 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 76653 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77617 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 78580 + sOffset) ) {d4Sub(  25,14,25,14 , 25,14,25,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79544 + sOffset) ) {d4Sub(  25,14,25,14 , 25,14,25,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80507 + sOffset) ) {d4Sub(  25,14,25,14 , 25,14,25,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 81471 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82434 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 83398 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 84361 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 85325 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 86288 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 87252 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88215 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 89179 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90142 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 91106 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 92069 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93033 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93996 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 94960 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95923 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 96887 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 97850 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98814 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 99777 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100741 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 101704 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 102668 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 103631 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104595 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 105558 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 106522 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 107485 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108449 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 109412 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110376 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112303 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113266 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 114230 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 116157 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117120 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118084 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120011 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120974 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121938 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 123865 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124828 + sOffset) ) {d8Sub(  24,18,27,17 , 24,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125792 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 127719 + sOffset) ) {d4Sub(  23,14,23,16 , 24,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 129646 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 131573 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 133500 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 134463 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 135427 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 136390 + sOffset) ) {d4Sub(  27,17,23,13 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 137354 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 138317 + sOffset) ) {d8Sub(  26,16,24,14 , 26,16,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139281 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 140244 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 141208 + sOffset) ) {d8Sub(  22,15,22,15 , 22,15,22,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 142171 + sOffset) ) {d8Sub(  24,19,24,15 , 24,19,24,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 143135 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 144098 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 145062 + sOffset) ) {d8Sub(  22,15,22,15 , 22,15,22,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 146025 + sOffset) ) {d8Sub(  24,19,24,15 , 24,19,24,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 146989 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 147952 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 148916 + sOffset) ) {d8Sub(  22,15,22,15 , 22,15,22,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 149879 + sOffset) ) {d8Sub(  24,19,24,15 , 24,19,24,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 150843 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 151806 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 152770 + sOffset) ) {d8Sub(  22,15,22,15 , 22,15,22,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 153733 + sOffset) ) {d8Sub(  24,19,24,15 , 24,19,24,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 154697 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 155660 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 157587 + sOffset) ) {d4Sub(  23,13,21,11 , 21,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 159514 + sOffset) ) {d4Sub(  23,11,21,11 , 21,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 161441 + sOffset) ) {d4Sub(  21,18,28,11 , 28,11,28,11 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 163368 + sOffset) ) {d4Sub(  27,17,25,15 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 164332 + sOffset) ) {d8Sub(  22,15,22,15 , 22,15,22,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 165295 + sOffset) ) {d8Sub(  24,19,24,15 , 24,19,24,15 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 166259 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 167222 + sOffset) ) {d8Sub(  25,13,25,15 , 25,11,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 168186 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 169149 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 170113 + sOffset) ) {d8Sub(  26,16,26,16 , 26,16,26,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 171076 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 172040 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173003 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173967 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174930 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175894 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 176857 + sOffset) ) {d8Sub(  23,14,23,19 , 23,18,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177821 + sOffset) ) {d8Sub(  24,13,29,13 , 28,13,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178784 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179748 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180711 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181675 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182638 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 183602 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184565 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 185529 + sOffset) ) {d8Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 186492 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187456 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 188419 + sOffset) ) {d8Sub(  22,13,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 189383 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 190346 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 191310 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192273 + sOffset) ) {d8Sub(  23,13,26,19 , 22,15,24,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 193237 + sOffset) ) {d8Sub(  21,11,28,14 , 25,12,29,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194200 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 195164 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 196127 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 197091 + sOffset) ) {d8Sub(  22,13,22,13 , 23,12,23,12 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 198054 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 199018 + sOffset) ) {d8Sub(  23,12,23,12 , 22,13,22,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 199981 + sOffset) ) {d8Sub(  23,12,26,13 , 23,12,26,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 200945 + sOffset) ) {d8Sub(  23,13,26,19 , 22,15,24,18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 201908 + sOffset) ) {d8Sub(  21,11,28,14 , 25,12,29,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 202872 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203835 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 204799 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 205762 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 206726 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 207689 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 208653 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 209616 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 210580 + sOffset) ) {d8Sub(  26,13,23,13 , 26,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 211543 + sOffset) ) {d8Sub(  23,19,23,17 , 23,19,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 212507 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 213470 + sOffset) ) {d8Sub(  28,14,27,17 , 28,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 215397 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 217324 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 219251 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 221178 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 223105 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 225032 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 226959 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 228886 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 230813 + sOffset) ) {d4Sub(  25,15,25,15 , 25,15,25,15 ); simpleSway(90 , 90 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}


void titan(){
  newSong = 26;
  qfrequency = 482;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  10 ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2927 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 4854 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 6781 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 8708 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 10635 + sOffset) ) {d4Sub(  23,19,23,15 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12562 + sOffset) ) {d4Sub(  29,13,25,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 14489 + sOffset) ) {d4Sub(  23,19,23,15 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 16416 + sOffset) ) {d4Sub(  29,13,25,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 18343 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 20270 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 22197 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 24124 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 26051 + sOffset) ) {d4Sub(  24,14,26,16 , 23,17,23,16 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 27978 + sOffset) ) {d4Sub(  23,16,26,16 , 27,13,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 29905 + sOffset) ) {d4Sub(  26,16,26,16 , 23,17,23,16 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 31832 + sOffset) ) {d4Sub(  23,16,26,16 , 27,13,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 33759 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 35686 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37613 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 39540 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41467 + sOffset) ) {d4Sub(  23,17,23,12 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43394 + sOffset) ) {d4Sub(  27,13,22,13 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45321 + sOffset) ) {d4Sub(  22,12,22,15 , 27,17,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47248 + sOffset) ) {d4Sub(  22,12,25,12 , 27,17,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49175 + sOffset) ) {d4Sub(  23,17,23,12 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51102 + sOffset) ) {d4Sub(  27,13,22,13 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53029 + sOffset) ) {d4Sub(  22,12,22,15 , 27,17,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54956 + sOffset) ) {d4Sub(  22,12,25,12 , 27,17,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56883 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 58810 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 60737 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62664 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 64591 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 66518 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 68445 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70372 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72299 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 74226 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 76153 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 78080 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 80007 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 81934 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 83861 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 85788 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 87715 + sOffset) ) {d4Sub(  23,19,23,15 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 89642 + sOffset) ) {d4Sub(  29,13,25,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 91569 + sOffset) ) {d4Sub(  23,19,23,15 , 23,17,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93496 + sOffset) ) {d4Sub(  29,13,25,13 , 27,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95423 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 97350 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 99277 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 101204 + sOffset) ) {d4Sub(  29,19,25,15 , 24,14,22,12 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 103131 + sOffset) ) {d4Sub(  24,14,26,16 , 23,17,23,16 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 105058 + sOffset) ) {d4Sub(  23,16,26,16 , 27,13,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 106985 + sOffset) ) {d4Sub(  26,16,26,16 , 23,17,23,16 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 108912 + sOffset) ) {d4Sub(  23,16,26,16 , 27,13,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 110839 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112766 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 114693 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 116620 + sOffset) ) {d4Sub(  23,11,23,15 , 21,13,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118547 + sOffset) ) {d4Sub(  23,17,23,12 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120474 + sOffset) ) {d4Sub(  27,13,22,13 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 122401 + sOffset) ) {d4Sub(  22,12,22,15 , 27,17,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124328 + sOffset) ) {d4Sub(  22,12,25,12 , 27,17,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126255 + sOffset) ) {d4Sub(  23,17,23,12 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 128182 + sOffset) ) {d4Sub(  27,13,22,13 , 22,13,22,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130109 + sOffset) ) {d4Sub(  22,12,22,15 , 27,17,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132036 + sOffset) ) {d4Sub(  22,12,25,12 , 27,17,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 133963 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 135890 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 137817 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139744 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141671 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 143598 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 145525 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 147452 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 149379 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 151306 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 153233 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 155160 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 157087 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 159014 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 160941 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 162868 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 164795 + sOffset) ) {d4Sub(  23,18,23,18 , 23,17,23,19 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 166722 + sOffset) ) {d4Sub(  23,15,23,17 , 23,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 168649 + sOffset) ) {d4Sub(  23,13,23,13 , 28,18,28,18 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 170576 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 172503 + sOffset) ) {d4Sub(  22,13,23,13 , 23,13,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 174430 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,23,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 176357 + sOffset) ) {d4Sub(  23,12,22,12 , 22,17,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178284 + sOffset) ) {d4Sub(  27,19,29,19 , 28,18,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180211 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 182138 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 184065 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 185992 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187919 + sOffset) ) {d4Sub(  23,14,29,14 , 25,15,26,13 ); simpleSway(110 , 110 );
} else if ( nowMotorTime < ( 189846 + sOffset) ) {d4Sub(  24,13,24,19 , 25,15,26,13 ); simpleSway(70 , 70 );
} else if ( nowMotorTime < ( 191773 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 193700 + sOffset) ) {d4Sub(  29,17,29,19 , 27,19,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195627 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 197554 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 199481 + sOffset) ) {d4Sub(  27,14,27,18 , 27,14,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 201408 + sOffset) ) {d4Sub(  24,17,28,17 , 24,17,23,13 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 203335 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 205262 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 207189 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 209116 + sOffset) ) {d4Sub(  27,13,23,13 , 23,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 211043 + sOffset) ) {d4Sub(  23,18,23,18 , 23,18,23,18 ); simpleSway(70 , 70 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}


void applause(){
  newSong = 22;
  qfrequency = 428;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  10 ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 2713 + sOffset) ) {d4Sub(  23,14,23,14 , 23,14,23,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 4426 + sOffset) ) {d4Sub(  23,14,23,14 , 23,14,23,14 ); simpleSway(90 , 100 );
} else if ( nowMotorTime < ( 6139 + sOffset) ) {d4Sub(  23,14,29,19 , 29,19,24,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 7852 + sOffset) ) {d4Sub(  24,13,24,13 , 24,13,24,13 ); simpleSway(80 , 90 );
} else if ( nowMotorTime < ( 9565 + sOffset) ) {d4Sub(  24,13,29,19 , 29,19,23,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 11278 + sOffset) ) {d4Sub(  23,14,23,14 , 23,14,23,14 ); simpleSway(90 , 100 );
} else if ( nowMotorTime < ( 12991 + sOffset) ) {d4Sub(  23,14,29,19 , 29,19,24,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 14704 + sOffset) ) {d4Sub(  24,13,24,13 , 24,13,24,13 ); simpleSway(80 , 90 );
} else if ( nowMotorTime < ( 16417 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(90 , 110 );
} else if ( nowMotorTime < ( 18130 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 19843 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 21556 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 23269 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(90 , 110 );
} else if ( nowMotorTime < ( 24982 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 26695 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 28408 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30121 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 31834 + sOffset) ) {d8Sub(  28,17,28,13 , 28,19,28,15 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 33547 + sOffset) ) {d8Sub(  28,17,28,13 , 28,19,28,15 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 35260 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 36973 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 38686 + sOffset) ) {d8Sub(  27,18,23,18 , 29,18,25,18 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 40399 + sOffset) ) {d8Sub(  27,18,23,18 , 29,18,25,18 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 42112 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 43825 + sOffset) ) {d4Sub(  28,14,28,14 , 24,18,24,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45538 + sOffset) ) {d4Sub(  28,14,28,14 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47251 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48964 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 50677 + sOffset) ) {d4Sub(  28,18,28,18 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52390 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54103 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55816 + sOffset) ) {d4Sub(  23,12,22,12 , 26,14,24,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56673 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 57529 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 58386 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 59242 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 60955 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62668 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63525 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 64381 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 65238 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 66094 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 67807 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 69520 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71233 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72946 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74659 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 76372 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 78085 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79798 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 81511 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 83224 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 84937 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(90 , 110 );
} else if ( nowMotorTime < ( 86650 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 88363 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90076 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 91789 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(90 , 110 );
} else if ( nowMotorTime < ( 93502 + sOffset) ) {d4Sub(  22,12,26,16 , 22,12,26,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 95215 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 96928 + sOffset) ) {d4Sub(  24,18,28,14 , 24,18,28,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98641 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 100354 + sOffset) ) {d8Sub(  28,17,28,13 , 28,19,28,15 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 102067 + sOffset) ) {d8Sub(  28,17,28,13 , 28,19,28,15 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 103780 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 105493 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 107206 + sOffset) ) {d8Sub(  27,18,23,18 , 29,18,25,18 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 108919 + sOffset) ) {d8Sub(  27,18,23,18 , 29,18,25,18 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 110632 + sOffset) ) {d4Sub(  27,17,27,17 , 27,17,27,17 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 112345 + sOffset) ) {d4Sub(  28,14,28,14 , 24,18,24,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 114058 + sOffset) ) {d4Sub(  28,14,28,14 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115771 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117484 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 119197 + sOffset) ) {d4Sub(  28,18,28,18 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120910 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 122623 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124336 + sOffset) ) {d4Sub(  23,12,22,12 , 26,14,24,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125193 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 126049 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 126906 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 127762 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 129475 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 131188 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132045 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 132901 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 133758 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 134614 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 136327 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 138040 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 138897 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139753 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 140610 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 141466 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 143179 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144892 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 146605 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 148318 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150031 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151744 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 153457 + sOffset) ) {d4Sub(  27,17,21,11 , 21,11,21,11 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 155170 + sOffset) ) {d4Sub(  24,14,24,14 , 24,14,24,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 156883 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 158596 + sOffset) ) {d4Sub(  28,15,28,17 , 28,12,28,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 160309 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 162022 + sOffset) ) {d4Sub(  25,18,27,18 , 22,18,22,18 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 163735 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,25,15 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 165448 + sOffset) ) {d4Sub(  28,15,28,17 , 28,12,28,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 167161 + sOffset) ) {d4Sub(  28,14,28,14 , 24,18,24,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 168874 + sOffset) ) {d4Sub(  28,14,28,14 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 170587 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 172300 + sOffset) ) {d4Sub(  28,18,28,18 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174013 + sOffset) ) {d4Sub(  28,18,28,18 , 28,18,28,18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 175726 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177439 + sOffset) ) {d8Sub(  27,17,23,13 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179152 + sOffset) ) {d4Sub(  23,12,22,12 , 26,14,24,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 180009 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 180865 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 181722 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 182578 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 184291 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186004 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186861 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 187717 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 188574 + sOffset) ) {d8Sub(  21,18,28,11 , 21,18,28,11 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 189430 + sOffset) ) {d8Sub(  23,19,29,13 , 23,19,29,13 ); simpleSway(82 , 97 );
} else if ( nowMotorTime < ( 191143 + sOffset) ) {d4Sub(  23,18,23,19 , 23,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192856 + sOffset) ) {d4Sub(  28,13,29,13 , 28,13,29,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194569 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 196282 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 197995 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 199708 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 201421 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203134 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 204847 + sOffset) ) {d8Sub(  23,17,23,19 , 23,17,23,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 206560 + sOffset) ) {d4Sub(  23,11,23,13 , 21,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 208273 + sOffset) ) {d4Sub(  22,12,23,13 , 27,17,22,12 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 209986 + sOffset) ) {d4Sub(  22,12,22,12 , 22,12,22,12 ); simpleSway(90 , 90 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void price(){
  newSong = 14;
  qfrequency = 347;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 1375 + sOffset) ) {d8Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 2750 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 4125 + sOffset) ) {d8Sub(  24,16,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 5500 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 6875 + sOffset) ) {d8Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 8250 + sOffset) ) {d8Sub(  26,14,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 9625 + sOffset) ) {d8Sub(  24,16,24,16 , 26,14,26,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 11000 + sOffset) ) {d8Sub(  24,16,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 16500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 19250 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22000 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 24750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 27500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 30250 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33000 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 35750 + sOffset) ) {d4Sub(  23,13,23,13 , 25,12,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 38500 + sOffset) ) {d4Sub(  22,15,23,13 , 23,13,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 41250 + sOffset) ) {d4Sub(  25,12,23,13 , 23,13,25,12 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 44000 + sOffset) ) {d4Sub(  23,13,22,15 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 46750 + sOffset) ) {d4Sub(  29,15,29,17 , 29,15,29,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49500 + sOffset) ) {d4Sub(  28,18,27,17 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 52250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56375 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 57750 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 59125 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 60500 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 71500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 74250 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 77000 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 82500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 85250 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88000 + sOffset) ) {d4Sub(  21,11,22,12 , 23,13,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90750 + sOffset) ) {d4Sub(  23,13,23,13 , 25,12,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 93500 + sOffset) ) {d4Sub(  22,15,23,13 , 23,13,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 96250 + sOffset) ) {d4Sub(  25,12,23,13 , 23,13,25,12 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 99000 + sOffset) ) {d4Sub(  23,13,22,15 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 101750 + sOffset) ) {d4Sub(  29,15,29,17 , 29,15,29,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104500 + sOffset) ) {d4Sub(  28,18,27,17 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 107250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 111375 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 112750 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 114125 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115500 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 121000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 123750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 129250 + sOffset) ) {d4Sub(  21,11,26,16 , 21,11,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132000 + sOffset) ) {d4Sub(  21,11,26,16 , 21,11,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134750 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137500 + sOffset) ) {d4Sub(  22,12,27,17 , 25,15,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 140250 + sOffset) ) {d4Sub(  21,11,26,16 , 21,11,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 143000 + sOffset) ) {d4Sub(  21,11,26,16 , 21,11,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145750 + sOffset) ) {d4Sub(  22,12,25,15 , 23,13,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 148500 + sOffset) ) {d4Sub(  22,12,25,15 , 23,13,23,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151250 + sOffset) ) {d4Sub(  21,11,26,16 , 21,11,26,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 154000 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 156750 + sOffset) ) {d4Sub(  29,15,29,17 , 29,15,29,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 159500 + sOffset) ) {d4Sub(  28,18,27,17 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 162250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 165000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 166375 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 167750 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 169125 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 170500 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 173250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 176000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178750 + sOffset) ) {d4Sub(  29,15,29,17 , 29,15,29,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181500 + sOffset) ) {d4Sub(  28,18,27,17 , 28,18,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 188375 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 189750 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 191125 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192500 + sOffset) ) {d8Sub(  22,15,25,12 , 22,15,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195250 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,28,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 198000 + sOffset) ) {d4Sub(  22,18,28,12 , 22,18,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 199375 + sOffset) ) {d8Sub(  26,12,26,12 , 22,16,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 200750 + sOffset) ) {d8Sub(  26,12,22,16 , 26,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 202125 + sOffset) ) {d8Sub(  22,16,22,16 , 26,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203500 + sOffset) ) {d8Sub(  22,16,26,12 , 22,16,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 204875 + sOffset) ) {d8Sub(  26,12,26,12 , 22,16,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 206250 + sOffset) ) {d8Sub(  26,12,22,16 , 26,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 207625 + sOffset) ) {d8Sub(  22,16,22,16 , 26,12,26,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 209000 + sOffset) ) {d8Sub(  22,16,26,12 , 22,16,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 210375 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 211750 + sOffset) ) {d8Sub(  25,12,22,15 , 25,12,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 213125 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 214500 + sOffset) ) {d8Sub(  25,12,22,15 , 25,12,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 215875 + sOffset) ) {d8Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 217250 + sOffset) ) {d8Sub(  25,12,22,15 , 25,12,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 220000 + sOffset) ) {d4Sub(  23,13,27,17 , 24,14,24,14 ); simpleSway(90 , 90 );

  } else {
    motorTimer = millis(); //reset the timer
  } 
}
void Roar(){
  newSong = 11;
  qfrequency = 666;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
    servoIncrementDelay = 10;  //Arm Refresh Rate for this song
  }
  //Lets get ths song started!
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime <  sOffset ){  d2Sub(26,16,26,16);  simpleSway( 70,  110); servoIncrementDelay = 10;  //Arm Refresh Rate for this song
} else if ( nowMotorTime < ( 5325 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 7987 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 10650 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 13313 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 15975 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 18638 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 21301 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 23963 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 26626 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 29289 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,25,15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 31951 + sOffset) ) {d8Sub(  27,15,25,17 , 25,17,27,15 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 34614 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 37277 + sOffset) ) {d8Sub(  23,12,23,19 , 23,12,23,15 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 39939 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,25,15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 42602 + sOffset) ) {d8Sub(  27,15,25,17 , 25,17,27,15 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 45265 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 47927 + sOffset) ) {d8Sub(  23,12,23,19 , 23,12,23,19 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 50590 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53253 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55915 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 58578 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 61240 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63903 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66566 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 69228 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 71891 + sOffset) ) {d8Sub(  26,14,26,11 , 26,14,26,11 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 74554 + sOffset) ) {d8Sub(  23,17,27,13 , 23,17,27,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 77216 + sOffset) ) {d8Sub(  24,16,21,16 , 24,16,21,16 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 79879 + sOffset) ) {d8Sub(  27,13,23,17 , 27,13,23,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 82542 + sOffset) ) {d4Sub(  22,15,23,16 , 23,13,23,13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 85204 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 90 );
} else if ( nowMotorTime < ( 87867.483 + sOffset) ) {d4Sub(  23,16,23,12 , 26,13,22,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90530.134 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 93192.785 + sOffset) ) {d4Sub(  27,17,25,15 , 29,19,23,13 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 95855.436 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98518.087 + sOffset) ) {d8Sub(  27,15,25,17 , 25,17,27,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 101180.738 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 103843.389 + sOffset) ) {d8Sub(  23,12,23,19 , 23,12,23,19 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 106506.04 + sOffset) ) {d4Sub(  23,13,22,12 , 23,13,25,15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 109168.691 + sOffset) ) {d8Sub(  27,15,25,17 , 25,17,27,15 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 111831.342 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(110 , 150 );
} else if ( nowMotorTime < ( 114493.993 + sOffset) ) {d8Sub(  23,12,23,19 , 23,12,23,19 ); simpleSway(30 , 70 );
} else if ( nowMotorTime < ( 117156.644 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 119819.295 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 122481.946 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125144.597 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 127807.248 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 130469.899 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 133132.55 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135795.201 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 138457.852 + sOffset) ) {d8Sub(  26,14,26,11 , 26,14,26,11 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 141120.503 + sOffset) ) {d8Sub(  23,17,27,13 , 23,17,27,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 143783.154 + sOffset) ) {d8Sub(  24,16,21,16 , 24,16,21,16 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 146445.805 + sOffset) ) {d8Sub(  27,13,23,17 , 27,13,23,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 149108.456 + sOffset) ) {d4Sub(  22,15,23,16 , 23,13,23,13 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 151771.107 + sOffset) ) {d8Sub(  26,14,26,11 , 26,14,26,11 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 154433.758 + sOffset) ) {d8Sub(  23,17,27,13 , 23,17,27,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 157096.409 + sOffset) ) {d8Sub(  24,16,21,16 , 24,16,21,16 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 159759.06 + sOffset) ) {d8Sub(  27,13,23,17 , 27,13,23,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 162421.711 + sOffset) ) {d4Sub(  23,13,26,16 , 22,12,24,14 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 165084.362 + sOffset) ) {d4Sub(  21,11,21,11 , 21,17,21,13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 167747.013 + sOffset) ) {d4Sub(  24,13,22,13 , 26,13,23,13 ); simpleSway(110 , 70 );
} else if ( nowMotorTime < ( 170409.664 + sOffset) ) {d4Sub(  23,13,23,12 , 23,12,22,12 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 173072.315 + sOffset) ) {d4Sub(  22,12,29,19 , 27,17,29,19 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 175734.966 + sOffset) ) {d4Sub(  26,16,26,16 , 29,19,26,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 178397.617 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 181060.268 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 183722.919 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 186385.57 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 189048.221 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 191710.872 + sOffset) ) {d4Sub(  23,11,23,14 , 21,13,24,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194373.523 + sOffset) ) {d8Sub(  23,11,21,13 , 23,11,21,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 197036.174 + sOffset) ) {d4Sub(  22,12,22,12 , 27,17,26,16 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 199698.825 + sOffset) ) {d8Sub(  26,14,26,11 , 26,14,26,11 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 202361.476 + sOffset) ) {d8Sub(  23,17,27,13 , 23,17,27,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 205024.127 + sOffset) ) {d8Sub(  24,16,21,16 , 24,16,21,16 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 207686.778 + sOffset) ) {d8Sub(  27,13,23,17 , 27,13,23,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 210349.429 + sOffset) ) {d8Sub(  26,14,26,11 , 26,14,26,11 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 213012.08 + sOffset) ) {d8Sub(  23,17,27,13 , 23,17,27,13 ); simpleMove(110 , 30 );
} else if ( nowMotorTime < ( 215674.731 + sOffset) ) {d8Sub(  24,16,21,16 , 24,16,21,16 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 218337.382 + sOffset) ) {d8Sub(  27,13,23,17 , 27,13,23,17 ); simpleMove(70 , 30 );
} else if ( nowMotorTime < ( 221000.033 + sOffset) ) {d4Sub(  26,16,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
} else if ( nowMotorTime < ( 223662.684 + sOffset) ) {d4Sub(  23,13,23,13 , 23,13,23,13 ); simpleSway(90 , 90 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void fire(){
  newSong = 21;
  qfrequency = 491;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowMotorTime < (  sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12000 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 19500 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(20 , 170 );
} else if ( nowMotorTime < ( 27000 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34500 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(20 , 170 );
} else if ( nowMotorTime < ( 36000 + sOffset) ) { d2Sub(  26,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 38000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41000 + sOffset) ) { d2Sub(  24,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43000 + sOffset) ) { d2Sub(  26,16,24 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 45000 + sOffset) ) { d2Sub(  26,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 46000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 49000 + sOffset) ) { d2Sub(  24,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51000 + sOffset) ) { d2Sub(  26,16,24 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 89500 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 97000 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(20 , 170 );
} else if ( nowMotorTime < ( 104500 + sOffset) ) { d2Sub(  23,14,24 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 112000 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(20 , 170 );
} else if ( nowMotorTime < ( 114000 + sOffset) ) { d2Sub(  26,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 116000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 118000 + sOffset) ) { d2Sub(  24,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 120000 + sOffset) ) { d2Sub(  26,16,24 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 122000 + sOffset) ) { d2Sub(  26,16,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 124000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 126000 + sOffset) ) { d2Sub(  24,14,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 128000 + sOffset) ) { d2Sub(  26,16,24 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 136000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 144000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 148000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150000 + sOffset) ) { d2Sub(  23,13,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 151000 + sOffset) ) { d2Sub(  23,14,23 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 152000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void better(){
  newSong = 24;
  qfrequency = 937;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 2000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 6000 + sOffset) ) { d2Sub(  23,16,23 , 13 ); simpleSway(140 , 80 );
} else if ( nowMotorTime < ( 8000 + sOffset) ) { d2Sub(  23,13,21 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 10000 + sOffset) ) { d2Sub(  29,18,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 14000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 16000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 18000 + sOffset) ) { d2Sub(  29,18,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 23000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 24000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 25000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 26000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 27000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 28000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 32000 + sOffset) ) { d2Sub(  26,15,25 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 34000 + sOffset) ) { d2Sub(  28,18,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 35000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 37000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 40000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 42000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 47000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 51000 + sOffset) ) { d2Sub(  21,11,26 , 16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 54000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55000 + sOffset) ) { d2Sub(  29,14,24 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56000 + sOffset) ) { d2Sub(  29,16,26 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 57000 + sOffset) ) { d2Sub(  29,14,24 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58000 + sOffset) ) { d2Sub(  29,16,26 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59000 + sOffset) ) { d2Sub(  26,16,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 64000 + sOffset) ) { d2Sub(  29,18,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 68000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 70000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 72000 + sOffset) ) { d2Sub(  29,18,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73000 + sOffset) ) { d2Sub(  21,11,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 76000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 77000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 78000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 79000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 80000 + sOffset) ) { d2Sub(  29,19,25 , 15 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 81000 + sOffset) ) { d2Sub(  25,15,28 , 18 ); simpleMove(90 , 40 );
} else if ( nowMotorTime < ( 85000 + sOffset) ) { d2Sub(  26,15,25 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 86000 + sOffset) ) { d2Sub(  28,18,25 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 92000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 94000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(50 , 130 );
} else if ( nowMotorTime < ( 104000 + sOffset) ) { d2Sub(  21,11,26 , 16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 105000 + sOffset) ) { d2Sub(  22,12,25 , 15 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void findyourthing(){
  newSong = 25;
  qfrequency = 542;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 1000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 2000 + sOffset) ) { d2Sub(  24,14,29 , 19 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 3000 + sOffset) ) { d2Sub(  29,19,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 5000 + sOffset) ) { d2Sub(  27,17,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 6000 + sOffset) ) { d2Sub(  24,14,24 , 14 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 7000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 8000 + sOffset) ) { d2Sub(  27,17,21 , 11 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 14000 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 15000 + sOffset) ) { d2Sub(  26,11,26 , 11 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 16000 + sOffset) ) { d2Sub(  27,17,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 21000 + sOffset) ) { d2Sub(  27,17,26 , 16 ); simpleSway(110 , 130 );
} else if ( nowMotorTime < ( 25000 + sOffset) ) { d2Sub(  27,17,26 , 16 ); simpleSway(70 , 50 );
} else if ( nowMotorTime < ( 30000 + sOffset) ) { d2Sub(  27,17,26 , 16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 32000 + sOffset) ) { d2Sub(  27,17,24 , 14 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 33000 + sOffset) ) { d2Sub(  22,14,28 , 18 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 34000 + sOffset) ) { d2Sub(  23,14,26 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 35000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 36000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 38000 + sOffset) ) { d2Sub(  27,17,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 39000 + sOffset) ) { d2Sub(  29,16,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 40000 + sOffset) ) { d2Sub(  26,19,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 43000 + sOffset) ) { d2Sub(  27,17,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 47000 + sOffset) ) { d2Sub(  24,14,23 , 13 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 49000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 51000 + sOffset) ) { d2Sub(  22,14,28 , 18 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 52000 + sOffset) ) { d2Sub(  23,14,26 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 54000 + sOffset) ) { d2Sub(  22,12,27 , 17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 55000 + sOffset) ) { d2Sub(  21,11,24 , 14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58000 + sOffset) ) { d2Sub(  26,17,27 , 14 ); simpleSway(70 , 50 );
} else if ( nowMotorTime < ( 60000 + sOffset) ) { d2Sub(  27,16,24 , 17 ); simpleSway(110 , 130 );
} else if ( nowMotorTime < ( 64000 + sOffset) ) { d2Sub(  25,15,22 , 12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 65000 + sOffset) ) { d2Sub(  24,14,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 67000 + sOffset) ) { d2Sub(  26,17,27 , 14 ); simpleSway(70 , 50 );
} else if ( nowMotorTime < ( 68000 + sOffset) ) { d2Sub(  27,16,24 , 17 ); simpleSway(110 , 130 );
} else if ( nowMotorTime < ( 71000 + sOffset) ) { d2Sub(  28,14,24 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 73000 + sOffset) ) { d2Sub(  29,16,26 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75000 + sOffset) ) { d2Sub(  28,14,24 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 78000 + sOffset) ) { d2Sub(  29,16,26 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80000 + sOffset) ) { d2Sub(  28,14,24 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 82000 + sOffset) ) { d2Sub(  29,16,26 , 19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 83000 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 84000 + sOffset) ) { d2Sub(  21,11,28 , 18 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 85000 + sOffset) ) { d2Sub(  21,11,25 , 15 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 86000 + sOffset) ) { d2Sub(  27,17,26 , 16 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 92000 + sOffset) ) { d2Sub(  27,16,26 , 17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95000 + sOffset) ) { d2Sub(  22,15,25 , 12 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 99000 + sOffset) ) { d2Sub(  23,13,24 , 14 ); simpleSway(130 , 50 );
} else if ( nowMotorTime < ( 101000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 103000 + sOffset) ) { d2Sub(  24,12,28 , 18 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 104000 + sOffset) ) { d2Sub(  23,11,23 , 13 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 107000 + sOffset) ) { d2Sub(  25,12,22 , 15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108000 + sOffset) ) { d2Sub(  24,14,21 , 11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110000 + sOffset) ) { d2Sub(  26,17,27 , 14 ); simpleSway(70 , 50 );
} else if ( nowMotorTime < ( 112000 + sOffset) ) { d2Sub(  27,16,24 , 17 ); simpleSway(110 , 130 );
} else if ( nowMotorTime < ( 116000 + sOffset) ) { d2Sub(  25,15,26 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 117000 + sOffset) ) { d2Sub(  28,18,24 , 14 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 119000 + sOffset) ) { d2Sub(  26,17,27 , 14 ); simpleSway(70 , 50 );
} else if ( nowMotorTime < ( 121000 + sOffset) ) { d2Sub(  27,16,24 , 17 ); simpleSway(110 , 130 );
} else if ( nowMotorTime < ( 123000 + sOffset) ) { d2Sub(  28,12,22 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 125000 + sOffset) ) { d2Sub(  26,19,29 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 127000 + sOffset) ) { d2Sub(  28,12,22 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130000 + sOffset) ) { d2Sub(  26,17,27 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132000 + sOffset) ) { d2Sub(  28,12,22 , 18 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134000 + sOffset) ) { d2Sub(  26,17,27 , 16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135000 + sOffset) ) { d2Sub(  23,13,27 , 17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 136000 + sOffset) ) { d2Sub(  25,15,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 137000 + sOffset) ) { d2Sub(  21,11,27 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 138000 + sOffset) ) { d2Sub(  23,13,26 , 17 ); simpleSway(80 , 100 );
} else if ( nowMotorTime < ( 139000 + sOffset) ) { d2Sub(  26,11,23 , 11 ); simpleSway(80 , 100 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void Cheap(){
  newSong = 28;
  qfrequency = 669;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 8675 + sOffset) ) {d4Sub(  23,13,26,16 , 22,12,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 11350 + sOffset) ) {d4Sub(  28,18,25,15 , 29,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12687.5 + sOffset) ) {d8Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 14025 + sOffset) ) {d8Sub(  22,13,23,13 , 27,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 15362.5 + sOffset) ) {d8Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 16700 + sOffset) ) {d8Sub(  22,13,23,13 , 27,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 19375 + sOffset) ) {d8Sub(  23,13,27,17 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20712.5 + sOffset) ) {d8Sub(  23,13,22,13 , 21,13,25,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 22050 + sOffset) ) {d4Sub(  23,13,27,17 , 27,17,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 24725 + sOffset) ) {d8Sub(  23,13,27,17 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 26062.5 + sOffset) ) {d8Sub(  23,13,23,12 , 23,11,23,15 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 27400 + sOffset) ) {d4Sub(  23,13,27,17 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 30075 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 32750 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 35425 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 38100 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 40775 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43450 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 46125 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48800 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51475 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 54150 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56825 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 59500 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 62175 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 64850 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 67525 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 70200 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 72875 + sOffset) ) {d8Sub(  23,13,27,17 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 74212.5 + sOffset) ) {d8Sub(  23,13,22,13 , 21,13,25,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 75550 + sOffset) ) {d4Sub(  23,13,27,17 , 27,17,23,13 ); simpleMove(120 , 30 );
} else if ( nowMotorTime < ( 78225 + sOffset) ) {d8Sub(  23,13,27,17 , 23,13,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 79562.5 + sOffset) ) {d8Sub(  23,13,23,12 , 23,11,23,15 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 80900 + sOffset) ) {d4Sub(  23,13,27,17 , 27,17,23,13 ); simpleMove(60 , 30 );
} else if ( nowMotorTime < ( 83575 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 86250 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 88925 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 91600 + sOffset) ) {d4Sub(  26,16,29,19 , 26,16,29,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 94275 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 96950 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 99625 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 102300 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 104975 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 107650 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110325 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113000 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115675 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 118350 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 121025 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 123700 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 126375 + sOffset) ) {d4Sub(  21,11,23,13 , 21,11,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 129050 + sOffset) ) {d4Sub(  21,11,23,13 , 21,11,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 131725 + sOffset) ) {d4Sub(  23,15,25,13 , 23,15,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 134400 + sOffset) ) {d4Sub(  23,15,25,13 , 23,15,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137075 + sOffset) ) {d4Sub(  21,11,23,13 , 21,11,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 139750 + sOffset) ) {d4Sub(  21,11,23,13 , 21,11,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 142425 + sOffset) ) {d4Sub(  23,15,25,13 , 23,15,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145100 + sOffset) ) {d4Sub(  23,15,25,13 , 23,15,25,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 147775 + sOffset) ) {d4Sub(  27,14,24,17 , 27,14,24,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150450 + sOffset) ) {d4Sub(  27,17,21,11 , 27,17,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 153125 + sOffset) ) {d4Sub(  27,14,24,17 , 27,14,24,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 155800 + sOffset) ) {d4Sub(  27,17,21,11 , 27,17,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 158475 + sOffset) ) {d4Sub(  27,14,24,17 , 27,14,24,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 161150 + sOffset) ) {d4Sub(  27,17,21,11 , 27,17,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 163825 + sOffset) ) {d4Sub(  27,14,24,17 , 27,14,24,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 166500 + sOffset) ) {d4Sub(  27,17,21,11 , 27,17,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 169175 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 171850 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174525 + sOffset) ) {d4Sub(  23,16,23,11 , 23,16,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177200 + sOffset) ) {d4Sub(  23,16,23,13 , 22,13,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179875 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182550 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 185225 + sOffset) ) {d4Sub(  21,11,24,14 , 22,12,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187900 + sOffset) ) {d4Sub(  22,12,25,15 , 27,17,22,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 190575 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 193250 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 195925 + sOffset) ) {d4Sub(  23,11,23,18 , 23,15,23,19 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 198600 + sOffset) ) {d4Sub(  21,13,28,13 , 25,19,29,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 201275 + sOffset) ) {d4Sub(  23,13,22,12 , 24,14,21,11 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 203950 + sOffset) ) {d4Sub(  28,18,25,15 , 29,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 205287.5 + sOffset) ) {d8Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 206625 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 207962.5 + sOffset) ) {d8Sub(  23,12,23,13 , 23,12,23,13 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 209300 + sOffset) ) {d8Sub(  22,13,23,13 , 22,13,23,13 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 211975 + sOffset) ) {d4Sub(  23,13,22,12 , 24,14,21,11 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 214650 + sOffset) ) {d4Sub(  28,18,25,15 , 29,19,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 217325 + sOffset) ) {d4Sub(  22,19,29,12 , 22,19,29,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 220000 + sOffset) ) {d4Sub(  22,19,29,12 , 24,14,21,11 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}


void Great(){
  newSong = 27;
  qfrequency = 669;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 5474 + sOffset) ) {d4Sub(  23,19,29,19 , 23,19,29,19 ); simpleSway(80 , 80 );
} else if ( nowMotorTime < ( 7948 + sOffset) ) {d4Sub(  23,19,29,19 , 23,19,29,19 ); simpleSway(100 , 100 );
} else if ( nowMotorTime < ( 10422 + sOffset) ) {d4Sub(  23,15,22,15 , 27,12,25,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 12896 + sOffset) ) {d4Sub(  25,11,24,11 , 27,17,25,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 15370 + sOffset) ) {d4Sub(  23,19,29,19 , 25,15,28,18 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 16607 + sOffset) ) {d4Sub(  27,17,22,12 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 17844 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 20318 + sOffset) ) {d4Sub(  23,19,29,19 , 25,15,28,18 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 21555 + sOffset) ) {d4Sub(  27,17,22,12 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 22792 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 25266 + sOffset) ) {d4Sub(  23,19,29,19 , 25,15,28,18 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 26503 + sOffset) ) {d4Sub(  27,17,22,12 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 27740 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 30214 + sOffset) ) {d4Sub(  23,19,29,19 , 25,15,28,18 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 31451 + sOffset) ) {d4Sub(  27,17,22,12 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 33925 + sOffset) ) {d8Sub(  24,14,27,17 , 24,14,27,17 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 36399 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 38873 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 41347 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 43821 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 46295 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 48769 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 51243 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 53717 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 56191 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 58665 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 61139 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 63613 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 66087 + sOffset) ) {d4Sub(  23,12,23,16 , 23,12,23,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 68561 + sOffset) ) {d4Sub(  22,12,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 71035 + sOffset) ) {d4Sub(  23,12,23,16 , 23,12,23,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 73509 + sOffset) ) {d4Sub(  22,12,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 75983 + sOffset) ) {d4Sub(  23,12,23,16 , 23,12,23,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 78457 + sOffset) ) {d4Sub(  22,12,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 80931 + sOffset) ) {d4Sub(  23,12,23,16 , 23,12,23,17 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 83405 + sOffset) ) {d4Sub(  22,12,24,14 , 27,17,24,14 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 85879 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 88353 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 90827 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 93301 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 95775 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 98249 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 100723 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 103197 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 105671 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 108145 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 110619 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 113093 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 115567 + sOffset) ) {d4Sub(  27,17,29,19 , 26,14,24,16 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 118041 + sOffset) ) {d4Sub(  27,17,29,19 , 26,14,24,16 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 120515 + sOffset) ) {d4Sub(  27,17,29,19 , 26,14,24,16 ); simpleSway(90 , 130 );
} else if ( nowMotorTime < ( 122989 + sOffset) ) {d4Sub(  27,17,29,19 , 26,14,24,16 ); simpleSway(50 , 90 );
} else if ( nowMotorTime < ( 125463 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 127937 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 130411 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 132885 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 135359 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 137833 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 140307 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,12 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 142781 + sOffset) ) {d4Sub(  23,12,22,13 , 23,12,23,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 145255 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 147729 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 150203 + sOffset) ) {d4Sub(  26,14,26,14 , 24,16,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 152677 + sOffset) ) {d4Sub(  26,14,26,14 , 23,13,23,13 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 155151 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 157625 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 160099 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 162573 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 165047 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 167521 + sOffset) ) {d4Sub(  22,12,29,19 , 22,12,29,19 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 169995 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 172469 + sOffset) ) {d4Sub(  21,11,25,15 , 21,11,25,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 174943 + sOffset) ) {d4Sub(  29,16,25,12 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 177417 + sOffset) ) {d4Sub(  22,12,26,14 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 179891 + sOffset) ) {d4Sub(  29,16,25,12 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 182365 + sOffset) ) {d4Sub(  22,12,26,14 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 184839 + sOffset) ) {d4Sub(  29,16,25,12 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 187313 + sOffset) ) {d4Sub(  22,12,26,14 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 189787 + sOffset) ) {d4Sub(  29,16,25,12 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 192261 + sOffset) ) {d4Sub(  22,12,26,14 , 22,12,24,16 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 194735 + sOffset) ) {d4Sub(  29,16,25,12 , 26,19,22,15 ); simpleSway(70 , 110 );
} else if ( nowMotorTime < ( 197209 + sOffset) ) {d4Sub(  22,12,26,14 , 22,12,24,16 ); simpleSway(70 , 110 );
  } else {
    motorTimer = millis(); //reset the timer
  } 
}

void testPattern(){
  newSong = 0;
  qfrequency = 700;
  if (oldSong != newSong ){
    NewSongStep = 1;
    oldSong = newSong;
    motorTimer = millis(); //reset the timer
  }
  currentMillis = millis();
  nowMotorTime = currentMillis - motorTimer ;
  if ( nowMotorTime < 10 ){   target1 = 25;   d2Sub(23,13,23,13); //doesnt have time to get here!
} else if ( nowMotorTime < ( 2000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(70 , 110 ); //down
} else if ( nowMotorTime < ( 4000 + sOffset) ) { d2Sub(  21,11,21 , 11 ); simpleSway(70 , 110 ); //up
} else if ( nowMotorTime < ( 6000 + sOffset) ) { d2Sub(  22,12,22 , 12 ); simpleSway(70 , 110 ); //out
} else if ( nowMotorTime < ( 8000 + sOffset) ) { d2Sub(  23,13,23 , 13 ); simpleSway(70 , 110 ); //down
} else if ( nowMotorTime < ( 10000 + sOffset) ) { d2Sub(  24,14,24 , 14 ); simpleSway(70 , 110 ); //yup
} else if ( nowMotorTime < ( 12000 + sOffset) ) { d2Sub(  25,15,25 , 15 ); simpleSway(70 , 110 ); //in
} else if ( nowMotorTime < ( 14000 + sOffset) ) { d2Sub(  26,16,26 , 16 ); simpleSway(70 , 110 ); //ydown
} else if ( nowMotorTime < ( 16000 + sOffset) ) { d2Sub(  27,17,27 , 17 ); simpleSway(70 , 110 ); //forward
} else if ( nowMotorTime < ( 18000 + sOffset) ) { d2Sub(  28,18,28 , 18 ); simpleSway(70 , 110 ); //uin
} else if ( nowMotorTime < ( 20000 + sOffset) ) { d2Sub(  29,19,29 , 19 ); simpleSway(70 , 110 ); //din
  } else {
    motorTimer = millis(); //reset the timer
  } 
}




void calcDanceStep() {
  //resetting targets if new dance song or new dance step
 
}

void basicDanceSub(){
  if (subDone == 1) {    subTimer = millis();     subDone = 0;
  } 
  currentMillis = millis();
  nowSubTime = currentMillis - subTimer ;
  if ( nowSubTime < 10 ){  stopTurn(); target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowSubTime <  2000 ){ rUp();   lUp();  //arm up
  } else if ( nowSubTime <  4000 ){ rOut(); lOut(); //arm out
  } else if ( nowSubTime <  8000 ){ rDown(); lDown(); //arm down
  } else if ( nowSubTime <  12000 ){ rYUp(); lYUp(); // LYup
  } else if ( nowSubTime <  14000 ){ rin();  lin(); // Lin
  } else if ( nowSubTime <  18000 ){ rYdown(); lYdown(); //LYdown
  } else if ( nowSubTime <  20000 ){ rForward(); lForward(); //LforWard
  } else {
    subTimer = millis(); //reset the timer
    subDone = 1;
  }
 }

// 
//void rUp()  {  target1 = 25;   target2 = 20;   }      void lUp()  {  target3 = 130;   target4 = 120; }
//void rOut()  { target1 = 70;   target2 = 70;  }       void lOut()  {  target3 = 70;   target4 = 80; }
//void rDown()  {  target1 = 130;  target2 = 20;   }    void lDown()  {  target3 = 35;    target4 = 140; }
//void rYUp()  {  target1 = 20;   target2 = 70;   }     void lYUp()  {  target3 = 130;   target4 = 85; }
//void rin()  {  target1 = 70;   target2 = 20;   }      void lin()  {  target3 = 70;   target4 = 140; }
//void rYdown()  {  target1 = 130;  target2 = 70;   }     void lYdown()  {  target3 = 15;    target4 = 85; }
//void rForward()  {  target1 = 70;  target2 = 50;    }   void lForward()  {  target3 = 70;    target4 = 100; }
 
void rUp()  {  target1 = 55;   target2 = 35;   }      void lUp()  {  target3 = 180;   target4 = 80; }
void rOut()  { target1 = 105;   target2 = 100;  }       void lOut()  {  target3 = 130;   target4 = 10; }
void rDown()  {  target1 = 160;  target2 = 45;   }    void lDown()  {  target3 = 80;    target4 = 75; }
void rYUp()  {  target1 = 40;   target2 = 95;   }     void lYUp()  {  target3 = 180;   target4 = 35; }
void rin()  {  target1 = 120;   target2 = 5;   }      void lin()  {  target3 = 120;   target4 = 110; }
void rUin()  {  target1 = 65;   target2 = 15;   }      void lUin()  {  target3 = 170;   target4 = 105; }
void rDin()  {  target1 = 160;   target2 = 20;   }      void lDin()  {  target3 = 80;   target4 = 105; }
void rYdown()  {  target1 = 160;  target2 = 80;   }     void lYdown()  {  target3 = 80;    target4 = 40; }
void rForward()  {  target1 = 125;  target2 = 55;    }   void lForward()  {  target3 = 115;    target4 = 85; }

void dlist( int dance ){
  if (dance == 11 ) { rUp(); }
  if (dance == 12 ) { rOut(); }
  if (dance == 13 ) { rDown(); }
  if (dance == 14 ) { rYUp(); }
  if (dance == 15 ) { rin(); }
  if (dance == 16 ) { rYdown(); }
  if (dance == 17 ) { rForward(); }
  if (dance == 18 ) { rUin(); }
  if (dance == 19 ) { rDin(); }
  if (dance == 21 ) { lUp(); }
  if (dance == 22 ) { lOut(); }
  if (dance == 23 ) { lDown(); }
  if (dance == 24 ) { lYUp(); }
  if (dance == 25 ) { lin(); }
  if (dance == 26 ) { lYdown(); }
  if (dance == 27 ) { lForward(); }
  if (dance == 28 ) { lUin(); }
  if (dance == 29 ) { lDin(); }
}

void d2Sub( int Adance, int Bdance, int Cdance, int Ddance){
  if (subDone == 1) {    subTimer = millis();    subDone = 0;
  } 
  currentMillis = millis();
  nowSubTime = currentMillis - subTimer ;
  if ( nowSubTime < 7 ){  stopTurn(); target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowSubTime <  qfrequency  ){ dlist( Adance ); dlist( Bdance );// Lin
  } else if ( nowSubTime <  (2 * qfrequency) ){ dlist( Cdance ); dlist( Ddance ); //arm out
  } else {
    subTimer = millis(); //reset the timer
    subDone = 1;
  }   
 } 
 
void d3Sub( int Adance, int Bdance, int Cdance, int Ddance, int Edance, int Fdance){
  if (subDone == 1) {    subTimer = millis();    subDone = 0;
  } 
  currentMillis = millis();
  nowSubTime = currentMillis -  subTimer ;
  if ( nowSubTime < 7 ){  stopTurn(); target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowSubTime <  400  ){ dlist( Adance ); dlist( Bdance );// Lin
  } else if ( nowSubTime <  800 ){ dlist( Cdance ); dlist( Ddance ); //arm out
  } else if ( nowSubTime <  1200 ){ dlist( Edance ); dlist( Fdance ); //arm out
  } else {
    subTimer = millis(); //reset the timer
    subDone = 1;
  }
 } 
 void d4Sub( int Adance, int Bdance, int Cdance, int Ddance,int Edance, int Fdance, int Gdance, int Hdance){
  if (subDone == 1) {    subTimer = millis();    subDone = 0;
  } 
  currentMillis = millis();
  nowSubTime = currentMillis - subTimer ;
  if ( nowSubTime < 7 ){  stopTurn(); //target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowSubTime <  qfrequency  ){ dlist( Adance ); dlist( Bdance );
  } else if ( nowSubTime <  (2 * qfrequency) ){ dlist( Cdance ); dlist( Ddance ); 
  } else if ( nowSubTime <  (3 * qfrequency) ){ dlist( Edance ); dlist( Fdance );
  } else if ( nowSubTime <  (4 * qfrequency) ){ dlist( Gdance ); dlist( Hdance ); 
  } else {
    subTimer = millis(); //reset the timer
    subDone = 1;
  }
//  if ( qfrequency > 430 ){
//    servoIncrementDelay = 7;
//  } else {
//    servoIncrementDelay = 5;
//  }

  PID();

 }

 void d8Sub( int Adance, int Bdance, int Cdance, int Ddance,int Edance, int Fdance, int Gdance, int Hdance){
  if (subDone == 1) {    subTimer = millis();    subDone = 0;
  } 
  currentMillis = millis();
  nowSubTime = currentMillis - subTimer ;
  if ( nowSubTime < 7 ){  stopTurn(); //target1 = 25;   target2 = 20;  target3 = 15; target4 = 15; //doesnt have time to get here!
  } else if ( nowSubTime <  (qfrequency/2)  ){ dlist( Adance ); dlist( Bdance );
  } else if ( nowSubTime <   qfrequency      ){ dlist( Cdance ); dlist( Ddance ); 
  } else if ( nowSubTime <  (1.5 * qfrequency) ){ dlist( Edance ); dlist( Fdance );
  } else if ( nowSubTime <  (2* qfrequency) ){ dlist( Gdance ); dlist( Hdance ); 
  } else {
    subTimer = millis(); //reset the timer
    subDone = 1;
  }
  //servoIncrementDelay = 5;
  PIDfast();
 }
 
void servoIncrement() {
   //move the servos incrementally according to current targets 
  if ( pos1 < target1 ){ pos1 = pos1 +1 ; }  if ( pos1 > target1 ){ pos1 = pos1 -1 ; }
  myservo1.write(pos1);
  if ( pos2 < target2 ){ pos2 = pos2 +1 ; }  if ( pos2 > target2 ){ pos2 = pos2 -1 ; }
  myservo2.write(pos2);
  if ( pos3 < target3 ){ pos3 = pos3 +1 ; }  if ( pos3 > target3 ){ pos3 = pos3 -1 ; }
  myservo3.write(pos3);
  if ( pos4 < target4 ){ pos4 = pos4 +1 ; }  if ( pos4 > target4 ){ pos4 = pos4 -1 ; }
  myservo4.write(pos4);
 // delay(servoIncrementDelay);
}


void PID() {
  e1 = abs(target1 - pos1);
  e2 = abs(target2 - pos2);
  e3 = abs(target3 - pos3);
  e4 = abs(target4 - pos4);
  maxError = max(e1, e2);
  maxError = max(maxError, e3);
  maxError = max(maxError, e4);
  if ( maxError > 20 ) {
    servoIncrementDelay = 7;
  } else { 
    servoIncrementDelay = map( maxError, 0, 20, 20, 7); 
  }  
}

void PIDfast() {
  e1 = abs(target1 - pos1);
  e2 = abs(target2 - pos2);
  e3 = abs(target3 - pos3);
  e4 = abs(target4 - pos4);
  maxError = max(e1, e2);
  maxError = max(maxError, e3);
  maxError = max(maxError, e4);
  if ( maxError > 15 ) {
    servoIncrementDelay = 5;
  } else { 
    servoIncrementDelay = map( maxError, 0,15, 12, 5); 
  }  
}


void stopTurn() {
  if (motorMode != 0){
     analogWrite(ledPins[0], 0);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    analogWrite(ledPins[3], 0);
    digitalWrite(ledPins[4], LOW);  
    digitalWrite(ledPins[5], LOW); 
    motorMode=0;
  }
}
void leftTurn()  {
  if (motorMode != 1) {
    analogWrite(ledPins[0], 45);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    analogWrite(ledPins[3], 45);
    digitalWrite(ledPins[4], LOW);  
    digitalWrite(ledPins[5], HIGH);
    motorMode = 1; //1=left
  } 
}
void rightTurn()  {
  if (motorMode != 2) {
    analogWrite(ledPins[0], 45);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH);
    analogWrite(ledPins[3], 45);
    digitalWrite(ledPins[4], HIGH);  
    digitalWrite(ledPins[5], LOW);
    motorMode = 2; //2=right
  } 
}
void backTurn()  {
  if (motorMode != 4) {
     analogWrite(ledPins[0], 45);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH);
    analogWrite(ledPins[3], 45);
    digitalWrite(ledPins[4], LOW);  
    digitalWrite(ledPins[5], HIGH);
    motorMode = 4; //4=backward
  } 
}
void forwardTurn()  {
  if (motorMode != 3) {
    analogWrite(ledPins[0], 45);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    analogWrite(ledPins[3], 45);
    digitalWrite(ledPins[4], HIGH);  
    digitalWrite(ledPins[5], LOW);
    motorMode = 3; //3=forward
  } 
}
