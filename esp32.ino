
#include <WiFi.h>

const char* ssid = "Gatao 2.4 Ghz"; // Nome da rede
const char* password = "saginmoi"; // Senha da rede
const char* websockets_server_host = "192.168.100.5"; // IP do servidor websocket
const int websockets_server_port = 3000; // Porta de conexão do servidor


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
}
void loop() 
{
 digitalWrite(led, LOW);
 delay(1000);
  digitalWrite(led, HIGH);
}
