


When using a standard Arduino (like UNO) there are things you need to do in order for the device to be recognized as a MIDI device.


You must install two pieces of software:
* [LoopMIDI] (https://www.tobias-erichsen.de/software/loopmidi.html)
* [Hairless] (https://projectgus.github.io/hairless-midiserial/)

LoopMIDI is going to create a virtual MIDI device.  There is a default software in Windows that does this, but it often crashes and LoopMIDI is much more stable.  When you open it click on the button with the plus sign to create a virtual MIDI port.
Hairless is going to take the serialData and send it to the MIDI device.

Hairless will sometimes crash on startup.  This is because it is trying to access something that doesn't work, like Windows broken virtual MIDI device.
When you do that disconnect the Arduino so that it can try again.  Set both the input and output MIDI device to the LoopMIDI port.

If you have an Ardunio that has the ability to become a USB device then these steps are apparently not necessary.

In the Arduino IDE you are going to want to add the MIDI Library by Forty Seven Effects.  Once you have done that go to Sketch->Include Library in the Ardunio IDE and include the MIDI Library.

Start LoopMIDI first.  Then start Hairless.  

A nice feature of Hairless is that it has a logging window where you can see the MIDI messages that are being sent.

If you have this software running while you are updating the Arduino code you might encounter a problem as Hairless has taken control of the serial port and won't allow the IDE to upload a new sketch.  Close Hairless and try to upload your sketch again.  Then restart Hairless.


