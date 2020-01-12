/**
 * Purpose: Sends accelorometer and distance pure data
 * @author Christopher Heiden, ...
 * @version 0.4 31/12/2019
 */

#include "Accelorometer.h" //[works]
#include "DistanceSensor.h" //[works]
//#include "OSCSender.h" //[create network works; sending udp not]

#define SDAPIN D2
#define SCLPIN D1
//#define PORT 9999

Accelorometer acc;
DistanceSensor distanceSensor(SDAPIN, SCLPIN);
//const IPAddress outIp(192,168,1,110);
//OSCSender osc(outIp, PORT);

bool test;
/**
 * defines the baudrate
 */
void setup() {
  test = false;
  Serial.begin(115200);
}

/**
 *  loop through the code to send sensor values to pure data
 */
void loop() {
  /*****Test distance sensor******/
  int distance = distanceSensor.getDistance();
  Serial.println(distance);
  Serial.println();
  Serial.println();
  /*****Test accelorometer******/
  acc.getAccData();
  
  //osc.sendMessage();
  //acc.getAccData();
  
}
