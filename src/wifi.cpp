#include <WiFi.h>              // Library for Wi-Fi functionality
#include "wifi_config.h"       // Wi-Fi configuration file containing SSID and password

// Function to set up Wi-Fi connection
void setup_wifi() {
    // Print the SSID of the Wi-Fi network being connected to
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);

    // Begin the connection using the provided SSID and password
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Wait until the connection is established
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");    // Print a dot every 500 ms as a loading indicator
    }

    // Once connected, print a success message
    Serial.println("\nWiFi connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());  // Print the device's local IP address
}