#include <PubSubClient.h>
#include "mqtt_config.h"

extern PubSubClient client;

void reconnect() {
    while (!client.connected()) {
        Serial.print("Conectando a MQTT...");
        if (client.connect(MQTT_ID, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Conectado.");
        } else {
            Serial.print("Fallo, rc=");
            Serial.print(client.state());
            Serial.println(" Reintentando en 5 segundos...");
            delay(5000);
        }
    }
}

void publish_message(const char* message) {
    Serial.print("Enviando mensaje: ");
    Serial.println(message);
    client.publish(MQTT_TOPIC_UPLINK, message);
}