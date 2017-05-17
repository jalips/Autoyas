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
    Serial.println("[Client disonnected]");
  }

  /*
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

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



  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  */
}


/*
void setApMode() {

    WiFiClient myClient = server.available();

    if (myClient)
    { // if you get a client,
        Serial.println(". Client connected to server");           // print a message out the serial port
        char buffer[150] = {0};                 // make a buffer to hold incoming data
        int8_t i = 0;
        while (myClient.connected())
        { // loop while the client's connected
            if (myClient.available())
            { // if there's bytes to read from the client,
                char c = myClient.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (strlen(buffer) == 0)
                    {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        myClient.println("HTTP/1.1 200 OK");
                        myClient.println("Content-type:text/html");
                        myClient.println();

                        // the content of the HTTP response follows the header:
                        myClient.println("<html><head><title>Wemos D1 WiFi Web-Server in AP Mode</title></head><body align=center>");
                        myClient.println("<h1 align=center><font color=\"red\">Wemos D1 WiFi Web-Server in AP Mode</font></h1>");
                        myClient.println("<FORM METHOD=\"GET\" ACTION=\"\">");
                        myClient.println("<INPUT type=\"text\" name=\"ssid\">");
                        myClient.println("<INPUT type=\"password\" name=\"password\">");
                        myClient.println("<INPUT type=\"submit\">");
                        myClient.println("</FORM>");

                        // The HTTP response ends with another blank line:
                        myClient.println();
                        // break out of the while loop:
                        break;
                    }
                    else
                    { // if you got a newline, then clear the buffer:
                        memset(buffer, 0, 150);
                        i = 0;
                    }
                }
                else if (c != '\r')
                { // if you got anything else but a carriage return character,
                    buffer[i++] = c;      // add it to the end of the currentLine
                }

                Serial.println();

                String text = buffer;

                // Check to see if the client request was "GET /H" or "GET /L":
                if (text.endsWith(" HTTP/1.1") && text.startsWith("GET /?ssid="))
                {
                    text.replace(" HTTP/1.1", "");
                    text.replace("GET /?ssid=", "");
                    text.replace("password=", "");

                    // TODO : Function missing
                    //writeconf(text);
                    //restart();
                }
            }
        }

        // close the connection:
        myClient.stop();
        Serial.println(". Client disconnected from server");
        Serial.println();
    }
}
*/
