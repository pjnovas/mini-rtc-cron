// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600);
  delay(3000); // wait for console opening

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

char* const TEST_RATES[] = {
  "*/15 * *", // 0, 15, 30 & 45 seconds
  // "0 */2 *", // every two minutes (it will start on first 0 secs and then every two)
  // "10 33 22", // specific time 22:33:10 hs
};

// * : Any 
// */[0-59]: Every but each: */15 would be at 0, 15, 30 & 45
// [0-59]: Exact
bool checkTime(char* sentence, short current) {
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
  bool isIt = false;

  char hours[8];
  char mins[8];
  char secs[8];

  sscanf(sentence, "%4s %4s %4s", &secs, &mins, &hours);

  return (
    checkTime(secs, now.second()) && 
    checkTime(mins, now.minute()) && 
    checkTime(hours, now.hour())
  );
}

void loop () {
  DateTime now = rtc.now();
  showTime(now);

  for (size_t i = 0; i <= sizeof(&TEST_RATES); i++) {
    if (isTime(TEST_RATES[i], now)) {
      Serial.println("RUN!");
    }
  }

  delay(1000);
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
void showTime() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days and 30 seconds into the future
  DateTime future (now + TimeSpan(7,12,30,6));

  Serial.print(" now + 7d + 30s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();

  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  Serial.println();
  delay(3000);
}
*/