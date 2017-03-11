#pragma GCC diagnostic ignored "-Wreorder"

/**------> treemonitor.1

Author: Gianni Massi
Year: 2016
For: Arduino 1284p + SD card module + GY521 accelerometer + DHT22/DHT21 + DS3231.

This sketch samples at regular intervals (1kHz) an accelerometer. After is has collected
a predetermined number of samples described by the smpLength variable, it stores them on
the SD card connected.
*/

#include "Arduino.h"
#include <Sleep_n0m1.h>

#include <defines.h>
#include <RTCroutines.h>
#include <SDroutines.h>
#include <ACCroutines.h>
#include "DHTroutines.h"
#include "debugger.h"
#include "utilities.h"


bool control = 0;
bool sdWorks = false;
bool accWorks = false;
bool dhtWorks = false;
bool rtcWorks = false;

uint32_t lastReading;    //keep track of the timing of the last data collection
uint32_t lastBatteryCheck;
uint32_t sleepTime = DEFAULT_SLEEPTIME; //How long the boards sleeps between sampling periods
uint16_t smpLength = DEFAULT_N_SAMPLES;    //how many samples are collected in each sampling period

uint16_t counter = 0;          //keeps track of how many times the accelerometer has been sampled

// Allocate space for data collected at each sampling.
// Pointers to the space in memory allocated will be passed to instances
// of classes of each sensor for storing data.
int16_t ax[MAX_N_SAMPLES];
int16_t ay[MAX_N_SAMPLES];
int16_t az[MAX_N_SAMPLES];

float temperature;
float humidity;

Sleep sleep;

Debugger d;
RTCroutines rtc(&sleepTime, &d);
SDroutines sd(&sleepTime, &smpLength, &d,  ax, ay, az);
Accelerometer acc(&d, ax, ay, az);
DHTsensor dht22(&temperature, &humidity);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(SD_PIN, OUTPUT);
  pinMode(NPN_PIN, OUTPUT);

  digitalWrite(NPN_PIN, HIGH);
  delay(ACC_STARTUPTIME);

  if (DEBUG)  Serial.begin(DEFAULT_BAUDRATE);

  d.restarted();

  rtcWorks = rtc.setup();
  sdWorks = sd.setup();      //initialize SD card module
  accWorks = acc.setup();              //initialize accelerometer
  dhtWorks = dht22.setup();

  if (sdWorks && accWorks){
    d.startSampling();
  }else{
    d.print("Hardware fault. Testing hardware again in ");
    d.print(String(sleepTime*2));
    d.println(" s.");
  }
}


/* -------------------------> Main Loop
*/

void loop()
{
  if (sdWorks && accWorks) {
    if (micros () - lastReading >= 4000) {
      lastReading = micros();
      acc.sample(counter);
      counter++;
    }

    //gather 10 values more than needed so that the first 10 can be discarded
    if (counter >= smpLength + 10) {
      sd.logData(rtc.getDateTimeString());
      sd.close();
      flashLed(1);
      counter = 0;

      digitalWrite(NPN_PIN, LOW);
      d.sleepAlert(sleepTime);
      sleep.pwrDownMode(); //set sleep mode
      sleep.sleepDelay(sleepTime); //sleep for: sleepTime
      digitalWrite(NPN_PIN, HIGH);
      delay(ACC_STARTUPTIME);
      d.println("Woke up. Testing hardware...");
      accWorks = acc.setup();              //initialize accelerometer
      sdWorks = sd.setup();
      dhtWorks = dht22.setup();
      d.startSampling();
    }
  }
  else {
    if (!accWorks && sdWorks){
      sd.writeAccError(rtc.getDateTimeString());
    }
    else if(!sdWorks){
      digitalWrite(LED_PIN, HIGH);
    }
    digitalWrite(NPN_PIN, LOW);
    sd.close();
    d.sleepAlert(sleepTime);
    sleep.pwrDownMode();
    sleep.sleepDelay(sleepTime);
    digitalWrite(NPN_PIN, HIGH);
    d.println("Woke up. Testing hardware...");
    delay(ACC_STARTUPTIME);
    accWorks = acc.setup();              //initialize accelerometer
    sdWorks = sd.setup();
    dhtWorks = dht22.setup();
  }
}
