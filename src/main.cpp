#include <Arduino.h>           // Core Arduino library
#include <WiFi.h>              // Library for Wi-Fi functionality
#include <PubSubClient.h>      // Library for MQTT functionality
#include "mqtt_config.h"       // MQTT configuration file
#include "wifi_config.h"       // Wi-Fi configuration file

// Function declarations (defined in other files)
void setup_wifi();                   // Function to connect to Wi-Fi
void reconnect();                    // Function to reconnect to the MQTT broker
void publish_message(const char* message); // Function to publish messages to MQTT

String get_uplink_message();          // Function to get the current uplink message
unsigned long get_send_interval();    // Function to get the current send time interval

// Global variables
WiFiClient espClient;                // Wi-Fi client instance
PubSubClient client(espClient);      // MQTT client instance using the Wi-Fi client

// Setup function: runs once when the ESP32 starts
void setup() {
    Serial.begin(9600);              // Initialize the serial monitor at 9600 baud

    // Connect to Wi-Fi
    setup_wifi();

    // Configure the MQTT client
    client.setServer(MQTT_HOST, MQTT_PORT); // Set the MQTT broker address and port
    client.setCallback(mqtt_callback);     // Set the callback function to handle incoming messages

    Serial.println("Setup completed.");    // Indicate that setup is complete
}

// Loop function: runs repeatedly after setup()
void loop() {
    // Reconnect to the MQTT broker if disconnected
    if (!client.connected()) {
        reconnect();
    }
    client.loop();                  // Handle incoming MQTT messages and maintain connection

    // Publish a message every 5 seconds
    static unsigned long lastMsg = 0; // Track the last message time
    unsigned long now = millis();    // Get the current time in milliseconds
    if (now - lastMsg > get_send_interval()) {      // Check if SEND_INTERVAL seconds have passed
        lastMsg = now;               // Update the last message time
        String uplink_message = get_uplink_message();  // Get the current uplink message
        publish_message(uplink_message.c_str());       // Publish the message to MQTT
    }
}