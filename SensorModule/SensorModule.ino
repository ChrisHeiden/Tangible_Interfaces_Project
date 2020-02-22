#include <Wire.h>
/********Distance Sensor********/
#include <VL53L1X.h>
VL53L1X distanceSensor;

/********Accel Sensor********/
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

/********Orientation Sensor********/
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
Adafruit_9DOF dof   = Adafruit_9DOF();
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

/********Button********/
#define BUTTONPIN D0
boolean oldState;

/********RFID Sensor********/
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D8
#define RST_PIN D3
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
int oldTag;

/********MIDI********/
#include <MIDI.h>
#include <midi.h>
#include <midi_defs.h>
#include <midi_message.h>
#include <midi_namespace.h>
#include <midi_settings.h>
#define MAXVELUE 127
int channelNumber;
MIDI_CREATE_INSTANCE(HardwareSerial,Serial, midiOut);


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
        tag += rfid.uid.uidByte[i];
      }
      oldTag = tag;
      //Serial.println(tag);
      if(tag == 398) { oldTag = 1; return 1; }
      else if(tag == 373) { oldTag = 2; return 2; }
      else if(tag == 379) { oldTag = 3; return 3; }
  }
}

/**
 * check state of the button
 * @return {boolean} - has been pressed and not pressed before
 */
boolean getButtonState(){
  boolean actualState = false;
  int buttonState = digitalRead(BUTTONPIN);
  if (buttonState == HIGH) {
    if(oldState == false){
      actualState = true;
      oldState = actualState;
      channelNumber = 0;
    }
  }
  else{
    actualState = false;
    oldState = actualState;
  }
  return actualState;
}

/**
 * map the value to a new scale
 * @param {float} actual value
 * @param {float} minimum value of the new scale
 * @param {float} maximum value of the new scale
 * @return {int} - mapped value of a new scale
 */
int mapValuesToMIDI(float theValue, float minValue, float maxValue){
  float tmpValue = theValue;

  if(tmpValue < minValue) tmpValue = minValue; 
  if(tmpValue > maxValue) tmpValue = maxValue;

  tmpValue = map(tmpValue, minValue, maxValue, 0, 127);  // This minimum MIDI value for a note or note intensity is zero and the maximum is 127
  
  return (int) tmpValue; 
}

/**
 * constructor of the file and is the first function that will be called 
 * after powering the microcontroller
 */
void setup() {
  Serial.begin(4800);  

  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  
  /********Distance Sensor********/
  distanceSensor.setTimeout(500);
  if (!distanceSensor.init()){ while (1); }
  
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
  oldTag = 0;

  /********Button********/
  pinMode(BUTTONPIN, INPUT);
  oldState = false;
  channelNumber = 0;
}

/**
 * send distance sensor value to Pure Data
 */
void sendDistance(){
  int distance;
  distance = distanceSensor.read(); // in mm
  if (distanceSensor.timeoutOccurred()) { distance = -1; }
  distance = mapValuesToMIDI( distance, 30, 1000);
  //Serial.println(distance);
  midiOut.sendNoteOn(distance, MAXVELUE, channelNumber);  // This is how to send a note
}

/**
 * send acceleration sensor values to Pure Data
 */
void sendAcceleration(sensors_event_t accel_event){
  accel.getEvent(&accel_event);
  int accelerationData[3];

  accelerationData[0] = accel_event.acceleration.x;
  accelerationData[1] = accel_event.acceleration.y;
  accelerationData[2] = accel_event.acceleration.z;

  for(int i = 0; i < 3; ++i){
    Serial.println(accelerationData[i]);
    midiOut.sendNoteOn(accelerationData[i], MAXVELUE, channelNumber);  // This is how to send a note
  }
}

/**
 * send orientation sensor values to Pure Data  
 */
void sendOrientation(sensors_event_t accel_event){
  sensors_event_t mag_event;
  sensors_vec_t orientation;
  int orientationData[3];

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

  for(int i = 0; i < 3; ++i){
    orientationData[i] = mapValuesToMIDI( orientationData[i], 0, 180);
    Serial.println(orientationData[i]);
    midiOut.sendNoteOn(orientationData[i], MAXVELUE, channelNumber);  // This is how to send a note
  }
}

/**
 * loop through the all functions
 */
void loop() {
  /********Button********/
  boolean pressed = getButtonState();
  if(pressed == true)
  {
     /********RFID Sensor********/
     channelNumber = getRFIDTag();
     //Serial.println(channelNumber);
  }
  
  if(channelNumber != 0)
  {
    //Serial.println("Hallo2");
    /********Distance Sensor********/
    sendDistance();

    //sensors_event_t accel_event;
    /********Accel Sensor********/
    //sendAcceleration(accel_event);
  
    /********Orientation Sensor********/
    //sendOrientation(accel_event); 
    //Serial.println("");
  } 
}
