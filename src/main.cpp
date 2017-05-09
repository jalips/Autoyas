/**
 * Main program with setup and loop
 */

#include "Arduino.h"

#include "conf/libManager.h"
//#include "conf/coreManager.cpp"

void setup()
{
  Serial.begin(115200);
  displayBanner();
}

void loop()
{
  Serial.println("Hello world");
  delay(2000);
}
