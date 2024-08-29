#include "helperfunctions.h"
#include "global_variables.h"
#include "driver/touch_sensor.h"
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(1, 38, NEO_GRB + NEO_KHZ800);

uint16_t niceRead(uint8_t pin, uint16_t numSamples) { //nice function to average some sensor readings to reduce noise
  unsigned long addedVal = 0;
  uint16_t returnVal = 0;
  for (int i = 0; i < numSamples; i++) {
    addedVal = addedVal + (analogRead(pin));
  }
  returnVal = uint16_t(addedVal / numSamples);
  return returnVal;
}

void initDeviceSensorInput(){
  //touch_pad_deinit();
  touch_pad_init();   
  touch_pad_set_cnt_mode(touch_pad_t(TOUCH_PAD_NUM1), touch_cnt_slope_t(TOUCH_PAD_SLOPE_7), touch_tie_opt_t(0));
  touch_pad_config(touch_pad_t(TOUCH_PAD_NUM1));
  touch_pad_set_meas_time(10, 10);
  touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
  touch_pad_fsm_start();
  
}

void initDeviceOutput(){
  pixels.begin(); 
}

uint32_t raw_input_val = 10;
uint32_t min32_t = 0;
uint32_t max32_t = -1;
uint16_t min16_t = 0;
uint16_t max16_t = -1;

void handleDeviceSensorInput(){ 
  //sensor input here
  touch_pad_read_raw_data(touch_pad_t(1), &raw_input_val);
  mqttOutputVal = uint16_t(map(raw_input_val, min32_t, max32_t, min16_t, max16_t));
  Serial.println(mqttOutputVal);
}

void handleDeviceOutput(){
  uint16_t min = 0;
  uint16_t max = -1;
  pixels.setPixelColor(0, pixels.Color(map(mqttOutputVal, min,max,0,255), map(mqttOutputVal, min,max,0,255), map(mqttOutputVal, min,max,0,255)));
  pixels.show();   // Send the updated pixel colors to the hardware.
// sensor output here
}