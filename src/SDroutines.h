#ifndef SDroutines_h
#define SDroutines_h

#include "Arduino.h"    // Arduino header
#include <defines.h>    // Defines header
#include <debugger.h>   // Debugger Module
#include "utilities.h"  // Utilities Module

// Module specific headers
#include <SPI.h>
#include <SD.h>

class SDroutines
{
  public:
    // Functions definitions
    SDroutines(uint32_t * _sleepTime, uint16_t * _smpLength, Debugger *_d, int16_t (&_ax)[MAX_N_SAMPLES], int16_t (&_ay)[MAX_N_SAMPLES], int16_t (&_az)[MAX_N_SAMPLES]);
    ~SDroutines();
    bool setup();
    void close();
    void readSettings();
    void write();
    long getLastFile(File dir);
    void writeFloatToByte(File &dir, float &data);
    void writeIntToByte(File &dir, int16_t &data);
    void writeDhtError(File &dir, int &error);
    void writeAccError();

    File myFile;          //class for writing/reading to SD card
    uint32_t * sleepTime; //How long the boards sleeps between sampling periods
    uint16_t * smpLength;    //how many samples are collected in each sampling period

    Debugger * d;

    int16_t (&ax)[MAX_N_SAMPLES];         //variables for storing accelerometer values before writing to SD
    int16_t (&ay)[MAX_N_SAMPLES];
    int16_t (&az)[MAX_N_SAMPLES];

  private:
    int fake_private;
};

#endif
