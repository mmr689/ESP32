#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "mqtt_config.h"
#include "wifi_config.h"

// Declaración de funciones en otros archivos
void setup_wifi();
void reconnect();
void publish_message(const char* message);

// Variables globales
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(9600);

    // Conectar al Wi-Fi
    setup_wifi();

    // Configurar cliente MQTT
    client.setServer(MQTT_HOST, MQTT_PORT);

    Serial.println("Setup completado.");
}

void loop() {
    // Reintentar conexión MQTT si es necesario
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Enviar mensaje cada 5 segundos
    static unsigned long lastMsg = 0;
    unsigned long now = millis();
    if (now - lastMsg > 5000) {
        lastMsg = now;
        publish_message("Hello world!");
    }
}
