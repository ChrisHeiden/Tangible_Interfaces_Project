String s = "Music Data: RFID[122] Distance[211], Orientation[14,50,10], Acceleration[12,142,193]";  

void setup() {
  Serial.begin(115200);          //Baud Rate for Communication
}

void loop() {
 getRFIDTag(s);
 getDistance(s);
 getOrientation(s);
 getAcceleration(s);
 Serial.println("");
 delay(1000);
}

void getRFIDTag(String message){
   int value = -1; 
   int distancePos = message.indexOf("RFID") + 5;
   int index = message.indexOf("]");
   value = message.substring(distancePos, index).toInt();
   Serial.println(value);
}

void getDistance(String message){
   int value = -1; 
   int distancePos = message.indexOf("Distance") + 9;
   String distance = message.substring(distancePos, distancePos+5);
   int index = distance.indexOf("]");
   value = distance.substring(0, index).toInt();
   Serial.println(value);
}

void getOrientation(String message){

  int orientationValues[3];
  int arrayLength = sizeof(orientationValues) / sizeof(orientationValues[0]);

  int orientationPos = message.indexOf("Orientation") + 12;
  String orientation = message.substring(orientationPos, orientationPos+15);
  int index = -1;
  for(int i = 0; i < arrayLength; ++i)
  {
    if(i < 3) { index = orientation.indexOf(","); }
    else      { index = orientation.indexOf("]"); }
    orientationValues[i] = orientation.substring(0, index).toInt();
    orientation = orientation.substring(index + 1);
  }

  for(int i = 0; i < arrayLength; ++i)
  {
    Serial.println(orientationValues[i]);
  }
}

void getAcceleration(String message){
  int accelerationValues[3];
  int arrayLength = sizeof(accelerationValues) / sizeof(accelerationValues[0]);

  int accelerationPos = message.indexOf("Acceleration") + 13;
  String acceleration = message.substring(accelerationPos, message.lastIndexOf("]"));
  int index = -1;
  for(int i = 0; i < arrayLength; ++i)
  {
    if(i < 3) { index = acceleration.indexOf(","); }
    else      { index = acceleration.indexOf("]"); }
    
    accelerationValues[i] = acceleration.substring(0, index).toInt();
    acceleration = acceleration.substring(index + 1);
  }

  for(int i = 0; i < arrayLength; ++i)
  {
    Serial.println(accelerationValues[i]);
  }
}
