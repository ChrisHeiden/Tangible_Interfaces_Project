#include "Accelorometer.h"
#include "DistanceSensor.h" 

#define TRIGPIN 9
#define ECHOPIN 10

Accelorometer acc;
DistanceSensor distanceSensor(TRIGPIN, ECHOPIN);

void setup() {

Serial.begin(9600); // Starts the serial communication

}

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
