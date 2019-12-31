#include "OSCSender.h"

OSCSender::OSCSender(IPAddress outIp, int outPort){
  _outIp = outIp;
  _outPort = outPort;
  
  WiFi.begin(_ssid, _pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  printWifiStatus();
}


void OSCSender::sendMessage(){
  OSCMessage msg("/test");
  msg.add("Hello from ESP8266");
  _udp.beginPacket(_outIp, _outPort);
  msg.send(_udp);
  _udp.endPacket();
  msg.empty();
  delay(5);
}


void OSCSender::printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print your WiFi shield's IP address:
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
 
  Serial.println("Starting UDP");
  _udp.begin(LOCALHOST);
  Serial.print("Local port: ");
  Serial.println(_udp.localPort());
}
