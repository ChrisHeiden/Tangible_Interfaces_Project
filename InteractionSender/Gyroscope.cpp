#include "Gyroscope.h"

Gyroscope::Gyroscope()
{
  #ifndef ESP8266
    while (!Serial)
      ;
  #endif

  if(!_bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

float Gyroscope::getX()
{
  imu::Vector<3> euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  return euler.x()
}

float Gyroscope::getY()
{
  imu::Vector<3> euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  return euler.y()
}

float Gyroscope::getZ()
{
  imu::Vector<3> euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  return euler.z()
}
