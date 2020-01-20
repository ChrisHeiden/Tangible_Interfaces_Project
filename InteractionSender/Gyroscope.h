#ifndef GyroScope_H
#define GyroScope_H

#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "Arduino.h"

/*
 * Gyroscope object for getting gyroscope values
 */
class Gyroscope {

  public:

    /**
     * constructor of the object Gyroscope that initialises the sensor
     */
    Gyroscope();

    /**
     * get x gyroscope values 
     * @return {float} - get x values
     */
    float getX();

    /**
     * get y gyroscope value
     * @return {float} - get y values
     */
    float getY();

    /**
     * get z gyroscope value
     * @return {float} - get z values
     */
    float getZ();

  private:
    Adafruit_BNO055 _bno = Adafruit_BNO055(55);
};
