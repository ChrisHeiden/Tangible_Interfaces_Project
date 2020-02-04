#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "TangibleInteractionProject";
ESP8266WebServer server(80); 

void handleRoot() {
  String s = "Music Data: Distance[21], Orientation[14,50,10], Acceleration[1,1,1]";  
  server.send(200,"text/plain",s);      
}

void setup() {
  delay(200);                          
  Serial.begin(115200);                
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();     
  server.on("/", handleRoot);           
  server.begin();                       
}

void loop() {
  server.handleClient();
}
