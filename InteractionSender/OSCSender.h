#ifndef OSCSender_H
#define OSCSender_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include "Arduino.h"

#define LOCALHOST 8888


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
  
  private: //functions

    /**
     * print out WIFI status
     */
    void printWifiStatus();
  
  private: //variables
    int status = WL_IDLE_STATUS;
    String _ssid = "linksys";
    String _pass = "";
    WiFiUDP _udp;

    IPAddress _outIp;
    unsigned int _outPort;
};

#endif
