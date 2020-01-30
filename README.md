# Tangible Interaction Project
The project is about exploring the

## Installation 
### Esp 32 and ESP8266
First of all, you have to enter this
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json, https://dl.espressif.com/dl/package_esp32_index.json
```

to your Preferences. Therefore, click on "File" and search for your
"Preferences". There, enter the link to the "additional board management_URL".
After doing so, click on board managment and search for esp32. Install it.
This will take some time. However, then you will find all ESP32 boards in your 
board lib and many examples for it.
In this project, we use the Adafruit ESP32 Feather board.

### Adding libraries 
To upload the code, you have to install following external libraries:

* [VL53L1X](https://github.com/pololu/vl53l1x-arduino) 
* [OSCMessage](https://github.com/CNMAT/OSC) 

After downloading, add these libraries to the Arduino IDE. This
can be done by 

```
sketch >> add library >> add ZIP. library
```

The Adafruit_LSM303_Accel and the Adafruit_BNO055 go to:
```
sketch >> add library >> manage library
```
Search for Adafruit_LSM303_Acceland install all necessary libraries. In addition, you have to search and install Adafruit_BNO055 .

## Wiring
![Image of the wiring](/images/Tangible_Interfaces_Project_Steckplatine.png)
