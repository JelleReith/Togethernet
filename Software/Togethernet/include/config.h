#define IS_INPUT_DEVICE //comment this line if device does not have an sensor input
#define IS_OUTPUT_DEVICE //comment this line if device does not have an output 

const char *id = "extrapractice_door_sensor"; 

#ifdef IS_OUTPUT_DEVICE
      const char *listen_topic = "/swsws_coffeepot_temperature";
#endif

#ifdef IS_INPUT_DEVICE
      const char *publisch_topic = "/extrapractice_door_open";
#endif
