#include "sensor_root.h"

void Sensor_root::config_mqtt(Adafruit_MQTT_Client *mqtt, uint8_t qos) {
  adafruit_mqtt_client = mqtt;
  adafruit_mqtt_client_qos = qos;
}

