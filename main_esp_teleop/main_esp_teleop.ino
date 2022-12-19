//MOTOR AND SERVO
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_VL53L0X.h>   // for LiDAR
#include <ArduinoJson.h>        // for wifi package parsing
#include <ESP32Encoder.h>
#include "ESPAsyncWebServer.h"  // for matlab/wifi
#include <JY901.h>
#include <WiFi.h>               // for wifi     

// wifi communication with matlab
const char* ssid = "Madhu-ESP-Network";  
const char* password = "123456789"; 

AsyncWebServer server(80);
DynamicJsonDocument jsonBuffer(256);

String command_type  = "";
int motor_index   = 0;
float state_float = 0;
bool state_bool   = false; 

// constants for servo control
#define MIN_PULSE 150
#define MAX_PULSE 600 
#define FREQ 50
#define PI 3.1415926
//#define enc_sample 0

int encoder_tick_count=48;
int gear_ratio=48;

//gear ratio=1/48
int encoder_ticks_per_rotation=encoder_tick_count*gear_ratio;
int rotation_quarter=encoder_ticks_per_rotation/4;

float gear_diameter=29.75; //mm
float circumference=PI*gear_diameter;

float one_tick=circumference/encoder_ticks_per_rotation;


//declare encoder object
ESP32Encoder encoder1; // Left arm
ESP32Encoder encoder2; // Right arm
float encoderTickToMm=circumference/encoder_ticks_per_rotation;

//servo
Adafruit_PWMServoDriver control = Adafruit_PWMServoDriver(0x40, Wire);
int servo_1 = 0;
int servo_2 = 1;
int servo_3 = 2;

int servo_close_pwm = MIN_PULSE + (MAX_PULSE - MIN_PULSE)*0.1; //*0.5; // 800;  //
int servo_open_pwm  = MIN_PULSE + (MAX_PULSE - MIN_PULSE)*0.5; //*0.9; // 2000; //

// Motor A
int motor1Pin1 = 17; 
int motor1Pin2 = 5; 
int enable1Pin = 16; 

int encoder1A = 34;
int encoder1B = 35;

//Motor B
int motor2Pin3 = 33; 
int motor2Pin4 = 32; 
int enable2Pin = 23; 

int encoder2A = 36;
int encoder2B = 39;

// Setting PWM properties
const int freq1 = 30000;
const int freq2 = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 0;
const int resolution1 = 8;
const int resolution2 = 8;
int dutyCycle1 = 200;
int dutyCycle2 = 200;

// // lidar 
// Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// const int lox1xshutPin = 18;
// const int lox2xshutPin = 19;
// const int lox3xshutPin = 13;

// // IMU
// float angles  [3];


void setup() {
  // Serial set-up
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }

  //encoder parameter
  Serial.println("Setting up encoder code");
  ESP32Encoder::useInternalWeakPullResistors=UP;
  encoder1.attachHalfQuad(encoder1A, encoder1B); // (A,B)/A==> yellow, B==>White
  encoder2.attachHalfQuad(encoder2A, encoder2B); // (A,B)/19->white
  encoder1.clearCount();
  encoder2.clearCount();

  Serial.print("Initial encoder1 reading = "); Serial.println(encoder1.getCount());
  Serial.print("Initial encoder2 reading = "); Serial.println(encoder2.getCount());
  
  //servo set-up
  Serial.println("Setting up servos");
  control.begin();
  control.setPWMFreq(FREQ);
  control.setOscillatorFrequency(27000000);
  
  // DC motor setup
  Serial.println("Setting up DC motors");
  // sets the DC motor pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq1, resolution1);
  ledcSetup(pwmChannel2, freq2, resolution2);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);

  // // start IMU
  // Serial.println("IMU setup");
  // JY901.StartIIC();

  //  // LiDAR 
  // Serial.println("LiDAR setup");
  // pinMode(lox1xshutPin, OUTPUT);
  // pinMode(lox2xshutPin, OUTPUT);
  // pinMode(lox3xshutPin, OUTPUT);
  // digitalWrite(lox1xshutPin, LOW);
  // digitalWrite(lox2xshutPin, LOW);
  // digitalWrite(lox3xshutPin, LOW);

  // Serial.println("LiDAR 1 setup");
  // pinMode(lox1xshutPin, INPUT);
  // delay(150);
  // if (!lox1.begin()) {
  //   Serial.println(F("Failed to boot LiDAR 1"));
  //   while(1);
  // }
  // lox1.setAddress((uint8_t)22);
  // lox1.startRangeContinuous(); // start continuous ranging

  // Serial.println("LiDAR 2 setup");
  // pinMode(lox2xshutPin, INPUT);
  // delay(150);
  // if (!lox2.begin()) {
  //   Serial.println(F("Failed to boot LiDAR 2"));
  //   while(1);
  // }
  // lox2.setAddress((uint8_t)22);
  // lox2.startRangeContinuous(); // start continuous ranging

  // Serial.println("LiDAR 3 setup");
  // pinMode(lox3xshutPin, INPUT);
  // delay(150);
  // if (!lox3.begin()) {
  //   Serial.println(F("Failed to boot LiDAR 3"));
  //   while(1);
  // }
  // lox3.setAddress((uint8_t)22);
  // lox3.startRangeContinuous(); // start continuous ranging

  // WiFi
  Serial.println("setup WiFi");
  setup_server();

  Serial.println("=======================\nDone setup\n=======================\n");
}

