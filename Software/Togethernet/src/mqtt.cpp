#include <mqtt.h>
#include "global_variables.h"
#include <Wifi.h>
#include <PubSubClient.h>  
#include "credentials.h"
#include "config.h"

WiFiClient net;
PubSubClient client(net);

bool internet_connected = false;

void pushMQTT(){
  char test_char_int[10];
  sprintf(test_char_int,"%ld", mqttOutputVal);
  client.publish(publisch_topic,test_char_int);
}

void connectToInternet() {
  Serial.println("Connecting to WiFi.");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  internet_connected = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void handleMQTT(){
    client.loop(); 
}

void connect_MQTT() {
  connectToInternet();
  while (!internet_connected) {
    delay(1);
  }
  Serial.println("connecting to Shiftr ");
  while (!client.connect(id, user, password)){
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("Connected!");
  #ifdef IS_OUTPUT_DEVICE
    client.subscribe(listen_topic);
  #endif
  client.setBufferSize(1024);
}

uint32_t byteToInt(byte* payload, unsigned int length) {
  char format[16];
  snprintf(format, sizeof format, "%%%ud", length);
  uint32_t payload_value = 0;
  if (sscanf((const char*)payload, format, &payload_value) == 1) {
    return payload_value;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, listen_topic) == 0) {
    mqttInputVal = byteToInt(payload, length);
  } 
}

void MQTT_init() {
  client.setServer(domain, 1883);
  client.setCallback(callback);
  connect_MQTT();
  Serial.println("connected to MQTT");
}