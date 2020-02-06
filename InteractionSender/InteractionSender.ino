#include <Wire.h>

/********Distance Sensor********/
#include <VL53L1X.h>

/********Accel Sensor********/
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/********Orientation Sensor********/
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

/********RFID chip********/
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define RST_PIN D3
 

VL53L1X distanceSensor;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

Adafruit_9DOF dof   = Adafruit_9DOF();
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  /********Distance Sensor********/
  distanceSensor.setTimeout(500);
  if (!distanceSensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  distanceSensor.setDistanceMode(VL53L1X::Long);
  distanceSensor.setMeasurementTimingBudget(50000);
  distanceSensor.startContinuous(50);

  /********Accel Sensor********/
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
    Serial.begin(115200);
    Serial.println("Accelerometer Test"); Serial.println("");

    /* Initialise the sensor */
    if(!accel.begin())
    {
      /* There was a problem detecting the ADXL345 ... check your connections */
      Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
      while(1);
    }

  /********Orientation Sensor********/
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  /********RFID chip********/
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
}

void loop()
{
  /********Distance Sensor********/
  Serial.print(distanceSensor.read()); // in mm
  if (distanceSensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  /********Accel Sensor********/
  sensors_event_t accel_event;
  accel.getEvent(&accel_event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(accel_event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accel_event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accel_event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

  /********Orientation Sensor********/
  sensors_event_t mag_event;
  sensors_vec_t orientation;

  /* Calculate pitch and roll from the raw accelerometer data */
  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
    Serial.print(F("Roll: "));
    Serial.print(orientation.roll);
    Serial.print(F("; "));
    Serial.print(F("Pitch: "));
    Serial.print(orientation.pitch);
    Serial.print(F("; "));
  }
  
  /* Calculate the heading using the magnetometer */
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    Serial.print(F("Heading: "));
    Serial.print(orientation.heading);
    Serial.print(F("; "));
  }

  Serial.println(F(""));

  /********RFID chip********/
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i], DEC);
  }
}
