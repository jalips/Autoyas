/************************************************************************
* Wifi in AP Mode to connect to a wired network
***********************************************************************/

#include <ESP8266WiFi.h>

#include "html/html.h"

// Config for webserver port
WiFiServer server(80);

// Config for connect to wifi AP
const char* ssid = "MyWemosWifiAP";
const char* password = "password";

IPAddress local_IP(192, 168, 1, 7); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network

//String html_ssid = "";
//String html_password = "";
//int ledPin = D5;
//int firstLaunch = 1;


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

String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Analog input:  " + String(analogRead(A0)) +
            "</html>" +
            "\r\n";
  return htmlPage;
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


    // Start the web server on port 80
    Serial.print("Webserver IP address = " + local_IP);
    Serial.print("Web-server port = ");
    server.begin();
    Serial.println("80");
    Serial.println();

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

  /*

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    Serial.println("LED=ON");
  }
  if (request.indexOf("/LED=OFF") != -1){
    Serial.println("LED=OFF");
  }

  */
}