void loop() {
  // Serial.print(  "lidar1: "); Serial.print(getLidar1Reading());
  // Serial.print("; lidar2: "); Serial.print(getLidar2Reading());
  // Serial.print("; lidar3: "); Serial.println(getLidar3Reading());

  // get_angles(angles);
  // Serial.print(  "angles[0] = "); Serial.print(angles[0]);
  // Serial.print("; angles[1] = "); Serial.print(angles[1]);
  // Serial.print("; angles[2] = "); Serial.print(angles[2]); Serial.print("\n");

  delay(50);
}

void setup_server() 
{
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP Address = "); Serial.println(IP);

  // setup for recieving from matlab
  server.on("/receive",HTTP_POST,[](AsyncWebServerRequest * request){},
    NULL,[](AsyncWebServerRequest * request, uint8_t *data_in, size_t len, size_t index, size_t total) {

      String msg = String((char *)data_in, len); // takes the given value 

     // parse the json message. the format is 
      DeserializationError error = deserializeJson(jsonBuffer, msg); 
      if (error) {
        request->send_P(200, "text/plain", "-1"); 
        Serial.println("error in json parsing");
        return;
      }

      command_type = jsonBuffer["commandType"].as<String>();
      motor_index  = jsonBuffer["index"];
      state_bool   = jsonBuffer["stateBool"];
      state_float  = jsonBuffer["stateFloat"];

      Serial.print("received wifi package: command_type = "); Serial.print(command_type);
      Serial.print("; motor_index = "); Serial.print(motor_index);
      Serial.print("; stateBool = ");   Serial.print(state_bool);
      Serial.print("; stateFloat = ");  Serial.print(state_float);
      Serial.print("\n");

      processWifiPacket();

      request->send_P(200, "text/plain", "1"); 

  });

  // Start server (needed)
  server.begin();  

}

void processWifiPacket() {
  if (command_type.equals("gripper")) {
    processGripperPacket();
  } else { //command_type.equals("arm")
    processArmPacket();
  }
}

void processGripperPacket() {
  if (state_bool == 0) {
    closeGripper();
  } else {
    openGripper();
  }
}

void openGripper() {
  control.setPWM(motor_index, 0, servo_open_pwm);
}

void closeGripper() {
  control.setPWM(motor_index, 0, servo_close_pwm);
}

void processArmPacket() {
  if (motor_index == 0) {
    moveLeftArm();
  } else { // motor_index == 1
    moveRightArm();
  }
}

void moveLeftArm() {
  Serial.println("moving left arm");
  float currentPosMm = encoderToMm((int32_t)encoder1.getCount());
  if (currentPosMm > state_float) {
    // reverse
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel1, dutyCycle1);

  } else if (currentPosMm < state_float) {
    // forward
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel1, dutyCycle1);
  } else {
    // off
  }

  while (abs(currentPosMm - state_float) > 5) { // keep moving until w/in 5 mm of target
    Serial.print("encoder = "); Serial.println(currentPosMm);
    currentPosMm = encoderToMm((int32_t)encoder1.getCount());
    // delay(50);
  }

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
}

void moveRightArm() {
  Serial.println("moving right arm");
  Serial.print("dutyCycle2 = "); Serial.println(dutyCycle2);
  float currentPosMm = -1*encoderToMm((int32_t)encoder2.getCount());
  if (currentPosMm > state_float) {
    // reverse
    // TODO: these directions might need to change after mounted
    digitalWrite(motor2Pin3, HIGH);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannel2, dutyCycle2);
    
  } else if (currentPosMm < state_float) {
    // forward
    // TODO: these directions might need to change after mounted
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    ledcWrite(pwmChannel2, dutyCycle2);

  } else {
    // off
  }

  while (abs(currentPosMm - state_float) > 5) { // keep moving until w/in 5 mm of target
    Serial.print("encoder2 = "); Serial.println(currentPosMm);
    currentPosMm = -1*encoderToMm((int32_t)encoder2.getCount());
    // delay(50);
  }

  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);

}

float encoderToMm(int encoderVal) {
  // Serial.print("encoderVal = ");  Serial.println(encoderVal);
  return encoderVal * encoderTickToMm;
}

// void get_angles(float (& angle) [3])
// {
//   // propogate angles from IMU
//   JY901.GetAngle();
//   angle[0] = (float)JY901.stcAngle.Angle[0]/32768*180;
//   angle[1] = (float)JY901.stcAngle.Angle[1]/32768*180;
//   angle[2] = (float)JY901.stcAngle.Angle[2]/32768*180;
// }

// int getLidar1Reading() {
//   return lox1.readRange();
// }

// int getLidar2Reading() {
//   return lox2.readRange();
// }

// int getLidar3Reading() {
//   return lox3.readRange();
// }