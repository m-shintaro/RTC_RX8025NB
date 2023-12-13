// RTC_RX8025NB.h
#ifndef _RTC_RX8025NB_H1
#define _RTC_RX8025NB_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <TimeLib.h>

#define RTC8052_I2CADDR 0x32
#define RTC8052_CFG_PULSE_ITR_SEC 0b00100011

class RTC_RX8025NB {
public:
    RTC_RX8025NB();
    bool write(const tmElements_t& tm);
    tmElements_t read();

    // Convenience functions
    int getYear() const { return _year; }
    int getMonth() const { return _month; }
    int getDay() const { return _day; }
    int getHour() const { return _hour; }
    int getMinute() const { return _minute; }
    int getSecond() const { return _second; }

    void setDateTime(int year, int month, int day, int hour, int minute, int second);
    void adjustSecond(int adjustment);

private:
    bool _begin();
    bool _read();
    byte _toBCD(int i);
    int _fromBCD(byte bcd);

    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _second;
    bool _configured;
};

#endif
