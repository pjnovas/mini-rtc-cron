# mini-rtc-cron

[WIP]  

Just a mini CRON lib for Arduino using an RTC (RealTimeClock).  

Only accept the "time" part of a cron expression: `"* * *"` (seconds, minutes and hours).  

### Examples 

* `*/15 * *` Run at 0, 15, 30 & 45 seconds of every minute of every hour.
* `0 */2 *` Run every two minutes (but it will start on first 0 seconds *and then* every two)
* `10 33 22` Run on the specific time 22:33:10 hs (every day)

