#include <SFE_MMA8452Q.h>
#include <Servo.h>
Servo rearLeftEngine;
Servo rearRightEngine;
Servo frontLeftEngine;
Servo frontRightEngine;

MMA8452Q acelerometro(0x1C);
int speed = 50;
int maxSpeed = 180;
void setup()
{
  Serial.begin(9600);
  rearLeftEngine.attach(9, 1000, 2000);
  frontLeftEngine.attach(6, 1000, 2000);
  rearRightEngine.attach(5, 1000, 2000);
  frontRightEngine.attach(3, 1000, 2000);
  Serial.println("Teste de comunicacao MMA8452");
  acelerometro.init();
  rearLeftEngine.write(0);
  rearRightEngine.write(0);
  frontLeftEngine.write(0);
  frontRightEngine.write(0);
}

void loop()
{
  
//
//  delay(5000);
//  for(int i = 0; i < 180; i ++){
//   Serial.println(i);
//   rearLeftEngine.write(i);
//   rearRightEngine.write(i);
//   frontLeftEngine.write(i);
//   frontRightEngine.write(i);
//   delay(100);
//  }
//  for(int i = 180; i > 0; i --){
//   Serial.println(i);
//   rearLeftEngine.write(i);
//   rearRightEngine.write(i);
//   frontLeftEngine.write(i);
//   frontRightEngine.write(i);
//   delay(100);
//  }
//  delay(5000);

  //A linha abaixo aguarda o envio de novos dados pelo acelerometro
  if (acelerometro.available())
  {
    //Efetua a leitura dos dados do sensor
    acelerometro.read();
    //acelerometro.read() atualiza dois grupos de variaveis:
    //* int x, y, e z armazena o valor de 12 bits lido do
    //acelerometro
    // * float cx, cy, e cz armazena o calculo da aceleracao
    //dos valores de 12 bits. Essas variaveis estao em
    //unidades de "g"
    
    //Mostra as coordenadas lidas do sensor
//    printCalculatedAccels();
//    delay(100);
    //Selecione a linha abaixo para mostra os valores digitais
    stabilizeFlight();
    
    //Mostra a orientacao (retrato/paisagem/flat)
//    Serial.println();
  }
}

void printOrientation()
{
  //acelerometro.readPL() retorna um byte contendo informacoes sobre
  //a orientacao do sensor (retrato/paisagem)
  //PORTRAIT_U (Retrato Up/Para cima), PORTRAIT_D (Retrato Down/Para Baixo), 
  //LANDSCAPE_R (Paisagem right/direita), LANDSCAPE_L (Paisagem left/esquerda)
  //e LOCKOUT (bloqueio)
  byte pl = acelerometro.readPL();
  
  switch (pl)
  {
  case PORTRAIT_U:
    Serial.print("Retrato Para Cima");
    break;
  case PORTRAIT_D:
    Serial.print("Retrato Para Baixo");
    break;
  case LANDSCAPE_R:
    Serial.print("Paisagem Direita");
    break;
  case LANDSCAPE_L:
    Serial.print("Paisagem Esquerda");
    break;
  case LOCKOUT:
    Serial.print("Plano");
    break;
  }
}

void stabilizeFlight()
{
   int x = acelerometro.cx * 100;
   int y = acelerometro.cy * 100;
//   delay(100);
   Serial.print(x);
   Serial.print("x ");
   Serial.print(y);
   Serial.print("y ");
//  if(x > 0) {
//    Serial.print("x não é negativo");
//    rearLeftEngine.write(x);
//    rearRightEngine.write(x);
//    Serial.println(x);
//  }
    if(x < 0 && y < 0) {
      Serial.print("rear left ");
      Serial.print( (-1*x+100) * speed/100);
      rearLeftEngine.write((x+100) * speed/100);
      rearRightEngine.write(speed);
      frontLeftEngine.write(speed);
      frontRightEngine.write(speed);
    }
    else if(x > 0 && y < 0) {
      Serial.print("rear right ");
      Serial.print( (x+100) * speed/100);
      rearLeftEngine.write(speed);
      rearRightEngine.write((x+100) * speed/100);
      frontLeftEngine.write(speed);
      frontRightEngine.write(speed);
    }
     else if(x < 0 && y > 0) {
      Serial.print("front left ");
      Serial.print((-1 * x+100) * speed/100);
      rearLeftEngine.write(speed);
      rearRightEngine.write(speed);
      frontLeftEngine.write((x+100) * speed/100);
      frontRightEngine.write(speed);
    }
     else if(x > 0 && y > 0) {
      Serial.print("front right ");
      Serial.print((x+100) * speed/100);
      rearLeftEngine.write(speed);
      rearRightEngine.write(speed);
      frontLeftEngine.write(speed);
      frontRightEngine.write((x+100) * speed/100);
    }
  Serial.println();  
}

void printCalculatedAccels()
{ 
  Serial.print("x ");
  Serial.print(acelerometro.cx);
  Serial.print(" y");
  Serial.print(acelerometro.cy);
  Serial.print(" z");
  Serial.print(acelerometro.cz);

}
