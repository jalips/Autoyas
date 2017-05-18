/************************************************************************
* Wifi in Station Mode that has the capability to use the 802.11 protocol
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
boolean connectioWasAlive = true;

//const char* station_ssid = "MyRedmi";
//const char* station_pass = "password";

void initSetupWifiStation() {
  // get indexof & symbol in wifi config string from wifi config file
  String wifiConf = readFile();
  int index = wifiConf.indexOf("&");

  // Split string and attribute values to ssid and password strings
  String station_ssid_str = wifiConf.substring(0, index);
  String station_password_str = wifiConf.substring(index + 1);
  station_password_str.replace("%21", "!");

  // get size of ssid and password strings
  int size_station_ssid_str = sizeof(station_ssid_str) + 1;
  int size_station_password_str = sizeof(station_password_str) + 1 ;

  // initialize char arrays for ssid and password
  char station_ssid[size_station_ssid_str];
  char station_password[size_station_password_str];

  // put string values of ssid and password into char arrays
  strcpy(station_ssid, station_ssid_str.c_str());
  strcpy(station_password, station_password_str.c_str());

  // print ssid and password
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(station_ssid);
  Serial.print("With password: ");
  Serial.println(station_password);

  wifiMulti.addAP(station_ssid, station_password);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  //WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
}

void loopWifiStation() {

  if (wifiMulti.run() != WL_CONNECTED) {
    if (connectioWasAlive == true) {
      connectioWasAlive = false;
      Serial.print("Looking for WiFi ");
    }
    Serial.print(".");
    delay(500);
  } else if (connectioWasAlive == false) {
    connectioWasAlive = true;
    Serial.printf(" connected to %s\n", WiFi.SSID().c_str());
    Serial.print("=> Addresse IP : ");
    Serial.print(WiFi.localIP());
  }

}
