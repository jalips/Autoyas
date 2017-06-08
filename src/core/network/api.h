/************************************************************************
* Method to call API
***********************************************************************/
#include <ESP8266WiFi.h>

const char* host = "www.mocky.io";
const String url_register = "/v2/5185415ba171ea3a00704eed";
const String url_alive = "/v2/5185415ba171ea3a00704eed";

String getMacAdress(){
  byte mac[6];
  WiFi.macAddress(mac);
  String stringOne = "";
  String stringTwo = ":";
  String stringFinal = stringOne + mac[5] +
                        stringTwo + mac[4] +
                        stringTwo + mac[3] +
                        stringTwo + mac[2] +
                        stringTwo + mac[1] +
                        stringTwo + mac[0];
  Serial.println(stringFinal);
  return stringFinal;
}

void sampleAPIGet(const char* host, String url){
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80)){
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected()){
      if (client.available()){
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }else{
    Serial.println("connection failed!]");
    client.stop();
  }
}

int callAPIForRegister(String data){
  sampleAPIGet(host,url_register+data);
}

void callAPIForStayingAlive(String data){
  sampleAPIGet(host,url_alive+data);
}
