#include <Arduino.h>
#include "global_variables.h"
#include "global_variables_init.h"
#include "helperfunctions.h"
#include "mqtt.h"

void setup(){
  Serial.begin(115200);
  MQTT_init();

  pinMode(10, INPUT);
}

void loop(){
 handleMQTT();
 pushMQTT();
 delay(100);
}



