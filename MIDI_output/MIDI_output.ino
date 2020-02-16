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

  midiOut.sendNoteOn(42, 127, 1);  // This is how to send a note
  delay(1000);

  midiOut.sendNoteOn(48, 110, 1);  // This is how to send a note
 // midiOut.sendProgramChange(12,1);
  delay(1000);

  // So for example let's assume that we are a value between 0.0 and 359.9 from the gyroscope.  But we only want to read the values from 0 to 180
  float gyroScopeXvalue = 97;
  int noteVal = mapValuesToMIDI( gyroScopeXvalue, 0, 180);

  float distanceSensorValue = 800;  // This assumes we are getting a value of 800 from the distance sensor and we only want to map values from 30 to 1000 coming in from the distance sensor (and ignore all other values).
  int noteIntensity = mapValuesToMIDI( distanceSensorValue, 30, 1000);

  midiOut.sendNoteOn(noteVal, noteIntensity, 1);  // This is how to send a note of noteVal of noteIntensity on channel 1. 
  delay(1000);

  int marioBrothers[2][12] = {
      {76, 76, 20, 76, 20, 72, 76, 20, 79, 20, 67, 20},
      {12, 12, 12, 12, 12, 12, 12, 12, 12, 36, 12, 36}    
  };

  for(int i=0;i<12;i++)
  {
    int note = marioBrothers[0][i];
    int duration = marioBrothers[1][i];
    midiOut.sendNoteOn(note, 127, 1);
    delay(duration * 20);
    midiOut.sendNoteOn(note, 0, 1);
    delay(50);
  }
  
}


int mapValuesToMIDI(float theValue, float minValue, float maxValue)
{
  float tmpValue = theValue;

  if(tmpValue < minValue) tmpValue = minValue; 
  if(tmpValue > maxValue) tmpValue = maxValue;

  tmpValue = map(tmpValue, minValue, maxValue, 0, 127);  // This minimum MIDI value for a note or note intensity is zero and the maximum is 127
  
  return (int) tmpValue; 
}
