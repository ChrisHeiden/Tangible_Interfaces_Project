#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int sdaPin, int sclPin) {
  
  //Wire.begin(D2, D1); //SDA, SCL
  //Wire.setClock(400000); // use 400 kHz I2C
  _distanceSensor.setTimeout(1000);
  if (!_distanceSensor.init())
  {
    while (1);
  }
  _distanceSensor.setDistanceMode(VL53L1X::Long);
  _distanceSensor.setMeasurementTimingBudget(50000);
  _distanceSensor.startContinuous(50);
}

float DistanceSensor::getDistance() {
  float distance = _distanceSensor.read();
  return distance;
}
