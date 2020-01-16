#ifndef RFID_H
#define RFID_H

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

class RFID {
  public: //functions
    RFID(MFRC522 rfid);
    void getID();

  private: //functions
    void printHex(byte *buffer, byte bufferSize);
    void printDec(byte *buffer, byte bufferSize);

  private: //variable
    byte nuidPICC[4];
    MFRC522 _rfid;
    MFRC522::MIFARE_Key key; 
};
#endif
