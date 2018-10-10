#include "sensor_analog.h"

Sensor_analog::Sensor_analog(const char *topic, int pin) {
  Sensor_analog(topic, pin, 1);
}

Sensor_analog::Sensor_analog(const char *topic, int pin, double normalize) {
  analog_pin = pin;
  analog_topic = topic;
  analog_normalize = normalize;
}

bool Sensor_analog::setup() {
  analog_publisher = new Adafruit_MQTT_Publish(adafruit_mqtt_client, analog_topic, adafruit_mqtt_client_qos);
  return true;
}

bool Sensor_analog::publish(void) {
    analog_publisher->publish(analogRead(analog_pin)*analog_normalize);
}
