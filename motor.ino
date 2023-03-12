void stabilizeFlight(int speedMotor){
    mpu6050.update();
  
    int x = mpu6050.getAngleX();
    int y = mpu6050.getAngleY();
    anguloZ = mpu6050.getAngleZ();
    int speedRearMotor = speedMotor + 5;
    Serial.print(x);
    Serial.print("x ");
    Serial.print(y);
    Serial.print("y ");
    Serial.print(speedMotor);
    if(x < 0 && y < 0 && activeMotor == HIGH) {
      Serial.print("rear left ");
//      Serial.print(5+speedRearMotor);//(-1 * x + 100) * speedMotor / 100);
      Serial.print(speedMotor);
      rearLeftEngine.write(5 + speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
    else if(x > 0 && y < 0 && activeMotor == HIGH) {
      Serial.print("rear right ");
      Serial.print(speedRearMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(5+speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
     else if(x < 0 && y > 0 && activeMotor == HIGH) {
     Serial.print("front left ");
//      Serial.print((-1 * x + 100) * speedMotor / 100);
//      Serial.print(" front right ");
//      Serial.print((x+100) * speedMotor/100);
//      Serial.print(" speedMotor:");
      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(5 + speedMotor);
      frontRightEngine.write(speedMotor);
    }
     else if(x > 0 && y > 0 && activeMotor == HIGH) {
      Serial.print("front right ");
//      Serial.print(5 + speedMotor);
//      Serial.print(" speedMotor:");
      Serial.print(speedMotor);
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(5 + speedMotor);
    }else if(activeMotor == HIGH) {
      rearLeftEngine.write(speedRearMotor);
      rearRightEngine.write(speedRearMotor);
      frontLeftEngine.write(speedMotor);
      frontRightEngine.write(speedMotor);
    }
    Serial.println();  
}
