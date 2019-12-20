#ifndef Accelorometer_H
#define Accelorometer_H

#include <Wire.h> //I2C Arduino Library
#include "Arduino.h"
#define ADDR 0x1E //I2C Address for The HMC5883

class Accelorometer {

public:
  Accelorometer();
  int* getAccData();

private:

};

#endif
