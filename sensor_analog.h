#ifndef SENSOR_ANALOG_H
#define SENSOR_ANALOG_H

#include "sensor_root.h"

class Sensor_analog : public Sensor_root {
    public:
    Sensor_analog(const char *topic, int pin);
    Sensor_analog(const char *topic, int pin, double normalize);
    bool setup();
    bool publish(void);

    private:
    Adafruit_MQTT_Publish *analog_publisher;
    const char *analog_topic;
    int analog_pin = A0;
    double analog_normalize = 1;
};

#endif /* SENSOR_ANALOG_H */
