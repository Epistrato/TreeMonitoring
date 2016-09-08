#ifndef Debugger_h
#define Debugger_h


#include "Arduino.h"  // Arduino header
#include "defines.h"  // defines header

// Module specific headers




class Debugger
{
  public:

    Debugger();
    // Methods definitions
    //Debugger(void);

    void debug_sleepAlert(unsigned long int _sleepTime);
    void debug_startSampling();
    void debug_restarted();
    void debug_sleepTime(unsigned long int _sleepTime);
    void debug_SDinitialization(bool init);
    void debug_sleepTime();
    bool debug_OpenFile(bool fileIsOpen, String fileName);
    void debug_writeToFile(const char * fileName);
    void debug_print(String sentence);

  public:

};

#endif
