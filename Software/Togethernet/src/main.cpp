#include <Arduino.h>
#include "global_variables.h"
#include "global_variables_init.h"
#include "helperfunctions.h"
#include "mqtt.h"

void setup(){
  Serial.begin(115200);
  while(!Serial){
    delay(10);
  }
  MQTT_init();
  initDeviceSensorInput();
  initDeviceOutput();
  Serial.println("setup done");
}

TickType_t currentTicks;
TickType_t previousTicks; 
uint16_t tickInterval = 500;

void loop(){
  currentTicks = xTaskGetTickCount();
 
  handleMQTT(); //handles MQTT, internet connection etc

  handleDeviceSensorInput(); //this functions handles sensors
  handleDeviceOutput(); //this function handles outputs e.g. motors, relays, led lights etc

  if(currentTicks > previousTicks + tickInterval){ // check if 500ms have passed
    previousTicks = currentTicks;
    pushMQTT(); //sends sensor data over MQTT
  }

  delay(10);
}



