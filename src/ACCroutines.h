#ifndef ACCroutines_h
#define ACCroutines_h

#include "Arduino.h"  // Arduino header
#include <defines.h>  // defines header
#include <debugger.h>
//#include "DEBUGroutines.h" // Debug functions

// Module specific headers
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

class Accelerometer
{
  public:
    Accelerometer(Debugger *_d, int16_t (&_ax)[MAX_N_SAMPLES], int16_t (&_ay)[MAX_N_SAMPLES], int16_t (&_az)[MAX_N_SAMPLES]);
    //~Accelerometer();

    bool setup();
    void sample(int i);

    Debugger * d;           // Debugger class
    MPU6050 accelerometer;  //class for reading the accelerometer values

    // Pointers to arrays used to store accelerometer data (defined in main.cpp)
    int16_t (&ax)[MAX_N_SAMPLES];         //variables for storing accelerometer values before writing to SD
    int16_t (&ay)[MAX_N_SAMPLES];
    int16_t (&az)[MAX_N_SAMPLES];

  private:
};

#endif
