#include <TimeLib.h>
#include <Wire.h>
#include <RTC_RX8025NB.h>

RX8025_RTC rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.setDateTime(2023, 12, 13, 12, 0, 0); // 年,月,日,時間,分,秒
}

void loop() {
  tmElements_t tm = rtc.read();
  char s[20];
  sprintf(s, "%d/%d/%d %d:%d:%d", tmYearToCalendar(tm.Year), tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second);
  Serial.println(s);
  delay(1000);
}
