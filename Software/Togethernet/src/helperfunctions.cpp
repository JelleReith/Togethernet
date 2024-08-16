#include "helperfunctions.h"
#include "global_variables.h"
#include <WiFi.h>

uint16_t niceRead(uint8_t pin, uint16_t numSamples) {
  unsigned long addedVal = 0;
  uint16_t returnVal = 0;
  for (int i = 0; i < numSamples; i++) {
    addedVal = addedVal + (analogRead(pin));
  }
  returnVal = uint16_t(addedVal / numSamples);
  return returnVal;
}