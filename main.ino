
//#include <Wire.h>
#include <SFE_MMA8452Q.h>
#include <Servo.h>
Servo ESC;

MMA8452Q acelerometro(0x1C);

void setup()
{
  Serial.begin(9600);
  ESC.attach(9, 1000, 2000);
  Serial.println("Teste de comunicacao MMA8452");
  acelerometro.init();
  ESC.write(0);
}

void loop()
{
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
    delay(100);
    //Selecione a linha abaixo para mostra os valores digitais
    printCalculatedAccels();
    
    //Mostra a orientacao (retrato/paisagem/flat)
    Serial.println();
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

void printCalculatedAccels()
{ 
  Serial.print("x ");
  Serial.print(acelerometro.cx);
  Serial.print(" y");
  Serial.print(acelerometro.cy);
  Serial.print(" z");
  Serial.print(acelerometro.cz);

}
