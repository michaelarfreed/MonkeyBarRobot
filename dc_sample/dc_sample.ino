//MOTOR AND SERVO
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP32Encoder.h>
#include <ArduinoJson.h>        // for wifi package parsing
#include "ESPAsyncWebServer.h"  // for matlab/wifi
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
int encoder_ticks_per_rotation=_tick*gear_ratio;
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

int servo_1_pwm = 0;
int servo_2_pwm = 0;
int servo_3_pwm = 0;

int servo_close_pwm = MIN_PULSE + (MAX_PULSE - MIN_PULSE)*0.1;
int servo_open_pwm  = MIN_PULSE + (MAX_PULSE - MIN_PULSE)*0.9;

// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

//Motor B
int motor2Pin3 = 32; 
int motor2Pin4 = 33; 
int enable2Pin = 25; 

// Setting PWM properties
const int freq1 = 30000;
const int freq2 = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 0;
const int resolution1 = 8;
const int resolution2 = 8;
int dutyCycle1 = 200;
int dutyCycle2 = 200;

void setup() {
  // Serial set-up
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }

  //encoder parameter
  Serial.println("Setting up encoder code");
  ESP32Encoder::useInternalWeakPullResistors=UP;
  encoder1.attachHalfQuad(19, 18); // (A,B)/19->white
  encoder2.attachHalfQuad(19, 18); // (A,B)/19->white
  encoder1.clearCount();
  encoder2.clearCount();
  
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
  pinMode(motor2Pin3, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq1, resolution1);
  ledcSetup(pwmChannel2, freq2, resolution2);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);

  // WiFi
  Serial.println("setup WiFi");
  setup_server();

  Serial.println("=======================\nDone setup\n=======================\n");
}

void loop() {

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
    processArmPacket(motor_index);
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

void processArmPacket(int index) {
  if (motor_index == 0) {
    moveLeftArm();
  } else { // motor_index == 1
    moveRightArm();
  }
}

void moveLeftArm() {
  float currentPosMm = encoderToMm((int32_t)encoder1.getCount());
  if (currentPosMm > state_float) {
    // reverse
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);

  } else if (currentPosMm < state_float) {
    // forward
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  } else {
    // off
  }

  while (abs(currentPosMm - state_float) > 5) { // keep moving until w/in 5 mm of target
    currentPosMm = encoderToMm((int32_t)encoder1.getCount());
  }

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
}

void moveRightArm() {
  float currentPosMm = encoderToMm((int32_t)encoder2.getCount());
  if (currentPosMm > state_float) {
    // reverse
    // TODO: these directions might need to change after mounted
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    
  } else if (currentPosMm < state_float) {
    // forward
    // TODO: these directions might need to change after mounted
    digitalWrite(motor2Pin3, HIGH);
    digitalWrite(motor2Pin4, LOW);
  } else {
    // off
  }

  while (abs(currentPosMm - state_float) > 5) { // keep moving until w/in 5 mm of target
    currentPosMm = encoderToMm((int32_t)encoder2.getCount());
  }

  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);

}

float encoderToMm(int encoderVal) {
  return encoderVal * encoderTickToMm;
}