#ifndef RFID_H
#define RFID_H

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

/*
 * RFID object for the MFRC522 sensor
 */
class RFID {
  public: //functions

    /**
     * constructor of the object RFID that initialises variables and initialises WIFI network
     * @param {MFRC522} rfid - MFRC522 chip that is used to detect RFID and NFC tags
     */
     
    RFID(MFRC522 rfid);

    /**
     * get the ID of the Tag
     * @return {long} - ID
     */
    long getID();

  private: //variable
    byte nuidPICC[4];
    MFRC522 _rfid;
    MFRC522::MIFARE_Key key; 
};
#endif
