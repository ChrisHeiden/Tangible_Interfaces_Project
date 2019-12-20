#include "Accelorometer.h"

Accelorometer::Accelorometer() {

  Wire.begin();
  
  Wire.beginTransmission(ADDR); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}

int* Accelorometer::getAccData() {

  int x,y,z; //triple axis data
  int accData[3];

  Wire.beginTransmission(ADDR);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
  Wire.requestFrom(ADDR, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //MSB  x 
    x |= Wire.read(); //LSB  x
    z = Wire.read()<<8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read()<<8; //MSB y
    y |= Wire.read(); //LSB y
  }

  accData[0] = x;
  accData[1] = y;
  accData[2] = z;

  return accData;
}
