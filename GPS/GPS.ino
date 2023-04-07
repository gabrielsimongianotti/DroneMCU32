#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <Adafruit_Sensor.h>

const char* ssid = "Gatao 2.4 Ghz"; // Nome da rede
const char* password = "saginmoi"; // Senha da rede
const char* websockets_server_host = "192.168.100.9"; // IP do servidor websocket
const int websockets_server_port = 3000; // Porta de conexão do servidor
const int led = 3;
const int ledRed = 15;
const int ledGreen = 22;
const int ledBlue = 24;

using namespace websockets;
WebsocketsClient client;
TinyGPSPlus gps;

void setup() 
{
    Serial.begin(115200);
    Serial2.begin(9600);
  pinMode(ledRed, OUTPUT);  
  pinMode(ledGreen, OUTPUT);  
  pinMode(ledBlue, OUTPUT);   
  pinMode(led, OUTPUT);
    connectWifi();
    connectServer();
//    gyroscopeInit();
}

void loop() 
{
    client.poll();
    Serial.println("loop ");
//    connectWifi();
    digitalWrite(led, LOW);
    delay(1000);
    digitalWrite(led, HIGH);
    delay(1000);
//    while (Serial2.available() > 0)
//      if (gps.encode(Serial2.read()))
//        gyro();     
//        String sat =String(gps.satellites.value());
//        String la =String(gps.location.lat(), 7);
//        String ln =String(gps.location.lng(), 7);
//        String text = "satellites: " + gps.satellites.value();
//           
//        text = String(" sat:" + sat + ", Lat:" + la + ", Lng:" +ln+", gps.charsProcessed()"+gps.charsProcessed());
//                
//    
//        Serial.println(text);
//      if (millis() > 1000 && gps.charsProcessed() < 10)
//      {
//        Serial.println(F("No GPS detected: check wiring."));
//        while (true);
//      }
}

void displayInfo()
{
    String sat =String(gps.satellites.value());
    String la =String(gps.location.lat(), 7);
    String ln =String(gps.location.lng(), 7);
    String text = "satellites: " + gps.satellites.value();
       
    text = String(" sat:" + sat + ", Lat:" + la + ", Lng:" +ln);
            

    Serial.println(text);
    Serial.println(client.available());
    if(client.available()) {
        WebsocketsMessage msg = client.readBlocking();
      
        Serial.print("Got Message: ");
        Serial.print(msg.data());
                
        if (gps.location.isValid()){
         
            client.send(text);
            client.ping();
        }
        else
        {
            Serial.println(F("INVALID"));
        }
    }  
    else
    {
        connectServer();
    }
}
