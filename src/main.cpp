/************************************************************************
* Main program with setup and loop
***********************************************************************/
/**
 * Main program with setup and loop
 */
#include "Arduino.h"
#include "station_mode.h"
#include "ap_mode.h"
#include "manager/libManager.h"

void setup()
{
  int baudSpeed = 115200;

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

  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output

  delay(5000);

  initApMode();
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
  setApMode();
}
