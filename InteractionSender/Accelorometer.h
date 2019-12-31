#ifndef Accelorometer_H
#define Accelorometer_H

#include <Wire.h>
#include "Arduino.h"
#define ADDR 0x1E 

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
    int* getAccData();
  
  private:

};

#endif
