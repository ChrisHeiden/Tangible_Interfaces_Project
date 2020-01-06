/**
 * Purpose: Sends accelorometer and distance pure data
 * @author Christopher Heiden, ...
 * @version 0.3 31/12/2019
 */

//#include "Accelorometer.h" //[works]
#include "DistanceSensor.h" 
//#include "OSCSender.h" //[create network works; sending udp not]

#define SDAPIN D2
#define SCLPIN D1


//#define PORT 9999
//Accelorometer acc;
DistanceSensor distanceSensor(SDAPIN, SCLPIN);

//const IPAddress outIp(192,168,1,110);
//OSCSender osc(outIp, PORT);

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
  //Serial.println("hallo");
  int distance = distanceSensor.getDistance();
  Serial.println(distance);
  //osc.sendMessage();
  //acc.getAccData();
  
}
