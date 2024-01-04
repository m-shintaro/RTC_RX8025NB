# RTC_RX8025NB
This is the RTC library for Arduino and microcontroller for EPSON RX-8025NB.

## Main functions
- `setDateTime` method to set the RTC time
- read`read` method to read the RTC time
- The `adjustSecond` method to adjust seconds

## Usage
### setDateTime
```c++
#include <TimeLib.h>
#include <Wire.h>
#include <RTC_RX8025NB.h>

RTC_RX8025NB rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.setDateTime(2023, 12, 13, 12, 0, 0); // year, month, day, hour, minute, second
}
```

### Reading time
```c++
void loop() {
  tmElements_t tm = rtc.read();
  char s[20];
  sprintf(s, "%d/%d/%d %d:%d:%d", tmYearToCalendar(tm.Year), tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second);
  Serial.println(s);
  delay(1000);
}
```

## License
This library is released under the MIT License. See [LICENSE.md](LICENSE.md) for details.

# RTC_RX8025NB
(Japanese Version)  
このライブラリは、EPSON RX-8025NB用のArduinoとマイクロコントローラ用のRTCライブラリです。

## 主な機能
- RTCの時間を設定する`setDateTime`メソッド
- RTCの時間を読み取る`read`メソッド
- 秒を調整する`adjustSecond`メソッド

## 使用方法
### 時間の設定
```c++
#include <TimeLib.h>
#include <Wire.h>
#include <RTC_RX8025NB.h>

RTC_RX8025NB rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.setDateTime(2023, 12, 13, 12, 0, 0); // 年,月,日,時間,分,秒
}
```

### 時間の読み取り
```c++
void loop() {
  tmElements_t tm = rtc.read();
  char s[20];
  sprintf(s, "%d/%d/%d %d:%d:%d", tmYearToCalendar(tm.Year), tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second);
  Serial.println(s);
  delay(1000);
}
```

## ライセンス
このライブラリはMITライセンスの下で公開されています。詳細は[LICENSE.md](LICENSE.md)を参照してください。
