#ifndef Defines_h
#define Defines_h

#include "Arduino.h"

#define DEBUG 1       //Turn debugging functions on/off


// PIN definitions
#define SD_PIN 4      //CS pin for SD module
#define LED_PIN 1    //pin for LED (for visual feedback)
#define NPN_PIN 21    //pin for NPN transistor
#define DHT_PIN 2// DHT pin

//TODO: find out startup time
#define ACC_STARTUPTIME 100 // ms that the accelerometer takes to startup
#define ACC_SAMPLERATE 1000 // Fixed accelerometer samplerate
#define EXTRA_SAMPLES  10  // Extra samples to be collected each time

// Max samples, Min samples
// TODO: arbitrary for now, find out based on memory usage
#define MAX_N_SAMPLES 2048
#define MIN_N_SAMPLES 1024
#define DEFAULT_N_SAMPLES MIN_N_SAMPLES + EXTRA_SAMPLES


typedef union unpackFloat {
  float f;
  byte b[4];
} UNPACKFLOAT;


#endif
