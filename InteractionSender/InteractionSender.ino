/**
 * Purpose: Sends accelorometer and distance pure data
 * @author Christopher Heiden, ...
 * @version 0.3 31/12/2019
 */
 
#include "Accelorometer.h" //[works]
//#include "DistanceSensor.h" 
//#include "OSCSender.h" //[create network works; sending udp not]

#define TRIGGER D1
#define ECHO D2
//#define PORT 9999
Accelorometer acc;
//DistanceSensor distanceSensor(TRIGPIN, ECHOPIN);

//const IPAddress outIp(192,168,1,110);
//OSCSender osc(outIp, PORT);

/**
 * defines the baudrate
 */
void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

/**
 *  loop through the code to send sensor values to pure data
 */
void loop() {
  //Serial.println("hallo");
  //int distance = distanceSensor.getDistance();
  //Serial.println(distance);
  //osc.sendMessage();
  //acc.getAccData();

   long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
}
