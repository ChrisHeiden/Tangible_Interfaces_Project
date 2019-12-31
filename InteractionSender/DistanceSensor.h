#ifndef DistanceSensor_H
#define DistanceSensor_H

#include "Arduino.h"

/*
 * DistanceSensor object for distance calculation
 */
class DistanceSensor {
  public:

    /**
     * constructor of the object DistanceSensor that initialises the sensor pins as OUTPUT(trigPin) and INPUT(echoPin)
     * @param {int} trigPin - trigger pin of the sensor
     * @param {int} echoPin - echo Pin of the sensor
     */
    DistanceSensor(int trigPin, int echoPin);

    /**
     * get distance
     * @return {int} - get the distance between an object and the sensor
     */
    int getDistance();
    
  private:
    int _trigPin;
    int _echoPin;
    int _distance;
};

#endif
