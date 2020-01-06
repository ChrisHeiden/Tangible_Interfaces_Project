#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int sdaPin, int sclPin) {
  
  Wire.begin(D2, D1); //SDA, SCL
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(1000);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
}

float DistanceSensor::getDistance() {
  float distance = sensor.read();
  return distance;
}
