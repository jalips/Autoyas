/************************************************************************
* Main program with setup and loop
***********************************************************************/

#include "Arduino.h"
#include "manager/libManager.h"

int baudSpeed = 115200;

void setup()
{
  // Setup baud speed
  Serial.begin(baudSpeed);
  // Wait for serial port to connect.
  delay(6000);
  // Display banner choose in banner manager
  displayBanner();
  // Display some log
  Serial.println("**********************************");
  Serial.println("        Start of Setup");
  Serial.println("**********************************");
  // Setup needed for temp
  initSetupTemp();
  // Setup needed for file
  initSetupFile();

  // Setup needed for Wifi Station
  //initSetupWifiStation();

  // Setup needed for Wifi AP
  //initSetupWifiAP();

  // Setup needed for Wifi Station
  initSetupWifiStation();

  // Setup needed for MQTT
  initSetupMQTT();

  //pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output

  // Display some log
  Serial.println("**********************************");
  Serial.println("        End of Setup");
  Serial.println("**********************************");
}

void loop()
{
  // Delay for testing
  delay(2000);
  // Display some log
  Serial.println("**********************************");
  Serial.println("        Start of Loop");
  Serial.println("**********************************");

  // Get temp and hydro for testing
  //getTemp();

  // Write file for testing
  //writeFile("houat", "Houat_WPA2!");

  // Read file for testing
  //String returnFile = readFile();
  //Serial.println(returnFile);

  // Delete file for testing
  //deleteFile();

  // Loop for wifi station
  //loopWifiStation();

  // Loop fir wifi AP
  //loopWifiAP();

  // Loop for wifi station
  loopWifiStation();

  // Loop for MQTT
  loopMQTT();

  // Display some log
  Serial.println("**********************************");
  Serial.println("        End of Loop");
  Serial.println("**********************************");
}
