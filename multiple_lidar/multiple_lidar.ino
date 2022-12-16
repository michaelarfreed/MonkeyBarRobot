#include <Wire.h>
#include <Adafruit_VL53L0X.h> 
#include <JY901.h>

Adafruit_VL53L0X sensor;
Adafruit_VL53L0X sensor2;
Adafruit_VL53L0X sensor3;

void setup()
{

  //IMU SETUP
  Serial.begin(115200);
  Serial.println("starting IMU setup");
  JY901.StartIIC();
  Serial.println("done IMU setup");

  Serial.println("starting LIDAR setup");
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.println("writing LIDAR pin");
  delay(100);
  digitalWrite(19, LOW);
  Serial.println("writing LIDAR pin 2");
  digitalWrite(18, LOW);
  Serial.println("writing LIDAR pin 3");
  digitalWrite(13, LOW);
  Serial.println("done LIDAR pin setup");

  delay(500);
  Wire.begin();


  Serial.begin (115200);

  //SENSOR
  Serial.println("setting up lidar 1");
  pinMode(19, INPUT);
  delay(150);
  Serial.println("00");
  sensor.begin();
  Serial.println("01");
  delay(100);
  sensor.setAddress((uint8_t)22);
  Serial.println("02");

  //SENSOR 2
  Serial.println("setting up lidar 2");
  pinMode(18, INPUT);
  delay(150);
  sensor2.begin();
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)25);
  Serial.println("04");

  //SENSOR 3
  Serial.println("setting up lidar 3");
  pinMode(13, INPUT);
  delay(150);
  sensor3.begin();
  Serial.println("05");
  delay(100);
  sensor3.setAddress((uint8_t)28);
  Serial.println("06");

  Serial.println("");
  Serial.println("addresses set");
  Serial.println("");
  Serial.println("");



  // sensor.setTimeout(500);
  // sensor2.setTimeout(500);
  // sensor3.setTimeout(500);


}

void loop()
{
  Serial.println("__________________________________________________________________");
  Serial.println("");
  Serial.println("=================================");
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  //IMU Display 
  JY901.GetAcc();
  Serial.print("Acc:");Serial.print((float)JY901.stcAcc.a[0]/32768*16);Serial.print(" ");Serial.print((float)JY901.stcAcc.a[1]/32768*16);Serial.print(" ");Serial.println((float)JY901.stcAcc.a[2]/32768*16);
  
  JY901.GetGyro();  
  Serial.print("Gyro:");Serial.print((float)JY901.stcGyro.w[0]/32768*2000);Serial.print(" ");Serial.print((float)JY901.stcGyro.w[1]/32768*2000);Serial.print(" ");Serial.println((float)JY901.stcGyro.w[2]/32768*2000);

  JY901.GetAngle();
  Serial.print("Angle:");Serial.print((float)JY901.stcAngle.Angle[0]/32768*180);Serial.print(" ");Serial.print((float)JY901.stcAngle.Angle[1]/32768*180);Serial.print(" ");Serial.println((float)JY901.stcAngle.Angle[2]/32768*180);


  //for (byte i = 1; i < 120; i++)
  for (byte i = 1; i < 30; i++)
  {

    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println("=================================");


  //CHECK DISTANCES
  long DISTANCE_FWD = (sensor.readRange()/25.4001);
  long DISTANCE_FLT = (sensor2.readRange()/25.4001);
  long DISTANCE_FRT = (sensor3.readRange()/25.4001);

  //FWD OR SENSOR
  if (sensor.timeoutOccurred())
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 1 Distance FWD (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 1 Distance FWD   (feet): ");
    Serial.println(DISTANCE_FWD/12);
    Serial.print("Sensor 1 Distance FWD (inches): ");
    Serial.println(DISTANCE_FWD);
    Serial.println("_________________________________");
    Serial.println("");
  }

  //FLT OR SENSOR2
  if (sensor2.timeoutOccurred())
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 2 Distance FLT (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 2 Distance FLT   (feet): ");
    Serial.println(DISTANCE_FLT/12);
    Serial.print("Sensor 2 Distance FLT (inches): ");
    Serial.println(DISTANCE_FLT);
    Serial.println("_________________________________");
    Serial.println("");
  }
  
  //FRT OR SENSOR3
  if (sensor3.timeoutOccurred())
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 3 Distance FRT (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    Serial.println("_________________________________");
    Serial.print("Sensor 3 Distance FRT   (feet): ");
    Serial.println(DISTANCE_FRT/12);
    Serial.print("Sensor 3 Distance FRTD (inches): ");
    Serial.println(DISTANCE_FRT);
    Serial.println("_________________________________");
    Serial.println("");
  }


  
  Serial.println("__________________________________________________________________");
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();


  
  delay(2000);//can change to a lower time like 100
}