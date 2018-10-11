#include "user_config.h"
#include "sensor_root.h"
#include "sensor_analog.h"
#include "sensor_bmp085.h"

uint8_t init_sensors(Sensor_root ***s) {
  Sensor_root **sensors;

  // Don't forget to update 'max_sensors' when you add more sensors
  uint8_t max_sensors = 2;

  *s = (Sensor_root **)calloc(max_sensors, sizeof(Sensor_root *));
  sensors = *s;

  // Add more sensors here
  sensors[0] = new Sensor_analog(SENSORBASE_MQTT_USERNAME "/" CLIENT_NAME "/arduino/a0", A0, 1.38696);
  sensors[1] = new Sensor_bmp085(SENSORBASE_MQTT_USERNAME "/" CLIENT_NAME "/bmp/temperature",
      SENSORBASE_MQTT_USERNAME "/" CLIENT_NAME "/bmp/pressure");
  // sensors[2] = ...

  return max_sensors;
}
