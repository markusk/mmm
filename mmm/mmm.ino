#include <Wire.h>
#include <VL53L0X.h> // by Pololu
#include "MIDIUSB.h"

// set the pins to shutdown pin of each sensor
#define XSHUT1 15
#define XSHUT2 16
#define XSHUT3 17
#define XSHUT4 18
#define XSHUT5 19

// distance in mm when a block is recognised as "UP"
int blockThreshold = 20;

// this is the base note for sensor1, all following sensor notes will be increased by 1
byte baseNote = 48;

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;

// holds the measurements
int measure = 0;

// The time in ms between note on and off
unsigned char noteBounceDelay = 50;

// general stuff
bool ON = true;
bool OFF = false;
bool UP = true;
bool DOWN = false;

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


// First MIDI parameter is the event type (0x09 = note on, 0x08 = note off)
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);

  // fancy LED blinking...
  digitalWrite(LED_BUILTIN, HIGH);
}


void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);

  // fancy LED blinking...
  digitalWrite(LED_BUILTIN, LOW);
}


// First MIDI parameter is the event type, combined with the MIDI channel.
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
  noteOn(0, note, 64);   // Channel 0, middle C, normal velocity
  // Wait for all messages to actually be sent.
  MidiUSB.flush();
  // Avoid  bouncing
  delay(noteBounceDelay);

  //----------
  // NOTE off
  //----------
  // Serial.println("Sending note off");
  noteOff(0, note, 64);  // Channel 0, middle C, normal velocity
  // Wait for all messages to actually be sent.
  MidiUSB.flush();
  // Avoid  bouncing
  delay(noteBounceDelay);
}


// block lies DOWN = turn music ON
void blockLies(byte block)
{
   switch (block)
  {
    case 1:
      if (track1 == OFF)
      {
        // play note (usually 48 (middle C), see definitions on the very top)
        toggleNote(baseNote);
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
        // play next note
        toggleNote(baseNote+1);
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
        // play note (usually 48 (middle C), see definitions on the very top)
        toggleNote(baseNote);
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
        // play next note
        toggleNote(baseNote+1);
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
}


void setup()
{
  // set shurdown pins to output
  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);
  pinMode(XSHUT4, OUTPUT);
  pinMode(XSHUT5, OUTPUT);
  // all sensors in standby
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  digitalWrite(XSHUT5, LOW);

  delay(500);
  Wire.begin();
  

 // for debugging messageas only
  Serial.begin(115200);

  // init sensor 1
  digitalWrite(XSHUT1, HIGH);
  delay(150);
  sensor1.init(true);
  delay(100);
  sensor1.setAddress( (uint8_t) 01);
  // init sensor 2
  digitalWrite(XSHUT2, HIGH);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress( (uint8_t) 02);
  // init sensor 3
  digitalWrite(XSHUT3, HIGH);
  delay(150);
  sensor3.init(true);
  delay(100);
  sensor3.setAddress( (uint8_t) 03);
  // init sensor 4
  digitalWrite(XSHUT4, HIGH);
  delay(150);
  sensor4.init(true);
  delay(100);
  sensor4.setAddress( (uint8_t) 04);
  // init sensor 5
  digitalWrite(XSHUT5, HIGH);
  delay(150);
  sensor5.init(true);
  delay(100);
  sensor5.setAddress( (uint8_t) 05);


  Serial.println("sensor addresses set");

  // start measurements
  sensor1.startContinuous();
  sensor2.startContinuous();
  sensor3.startContinuous();
  sensor4.startContinuous();
  sensor5.startContinuous();

  // (times 10 to convert into mm for the sensor measurement)
  blockThreshold *= 10;

  // let the LED show some stuff
  pinMode(LED_BUILTIN, OUTPUT);
  // LED on - We are ready!
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop()
{
  //----------
  // sensor 1
  //----------
  //Serial.print("Reading a measurement... ");
  // sensor1
  measure = sensor1.readRangeContinuousMillimeters();
  // Serial.print("sensor1: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
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

  //----------
  // sensor 2
  //----------
  //Serial.print("Reading a measurement... ");
  // sensor1
  measure = sensor2.readRangeContinuousMillimeters();
  // Serial.print("sensor2: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > 200)
  {
    // block 2 up -> STOP
    //Serial.println("block 2 UP");
    block2 = UP;
    // STOP playing
    blockIsLifted(2);
  }
  else
  {
    // block 2 down -> PLAY
    // Serial.println("block 2 DOWN");
    block2 = DOWN;
    // PLAY
    blockLies(2);
  }

}
