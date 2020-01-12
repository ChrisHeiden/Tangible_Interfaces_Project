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
     * constructor of the object DistanceSensor that initialises the sensor pins as SCL and SDA (I2C) pins
     * @param {int} sdaPin - message in
     * @param {int} sclPin - message out
     */
    DistanceSensor(int sdaPin, int sclPin);

    /**
     * get distance
     * @return {float} - get the distance between an object and the sensor
     */
    float getDistance();
    
  private:
    VL53L1X _distanceSensor;
};

#endif
