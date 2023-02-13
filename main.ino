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
int speed = 30;
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
  Wire.begin();
  mpu6050.begin();

  pinMode(pauseButton, INPUT_PULLUP);
}

void loop()
{

   
//    for(int i = 0; i <= speed; i ++){
//      int engine= i;
//      acelerometro.read();
      
      int pauseMotor = digitalRead(pauseButton);
      if(pauseMotor==0){
        Serial.print("printMotor");
        Serial.println(activeMotor);
//        if(activeMotor){
          activeMotor = LOW;
//        } else {
//          activeMotor = true;
//        }
      }
      else{
        stabilizeFlight(speed);
      }
//      delay(100);
//    }
//    delay(5000);
//    for(int i = speed; i > 0; i --){
//      int engine= i;
//      acelerometro.read();
//      stabilizeFlight(engine);
//      int pauseMotor = digitalRead(pauseButton);
//      if(pauseMotor==0){  
//        rearLeftEngine.write(0);
//        rearRightEngine.write(0);
//        frontLeftEngine.write(0);
//        frontRightEngine.write(0);
//        Serial.println(pauseMotor);
//        Serial.println("clicou no botão");
//        delay(20000000);
//      }
////     delay(100);
//    }
  
}

void stabilizeFlight(int speedMotor)
{
    mpu6050.update();
  
    int x = mpu6050.getAngleX();
    int y = mpu6050.getAngleY();
    anguloZ = mpu6050.getAngleZ();
    int speedRearMotor = speedMotor + 10;
    Serial.print(x);
    Serial.print("x ");
    Serial.print(y);
    Serial.print("y ");
    Serial.print(speedMotor);
    if(x < 10 && y < 10 && activeMotor == HIGH) {
      Serial.print("rear left ");
//      Serial.print(5+speedRearMotor);//(-1 * x + 100) * speedMotor / 100);
      rearLeftEngine.write(5 + speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
    else if(x > 10 && y < 10 && activeMotor == HIGH) {
      Serial.print("rear right ");
//      Serial.print(5 + speedRearMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(5+speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
     else if(x < 10 && y > 10 && activeMotor == HIGH) {
     Serial.print("front left ");
//      Serial.print((-1 * x + 100) * speedMotor / 100);
//      Serial.print(" front right ");
//      Serial.print((x+100) * speedMotor/100);
//      Serial.print(" speedMotor:");
//      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(5 + speedMotor);
      frontRightEngine.write(speedMotor);
    }
     else if(x > 10 && y > 10 && activeMotor == HIGH) {
      Serial.print("front right ");
//      Serial.print(5 + speedMotor);
//      Serial.print(" speedMotor:");
//      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(5 + speedMotor);
    }
  Serial.println();  
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
