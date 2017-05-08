/**
 * Main program with setup and loop
 */

#include "Arduino.h"

#include "banner/trollFace.h"
//#include "conf/libManager.h"
//#include "conf/coreManager.cpp"

void setup()
{
  Serial.begin(115200);
  trollFace();
}

void loop()
{

}
