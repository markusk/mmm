/**********************************************************************************

  - Remove all blocks from sensors
  - Plugin Arduino
  - Wait some seconds
  - Start Ableton LIVE or equivilant
    > File > Open Recent Set > mmm-set 16 Spuren 
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
//#include "MIDIUSB.h"

// set the pins to shutdown pin of each sensor
#define XSHUT1  3
/*
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
*/

//*******************************************************
// distance in mm when a block is recognised as "UP"
int blockThreshold = 10;
//*******************************************************


// this is the base note for sensor1, all following sensor notes will be increased by 1
byte baseNote = 48;

// the sensors
VL53L0X sensor1;
/*
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;
VL53L0X sensor6;
VL53L0X sensor7;
VL53L0X sensor8;
VL53L0X sensor9;
VL53L0X sensor10;
VL53L0X sensor11;
VL53L0X sensor12;
VL53L0X sensor13;
VL53L0X sensor14;
VL53L0X sensor15;
VL53L0X sensor16;
*/

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
  /*
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
*/
  // fancy LED blinking...
  digitalWrite(LED_BUILTIN, HIGH);
}


void noteOff(byte channel, byte pitch, byte velocity)
{
  /*
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
*/
  // fancy LED blinking...
  digitalWrite(LED_BUILTIN, LOW);
}


// First MIDI parameter is the event type, combined with the MIDI channel.
// Secomd parameter is the control number number (0-119).
// Third parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value)
{
/*
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
*/
}


