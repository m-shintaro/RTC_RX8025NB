//RTC_RX8025NB.cpp
#include "RTC_RX8025NB.h"
#include <Wire.h>
#include <TimeLib.h>

RTC_RX8025NB::RTC_RX8025NB() {
}

bool RTC_RX8025NB::write(const tmElements_t& tm) {
    _year = tmYearToCalendar(tm.Year);
    _month = tm.Month;
    _day = tm.Day;
    _hour = tm.Hour;
    _minute = tm.Minute;
    _second = tm.Second;
    return _begin();
}

tmElements_t RTC_RX8025NB::read() {
    tmElements_t tm;
    if (_read()) {
        tm.Year = CalendarYrToTm(_year);
        tm.Month = _month;
        tm.Day = _day;
        tm.Hour = _hour;
        tm.Minute = _minute;
        tm.Second = _second;
        return tm;
    }
}

void RTC_RX8025NB::setDateTime(int year, int month, int day, int hour, int minute, int second) {
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _second = second;
    _begin();
}

void RTC_RX8025NB::adjustSecond(int adjustment) {
    _second += adjustment;
    _begin();
}

bool RTC_RX8025NB::_begin() {
    byte n;
    Wire.beginTransmission(RTC8052_I2CADDR);
    Wire.write(0xE0);
    Wire.write(RTC8052_CFG_PULSE_ITR_SEC);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(1);

    Wire.beginTransmission(RTC8052_I2CADDR);
    Wire.write(0x00);
    n = _toBCD(_second);
    Wire.write(n);
    n = _toBCD(_minute);
    Wire.write(n);
    n = _toBCD(_hour);
    Wire.write(n);
    Wire.write(0x00);
    n = _toBCD(_day);
    Wire.write(n);
    n = _toBCD(_month);
    Wire.write(n);
    n = _toBCD(_year);
    Wire.write(n);
    Wire.endTransmission();
    delay(1);

    Wire.beginTransmission(RTC8052_I2CADDR);
    Wire.write(0x8E);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(1);

    return true;
}

bool RTC_RX8025NB::_read() {
    byte years, months, days, hours, minutes, seconds;

    Wire.requestFrom(RTC8052_I2CADDR, 8);
    Wire.read();
    seconds = Wire.read();
    minutes = Wire.read();
    hours = Wire.read();

    Wire.read();
    days = Wire.read();
    months = Wire.read();
    years = Wire.read();

    _year = _fromBCD(years) + 2000;
    _month = _fromBCD(months);
    _day = _fromBCD(days);
    _hour = _fromBCD(hours);
    _minute = _fromBCD(minutes);
    _second = _fromBCD(seconds);

    return true;
}

byte RTC_RX8025NB::_toBCD(int i) {
    byte n0, n1;
    n0 = i % 10;
    n1 = (i / 10) % 10;
    return (n1 << 4) | n0;
}

int RTC_RX8025NB::_fromBCD(byte bcd) {
    int i0, i1;
    i0 = bcd & 0x0F;
    i1 = (bcd >> 4) * 10;
    return i0 + i1;
}
