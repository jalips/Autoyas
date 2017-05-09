/************************************************************************
* Main program with setup and loop
***********************************************************************/

#include "Arduino.h"

#include "manager/confManager.h"
#include "manager/libManager.h"

void setup()
{
  Serial.begin(115200);
  displayBanner();

  initSetupTemp();
}

void loop()
{
  Serial.println("Hello world");
  delay(2000);

  getTemp();

}
