#include "Adafruit_VL53L0X.h"
#include "MIDIUSB.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
uint16_t distance1 = 0;
bool note1active = false;

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

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


void setup() {
  // for debugging messageas only
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

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
    //Serial.println(F("Failed to boot VL53L0X"));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  // power 
  //Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  // LED on
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop()
{
  VL53L0X_RangingMeasurementData_t measure;
    
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // phase failures have incorrect data
  {  
    distance1 = measure.RangeMilliMeter;
    Serial.print("Distance (mm): ");
    Serial.println(distance1);

    if (distance1 < 200)
    {
      //----------
      // NOTE on
      //----------
      Serial.println("Sending note on");
      noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
      note1active = true;
      MidiUSB.flush();

      // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65    }
    }
    else
    {
      if (note1active)
      {
        //----------
        // NOTE off
        //----------
        note1active = false;
        Serial.println("Sending note off");
        noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
        MidiUSB.flush();

        // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65    }
      }
    } // distance (obstacle detected)
  }
  else
  {
    Serial.println(" out of range ");
  }
  
  delay(100);
}
