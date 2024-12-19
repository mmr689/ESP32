# Changelog

This document contains a detailed history of the versions and their major changes.

## [Wifi+Mqtt-Uplink+Downlink] - 2024-12-19
### Added
- Basic WiFi connectivity.
- MQTT uplink functionality to publish messages.
- Downlink support to receive and process messages from an MQTT topic.

### Notes
- The downlink allows dynamic updates, such as changing the uplink message based on incoming data. 
- Supported formats for downlink messages include:
  - **Plain text**: Directly updates the uplink message.
  - **JSON**: If the message is in JSON format, the system looks for the key `"uplink_message"` to update the uplink message.

### Example
- **Plain Text**: Sending `Hello ESP32!` to the downlink topic updates the uplink message to `Hello ESP32!`.
- **JSON**: Sending the following JSON to the downlink topic:
  ```json
  {
    "uplink_message": "New message from downlink!"
  }

## [Wifi+Mqtt-Uplink] - 2024-12-19
### Added
- Initial implementation of WiFi connectivity.
- Integration with an MQTT server to handle uplink data transmission.

### Notes
- This version introduces the core features for connectivity and communication, suitable for basic IoT applications.
