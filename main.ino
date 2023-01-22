#include <SFE_MMA8452Q.h>
#include <Servo.h>
Servo rearLeftEngine;
Servo rearRightEngine;
Servo frontLeftEngine;
Servo frontRightEngine;

MMA8452Q acelerometro(0x1C);
int speed = 80;
int maxSpeed = 180;
#define pauseButton 13
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
  acelerometro.init();

  pinMode(pauseButton, INPUT_PULLUP);
}

void loop()
{
  if (acelerometro.available() )
  {
    acelerometro.read();
   
    for(int i = 0; i <= speed; i ++){
      int engine= i;
      acelerometro.read();
      up(engine);
      int pauseMotor = digitalRead(pauseButton);
      if(pauseMotor==0){
        rearLeftEngine.write(0);
        rearRightEngine.write(0);
        frontLeftEngine.write(0);
        frontRightEngine.write(0);
        Serial.println(pauseMotor);
        Serial.println("clicou no botão");
        delay(200000);
      }
      delay(100);+
    }
    delay(5000);
    for(int i = speed; i > 0; i --){
      int engine= i;
      acelerometro.read();
      up(engine);
      int pauseMotor = digitalRead(pauseButton);
      if(pauseMotor==0){  
        rearLeftEngine.write(0);
        rearRightEngine.write(0);
        frontLeftEngine.write(0);
        frontRightEngine.write(0);
        Serial.println(pauseMotor);
        Serial.println("clicou no botão");
        delay(200000);
      }
//     delay(100);
    }
  }
}

void stabilizeFlight(int speedMotor)
{
   int x = acelerometro.cx * 100;
   int y = acelerometro.cy * 100;
   int speedRearMotor = speedMotor + 10;
//   Serial.print(x);
//   Serial.print("x ");
//   Serial.print(y);
//   Serial.print("y ");
//  Serial.print(speedMotor);
    if(x < 10 && y < 10) {
      Serial.print("rear left ");
      Serial.print( (-1 * x + 100) * speedMotor / 100);
      rearLeftEngine.write((-1 * x + 100) * speedRearMotor / 100);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
    else if(x > 10 && y < 10) {
      Serial.print("rear right ");
      Serial.print( (x+100) * speedMotor/100);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write((x+100) * speedRearMotor/100);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
     else if(x < 10 && y > 10) {
      Serial.print("front left ");
      Serial.print((-1 * x + 100) * speedMotor / 100);
      Serial.print(" front right ");
      Serial.print((x+100) * speedMotor/100);
      Serial.print(" speedMotor:");
      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write((-1 * x + 100) * speedMotor / 100);
      frontRightEngine.write(speedMotor);
    }
     else if(x > 10 && y > 10) {
      Serial.print("front right ");
      Serial.print((x+100) * speedMotor/100);
      Serial.print(" speedMotor:");
      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write((x+100) * speedMotor/100);
    }
  Serial.println("speedMotor");  
}

void up(int speedMotor)
{ 
  int speedRearMotor = speedMotor + 17;
  Serial.print("front engine: ");
  Serial.print(speedMotor);
  Serial.print(" Rear Engine: ");
  Serial.println(speedRearMotor);
  rearLeftEngine.write(speedRearMotor);
  rearRightEngine.write(speedRearMotor);
  frontLeftEngine.write(speedMotor);
  frontRightEngine.write(speedMotor);
}
