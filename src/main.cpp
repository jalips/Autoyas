/************************************************************************
* Main program with setup and loop
***********************************************************************/

#include "Arduino.h"
#include "manager/libManager.h"

// Baud speed for serial monitor
int baudSpeed = 115200;
// Init wifi conf at false because we don't know
int isWifiConf = 0;
// Init first launch at true because it's true
int isFirstLaunch = 1;

void setup()
{
  // Setup baud speed
  Serial.begin(baudSpeed);
  // Wait for serial port to connect.
  delay(5000);

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

  // For testing -> Delete or Write file
  deleteFile();
  writeFile("SFR-0c78", "DVZ25M395J65");
  //writeFile("MyRedmi", "password");


  while(!isWifiConf){
    // Test if there is a file conf set
    if(isFile()) {
      isWifiConf = 1;
    }else{
      if(isFirstLaunch){
        // Setup needed for Wifi AP
        initSetupWifiAP();
        // And now it's not the first launch anymore
        isFirstLaunch = 0;
      }
      // Loop fir wifi AP
      loopWifiAP();
    }
    // Stay in setup until we don't have a conf file
    delay(2000);
  }

  // Setup needed for Wifi Station
  initSetupWifiStation();
  // Setup needed for MQTT
  initSetupMQTT();

  // Display some log
  Serial.println("**********************************");
  Serial.println("        End of Setup");
  Serial.println("**********************************");
}

void loop()
{
  // Delay for testing
  delay(5000);

  // Display some log
  Serial.println("**********************************");
  Serial.println("        Start of Loop");
  Serial.println("**********************************");

  // Loop for wifi station
  loopWifiStation();

  // Call API to register OR StayAlive
  //callAPIForStayingAlive(getMacAdress());

  // Get temp & send it to MQTT
  float temp = loopTemp();
  String tempString = getMacAdress()+"***"+String(temp);
  const char *tempMessage = tempString.c_str();
  loopMQTT("sensor/temp", tempMessage);

  // Get hydro & send it to MQTT
  float hydro = loopHydro();
  String hydroString = getMacAdress()+"***"+String(hydro);
  const char *hydroMessage = hydroString.c_str();
  loopMQTT("sensor/hydro", hydroMessage);

  // Get device's filling level & send it to MQTT
  int waterMesure = loopWater();
  String waterString = getMacAdress()+"***"+String(waterMesure);
  const char *waterMessage = waterString.c_str();
  loopMQTT("sensor/water", waterMessage);

  // Check if we need to open valve
  if(waterMesure < 600){
    loopValveOn();
    loopMQTT("sensor/valve", "on");
    delay(10000);
    loopValveOff();
    loopMQTT("sensor/valve", "off");
    delay(2000);
  }


  // Display some log
  Serial.println("**********************************");
  Serial.println("        End of Loop");
  Serial.println("**********************************");
}
