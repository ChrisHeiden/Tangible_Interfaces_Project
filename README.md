# Tangible Interaction Project
This project is ...

## Installation 
### Esp 2866 
First of all, you have to enter this:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
to your preference. Therefore, click on "File" and search for your
"Preferences". There, enter the link to the "additional board management_URL".

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
