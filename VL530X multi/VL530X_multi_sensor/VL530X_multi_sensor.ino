#include <Wire.h>
#include <VL53L0X.h> // by Pololu

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;
VL53L0X sensor6;
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;

void setup()
{
  pinMode(15, OUTPUT); // sensor1
  pinMode(16, OUTPUT); // sensor2
  /*
  pinMode(6, OUTPUT); // sensor3
  pinMode(7, OUTPUT); // sensor4
  pinMode(8, OUTPUT); // sensor5
  pinMode(9, OUTPUT); // sensor6
  */
  // all sensors in standby
  digitalWrite(15, LOW); // sensor1
  digitalWrite(16, LOW); // sensor2
  /*
  digitalWrite(6, LOW); // sensor3
  digitalWrite(7, LOW); // sensor4
  digitalWrite(8, LOW); // sensor5
  digitalWrite(9, LOW); // sensor6
  */

  delay(500);
  Wire.begin();


  Serial.begin (9600);

  // sensor1
  digitalWrite(15, HIGH);
  delay(150);
  Serial.println("00");
  sensor1.init(true);
  Serial.println("01");
  delay(100);
  sensor1.setAddress((uint8_t)01);
  Serial.println("02");
//  digitalWrite(15, LOW);

  // sensor2
  digitalWrite(16, HIGH);
    delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)02);
  Serial.println("04");
//  digitalWrite(16, LOW);

/*
  // sensor3
  digitalWrite(6, HIGH);
    delay(150);
  sensor3.init(true);
  Serial.println("05");
  delay(100);
  sensor3.setAddress((uint8_t)03);
  Serial.println("06");
  
  // sensor4
  digitalWrite(7, HIGH);
  delay(150);
  Serial.println("07");
  sensor4.init(true);
  Serial.println("08");
  delay(100);
  sensor4.setAddress((uint8_t)04);
  Serial.println("09");
  
  // sensor5
  digitalWrite(8, HIGH);
  delay(150);
  Serial.println("10");
  sensor5.init(true);
  Serial.println("11");
  delay(100);
  sensor5.setAddress((uint8_t)05);
  Serial.println("12");
  
  // sensor6
  digitalWrite(9, HIGH);
  delay(150);
  Serial.println("13");
  sensor6.init(true);
  Serial.println("14");
  delay(100);
  sensor6.setAddress((uint8_t)06);
  Serial.println("15");
*/

  Serial.println("addresses set");

  sensor1.startContinuous();
  sensor2.startContinuous();
  /*
  sensor3.startContinuous();
  sensor4.startContinuous();
  sensor5.startContinuous();
  sensor6.startContinuous();
  */
}

void loop()
{

  // sensor1
//  digitalWrite(15, HIGH);
//  delay(150);
  a=sensor1.readRangeContinuousMillimeters();
//  digitalWrite(15, LOW);
  Serial.print("sensor1: ");
  Serial.print(a);
  Serial.println(" mm");

  // sensor2
//  digitalWrite(16, HIGH);
//  delay(150);
  b=sensor2.readRangeContinuousMillimeters();
//  digitalWrite(16, LOW);
  Serial.print("Sensor2: ");
  Serial.print(b);
  Serial.println(" mm");
/*
  // sensor3
  c=sensor3.readRangeContinuousMillimeters();
  Serial.print(c);
  Serial.print("  ");

  // sensor4
  d=sensor4.readRangeContinuousMillimeters();
  Serial.print(d);
  Serial.print("  ");

  // sensor5
  e=sensor5.readRangeContinuousMillimeters();
  Serial.print(e);
  Serial.print("  ");

  // sensor6
  f=sensor6.readRangeContinuousMillimeters();
  Serial.print(f);
*/
  delay(100);
}
