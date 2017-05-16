/************************************************************************
* Wifi in AP Mode to connect to a wired network
***********************************************************************/

#include <ESP8266WiFi.h>

#include "html/html.h"

// Config for webserver port
WiFiServer server(80);
//ESP8266WebServer server(80);

// Config for connect to wifi AP
const char* ssid = "MyWemosWifiAP";
const char* password = "link";

IPAddress local_IP(192, 168, 1, 7); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network

//String html_ssid = "";
//String html_password = "";
//int ledPin = D5;
//int firstLaunch = 1;

void initSetupWifiAP() {
    Serial.println("*** Wemos D1 WiFi Web-Server in AP Mode ***");

    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("MyWemosWifiAP", "password") ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());

    /* VERSION TEST 2
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("ESPsoftAP_01") ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    */

    /* VERSION TEST
    Serial.print(F("Setting static ip to : "));
    Serial.println(ip);

    // Connect to WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address
    Serial.print("Use this URL : ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    */


    // VERSION MANON
    // Start WiFi and create a network with ssid as the network name
    // with password as the password.
    /*
    Serial.print("Starting AP...");
    WiFi.begin(ssid, password);

    // Print dots while we wait for the AP config to complete
    while (WiFi.localIP() == INADDR_NONE){
        Serial.print('.');
        delay(300);
    }
    Serial.println("DONE");

    Serial.print("LAN name = ");
    Serial.println(ssid);
    Serial.print("WPA password = ");
    Serial.println(password);

    IPAddress ip = WiFi.localIP();
    Serial.print("Webserver IP address = ");
    Serial.println(ip);

    // Start the web server on port 80
    Serial.print("Web-server port = ");
    server.begin();
    Serial.println("80");
    Serial.println();
    */
}

void loopWifiAP(){
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());

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


/*********************
Init wifi in AP Mode
**********************/
/*
void initWifi(){
    Serial.println("*** LaunchPad CC3200 WiFi Web-Server in AP Mode");

    // Start WiFi and create a network with ssid as the network name
    // with password as the password.
    Serial.print("Starting AP... ");
    WiFi.begin(ssid, password);
    while (WiFi.localIP() == INADDR_NONE)
    {
        // print dots while we wait for the AP config to complete
        Serial.print('.');
        delay(300);
    }
    Serial.println("DONE");

    Serial.print("LAN name = ");
    Serial.println(ssid);
    Serial.print("WPA password = ");
    Serial.println(password);

    IPAddress ip = WiFi.localIP();
    Serial.print("Webserver IP address = ");
    Serial.println(ip);

    Serial.print("Web-server port = ");
    server.begin();                           // start the web server on port 80
    Serial.println("80");
    Serial.println();
}
*/

/*********************
Wifi running in AP Mode
**********************/
/*
int modeAP(){
    // Start Led
    digitalWrite(ledPin, HIGH);

    // Init wifi if it's the firstLaunch for conf
    if(firstLaunch){
        firstLaunch = 0;
        // Init WiFi
        initWifi();
    }

    WiFiClient myClient = server.available();

    if (myClient)
    {                             // if you get a client,
        Serial.println(". Client connected to server");           // print a message out the serial port
        char buffer[150] = {0};                 // make a buffer to hold incoming data
        int8_t i = 0;
        while (myClient.connected())
        {            // loop while the client's connected
            if (myClient.available())
            {             // if there's bytes to read from the client,
                char c = myClient.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (strlen(buffer) == 0)
                    {
                        // Display Html Form with println
                        displayHtmlForm(myClient);

                        // The HTTP response ends with another blank line:
                        myClient.println();
                        // break out of the while loop:
                        break;
                    }
                    else
                    {      // if you got a newline, then clear the buffer:
                        memset(buffer, 0, 150);
                        i = 0;
                    }
                }
                else if (c != '\r')
                {    // if you got anything else but a carriage return character,
                    buffer[i++] = c;      // add it to the end of the currentLine
                }

                Serial.println();
                String text = buffer;

                //Serial.println(text);

                if (text.endsWith("HTTP/1.1") && text.startsWith("GET /?")){
                    Serial.println("Mon texte : "+text);

                    String text_get = text.substring(6);
                    Serial.println("Mon texte GET : "+text_get);

                    text_get.replace("ssid=", "");
                    text_get.replace("&Submit=Envoyer HTTP/1.1", "");
                    text_get.replace("key=", "");


                    Serial.println("Mon texte replace : "+text_get);

                    int text_index = text_get.indexOf('&');

                    String text_ssid = text_get.substring(0,text_index--);
                    //text_ssid.replace("%20"," ");
                    Serial.println("Mon texte SSID : "+text_ssid);

                    text_get.replace(text_ssid+"&", "");
                    text_get.replace("%21","!");
                    Serial.println("Mon texte Key : "+text_get);

                    html_ssid = text_ssid;
                    html_password = text_get;

                    // writeFile(html_ssid, html_password);

                    // close the connection & Yellow led stop:
                    digitalWrite(ledPin, LOW);
                    myClient.stop();

                    WiFi.disconnect();
                    return 0;
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
