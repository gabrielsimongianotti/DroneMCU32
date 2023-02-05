#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

const char* ssid = "Gatao 2.4 Ghz"; // Nome da rede
const char* password = "saginmoi"; // Senha da rede
const char* websockets_server_host = "192.168.100.5"; // IP do servidor websocket
const int websockets_server_port = 3000; // Porta de conexão do servidor
const int led = 3;

using namespace websockets;
WebsocketsClient client;
TinyGPSPlus gps;

void setup() 
{
    Serial.begin(115200);
    Serial2.begin(9600);
    delay(3000);
    pinMode(led, OUTPUT);
    
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(",");
        delay(1000);
    }
    Serial.println("Connected to Wifi, Connecting to server.");
    connectServer();
}
void loop() 
{
   client.poll();
   digitalWrite(led, LOW);
   delay(1000);
  digitalWrite(led, HIGH);
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();     
    if (millis() > 1000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
      while (true);
    }
}
void connectServer(){
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
  if(connected) 
  {
      Serial.println("Connected!");
  }
  else
  {
      Serial.println("Not Connected!");
      return;
  }
}

void displayInfo()
{
    Serial.println(client.available());
    if(client.available()) {
        WebsocketsMessage msg = client.readBlocking();
        String text = "satellites: " + gps.satellites.value();
        
        Serial.print("Got Message: ");
        Serial.print(msg.data());
                
        if (gps.location.isValid()){
            String sat =String(gps.satellites.value());
            String la =String(gps.location.lat(), 7);
            String ln =String(gps.location.lng(), 7);
            text = String("sat:" + sat + ",Lat:" + la + ",Lng:" +ln);
            

            Serial.println(text);
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
