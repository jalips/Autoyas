/************************************************************************
* Wifi in Station Mode that has the capability to use the 802.11 protocol
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
boolean connectioWasAlive = true;

const char* station_ssid = "MyRedmi";
const char* station_pass = "password";

void initSetupWifiStation() {

  wifiMulti.addAP(station_ssid, station_pass);

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
