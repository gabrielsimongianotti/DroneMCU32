#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

#define MPU6050_ADDR 0x69

void gyroscopeInit() 
{
  Serial.print("x ");
//  acelerometro.init();
}

//
void gyro() {
//  Serial.print("Acceleration X: ");
//  Serial.print(a.acceleration.x);
//  Serial.print(", Y: ");
//  Serial.print(a.acceleration.y);
//  Serial.print(", Z: ");
//  Serial.print(a.acceleration.z);
//  Serial.println(" m/s^2");
    mpu6050.update();
  
    int x = mpu6050.getAngleX();
    int y = mpu6050.getAngleY();

    Serial.print(x);
    Serial.print("x ");
    Serial.print(y);
    Serial.println("y ");
}

 
