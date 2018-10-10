#ifndef SENSOR_ROOT_H
#define SENSOR_ROOT_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

class Sensor_root {
    public:
    void config_mqtt(Adafruit_MQTT_Client *mqtt, uint8_t qos);
    virtual bool setup();
    virtual bool publish(void);

    protected:
    Adafruit_MQTT_Client *adafruit_mqtt_client = NULL;
    uint8_t adafruit_mqtt_client_qos = MQTT_QOS_0;
};
#endif /* SENSOR_ROOT_H */
