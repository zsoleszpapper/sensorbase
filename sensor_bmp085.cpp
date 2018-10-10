#include "sensor_bmp085.h"

Sensor_bmp085::Sensor_bmp085(const char *topic_temperature, const char *topic_pressure) {
  topic_temp = topic_temperature;
  topic_pres = topic_pressure;
}

bool Sensor_bmp085::setup() {
  publisher_temp = new Adafruit_MQTT_Publish(adafruit_mqtt_client, topic_temp, adafruit_mqtt_client_qos);
  publisher_pres = new Adafruit_MQTT_Publish(adafruit_mqtt_client, topic_pres, adafruit_mqtt_client_qos);
  return bmp.begin();
}

bool Sensor_bmp085::publish(void) {
    publisher_temp->publish(bmp.readTemperature());
    publisher_pres->publish(bmp.readPressure());
}
