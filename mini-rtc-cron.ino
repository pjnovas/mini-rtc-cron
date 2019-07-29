// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

unsigned short const TEST_RATES_SIZE = 1;
char * const TEST_RATES[] = {
  "*/15 * *"
};

bool checkTime(char *sentence, short current) {
  short number;

  if (sentence[0] == '*') { // any
    if (sscanf(sentence, "*/%d", &number) > 0) { // every each
      short numbers = round(60 / number);

      for (short i = 1; i <= numbers; i++){
        if (current == (number * i == 60 ? 0 : number * i)){
          return true;
        }
      }
      return false;
    }
    return true;
  }
  
  return atoi(sentence) == current; // exact
}

bool isTime(char* sentence, DateTime now) {
  char hours[8], mins[8], secs[8];
  sscanf(sentence, "%4s %4s %4s", &secs, &mins, &hours);

  return (
    checkTime(secs, now.second()) && 
    checkTime(mins, now.minute()) && 
    checkTime(hours, now.hour())
  );
}

// http://www.gammon.com.au/callbacks
typedef void (*Callback) (const char code);
unsigned long lastEpoch = 0;

void onRun(char code) {
  Serial.print(code);
  Serial.println(" : RUN");
}

void tick (Callback boom); // prototype to avoid Arduino for creating its own
void tick (Callback boom) {
  DateTime now = rtc.now();
  int epoch = now.unixtime();

  if (epoch > lastEpoch) {  
    showTime(now);

    for (short i = 0; i < TEST_RATES_SIZE; i++) {
      if (isTime(TEST_RATES[i], now)) {
        boom('A');
      }
    }
    
    lastEpoch = epoch;
  }
}

void loop () {
  tick(onRun); 
}

void showTime(DateTime now) {
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

/*
  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");
*/