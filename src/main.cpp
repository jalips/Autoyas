/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

/*  Get Chip ID
 *  wemos.cc
 *
 *
 */

 int solenoidPin = 4;    //This is the output pin on the Arduino we are using

void setup()
{

  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  delay(1000);                      //Wait 1 Second

  Serial.println("ello");
}
