#ifndef DistanceSensor_H
#define DistanceSensor_H

#include "Arduino.h"
#include <Wire.h>
#include <VL53L1X.h>

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
    DistanceSensor(int sdaPin, int sclPin);

    /**
     * get distance
     * @return {int} - get the distance between an object and the sensor
     */
    float getDistance();
    
  private:
    VL53L1X sensor;
};

#endif
