#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <Wire.h>
const char* ssid = "Gatao 2.4 Ghz"; // Nome da rede
const char* password = "saginmoi"; // Senha da rede
const char* websockets_server_host = "192.168.100.5"; // IP do servidor websocket
const int websockets_server_port = 3000; // Porta de conexão do servidor

// Utilizamos o namespace de websocket para podermos utilizar a classe WebsocketsClient
using namespace websockets;

// Objeto websocket client
WebsocketsClient client;
const int led = 3;


void setup() 
{
    Serial.begin(115200);
    
    
    pinMode(led, OUTPUT);
    
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(",");
        delay(1000);
    }
    Serial.println("Connected to Wifi, Connecting to server.");
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

void loop() 
{
      client.onMessage([&](WebsocketsMessage message)
      {
          Serial.print("Got Message: ");
          Serial.println(message.data());
  
          // Ligamos/Desligamos o led de acordo com o comando
          if(message.data().equalsIgnoreCase("ON"))
              digitalWrite(led, HIGH);
          else
          if(message.data().equalsIgnoreCase("OFF"))
              digitalWrite(led, LOW);
      });
//      Serial.print("pl");  
//      Serial.println(pl);
   
    //  De tempo em tempo, o websockets client checa por novas mensagens recebidas
    if(client.available()) {
        client.poll();
         client.send("esp: ");
    
    }
    delay(300);
}

void sendServer(){

}
