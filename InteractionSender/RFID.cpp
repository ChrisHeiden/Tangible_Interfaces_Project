#include "RFID.h"

RFID::RFID(MFRC522 rfid){
  _rfid = rfid;
  SPI.begin(); // Init SPI bus
  _rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

long RFID::getID(){
  if ( ! _rfid.PICC_IsNewCardPresent())
    return;

  if ( ! _rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = _rfid.PICC_GetType(_rfid.uid.sak);
  long tag;

  if (_rfid.uid.uidByte[0] != nuidPICC[0] || 
      _rfid.uid.uidByte[1] != nuidPICC[1] || 
      _rfid.uid.uidByte[2] != nuidPICC[2] || 
      _rfid.uid.uidByte[3] != nuidPICC[3] ) {
        
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = _rfid.uid.uidByte[i];
    }

    for (byte i = 0; i < _rfid.uid.size; i++) {
      tag += (_rfid.uid.uidByte[i], DEC);
    }
  }
  _rfid.PICC_HaltA();
  _rfid.PCD_StopCrypto1();
  return tag;
}
