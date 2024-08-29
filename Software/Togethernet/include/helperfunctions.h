#include <Arduino.h>
#include "driver/touch_sensor.h"
uint16_t niceRead(uint8_t pin, uint16_t numSamples);
void initDeviceSensorInput();
void initDeviceOutput();

void handleDeviceSensorInput();
void handleDeviceOutput();