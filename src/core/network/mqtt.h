/************************************************************************
* MQTT Client
***********************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

#define mqtt_server "broker.hivemq.com"
#define mqtt_user ""
#define mqtt_password ""

WiFiClient espClient;
PubSubClient client(espClient);

#define test_topic "test/esp"
//#define temperature_topic "sensor/temperature"  //Topic température
//#define humidity_topic "sensor/humidity"        //Topic humidité

//Reconnexion
void reconnect() {
  //Boucle jusqu'à obtenur une reconnexion
  while (!client.connected()) {
    Serial.print("Connexion au serveur MQTT...");
    //if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    if (client.connect("ESP8266Client")) {
      Serial.println("OK");
    } else {
      Serial.print("KO, erreur : ");
      Serial.print(client.state());
      Serial.println(" On attend 5 secondes avant de recommencer");
      delay(5000);
    }
  }
}

void initSetupMQTT(){
  //Configuration de la connexion au serveur MQTT
  client.setServer(mqtt_server, 1883);
}

void loopMQTT(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //Publie sur le topic
  client.publish(test_topic, "boooom", true);


    /*
    long now = millis();
    //Envoi d'un message par minute
    if (now - lastMsg > 1000 * 60) {
      lastMsg = now;
      //Lecture de l'humidité ambiante
      float h = dht.readHumidity();
      // Lecture de la température en Celcius
      float t = dht.readTemperature();

      //Inutile d'aller plus loin si le capteur ne renvoi rien
      if ( isnan(t) || isnan(h)) {
        Serial.println("Echec de lecture ! Verifiez votre capteur DHT");
        return;
      }

      if ( debug ) {
        Serial.print("Temperature : ");
        Serial.print(t);
        Serial.print(" | Humidite : ");
        Serial.println(h);
      }
      client.publish(temperature_topic, String(t).c_str(), true);   //Publie la température sur le topic temperature_topic
      client.publish(humidity_topic, String(h).c_str(), true);      //Et l'humidité
    }
    if (now - lastRecu > 100 ) {
      lastRecu = now;
      client.subscribe("homeassistant/switch1");
    }
    */
}
