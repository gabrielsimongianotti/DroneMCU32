
void connectWifi(){

  digitalWrite(ledRed, HIGH);
  Serial.println("ledRed!");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(ledBlue, HIGH);
    Serial.print(",");
    digitalWrite(ledBlue, LOW);
    delay(1000);
  }
  Serial.println("Connected to Wifi, Connecting to server.");
}

void connectServer(){
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
   digitalWrite(ledRed, HIGH);
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
