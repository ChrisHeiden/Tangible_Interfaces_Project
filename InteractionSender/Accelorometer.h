#ifndef Accelorometer_H
#define Accelorometer_H

#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "Arduino.h"

/*
 * Accelorometer object for the HMC5883 sensor
 */
class Accelorometer {

  public:
    /**
     * constructor of the object Accelorometer that begins and start transition of the accelorometer sensor
     */
    Accelorometer();

    /**
     * get accelorometer sensor abolute position data
     * @return {int*} - get accelorometer sensor values of the absolute position
     */
//    int* getAccData();
      void getAccData();
  private:
    Adafruit_LSM303_Accel_Unified _accel = Adafruit_LSM303_Accel_Unified(54321);

};

#endif
