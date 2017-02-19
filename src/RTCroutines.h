#ifndef RTCroutines_h
#define RTCroutines_h

#include "Arduino.h"    // Arduino header
#include <defines.h>    // Defines header
#include <debugger.h>   // Debugger Module
#include "utilities.h"  // Utilities Module

// Module specific headers
#include <avr/pgmspace.h>
#include <Wire.h>  // must be incuded here so that Arduino library object file references work
#include <RtcDS3231.h>
#define countof(a) (sizeof(a) / sizeof(a[0]))

class RTCroutines
{
  public:
    // Functions definitions
    RTCroutines(uint32_t * _sleepTime, Debugger *_d);
    ~RTCroutines();
    bool setup();
    String getDateTimeString();

    RtcDS3231 Rtc;
    uint32_t * sleepTime; //How long the boards sleeps between sampling periods
    Debugger * d;



  private:
    int fake_private;
};

#endif
