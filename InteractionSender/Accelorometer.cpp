#include "Accelorometer.h"

Accelorometer::Accelorometer() {
#ifndef ESP8266
  while (!Serial)
    ; // will pause Zero, Leonardo, etc until serial console opens
#endif
 
  if (!_accel.begin()) {
    while (1)
      ;
  }
  
  _accel.setMode(LSM303_MODE_NORMAL);
}

//int* Accelorometer::getAccData() {
void Accelorometer::getAccData() {
  sensors_event_t event;
  _accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: ");
  Serial.println(event.acceleration.x);
  Serial.print("Y: ");
  Serial.println(event.acceleration.y);
  Serial.print("Z: ");
  Serial.println(event.acceleration.z);
 
}
