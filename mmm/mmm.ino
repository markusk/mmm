#include "Adafruit_VL53L0X.h"
#include "MIDIUSB.h"

// address we will assign if dual sensor is present
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

/// @todo shouln't this line be global!?
VL53L0X_RangingMeasurementData_t measure;

// general stuff
uint16_t distance1 = 0;
bool ON = true;
bool OFF = false;
bool UP = true;
bool DOWN = false;

// distance in mm when a block is recognised as "UP"
int blockThreshold = 20;

// all tracks
bool track1 = ON;
bool track2 = ON;
bool track3 = ON;
bool track4 = ON;
bool track5 = ON;
bool track6 = ON;
bool track7 = ON;
bool track8 = ON;
bool track9 = ON;
bool track10 = ON;
bool track11 = ON;
bool track12 = ON;
// all wooden blocks
bool block1 = DOWN;
bool block2 = DOWN;
bool block3 = DOWN;
bool block4 = DOWN;
bool block5 = DOWN;
bool block6 = DOWN;
bool block7 = DOWN;
bool block8 = DOWN;
bool block9 = DOWN;
bool block10 = DOWN;
bool block11 = DOWN;
bool block12 = DOWN;


// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}


void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


// First parameter is the event type, combined with the channel.
// Secomd parameter is the control number number (0-119).
// Third parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


// turn the given note on and off with some delay
void toggleNote(byte note)
{
  //----------
  // NOTE on
  //----------
  // Serial.println("Sending note on");
  noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
  // Wait for all messages to actually be sent.
  MidiUSB.flush();
  // Avoid  bouncing
  delay(100);

  //----------
  // NOTE off
  //----------
  // Serial.println("Sending note off");
  noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
  // Wait for all messages to actually be sent.
  MidiUSB.flush();
  // Avoid  bouncing
  delay(100);
}


// block lies DOWN = turn music ON
void blockLies(byte block)
{
   switch (block)
  {
    case 1:
      if (track1 == OFF)
      {
        // play note 64 (middle C)
        toggleNote(64);
        // store track state
        track1 = ON;
        Serial.print("Track ");
        Serial.print(block);
        Serial.println(" turned ON.");
      }
      break;
    case 2:
      if (track2 == OFF)
      {
        // play note 65
        toggleNote(64);
        // store track state
        track2 = ON;
        Serial.print("Track ");
        Serial.print(block);
        Serial.println(" turned ON.");
      }
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 11:
      break;
    case 12:
      break;
  }
}


// block is lifted (UP) = turn music OFF
void blockIsLifted(byte block)
{
  switch (block)
  {
    case 1:
      if (track1 == ON)
      {
        // play note 64 (middle C)
        toggleNote(64);
        // store track state
        track1 = OFF;
        
        Serial.print("Track ");
        Serial.print(block);
        Serial.println(" turned OFF.");
      }
      break;
    case 2:
      if (track2 == ON)
      {
        // play note 65
        toggleNote(65);
        // store track state
        track2 = OFF;
        
        Serial.print("Track ");
        Serial.print(block);
        Serial.println(" turned OFF.");
      }
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 11:
      break;
    case 12:
      break;
  }

  // Serial.print("Track ");
  // Serial.print(block);
  // Serial.println(" turned OFF.");
}


void setup()
{
  // for debugging messageas only
  Serial.begin(115200);
  // power 
  Serial.println("*** Let's go! ***"); 

  // (times 10 to convert into mm for the sensor measurement)
  blockThreshold *= 10;

  //pinMode(LED_BUILTIN, OUTPUT);

 /*
  // wait until serial port opens for native USB devices
  while (! Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  
  Serial.println("Adafruit VL53L0X test");
  */

  if (!lox1.begin())
  {
    Serial.println(F("Failed to boot VL53L0X"));
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(100);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(100);
  }
  
  // LED on
  // digitalWrite(LED_BUILTIN, HIGH);
}


void loop()
{
  //Serial.print("Reading a measurement... ");
  lox1.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // phase failures have incorrect data
  {
    distance1 = measure.RangeMilliMeter;
    // Serial.print("Distance (mm): ");
    // Serial.println(distance1);

    //----------------------
    // block 1 up or down?
    //----------------------
    if (distance1 > 200)
    {
      // block 1 up -> STOP
      //Serial.println("block 1 UP");
      block1 = UP;
      // STOP playing
      blockIsLifted(1);
    }
    else
    {
      // block 1 down -> PLAY
      // Serial.println("block 1 DOWN");
      block1 = DOWN;
      // PLAY
      blockLies(1);
    }
  } // measurement failure (or object too far away!)
  else
  {
    //-----------------------------
    // distance war too big
    // let's assume block is away!
    //-----------------------------
    // Serial.println("Sensor error: Phase failures have incorrect data!");

    // block 1 up -> STOP
    //Serial.println("block 1 too far away");
    block1 = UP;

    // STOP playing
    blockIsLifted(1);
   }
}
