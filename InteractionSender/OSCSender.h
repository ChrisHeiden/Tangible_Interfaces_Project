#ifndef OSCSender_H
#define OSCSender_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include "Arduino.h"

/*
 * OSCSender object for OSC packaging
 */
class OSCSender {

  public: //functions

    /**
     * constructor of the object OSCSender that initialises variables and initialises WIFI network
     * @param {IPAddress} outIp - ip address of the network
     * @param {int} outPort - port of the message
     */
    OSCSender(IPAddress outIp, int outPort);

    /**
     * sends OSC messages
     */
    void sendMessage();
  
  private: //variables
    const char *_ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
    const char *_password = "test1234";   // The password required to connect to it, leave blank for an open network
    WiFiUDP _udp;

    IPAddress _outIp; 
    unsigned int _outPort;
    const unsigned int _localPort = 8888;
};

#endif
