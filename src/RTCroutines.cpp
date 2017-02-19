#include "RTCroutines.h"

RTCroutines::RTCroutines(uint32_t * _sleepTime, Debugger *_d)
{
  sleepTime = _sleepTime;
  d = _d;
}
RTCroutines::~RTCroutines()
{}


/*---------->setup
  Sets up the rtc clock module
*/
bool RTCroutines::setup() {
  bool rtcTest = false;
  d->print(F("Initializing rtc clock..."));
  // d->print("compiled time: ");
  // d->print(__DATE__);
  // d->println(__TIME__);
  //--------RTC SETUP ------------
  Rtc.Begin();
  // Get compiled time
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  // Check if valid, set to compiled otherwise
  if (!Rtc.IsDateTimeValid()) {
    Rtc.SetDateTime(compiled);
  }
  // Check if Rtc is running, set running otherwise
  if (!Rtc.GetIsRunning())
  {
      d->print("RTC was not actively running, starting now...");
      Rtc.SetIsRunning(true);
  }
  // Get current Date and Time
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
      d->print("RTC time its older than compile time, updating with compiled datetime... )");
      Rtc.SetDateTime(compiled);
  }
  // Reset features which are not required
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  rtcTest = true;
  d->print(rtcTest ? " Successful.\n" : " Failed.\n");
  return rtcTest;
}


/*---------->getDateTimeString
  Get string with date and time
*/
String RTCroutines::getDateTimeString() {
  String dateTimeString;
  char datestring[20];
  RtcDateTime dt = Rtc.GetDateTime();
  snprintf_P(datestring,
          countof(datestring),
          PSTR("%02u%02u%02u%02u%02u%02u"),
          dt.Year(),
          dt.Month(),
          dt.Day(),
          dt.Hour(),
          dt.Minute(),
          dt.Second() );
  dateTimeString = datestring;
  return dateTimeString;
}
