#include "OSCSender.h"

OSCSender::OSCSender(IPAddress outIp, int outPort){
  _outIp = outIp;
  _outPort = outPort;
  
  WiFi.softAP(_ssid, _password);            
  _udp.begin(_localPort);
}


void OSCSender::sendMessage(){
  OSCMessage msg("/test");
  msg.add("Hello from ESP8266");
  _udp.beginPacket(_outIp, _outPort);
  msg.send(_udp);
  _udp.endPacket();
  msg.empty();
  delay(500);
}
