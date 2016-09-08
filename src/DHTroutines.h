#ifndef DHTroutines_h
#define DHTroutines_h

#include "Arduino.h"  // Arduino header
#include "defines.h"  // defines header

// Module specific headers
#include "DHT.h"      // DHT library header


class DHTsensor
{
public:
  DHTsensor(float * _temperature, float * _humidity);
  bool setup();
  bool readDHT();


  DHT dht;
  float * temperature;
  float * humidity;


private:
};

#endif
