#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#define DEBUG
#undef DEBUG

#define SITE_USA 1
#define SITE_RUSSIA 2
#define CLIENT_SERIAL "01"

#define SITE SITE_USA

#if SITE == SITE_USA
#define WLAN_SSID       "WhiteHouse"
#define WLAN_PASS       "whiskeywhiskey"
#define CLIENT_NAME     "usa" CLIENT_SERIAL
#elif SITE == SITE_RUSSIA
#define WLAN_SSID       "Kreml"
#define WLAN_PASS       "vodkavodka"
#define CLIENT_NAME     "russia" CLIENT_SERIAL
#else
#define WLAN_SSID       "default"
#define WLAN_PASS       NULL
#define CLIENT_NAME     "unknown" CLIENT_SERIAL
#endif

#define SENSORBASE_MQTT_SERVER      "mqtt.server.cn"
#define SENSORBASE_MQTT_SERVERPORT  1883                   // use 8883 for SSL
#define SENSORBASE_MQTT_USERNAME    "weather"
#define SENSORBASE_MQTT_KEY         "secret"
#define SENSORBASE_MQTT_QOS MQTT_QOS_1

#define SENSORBASE_MY_HUP SENSORBASE_MQTT_USERNAME "/" CLIENT_NAME "/hup"
#define SENSORBASE_GLOBAL_HUP SENSORBASE_MQTT_USERNAME "/global/hup"

#include "sensor_root.h"
uint8_t init_sensors(Sensor_root ***sensors);

#endif /* USER_CONFIG_H */
