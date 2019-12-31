/**
 * Purpose: Sends accelorometer and distance pure data
 * @author Christopher Heiden, ...
 * @version 0.3 31/12/2019
 */

#include "Accelorometer.h"
#include "DistanceSensor.h" 
#include "OSCSender.h" 

#define TRIGPIN 9
#define ECHOPIN 10
#define PORT 9999
Accelorometer acc;
DistanceSensor distanceSensor(TRIGPIN, ECHOPIN);

const IPAddress outIp(192,168,1,110);
OSCSender osc(outIp, PORT);

/**
 * defines the baudrate
 */
void setup() {
  Serial.begin(115200);
}

/**
 *  loop through the code to send sensor values to pure data
 */
void loop() {
  int distance = distanceSensor.getDistance();
  //Serial.println(distance);
  int* accData = acc.getAccData();
  Serial.print("x: ");
  Serial.println(accData[0]);
  Serial.print("y: ");
  Serial.println(accData[1]);
  Serial.print("z: ");
  Serial.println(accData[2]);
  Serial.println("");
  delay(500);
}
