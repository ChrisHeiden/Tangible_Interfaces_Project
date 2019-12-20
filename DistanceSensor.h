#ifndef DistanceSensor_H
#define DistanceSensor_H

#include "Arduino.h"

class DistanceSensor {

public:
  DistanceSensor(int trigPin, int echoPin);
  int getDistance();
  
private:
  int _trigPin;
  int _echoPin;
  int _distance;

};

#endif
