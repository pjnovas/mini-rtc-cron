#include "Cron.h"
Cron cron;

void setup () {
  Serial.begin(9600);
  cron.begin();
}

void onTimer(const String code) {
  Serial.print(" RUN > ");
  Serial.print(code);
  Serial.println();
}

void loop () {
  cron.tick(onTimer); 
}

// 
// void showTime(DateTime now) {
//   Serial.print(now.hour(), DEC);
//   Serial.print(':');
//   Serial.print(now.minute(), DEC);
//   Serial.print(':');
//   Serial.print(now.second(), DEC);
//   Serial.println();
// }
// 
// /*
//   Serial.print("Temperature: ");
//   Serial.print(rtc.getTemperature());
//   Serial.println(" C");
// */