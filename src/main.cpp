/************************************************************************
* Main program with setup and loop
***********************************************************************/

#include "Arduino.h"

#include "manager/confManager.h"
#include "manager/libManager.h"

void setup()
{
  // Setup baud speed
  Serial.begin(baudSpeed);
  // Wait for serial port to connect.
  delay(6000);
  // Display banner choose in banner manager
  displayBanner();
  // Setup needed for temp
  initSetupTemp();
  // Setup needed for file
  initSetupFile();
}

void loop()
{
  // Serial and delay for testing
  Serial.println("Hello world");
  delay(2000);

  // Get temp and hydro for testing
  getTemp();

  // Write file for testing
  writeFile("houat", "Houat_WPA2!");

  // Read file for testing
  String returnFile = readFile();
  Serial.println(returnFile);

  // Delete file for testing
  //deleteFile();

}
