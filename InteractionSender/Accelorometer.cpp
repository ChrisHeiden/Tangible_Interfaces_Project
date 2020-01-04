#include "Accelorometer.h"

Accelorometer::Accelorometer() {
  Wire.begin(D6, D5);
  Wire.beginTransmission(hmc5883l_address);
  Wire.write(0x00);
  Wire.write(0x70); //8 samples per measurement, 15Hz data output rate, Normal measurement 
  Wire.write(0xA0); //
  Wire.write(0x00); //Continuous measurement mode
  Wire.endTransmission();
  delay(500);
}

//int* Accelorometer::getAccData() {
void Accelorometer::getAccData() {
  int16_t x, y, z;
  double Heading;
  Wire.beginTransmission(hmc5883l_address);
  Wire.write(0x03);
  Wire.endTransmission();
  /* Read 16 bit x,y,z value (2's complement form) */
  Wire.requestFrom(hmc5883l_address, 6);
  x = (((int16_t)Wire.read()<<8) | (int16_t)Wire.read());
  z = (((int16_t)Wire.read()<<8) | (int16_t)Wire.read());
  y = (((int16_t)Wire.read()<<8) | (int16_t)Wire.read());
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println(" ");
}
