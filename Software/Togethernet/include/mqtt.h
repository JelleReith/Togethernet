#include <Arduino.h>

uint32_t byteToInt(byte* payload, unsigned int length);
void callback(char* topic, byte* payload, unsigned int length);
void connectToInternet();
void connect_MQTT();

void MQTT_init();
void pushMQTT();
void handleMQTT();