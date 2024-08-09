#include "Adafruit_VL53L0X.h"
#include "MIDIUSB.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


// general stuff
uint16_t distance1 = 0;
bool ON = true;
bool OFF = false;
bool UP = true;
bool DOWN = false;

// distance in mm when a klotz is recognised as "UP"
int klotzThreshold = 20;

// all klotzes
bool track1 = ON;
bool klotz1 = DOWN;


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


void klotzDown(int klotz)
{
  if (track1 == OFF)
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

    // store track state
    track1 = ON;
    Serial.println("Track 1 turned ON.");
  }
}


void klotzUp(int klotz)
{
  switch (klotz)
  {
    case 1:
      break;
    case 2:
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
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;
    case 16:
      break;
  }
  if (track1 == ON)
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

    // store track state
    track1 = OFF;

    Serial.println("Track 1 turned OFF.");
  }
}


void setup()
{
  // for debugging messageas only
  Serial.begin(115200);
  // power 
  Serial.println("*** Let's go! ***"); 

  // (times 10 to convert into mm for the sensor measurement)
  klotzThreshold *= 10;

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

  if (!lox.begin()) {
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
  /// @todo shouln't this line be global!?
  VL53L0X_RangingMeasurementData_t measure;

  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // phase failures have incorrect data
  {
    distance1 = measure.RangeMilliMeter;
    // Serial.print("Distance (mm): ");
    // Serial.println(distance1);

    //----------------------
    // klotz 1 up or down?
    //----------------------
    if (distance1 > 200)
    {
      // klotz 1 up -> STOP
      Serial.println("Klotz 1 UP");
      klotz1 = UP;

      // STOP playing
      klotzUp();
    }
    else
    {
      // klotz 1 down -> PLAY
      // Serial.println("Klotz 1 DOWN");
      klotz1 = DOWN;

      // PLAY
      klotzDown();
    }
    
  } // measurement failure
  else
  {
    //-----------------------------
    // distance war too big
    // let's assume klotz is away!
    //-----------------------------
    // Serial.println("Sensor error: Phase failures have incorrect data!");

    // klotz 1 up -> STOP
    Serial.println("Klotz 1 UP");
    klotz1 = UP;

    // STOP playing
    klotzUp();
   }
  
  // /// @todo needed?
  // delay(100);
}
