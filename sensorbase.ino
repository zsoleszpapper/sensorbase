#define WLAN_SSID       "mywifissid"
#define WLAN_PASS       "mywifipass"
#define CLIENT_NAME     "client01"

#define SENSORBASE_MQTT_SERVER      "my.mqtt.server.com"
#define SENSORBASE_MQTT_SERVERPORT  1883                   // use 8883 for SSL
#define SENSORBASE_MQTT_USERNAME    "mqttuser"
#define SENSORBASE_MQTT_KEY         "mqttpass"

#define X_INTERVAL_SEC 60
#define TURNAROUND_SEC 2

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "sensor_root.h"

#include "user_config.h"

Sensor_root **sensors;
uint8_t num_of_sensors = 0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, SENSORBASE_MQTT_SERVER, SENSORBASE_MQTT_SERVERPORT, "SENSORBASE_" CLIENT_NAME, SENSORBASE_MQTT_USERNAME, SENSORBASE_MQTT_KEY);
Adafruit_MQTT_Subscribe my_hup = Adafruit_MQTT_Subscribe(&mqtt, SENSORBASE_MY_HUP, SENSORBASE_MQTT_QOS);
Adafruit_MQTT_Subscribe global_hup = Adafruit_MQTT_Subscribe(&mqtt, SENSORBASE_GLOBAL_HUP, SENSORBASE_MQTT_QOS);

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
#ifdef SB_DEBUG
  Serial.begin(115200); delay(10);
  Serial.println("Start init sensors");
#endif
  num_of_sensors = init_sensors(&sensors);
  for(int i = 0; i < num_of_sensors; i++) {
    if (!sensors[i]) {
      continue;
    }
    sensors[i]->config_mqtt(&mqtt, SENSORBASE_MQTT_QOS);
  }
#ifdef SB_DEBUG
  Serial.print("Connecting to "); Serial.println(WLAN_SSID);
#endif
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
#ifdef SB_DEBUG
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
#endif
  mqtt.subscribe(&my_hup);
  mqtt.subscribe(&global_hup);
  for(int i = 0; i < num_of_sensors; i++) {
    if (!sensors[i]) {
      continue;
    }
    bool result = sensors[i]->setup();
    if (!result) {
      delete(sensors[i]);
      sensors[i] = NULL;
    }
#ifdef SB_DEBUG
    if (result) {
     Serial.print("Setup OK "); Serial.println(i);
    } else {
     Serial.print("Setup ERROR "); Serial.println(i);
    }
#endif
  }
}

uint32_t x = 0;
uint32_t x_timer = 0;

void increment_timers() {
  x_timer++;
  if (x_timer >= (X_INTERVAL_SEC / TURNAROUND_SEC)) {
    x_timer = 0;
  }
}

void loop() {
  bool publish_success;
  Adafruit_MQTT_Subscribe *subscription;

  MQTT_connect();
  while ((subscription = mqtt.readSubscription(TURNAROUND_SEC * 1000))) {
    if (subscription == &my_hup || subscription == &global_hup) {
#ifdef SB_DEBUG
      Serial.print(F("Got: "));
      Serial.println((char *)((*subscription).lastread));
#endif
      x_timer = 0;
    }
  }

  publish_success = true;
  if (x_timer == 0) {
    for(int i = 0; i < num_of_sensors; i++) {
      if (!sensors[i]) {
        continue;
      }
      publish_success &= sensors[i]->publish();
    }
  }

  increment_timers();

  if (!publish_success) {
    x_timer = 0;
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
#ifdef SB_DEBUG
  Serial.print("Connecting to MQTT... ");
#endif
  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
#ifdef SB_DEBUG
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
#endif
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
#ifdef SB_DEBUG
  Serial.println("MQTT Connected!");
#endif
}
