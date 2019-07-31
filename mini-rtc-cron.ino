#include "Cron.h"
Cron cron;

// Called when a timer hits time
void onAlarm(const String code) {
  Serial.print(" RUN > ");
  Serial.print(code);
  Serial.println();
}

// Called every second
void onTick(const DateTime now) {
  Serial.print("TIME: ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print(" - ");

  Serial.print("TEMP: ");
  Serial.print(cron.getTemp());
  Serial.println("°c");
}

void setup () {
  Serial.begin(9600);
  cron.begin(onAlarm, onTick);
}

void loop () {
  cron.tick();
}
