#include <Wire.h>
#include <Adafruit_Sensor.h>

/**********Distant Sensor**************/
#include <VL53L1X.h>

/**********Acceleration**************/
#include <Adafruit_LSM303_U.h>

/**********Gyroscope**************/
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

VL53L1X sensor;
Adafruit_9DOF dof = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);

void setup()
{
  Serial.begin(115200);

  /**********Distant Sensor**************/
  Wire.begin();
  Wire.setClock(400000);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1);
  }
  
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);

  /**********Accelerometer**************/
  #ifndef ESP8266
    while (!Serial)
      ;
  #endif

  if (!accel.begin()) {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }
  
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
}

void loop()
{
  sensors_event_t accel_event;
  float gyroscopeData[3]; 
  float accelerationData[3]; 

  //if I just use a pointer -> rebooting loop
  int distance = getDistance();

  //Serial.println(distance);
  float* gyroscopeDataPointer = getGyroscopeData(accel_event, gyroscopeData);
  /*
  Serial.print("roll: ");
  Serial.print(gyroscopeDataPointer[0]);
  Serial.print("  ");
  Serial.print("pitch: ");
  Serial.print(gyroscopeDataPointer[1]);
  Serial.print("  ");
  Serial.print("heading: ");
  Serial.print(gyroscopeDataPointer[2]);
  Serial.println("  ");
  */
  float* accelerationDataPointer = getAccelerationData(accel_event, accelerationData);
  /*
  Serial.print("X: ");
  Serial.print(accelerationDataPointer[0]);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(accelerationDataPointer[1]);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(accelerationDataPointer[2]);
  Serial.print("  ");
  Serial.println("m/s^2");
  */
}

/**
 * get distance sensor value  
 * @return {int} - distance
 */
int getDistance(){
  int distance = sensor.read();
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  return distance;
}

/**
 * get gyroscope sensor values  
 * @return {float*} - gyroscope array values [roll,pitch,heading]
 */
float* getGyroscopeData(sensors_event_t accel_event, float *gyroscopeData){
  sensors_event_t mag_event;
  sensors_vec_t orientation;
  
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    gyroscopeData[0] = orientation.roll;
    gyroscopeData[1] = orientation.pitch;
    gyroscopeData[2] = orientation.heading;
  }
  return gyroscopeData;
}

/**
 * get acceleration sensor values  
 * @return {float*} - acceleration array values [x,y,z]
 */
float* getAccelerationData(sensors_event_t accel_event, float *accelerationData){
  accel.getEvent(&accel_event);
  accelerationData[0] = accel_event.acceleration.x;
  accelerationData[1] = accel_event.acceleration.y;
  accelerationData[2] = accel_event.acceleration.z;
  return accelerationData;
}
