/************************************************************************
* Wifi in AP Mode to connect to a wired network
***********************************************************************/

#include <ESP8266WiFi.h>

#include "../html/html.h"

// Config for webserver port
WiFiServer server(80);

// Config for connect to wifi AP
//const char* ssid = "AutoyasWifi";
const char* ssid = "MyWemosWifiAP";
const char* password = "password";

IPAddress local_IP(192, 168, 1, 7); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network

/*
void scanWifiNetwork(){
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
}
*/

void getResponse (String text) {
  Serial.println("Mon texte : "+text);

  if (text.endsWith("HTTP/1.1") && text.startsWith("GET /?")){

      String text_get = text.substring(6);
      Serial.println("Mon texte GET : "+text_get);

      text_get.replace("ssid=", "");
      text_get.replace("HTTP/1.1", "");
      text_get.replace("password=", "");

      Serial.println("Mon texte replace : "+text_get);

      int text_index = text_get.indexOf('&');
      String text_ssid = text_get.substring(0,text_index--);
      //text_ssid.replace("%20"," ");
      Serial.println("Mon texte SSID : "+text_ssid);

      text_get.replace(text_ssid+"&", "");
      text_get.replace("%21","!");
      Serial.println("Mon texte Key : "+text_get);

      String html_ssid = text_ssid;
      String html_password = text_get;

      writeFile(html_ssid, html_password);
  }
}

void initSetupWifiAP() {
    Serial.println("*** Wemos D1 WiFi Web-Server in AP Mode ***");
    // Doing some config for static IP
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
    // And start wifi with ssid and password set
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
    // Print it IP Adress
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());

    // Display info for wifi
    /*
    Serial.print("You can connect to :");
    Serial.println("SSID : "+ssid);
    Serial.println("password : "+password);
    */

    // Start the web server on port 80
    Serial.println("Webserver IP address = " + local_IP);
    Serial.println("Web-server port = 80");
    server.begin();
}

void loopWifiAP(){

  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());

  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);

        if (line.endsWith("HTTP/1.1") && line.startsWith("GET /?")){
            // Here we write the file
            getResponse(line);
        }

        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disconnected]");
  }
}
