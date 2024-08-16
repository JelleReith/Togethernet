#include <mqtt.h>
#include "global_variables.h"
#include <Wifi.h>
#include <PubSubClient.h>  
#include "credentials.h"


WiFiClient net;
PubSubClient client(net);

bool internet_connected = false;

void pushMQTT(){
  uint16_t test_int = 100;
  char test_char_int[10];
  sprintf(test_char_int,"%ld", test_int);
  client.publish("/test_int",test_char_int);

  float test_float = 100.5f;
  char test_char_float[10];
  dtostrf(test_float,2,2,test_char_float);
  client.publish("/test_float",test_char_float);

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

  client.setBufferSize(1024);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("got data");
  if (strcmp(topic, "/address") == 0) {
  }
}

void MQTT_init() {
  client.setServer(domain, 1883);
  client.setCallback(callback);
  connect_MQTT();
  Serial.println("connected to MQTT");
}