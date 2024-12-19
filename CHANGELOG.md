# Changelog

This document contains a detailed history of the versions and their major changes.

## [v1.1.0] - 2024-12-19
### Added
- Basic WiFi connectivity.
- MQTT uplink functionality to publish messages.
- Downlink support to receive and process messages from an MQTT topic.
- Dynamic configuration of the uplink interval via downlink JSON messages.

### Notes
- The downlink allows dynamic updates, such as changing the uplink message or adjusting the uplink interval based on incoming data.
- Supported formats for downlink messages include:
  - **Plain text**: Directly updates the uplink message.
  - **JSON**: If the message is in JSON format, the system processes specific keys:
    - `"uplink_message"`: Updates the message sent in uplink.
    - `"send_interval_seconds"`: Updates the interval for uplink messages in seconds.

### Example
- **Plain Text**: Sending `Hello ESP32!` to the downlink topic updates the uplink message to `Hello ESP32!`.
- **JSON**: Sending the following JSON to the downlink topic:
  ```json
  {
    "uplink_message": "New dynamic message!",
    "send_interval_seconds": 60
  }

## [v1.0.0] - 2024-12-19
### Added
- Initial implementation of WiFi connectivity.
- Integration with an MQTT server to handle uplink data transmission.

### Notes
- This version introduces the core features for connectivity and communication, suitable for basic IoT applications.
