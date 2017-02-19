#include "debugger.h"


Debugger::Debugger()
{

}
#if DEBUG

void Debugger::sleepAlert(unsigned long int _sleepTime) {
  print(F("Sleeping for: "));
  print((String)_sleepTime);
  println(F(" ms"));
  delay(100);
}
void Debugger::startSampling() {
  println(F("------> Sampling..."));
}

void Debugger::restarted() {
  println(F("Restarted"));
}

void Debugger::sleepTime(unsigned long int _sleepTime) {
  print(F("sleepTime read from config.txt on SD: "));
  println((String)_sleepTime);
}

void Debugger::SDinitialization(bool init) {
  if (init) println(F("SD initialization successful."));
  else println(F("SD initialization not successful."));

}
bool Debugger::OpenFile(bool fileIsOpen, String fileName) {
  if (!fileIsOpen) {
    println("###############################################################");
    println(" ");
    print("                       Could not open ");
    println(fileName);
    println(" ");
    println("###############################################################");
  }
  return fileIsOpen;
}

void Debugger::writeToFile(String fileName){
  print("------> Writing to SD [file:");
  print(fileName);
  println("]");
}

void Debugger::print(String sentence){
  if (DEBUG)  Serial.print(sentence);
}

void Debugger::println(String sentence){
  if (DEBUG)  Serial.println(sentence);
}

// If DEBUG is set to 0 then simply define empty functions
#else
void Debugger::sleepAlert(unsigned long int _sleepTime){}
void Debugger::startSampling(){}
void Debugger::restarted(){}
void Debugger::sleepTime(unsigned long int _sleepTime){}
void Debugger::SDinitialization(bool init){}
void Debugger::sleepTime(){}
bool Debugger::OpenFile(bool fileIsOpen, String fileName){
  return fileIsOpen;
}
void Debugger::writeToFile(const char * fileName){}
void Debugger::print(String sentence){}
void Debugger::println(String sentence){}
#endif
