#include "RFID.h"

RFID::RFID(MFRC522 rfid){
  _rfid = rfid;
  SPI.begin(); // Init SPI bus
  _rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void RFID::getID(){
    // Look for new cards
  if ( ! _rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! _rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = _rfid.PICC_GetType(_rfid.uid.sak);
  Serial.println(_rfid.PICC_GetTypeName(piccType));
/*
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
*/

  if (_rfid.uid.uidByte[0] != nuidPICC[0] || 
    _rfid.uid.uidByte[1] != nuidPICC[1] || 
    _rfid.uid.uidByte[2] != nuidPICC[2] || 
    _rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = _rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(_rfid.uid.uidByte, _rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(_rfid.uid.uidByte, _rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  _rfid.PICC_HaltA();

  // Stop encryption on PCD
  _rfid.PCD_StopCrypto1();
}

/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void RFID::printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void RFID::printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
