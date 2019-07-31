#ifndef Cron_h
#define Cron_h

#include "RTClib.h"
#include "Arduino.h"

typedef void (*cron_callback) (const String code);

class Cron
{
  public:
    Cron();
    void begin();
    void tick(cron_callback onRun);

  private:
    RTC_DS3231 rtc;
    unsigned short _timerSize;
    char * _timers;
    unsigned long lastEpoch = 0;
    bool checkTime(const char *sentence, const short current);
    String isTime(const char* sentence, DateTime now);
};

#endif

