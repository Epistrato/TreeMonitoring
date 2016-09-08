#include "debugger.h"


Debugger::Debugger()
{

}

void Debugger::debug_sleepAlert(unsigned long int _sleepTime) {
  if (DEBUG) {
    Serial.print(F("Sleeping for (ms): "));
    Serial.println(_sleepTime);
    delay(100);
  }
}

void Debugger::debug_startSampling() {
  if (DEBUG) {
    Serial.println(F("------> Sampling..."));
  }
}

void Debugger::debug_restarted() {
  if (DEBUG) {
    Serial.println(F("Restarted"));
  }
}

void Debugger::debug_sleepTime(unsigned long int _sleepTime) {
  if (DEBUG) {
    Serial.print(F("sleepTime read from config.txt on SD: "));
    Serial.println(_sleepTime);
  }
}

void Debugger::debug_SDinitialization(bool init) {
  if (DEBUG) {
    if (init) Serial.println(F("SD initialization successful"));
    else Serial.println(F("SD initialization not successful"));
  }
}
bool Debugger::debug_OpenFile(bool fileIsOpen, String fileName) {

  if (!fileIsOpen && DEBUG) {
    Serial.print("Could not open ");
    Serial.println(fileName);
  }
  return fileIsOpen;
}
void Debugger::debug_writeToFile(const char * fileName){
if (DEBUG) {
  Serial.print("------> Writing to SD [file:");
  Serial.print(fileName);
  Serial.println("]");
}
}

void Debugger::debug_print(String sentence){
  if (DEBUG)  Serial.print(sentence);
}
