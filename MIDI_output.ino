#include <MIDI.h>


#include <midi.h>
#include <midi_defs.h>
#include <midi_message.h>
#include <midi_namespace.h>
#include <midi_settings.h>

MIDI_CREATE_INSTANCE(HardwareSerial,Serial, midiOut);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {

  midiOut.sendControlChange(56,127,1);
  delay(1000);

 // midiOut.sendProgramChange(12,1);
 // delay(1000);

  int tmpVal = mapValuesToMIDI( 1300, 50, 500);
  //Serial.println(tmpVal);
}


int mapValuesToMIDI(float theValue, float minValue, float maxValue)
{
  float tmpValue = theValue;

  if(tmpValue < minValue) tmpValue = minValue; 
  if(tmpValue > maxValue) tmpValue = maxValue;

  tmpValue = map(tmpValue, minValue, maxValue, 0, 127);
  
  return (int) tmpValue; 
}
