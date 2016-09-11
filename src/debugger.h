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

    void sleepAlert(unsigned long int _sleepTime);
    void startSampling();
    void restarted();
    void sleepTime(unsigned long int _sleepTime);
    void SDinitialization(bool init);
    void sleepTime();
    bool OpenFile(bool fileIsOpen, String fileName);
    void writeToFile(const char * fileName);
    void print(String sentence);
    void println(String sentence);

  public:

};

#endif
