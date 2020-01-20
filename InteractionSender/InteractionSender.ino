#include <MFRC522.h>
#include "Accelorometer.h" //[works]
#include "DistanceSensor.h" //[works]
#include "RFID.h" //[works]
#include "Gyroscope.h" //[works]
//#include "OSCSender.h" //[create network works; sending udp not]

//#define SDAPIN D2
//#define SCLPIN D1
//#define PORT 9999
#define RST_PIN 5
#define SS_PIN 4

MFRC522 mfrc(SS_PIN, RST_PIN);
RFID rfid(mfrc);
//Accelorometer acc;
//DistanceSensor distanceSensor(SDAPIN, SCLPIN);
//Gyroscope gyroscope;
//const IPAddress outIp(192,168,1,110);
//OSCSender osc(outIp, PORT);

/*
 * Accelorometer object for the HMC5883 sensor
 */
void setup() {
  Serial.begin(115200);
}

void loop() {
  rfid.getID();
  //int distance = distanceSensor.getDistance();
  //Serial.println(distance);
  //Serial.println();
  //Serial.println();
  /*****Test accelorometer******/
  //acc.getAccData();
  
  //osc.sendMessage();
  //acc.getAccData();
}
