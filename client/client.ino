//with the esp32 feather

#include <WiFi.h>
#define RFIDLENGTH 5
#define DISTANCELENGTH 9
#define ORIENTATIONLENGTH 12
#define ACCELERATIONLENGTH 13
#define CHANNEL 1
#define NOTEINTENSITY 127

const char* host = "192.168.4.1";
WiFiClient client;
const int httpPort = 80;


void setup()
{
    Serial.begin(115200);
    delay(10);
    WiFi.mode(WIFI_STA);         
    WiFi.begin("TangibleInteractionProject");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(10);
    }
}

int value = 0;

void loop()
{
   
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    client.print(String("GET /") + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "Connection: close\r\n" +
      "\r\n"
    );

    delay(10);
    while(client.available()) {
      String message = client.readStringUntil('\r');
      int messageLength = message.length();
      //Serial.println(message);
      //midiOut.sendControlChange(56, NOTEINTENSITY, CHANNEL);
      getRFIDTag(message);
      getDistance(message, messageLength);    
      getOrientation(message, messageLength);    
      getAcceleration(message);
      Serial.println("");
      delay(250);
    }
}


/**
 * send RFID tag to Pure Data
 * @param {String} message that has been send to the client
 */
void getRFIDTag(String message){
   int value = -1; 
   int distancePos = message.indexOf("RFID") + RFIDLENGTH;
   int index = message.indexOf("]");
   value = message.substring(distancePos, index).toInt();
   Serial.println(value);
   //midiOut.sendNoteOn(value, NOTEINTENSITY, CHANNEL);
}

/**
 * send distance value to Pure Data
 * @param {String} message that has been send to the client
 * @param {int} length of the server message
 */
void getDistance(String message, int messageLength){
   int value = -1; 
   int distancePos = message.indexOf("Distance") + DISTANCELENGTH;
   String distance = message.substring(distancePos, messageLength - distancePos);
   int index = distance.indexOf("]");
   value = distance.substring(0, index).toInt();
   Serial.println(value);
   //value = mapValuesToMIDI( distanceSensorValue, 30, 1000);
   //midiOut.sendNoteOn(value, NOTEINTENSITY, CHANNEL);
}


/**
 * send orientation values to Pure Data
 * @param {String} message that has been send to the client
 * @param {int} length of the server message
 */
void getOrientation(String message, int messageLength){

  float orientationValues[3];
  int arrayLength = sizeof(orientationValues) / sizeof(orientationValues[0]);

  int orientationPos = message.indexOf("Orientation") + ORIENTATIONLENGTH;
  String orientation = message.substring(orientationPos, messageLength - orientationPos);
  int index = -1;
  for(int i = 0; i < arrayLength; ++i)
  {
    if(i < 3) { index = orientation.indexOf(","); }
    else      { index = orientation.indexOf("]"); }
    orientationValues[i] = orientation.substring(0, index).toFloat();
    orientation = orientation.substring(index + 1);
  }

  for(int i = 0; i < arrayLength; ++i)
  {
    Serial.println(orientationValues[i]);
    //orientationValues[i] = mapValuesToMIDI( orientationValues[i], 0, 180);
    //midiOut.sendNoteOn(orientationValues[i], NOTEINTENSITY, CHANNEL);
  }
}

/**
 * send acceleration value to Pure Data
 * @param {String} message that has been send to the client
 */
void getAcceleration(String message){
  float accelerationValues[3];
  int arrayLength = sizeof(accelerationValues) / sizeof(accelerationValues[0]);

  int accelerationPos = message.indexOf("Acceleration") + ACCELERATIONLENGTH;
  String acceleration = message.substring(accelerationPos, message.lastIndexOf("]"));
  int index = -1;
  for(int i = 0; i < arrayLength; ++i)
  {
    if(i < 3) { index = acceleration.indexOf(","); }
    else      { index = acceleration.indexOf("]"); }
    
    accelerationValues[i] = acceleration.substring(0, index).toFloat();
    acceleration = acceleration.substring(index + 1);
  }

  for(int i = 0; i < arrayLength; ++i)
  {
    Serial.println(accelerationValues[i]);
    //midiOut.sendNoteOn(accelerationValues[i], NOTEINTENSITY, CHANNEL);  
  }
}

/**
 * map the value to a new scale
 * @param {float} actual value
 * @param {float} minimum value of the new scale
 * @param {float} maximum value of the new scale
 */
int mapValuesToMIDI(float theValue, float minValue, float maxValue)
{
  float tmpValue = theValue;

  if(tmpValue < minValue) tmpValue = minValue; 
  if(tmpValue > maxValue) tmpValue = maxValue;

  tmpValue = map(tmpValue, minValue, maxValue, 0, 127);  // This minimum MIDI value for a note or note intensity is zero and the maximum is 127
  
  return (int) tmpValue; 
}
