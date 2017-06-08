/************************************************************************
* MQTT Client
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

// Broker adress
#define mqtt_server "jalips.ddns.net"
#define mqtt_user ""
#define mqtt_password ""

WiFiClient espClient;
PubSubClient client(espClient);

//Topic temp & hydro
//#define temperature_topic "sensor/temperature
//#define humidity_topic "sensor/hydro"

void reconnect() {
  int nbTry = 0;
  while (!client.connected()) {
    Serial.print("Connexion au serveur MQTT...");
    //if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    if (client.connect("AutoyasClient")) {
      Serial.println("OK");
    } else {
      Serial.print("KO, erreur : ");
      Serial.print(client.state());
      Serial.println(" On attend 5 secondes avant de recommencer");
      delay(5000);
    }
    nbTry++;
    if(nbTry == 1){
      break;
    }
  }
}

void initSetupMQTT(){
  // Config connexion for MQTT server
  client.setServer(mqtt_server, 1883);
}

void loopMQTT(const char* topic, const char* message){
  if (!client.connected()) {
    reconnect();
  }else{
    Serial.println("Still connected with MQTT Broker");
  }
  client.loop();

  // Publish on topic
  client.publish(topic, message, true);
}
