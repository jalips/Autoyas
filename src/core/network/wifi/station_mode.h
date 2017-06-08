/************************************************************************
* Wifi in Station Mode that has the capability to use the 802.11 protocol
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
boolean connectioWasAlive = true;

const char* station_ssid_test = "SFR-0c78";
const char* station_pass_test = "DVZ25M395J65";

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

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Add network
  //wifiMulti.addAP(station_ssid, station_password);

  WiFi.begin(station_ssid_test, station_pass_test);
  //WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    switch (WiFi.status()) {
      case 0:
        // when Wi-Fi is in process of changing between statuses
        Serial.println("WL_IDLE_STATUS");
        break;
      case 1:
        // in case configured SSID cannot be reached
        Serial.println("WL_NO_SSID_AVAIL");
        break;
      case 3:
        // after successful connection is established
        Serial.println("WL_CONNECTED");
        break;
      case 4:
        // if password is incorrect
        Serial.println("WL_CONNECT_FAILED");
        break;
      case 6:
        // if module is not configured in station mode
        Serial.println("WL_DISCONNECTED");
        break;
    }
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loopWifiStation() {

  switch (WiFi.status()) {
    case 0:
      // when Wi-Fi is in process of changing between statuses
      Serial.print("WL_IDLE_STATUS");
      break;
    case 1:
      // in case configured SSID cannot be reached
      Serial.print("WL_NO_SSID_AVAIL");
      break;
    case 3:
      // after successful connection is established
      Serial.print("WL_CONNECTED");
      break;
    case 4:
      // if password is incorrect
      Serial.print("WL_CONNECT_FAILED");
      break;
    case 6:
      // if module is not configured in station mode
      Serial.print("WL_DISCONNECTED");
      break;
  }

  /*
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
  */

}
