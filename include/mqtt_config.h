#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

#include "device_config.h"

#define MQTT_ID "bitaqua-" DEVICE_ID
#define MQTT_HOST "lorawan-live.wdna.com"
#define MQTT_PORT 1883
#define MQTT_USER "wdna"
#define MQTT_PASSWORD "B24Qsfp%PmVnM5"

#define MQTT_TOPIC_UPLINK "controller/" DEVICE_ID "/up"
#define MQTT_TOPIC_DOWNLINK "controller/" DEVICE_ID "/down"
#define MQTT_TOPIC_PING "controller/" DEVICE_ID "/ping"

void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
