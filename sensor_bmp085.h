#ifndef SENSOR_BMP085_H
#define SENSOR_BMP085_H

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "sensor_root.h"

class Sensor_bmp085 : public Sensor_root {
    public:
    Sensor_bmp085(const char *topic_temperature, const char *topic_pressure);
    bool setup();
    bool publish(void);

    private:
    Adafruit_BMP085 bmp;
    Adafruit_MQTT_Publish *publisher_temp;
    Adafruit_MQTT_Publish *publisher_pres;
    const char *topic_temp;
    const char *topic_pres;
};

#endif /* SENSOR_BMP085_H */
