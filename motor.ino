#include <Servo.h>

Servo ESC;

void setup() {
  ESC.attach(9,1000,2000);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  for(int i = 0; i < 180; i ++){
   Serial.println(i);
   ESC.write(i);
   delay(100);
  }
  for(int i = 180; i > 0; i --){
   Serial.println(i);
   ESC.write(i);   
   delay(100);
  }
  delay(5000);
}