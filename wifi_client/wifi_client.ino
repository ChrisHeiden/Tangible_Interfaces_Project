#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
const char* host = "192.168.4.1"; 

void setup() {
  Serial.begin(115200);          //Baud Rate for Communication
  delay(10);                     //Baud rate prper initialization
  WiFi.mode(WIFI_STA);           //NodeMcu esp12E in station mode
  WiFi.begin("TangibleInteractionProject");      //Connect to this SSID. In our case esp-01 SSID.  

  while (WiFi.status() != WL_CONNECTED) {      //Wait for getting IP assigned by Access Point/ DHCP. 
    delay(500);
  }
}

void loop() { 
  WiFiClient client;
  const int httpPort = 80;
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
  
  while(client.available()){
    String message = client.readStringUntil('\r');
    Serial.println(message);

    //getRFIDTag(s);
    //getDistance(s);    
    //getOrientation(s);    
    //getAcceleration(s);
    //Serial.println("");
    delay(100);
  }
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
