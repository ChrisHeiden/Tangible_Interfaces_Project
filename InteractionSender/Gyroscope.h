#ifndef GyroScope_H
#define GyroScope_H


#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "Arduino.h"


class Gyroscope {

  public:

    Gyroscope(); // Constructor
    float getX();
    float getY();
    float getZ();

  private:
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
};
