/**
 * Main program with setup and loop
 */
#include "conf/ap_conf.h"
#include "html/html.h"

const char* ssid = "";
const char* password = "";

String html_ssid = "";
String html_password = "";

int ledPin = D5;
WiFiServer server(80);
int firstLaunch = 1;

void initApMode() {
    delay(500);

    Serial.println("*** Wemos D1 WiFi Web-Server in AP Mode");

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



/*********************
Init wifi in AP Mode
**********************/
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


/*********************
Wifi running in AP Mode
**********************/
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

                    writeFile(html_ssid, html_password);

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
