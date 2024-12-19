#include <PubSubClient.h>       // Library for handling MQTT protocol
#include "mqtt_config.h"        // MQTT configuration file
#include <ArduinoJson.h>        // Library for parsing and handling JSON data

extern PubSubClient client;     // External MQTT client instance (defined elsewhere in the project)

// Global variables that can be modified by downlinks
String uplink_message = "Hello world!";
unsigned long send_interval = SEND_INTERVAL;

// Callback function to process received MQTT messages
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);

    // Convert the payload to a String for easier manipulation
    String received_message;
    for (unsigned int i = 0; i < length; i++) {
        received_message += (char)payload[i];
    }
    Serial.print("Received message: ");
    Serial.println(received_message);

    // Attempt to parse the message as JSON
    StaticJsonDocument<200> doc;  // Allocate memory for JSON processing
    DeserializationError error = deserializeJson(doc, received_message);
    if (error) {
        // If the message is not a valid JSON, use it as plain text
        Serial.println("Error parsing JSON. Using the message as plain text.");
        uplink_message = received_message;
    } else {
        // If the message is valid JSON, look for keys
        if (doc.containsKey("uplink_message")) {
            uplink_message = doc["uplink_message"].as<String>();
            Serial.print("Uplink message updated to: ");
            Serial.println(uplink_message);
        }

        if (doc.containsKey("send_interval_seconds")) {
            int interval_seconds = doc["send_interval_seconds"];
            if (interval_seconds > 0) {
                send_interval = interval_seconds * 1000; // Convert to milliseconds
                Serial.print("Send interval updated to: ");
                Serial.print(interval_seconds);
                Serial.println(" seconds.");
            } else {
                Serial.println("Invalid interval value. Must be greater than 0.");
            }
        }
    }
}

// Function to handle MQTT reconnection
void reconnect() {
    // Keep trying to connect to the MQTT broker until successful
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect(MQTT_ID, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Connected.");

            // Subscribe to the downlink topic
            client.subscribe(MQTT_TOPIC_DOWNLINK);
            Serial.print("Subscribed to: ");
            Serial.println(MQTT_TOPIC_DOWNLINK);
        } else {
            // If connection fails, print the error and retry after 5 seconds
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

// Function to publish a message to the uplink topic
void publish_message(const char* message) {
    Serial.print("Sending message: ");
    Serial.println(message);
    client.publish(MQTT_TOPIC_UPLINK, message);
}

// Function to get the current uplink message
String get_uplink_message() {
    return uplink_message;
}

unsigned long get_send_interval() {
    return send_interval;
}