# Tangible Interaction Project
The project is about exploring the

## Installation 
### Esp 2866 
First of all, you have to enter this:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
to your Preferences. Therefore, click on "File" and search for your
"Preferences". There, enter the link to the "additional board management_URL".
After doing so, click on board managment and search for esp8266. Install it.
This will take some time. However, then you will find all ESP8266 boards in your 
board lib and many examples for it.

### Adding libraries 
To upload the code, you have to install following external libraries:

* [VL53L1X](https://github.com/pololu/vl53l1x-arduino) 
* [OSCMessage](https://github.com/CNMAT/OSC) 

After downloading, add these libraries to the Arduino IDE. This
can be done by 

```
sketch >> add library >> add ZIP. library
```

The Adafruit_LSM303_Accel library can be found in the Arduino IDE
```
sketch >> add library >> manage library
```
Search for Adafruit_LSM303_Accel and install all necessary libraries.

## Wiring
![Image of the wiring](/images/Tangible_Interfaces_Project_Steckplatine.png)
