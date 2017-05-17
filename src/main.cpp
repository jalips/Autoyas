/************************************************************************
* Main program with setup and loop
***********************************************************************/

#include "Arduino.h"
#include "manager/libManager.h"

int baudSpeed = 115200;
int isWifiConf = 0;

void setup()
{
  // Setup baud speed
  Serial.begin(baudSpeed);
  // Wait for serial port to connect.
  delay(6000);

  // TODO : initialize onboard LED as output
  //pinMode(BUILTIN_LED, OUTPUT);

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

  // Setup needed for Wifi AP
  initSetupWifiAP();

  // Loop fir wifi AP
  loopWifiAP();

  // If there is something in confFile
  String returnFile = readFile();
  // TODO : test if there is something in file to go wifi station

  // Setup needed for Wifi Station
  //initSetupWifiStation();

  // TODO : call API to register while in Wifi Station and go to setup MQTT and loop !

  // Setup needed for MQTT
  //initSetupMQTT();

  while(isWifiConf == 0){
    // Stay in setup !
    delay(2000);
  }

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

  // Delete file for testing
  //deleteFile();

  // Loop for wifi station
  //loopWifiStation();

  // Loop for MQTT
  //loopMQTT();

  // Display some log
  Serial.println("**********************************");
  Serial.println("        End of Loop");
  Serial.println("**********************************");
}