// turn the given note on and off with some delay
void toggleNote(byte note)
{
/*
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
*/
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
      if (track6 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track6 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 7:
      if (track7 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track7 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 8:
      if (track8 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track8 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 9:
      if (track9 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track9 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 10:
      if (track10 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track10 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 11:
      if (track11 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track11 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 12:
      if (track12 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track12 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 13:
      if (track13 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track13 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 14:
      if (track14 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track14 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 15:
      if (track15 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track15 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
      break;
    case 16:
      if (track16 == OFF)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track16 = ON;
        Serial.println(String("Track " + String(block) + " turned ON."));
      }
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
      if (track6 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track6 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 7:
      if (track7 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track7 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 8:
      if (track8 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track8 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 9:
      if (track9 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track9 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 10:
      if (track10 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track10 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 11:
      if (track11 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track11 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 12:
      if (track12 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track12 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 13:
      if (track13 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track13 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 14:
      if (track14 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track14 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 15:
      if (track15 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track15 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
    case 16:
      if (track16 == ON)
      {
        // play next note
        toggleNote(baseNote + block);
        // store track state
        track16 = OFF;
        Serial.println(String("Track " + String(block) + " turned OFF."));
      }
      break;
  }
}


void setup()
{
  baseNote--; /// @ todo: remove line and update MIDI mapping! < < < < < < < < < < <

  // set shurdown pins to output
  pinMode(XSHUT1, OUTPUT);
/*
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
*/
  // all sensors in standby
  digitalWrite(XSHUT1, LOW);
/*
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
*/

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
  sensor1.setAddress( (uint8_t) 1);

  /*
  // init sensor 2
  digitalWrite(XSHUT2, HIGH);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress( (uint8_t) 2);
  // init sensor 3
  digitalWrite(XSHUT3, HIGH);
  delay(150);
  sensor3.init(true);
  delay(100);
  sensor3.setAddress( (uint8_t) 3);
  // init sensor 4
  digitalWrite(XSHUT4, HIGH);
  delay(150);
  sensor4.init(true);
  delay(100);
  sensor4.setAddress( (uint8_t) 4);
  // init sensor 5
  digitalWrite(XSHUT5, HIGH);
  delay(150);
  sensor5.init(true);
  delay(100);
  sensor5.setAddress( (uint8_t) 5);
  // init sensor 6
  digitalWrite(XSHUT6, HIGH);
  delay(150);
  sensor6.init(true);
  delay(100);
  sensor6.setAddress( (uint8_t) 6);
  // init sensor 7
  digitalWrite(XSHUT7, HIGH);
  delay(150);
  sensor7.init(true);
  delay(100);
  sensor7.setAddress( (uint8_t) 7);
  // init sensor 8
  digitalWrite(XSHUT8, HIGH);
  delay(150);
  sensor8.init(true);
  delay(100);
  sensor8.setAddress( (uint8_t) 8);
  // init sensor 9
  digitalWrite(XSHUT9, HIGH);
  delay(150);
  sensor9.init(true);
  delay(100);
  sensor9.setAddress( (uint8_t) 9);
  // init sensor 10
  digitalWrite(XSHUT10, HIGH);
  delay(150);
  sensor10.init(true);
  delay(100);
  sensor10.setAddress( (uint8_t) 10);
  // init sensor 11
  digitalWrite(XSHUT11, HIGH);
  delay(150);
  sensor11.init(true);
  delay(100);
  sensor11.setAddress( (uint8_t) 11);
  // init sensor 12
  digitalWrite(XSHUT12, HIGH);
  delay(150);
  sensor12.init(true);
  delay(100);
  sensor12.setAddress( (uint8_t) 12);
  // init sensor 13
  digitalWrite(XSHUT13, HIGH);
  delay(150);
  sensor13.init(true);
  delay(100);
  sensor13.setAddress( (uint8_t) 13);
  // init sensor 14
  digitalWrite(XSHUT14, HIGH);
  delay(150);
  sensor14.init(true);
  delay(100);
  sensor14.setAddress( (uint8_t) 14);
  // init sensor 15
  digitalWrite(XSHUT15, HIGH);
  delay(150);
  sensor15.init(true);
  delay(100);
  sensor15.setAddress( (uint8_t) 15);
  // init sensor 16
  digitalWrite(XSHUT16, HIGH);
  delay(150);
  sensor16.init(true);
  delay(100);
  sensor16.setAddress( (uint8_t) 16);
*/

  Serial.println("sensor addresses set");

  // start measurements
  Serial.print("init sensor 1...");
  sensor1.startContinuous();
  Serial.println("done.");

/*
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

  Serial.print("init sensor 6...");
  sensor6.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 7...");
  sensor7.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 8...");
  sensor8.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 9...");
  sensor9.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 10...");
  sensor10.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 11...");
  sensor11.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 12...");
  sensor12.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 13...");
  sensor13.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 14...");
  sensor14.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 15...");
  sensor15.startContinuous();
  Serial.println("done.");

  Serial.print("init sensor 16...");
  sensor16.startContinuous();
  Serial.println("done.");
*/

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

/*
  //----------
  // sensor 2
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor2.readRangeContinuousMillimeters();
  // Serial.print("sensor 2: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
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
  if (measure > blockThreshold)
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
  if (measure > blockThreshold)
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
  if (measure > blockThreshold)
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

  //----------
  // sensor 6
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor6.readRangeContinuousMillimeters();
  // Serial.print("sensor 6: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 6 up -> STOP
    //Serial.println("block 6 UP");
    block6 = UP;
    // STOP playing
    blockIsLifted(6);
  }
  else
  {
    // block 6 down -> PLAY
    // Serial.println("block 6 DOWN");
    block6 = DOWN;
    // PLAY
    blockLies(6);
  }

  //----------
  // sensor 7
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor7.readRangeContinuousMillimeters();
  // Serial.print("sensor 7: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 7 up -> STOP
    //Serial.println("block 7 UP");
    block7 = UP;
    // STOP playing
    blockIsLifted(7);
  }
  else
  {
    // block 7 down -> PLAY
    // Serial.println("block 7 DOWN");
    block7 = DOWN;
    // PLAY
    blockLies(7);
  }

  //----------
  // sensor 8
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor8.readRangeContinuousMillimeters();
  // Serial.print("sensor 8: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 8 up -> STOP
    //Serial.println("block 8 UP");
    block8 = UP;
    // STOP playing
    blockIsLifted(8);
  }
  else
  {
    // block 8 down -> PLAY
    // Serial.println("block 8 DOWN");
    block8 = DOWN;
    // PLAY
    blockLies(8);
  }

  //----------
  // sensor 9
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor9.readRangeContinuousMillimeters();
  // Serial.print("sensor 9: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 9 up -> STOP
    //Serial.println("block 9 UP");
    block9 = UP;
    // STOP playing
    blockIsLifted(9);
  }
  else
  {
    // block 9 down -> PLAY
    // Serial.println("block 9 DOWN");
    block9 = DOWN;
    // PLAY
    blockLies(9);
  }

  //----------
  // sensor 10
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor10.readRangeContinuousMillimeters();
  // Serial.print("sensor 10: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 10 up -> STOP
    //Serial.println("block 10 UP");
    block10 = UP;
    // STOP playing
    blockIsLifted(10);
  }
  else
  {
    // block 10 down -> PLAY
    // Serial.println("block 10 DOWN");
    block10 = DOWN;
    // PLAY
    blockLies(10);
  }

  //----------
  // sensor 11
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor11.readRangeContinuousMillimeters();
  // Serial.print("sensor 11: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 11 up -> STOP
    //Serial.println("block 11 UP");
    block11 = UP;
    // STOP playing
    blockIsLifted(11);
  }
  else
  {
    // block 11 down -> PLAY
    // Serial.println("block 11 DOWN");
    block11 = DOWN;
    // PLAY
    blockLies(11);
  }

  //----------
  // sensor 12
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor12.readRangeContinuousMillimeters();
  // Serial.print("sensor 12: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 12 up -> STOP
    //Serial.println("block 12 UP");
    block12 = UP;
    // STOP playing
    blockIsLifted(12);
  }
  else
  {
    // block 12 down -> PLAY
    // Serial.println("block 12 DOWN");
    block12 = DOWN;
    // PLAY
    blockLies(12);
  }


  //----------
  // sensor 13
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor13.readRangeContinuousMillimeters();
  // Serial.print("sensor 13: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 13 up -> STOP
    //Serial.println("block 13 UP");
    block13 = UP;
    // STOP playing
    blockIsLifted(13);
  }
  else
  {
    // block 13 down -> PLAY
    // Serial.println("block 13 DOWN");
    block13 = DOWN;
    // PLAY
    blockLies(13);
  }

  //----------
  // sensor 14
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor14.readRangeContinuousMillimeters();
  // Serial.print("sensor 14: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 14 up -> STOP
    //Serial.println("block 14 UP");
    block14 = UP;
    // STOP playing
    blockIsLifted(14);
  }
  else
  {
    // block 14 down -> PLAY
    // Serial.println("block 14 DOWN");
    block14 = DOWN;
    // PLAY
    blockLies(14);
  }

  //----------
  // sensor 15
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor15.readRangeContinuousMillimeters();
  // Serial.print("sensor 15: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 15 up -> STOP
    //Serial.println("block 15 UP");
    block15 = UP;
    // STOP playing
    blockIsLifted(15);
  }
  else
  {
    // block 15 down -> PLAY
    // Serial.println("block 15 DOWN");
    block15 = DOWN;
    // PLAY
    blockLies(15);
  }

  //----------
  // sensor 16
  //----------
  //Serial.print("Reading a measurement... ");
  measure = sensor16.readRangeContinuousMillimeters();
  // Serial.print("sensor 16: ");
  // Serial.print(measure);
  // Serial.println(" mm");

  // block up or down?
  if (measure > blockThreshold)
  {
    // block 16 up -> STOP
    //Serial.println("block 16 UP");
    block16 = UP;
    // STOP playing
    blockIsLifted(16);
  }
  else
  {
    // block 16 down -> PLAY
    // Serial.println("block 16 DOWN");
    block16 = DOWN;
    // PLAY
    blockLies(16);
  }
*/

}
