/**********************************************************************************

  - Remove all blocks from sensors
  - Plugin Arduino
  - Wait some seconds
  - Start Ableton or equivilant
  - All tracks in Ableton have to be DISABLED
  - Click on PLAY in Ableton (you should hear nothing)
  - Putting donw a block, should result in enabling the corresponding tracl
  - You should hear one track per block
  - Have fun1!


  https://youtube.com/@MarkusKnapp

  Markus Knapp - Einfach machen

**********************************************************************************/


#include <Wire.h>
#include <VL53L0X.h> // by Pololu
#include "MIDIUSB.h"

// set the pins to shutdown pin of each sensor
#define XSHUT1  15
#define XSHUT2  16
#define XSHUT3  17
#define XSHUT4  18
#define XSHUT5  19
#define XSHUT6  20
#define XSHUT7  21
#define XSHUT8   0
#define XSHUT9   1
#define XSHUT10  2
#define XSHUT11  3
#define XSHUT12  4
#define XSHUT13  5
#define XSHUT14  6
#define XSHUT15  7
#define XSHUT16  8

// distance in mm when a block is recognised as "UP"
int blockThreshold = 20;

// this is the base note for sensor1, all following sensor notes will be increased by 1
byte baseNote = 48;

// the sensors
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
bool track1 = OFF;
bool track2 = OFF;
bool track3 = OFF;
bool track4 = OFF;
bool track5 = OFF;
bool track6 = OFF;
bool track7 = OFF;
bool track8 = OFF;
bool track9 = OFF;
bool track10 = OFF;
bool track11 = OFF;
bool track12 = OFF;
bool track13 = OFF;
bool track14 = OFF;
bool track15 = OFF;
bool track16 = OFF;
// all wooden blocks
bool block1 = UP;
bool block2 = UP;
bool block3 = UP;
bool block4 = UP;
bool block5 = UP;
bool block6 = UP;
bool block7 = UP;
bool block8 = UP;
bool block9 = UP;
bool block10 = UP;
bool block11 = UP;
bool block12 = UP;
bool block13 = UP;
bool block14 = UP;
bool block15 = UP;
bool block16 = UP;


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
        toggleNote(baseNote + block);
        // store track state
        track1 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 2:
      if (track2 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track2 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 3:
      if (track3 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track3 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 4:
      if (track4 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track4 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 5:
      if (track5 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track5 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
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
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;
    case 16:
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
        toggleNote(baseNote + block);
        // store track state
        track1 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 2:
      if (track2 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track2 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 3:
      if (track3 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track3 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 4:
      if (track4 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track4 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 5:
      if (track5 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track5 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
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
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;
    case 16:
      break;
  }
}


void setup()
{
  baseNote--; /// @ todo: remove line and update MIDI mapping! < < < < < < < < < < <

  // set shurdown pins to output
  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);
  pinMode(XSHUT4, OUTPUT);
  pinMode(XSHUT5, OUTPUT);
  pinMode(XSHUT6, OUTPUT);
  pinMode(XSHUT7, OUTPUT);
  pinMode(XSHUT8, OUTPUT);
  pinMode(XSHUT9, OUTPUT);
  pinMode(XSHUT10, OUTPUT);
  pinMode(XSHUT11, OUTPUT);
  pinMode(XSHUT12, OUTPUT);
  pinMode(XSHUT13, OUTPUT);
  pinMode(XSHUT14, OUTPUT);
  pinMode(XSHUT15, OUTPUT);
  pinMode(XSHUT16, OUTPUT);
  // all sensors in standby
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  digitalWrite(XSHUT5, LOW);
  digitalWrite(XSHUT6, LOW);
  digitalWrite(XSHUT7, LOW);
  digitalWrite(XSHUT8, LOW);
  digitalWrite(XSHUT9, LOW);
  digitalWrite(XSHUT10, LOW);
  digitalWrite(XSHUT11, LOW);
  digitalWrite(XSHUT12, LOW);
  digitalWrite(XSHUT13, LOW);
  digitalWrite(XSHUT14, LOW);
  digitalWrite(XSHUT15, LOW);
  digitalWrite(XSHUT16, LOW);

  delay(500);
  Wire.begin();
  

 // for debugging messageas only
  Serial.begin(115200);
  while (!Serial)
  {
    // Wait for serial (USB) port readiness
  }
  Serial.println("Setting sensors addresses...");

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
  Serial.print("init sensor 1...");
  sensor1.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 2...");
  sensor2.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 3...");
  sensor3.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 4...");
  sensor4.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 5...");
  sensor5.startContinuous();
  Serial.println("done.");

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
  measure = sensor1.readRangeContinuousMillimeters();
  // Serial.print("sensor 1: ");
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
  measure = sensor2.readRangeContinuousMillimeters();
  // Serial.print("sensor 2: ");
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

  //----------
  // sensor 3
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor3.readRangeContinuousMillimeters();
  // Serial.print("sensor 3: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > 200)
  {
    // block 3 up -> STOP
    //Serial.println("block 3 UP");
    block3 = UP;
    // STOP playing
    blockIsLifted(3);
  }
  else
  {
    // block 3 down -> PLAY
    // Serial.println("block 3 DOWN");
    block3 = DOWN;
    // PLAY
    blockLies(3);
  }

  //----------
  // sensor 4
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor4.readRangeContinuousMillimeters();
  // Serial.print("sensor 4: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > 200)
  {
    // block 4 up -> STOP
    //Serial.println("block 4 UP");
    block4 = UP;
    // STOP playing
    blockIsLifted(4);
  }
  else
  {
    // block 4 down -> PLAY
    // Serial.println("block 4 DOWN");
    block4 = DOWN;
    // PLAY
    blockLies(4);
  }

  //----------
  // sensor 5
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor5.readRangeContinuousMillimeters();
  // Serial.print("sensor 5: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > 200)
  {
    // block 5 up -> STOP
    //Serial.println("block 5 UP");
    block5 = UP;
    // STOP playing
    blockIsLifted(5);
  }
  else
  {
    // block 5 down -> PLAY
    // Serial.println("block 5 DOWN");
    block5 = DOWN;
    // PLAY
    blockLies(5);
  }

}
