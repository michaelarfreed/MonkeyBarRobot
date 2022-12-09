//MOTOR AND SERVO
#include <Adafruit_PWMServoDriver.h>
#include <ESP32Encoder.h>
#include <ArduinoJson.h>        // for wifi package parsing
// #include "ESPAsyncWebServer.h"  // for matlab/wifi
// #include <WiFi.h>               // for wifi

// wifi communication with matlab
const char* ssid = "Madhu-ESP-Network";  
const char* password = "123456789"; 

// AsyncWebServer server(80);
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
//Servo
int pos = 0;
int encoder_count=48;
int gear_ratio=48;

//gear ratio=1/48
int rotation=encoder_count*gear_ratio;
int rotation_quarter=rotation/4;

float gear_diameter=29.75; //mm
float circumference=PI*gear_diameter;

float one_tick=circumference/rotation;


//declare encoder object
ESP32Encoder encoder;
//servo
Adafruit_PWMServoDriver control = Adafruit_PWMServoDriver(0x40, Wire);
int servo_1 = 0;
int servo_2 = 1;
int servo_3 = 2;

int servo_1_pwm = 0;
int servo_2_pwm = 0;
int servo_3_pwm = 0;

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
  //encoder parameter
  ESP32Encoder::useInternalWeakPullResistors=UP;
  encoder.attachHalfQuad(19, 18); // (A,B)/19->white
  encoder.clearCount();
  //servo
  control.begin();
  control.setPWMFreq(FREQ);
  control.setOscillatorFrequency(27000000);
  
  // sets the pins as outputs:
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

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");

  //Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }

  // WiFi
  Serial.println("setup WiFi");
  // setup_server();

  Serial.println("=======================\nDone setup\n=======================\n");
}

void loop() {
  //Motor 2
  //Serial.println(one_tick);
  dutyCycle2 = 200;
  Serial.println("Motor 2");
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  ledcWrite(pwmChannel2, dutyCycle2);
  while (((int32_t)encoder.getCount())*one_tick<50){
    // ledcWrite(pwmChannel2, dutyCycle2);   
    //Serial.print("Forward with duty cycle: ");
    //Serial.println(dutyCycle2);
    //dutyCycle2 = dutyCycle2 + 5;
    //delay(500);
    Serial.println((int32_t)encoder.getCount()*one_tick);
  }
  
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  encoder.clearCount();
  delay(2000);

  //Serial.println((int32_t)encoder.getCount());
  //Serial.println(enc_sample);
}

void setup_server() 
{
  // WiFi.softAP(ssid, password);
  // IPAddress IP = WiFi.softAPIP();
  // Serial.print("IP Address = "); Serial.println(IP);

  // setup for recieving from matlab
  // server.on("/receive",HTTP_POST,[](AsyncWebServerRequest * request){},
  //   NULL,[](AsyncWebServerRequest * request, uint8_t *data_in, size_t len, size_t index, size_t total) {

  //     String msg = String((char *)data_in, len); // takes the given value 

  //    // parse the json message. the format is 
  //     DeserializationError error = deserializeJson(jsonBuffer, msg); 
  //     if (error) {
  //       request->send_P(200, "text/plain", "-1"); 
  //       Serial.println("error in json parsing");
  //       return;
  //     }

  //     command_type = jsonBuffer["commandType"].as<String>();
  //     motor_index  = jsonBuffer["index"];
  //     state_bool   = jsonBuffer["stateBool"];
  //     state_float  = jsonBuffer["stateFloat"];

  //     processWifiPacket();

  //     request->send_P(200, "text/plain", "1"); 

  // });


  // Start server (needed)
  // server.begin();  

}

// void processWifiPacket(jsonBuffer) {

// }

void processWifiPacket() {
  if (command_type.equals("gripper")) {
    processGripperPacket();
  } else { //command_type.equals("arm")
    processArmPacket(motor_index);
  }
}

void processGripperPacket() {
  if (state_bool == 0) {
    closeGripper(motor_index);
  } else {
    openGripper(motor_index);
  }
}

void openGripper(int index) {
  if(index=1){
    //open servo 1
    Serial.println("Open servo 1");
  };
  return;
}

void closeGripper(int index) {
  //servos[index];
  if(index=2){
    //open servo 1
    Serial.println("Close servo 1");
  };
  return;
}

void processArmPacket(int index) {
  return;
}