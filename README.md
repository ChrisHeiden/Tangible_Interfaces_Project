# Tangible Interaction Project
The project is about exploring the

## Installation 
### ESP8266
First of all, you have to enter this
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

to your Preferences. Therefore, click on "File" and search for your
"Preferences". There, enter the link to the "additional board management_URL".
After doing so, click on board managment and search for ESP8266. Install it.
This will take some time. However, then you will find all ESP8266 boards in your 
board lib and many examples for it.
In this project, we use two ESP8266 node Version 1.0 boards.

### Adding libraries 
To upload the code, you have to install following external libraries:

* [VL53L1X](https://github.com/pololu/vl53l1x-arduino) 


After downloading, add these libraries to the Arduino IDE. This
can be done by 

```
sketch >> add library >> add ZIP. library
```

The other libaries like:

* Adafruit_Sensor
* Adafruit_LSM303_U
* Adafruit_L3GD20_U
* Adafruit_9DOF
* MFRC522

must be added as well. Therfore, go to "sketch" click on "add library" and
then on "manage libraries". There, you can search for all these libs. Please,
download all of them. If the system asks you if you want to download linked 
libaries, you click "yes, all".


## Wiring
![Image of the wiring](/images/Tangible_Interfaces_Project_Steckplatine.png)
