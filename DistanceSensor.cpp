#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int trigPin, int echoPin) {
  
  _trigPin = trigPin;
  _echoPin = echoPin;
  
  pinMode(_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(_echoPin, INPUT); // Sets the echoPin as an Input
}

int DistanceSensor::getDistance() {

  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  
  long duration = pulseIn(_echoPin, HIGH);
  
  _distance = duration*0.034/2;

  return _distance;
}
