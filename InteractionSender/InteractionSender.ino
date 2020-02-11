#include <Wire.h>

/********WIFI********/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/********Distance Sensor********/
#include <VL53L1X.h>

/********Accel Sensor********/
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/********Orientation Sensor********/
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

/********RFID Sensor********/
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define RST_PIN D3

const char* ssid = "TangibleInteractionProject";
ESP8266WebServer server(80); 

VL53L1X distanceSensor;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

Adafruit_9DOF dof   = Adafruit_9DOF();
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
int oldTag;

void setup(){
  delay(200);
  Serial.begin(115200);      
  
  /********WIFI********/
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();     
  server.on("/", handleRoot);           
  server.begin(); 
  
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  /********Distance Sensor********/
  distanceSensor.setTimeout(500);
  if (!distanceSensor.init()) { while (1); }
  
  distanceSensor.setDistanceMode(VL53L1X::Long);
  distanceSensor.setMeasurementTimingBudget(50000);
  distanceSensor.startContinuous(50);

  /********Accel Sensor********/
  #ifndef ESP8266
    while (!Serial);
  #endif
    if(!accel.begin()) { while(1); }

  /********Orientation Sensor********/
  if(!accel.begin()) { while(1); }
  if(!mag.begin()) { while(1); }
  
 /********RFID Sensor********/
  SPI.begin();
  rfid.PCD_Init();
  for (byte i = 0; i < 6; i++) { key.keyByte[i] = 0xFF; }
}

void loop(){
  server.handleClient();
  //int tag = getRFIDTag();
  //Serial.println(tag);
}

/**
 * send music data to client
 */
void handleRoot() {
 
  sensors_event_t accel_event;
  
  /********Distance Sensor********/
  int distance = getDistance();

  /********Accel Sensor********/
  float accelerationData[3] = {1,2,3};
  float* accelerationDataPointer = getAcceleration(accel_event, accelerationData);

  /********Orientation Sensor********/
  float orientationData[3] = {1,2,3};
  float* orientationPointer = getOrientation(accel_event, orientationData);
  
  /********RFID Sensor********/
  int tag = getRFIDTag();

  String rfidString = String(tag);
  String distString = String(distance);
  String oriXString = String(orientationPointer[0]);
  String oriYString = String(orientationPointer[1]);
  String oriZString = String(orientationPointer[2]);
  String accXString = String(accelerationDataPointer[0]);
  String accYString = String(accelerationDataPointer[1]);
  String accZString = String(accelerationDataPointer[2]);

  //String s = "Music Data: RFID[" + rfidString + "] Distance[" + distString + "], Orientation[" + oriXString + "," + oriYString + ","  + oriZString + "], Acceleration[" + accXString + "," + accYString + ","  + accZString + "]";  

  //String s = "Music Data: Distance[" + distString + "], Orientation[" + oriXString + "," + oriYString + ","  + oriZString + "], Acceleration[" + accXString + "," + accYString + ","  + accZString + "]";  
  String s = "Music Data: RFID[" + rfidString + "] Distance[" + distString + "], Orientation[" + oriXString + "," + oriYString + ","  + oriZString + "], Acceleration[" + accXString + "," + accYString + ","  + accZString + "]";  
  server.send(200,"text/plain",s);      
}

/**
 * get tag ID 
 * @return {int} - tag ID
 */
int getRFIDTag(){
  if ( ! rfid.PICC_IsNewCardPresent()) { return oldTag; }
  else if ( ! rfid.PICC_ReadCardSerial()) { return oldTag; }
  else{
      int tag = -1;
      for (byte i = 0; i < 4; i++) {
        //nuidPICC[i] = rfid.uid.uidByte[i];
        tag += rfid.uid.uidByte[i];
      }
      
      oldTag = tag;
      return tag;
  }
}

/**
 * get orientation sensor values  
 * @return {float*} - orientation array values [roll,pitch,heading]
 */
float* getOrientation(sensors_event_t accel_event, float *orientationData){
  sensors_event_t mag_event;
  sensors_vec_t orientation;

  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation))
  {
    orientationData[0] = orientation.roll;
    orientationData[1] = orientation.pitch;
  }
  
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    orientationData[2] = orientation.heading;
  }

  return orientationData;
}

/**
 * get acceleration sensor values  
 * @return {float*} - acceleration array values [x,y,z]
 */
float* getAcceleration(sensors_event_t accel_event, float *accelerationData){
  accel.getEvent(&accel_event);
  accelerationData[0] = accel_event.acceleration.x;
  accelerationData[1] = accel_event.acceleration.y;
  accelerationData[2] = accel_event.acceleration.z;
  return accelerationData;
}

/**
 * get distance sensor value  
 * @return {int} - distance
 */
int getDistance(){
  int distance;
  distance = distanceSensor.read(); // in mm
  if (distanceSensor.timeoutOccurred()) { distance = -1; }
  return distance;
}
