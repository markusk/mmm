#include <Adafruit_VL53L0X.h>
#include <vl53l0x_api.h>
#include <vl53l0x_api_calibration.h>
#include <vl53l0x_api_core.h>
#include <vl53l0x_api_ranging.h>
#include <vl53l0x_api_strings.h>
#include <vl53l0x_def.h>
#include <vl53l0x_device.h>
#include <vl53l0x_i2c_platform.h>
#include <vl53l0x_interrupt_threshold_settings.h>
#include <vl53l0x_platform.h>
#include <vl53l0x_platform_log.h>
#include <vl53l0x_tuning.h>
#include <vl53l0x_types.h>

#include <Wire.h>

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;
VL53L0X sensor6;


int a;
int b;
int c;
int d;
int e;
int f;


void setup()
{
  // Sensor 1, Pin 15 (SHUTDOWN)
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
 
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);

  delay(500);

  // Start I2C
  Wire.begin();

  // only for debugging purposes
  Serial.begin (9600);

  digitalWrite(15, HIGH);
  delay(150);
  Serial.println("00");
  sensor7.init(true);

  Serial.println("01");
  delay(100);
  sensor7.setAddress((uint8_t)01);
  Serial.println("02");


  digitalWrite(16, HIGH);
    delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)02);
  Serial.println("04");
  

  digitalWrite(17, HIGH);
    delay(150);
  sensor3.init(true);
  Serial.println("05");
  delay(100);
  sensor3.setAddress((uint8_t)03);
  Serial.println("06");
  
  digitalWrite(18, HIGH);
  delay(150);
  Serial.println("07");
  sensor4.init(true);

  Serial.println("08");
  delay(100);
  sensor4.setAddress((uint8_t)04);
  Serial.println("09");
  

  digitalWrite(19, HIGH);
  delay(150);
  Serial.println("10");
  sensor5.init(true);

  Serial.println("11");
  delay(100);
  sensor5.setAddress((uint8_t)05);
  Serial.println("12");


  digitalWrite(20, HIGH);
  delay(150);
  Serial.println("13");
  sensor1.init(true);

  Serial.println("14");
  delay(100);
  sensor1.setAddress((uint8_t)06);
  Serial.println("15");

  Serial.println("addresses set");

  sensor1.startContinuous();
  sensor2.startContinuous();
  sensor3.startContinuous();
  sensor4.startContinuous();
  sensor5.startContinuous();
  sensor6.startContinuous();

}


void loop()
{
  a=sensor1.readRangeContinuousMillimeters();
  Serial.print(a);
  Serial.print("  ");

  b=sensor2.readRangeContinuousMillimeters();
  Serial.print(b);
  Serial.print("  ");

  c=sensor3.readRangeContinuousMillimeters();
  Serial.print(c);
  Serial.print("  ");

  d=sensor4.readRangeContinuousMillimeters();
  Serial.print(d);
  Serial.print("  ");

  e=sensor5.readRangeContinuousMillimeters();
  Serial.print(e);
  Serial.print("  ");

  f=sensor6.readRangeContinuousMillimeters();
  Serial.println(f);

  delay(100);
}
