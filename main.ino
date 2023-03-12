#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>


Servo rearLeftEngine;
Servo rearRightEngine;
Servo frontLeftEngine;
Servo frontRightEngine;
MPU6050 mpu6050(Wire);

#define pauseButton 13
#define MPU6050_ADDR 0x69 

float anguloX;
float anguloY;
float anguloZ;
int speed = 54;
int maxSpeed = 180;
boolean activeMotor = HIGH;

void setup()
{
  Serial.begin(9600);
  rearLeftEngine.attach(9, 1000, 2000);
  frontLeftEngine.attach(6, 1000, 2000);
  rearRightEngine.attach(5, 1000, 2000);
  frontRightEngine.attach(3, 1000, 2000);
  rearLeftEngine.write(0);
  rearRightEngine.write(0);
  frontLeftEngine.write(0);
  frontRightEngine.write(0);
  
  Serial.println("on drone");
  Wire.setWireTimeout(250, false);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(pauseButton, INPUT_PULLUP);
}


void loop()
{
//    if(Wire.getWireTimeoutFlag())
//    {
//        Wire.clearWireTimeoutFlag();
//        Wire.end();
//        Wire.begin();
//        // put the code to reinit MPU6050 
////        mpu6050.begin();
//    }
    int x = mpu6050.getAngleX();
    int y = mpu6050.getAngleY();

      int pauseMotor = digitalRead(pauseButton);
//      if(pauseMotor==0 || x > 30 || x < -30  || y > 30 || y < -30){
//        Serial.print("printMotor");
//        Serial.println(activeMotor);
////        if(activeMotor){
//          activeMotor = LOW;
//          rearLeftEngine.write(0);
//          rearRightEngine.write(0);
//          frontLeftEngine.write(0);
//         frontRightEngine.write(0);
//      }
//      else{
        stabilizeFlight(speed);
//      }
}


void up(int speedMotor)
{ 
  int speedRearMotor = speedMotor + 10;
  Serial.print("front engine: ");
  Serial.print(speedMotor);
  Serial.print(" Rear Engine: ");
  Serial.println(speedRearMotor);
  rearLeftEngine.write(speedRearMotor);
  rearRightEngine.write(speedRearMotor);
  frontLeftEngine.write(speedMotor);
  frontRightEngine.write(speedMotor);
}
