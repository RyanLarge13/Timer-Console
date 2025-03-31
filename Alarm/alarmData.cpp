/*
MIT License

Copyright (c) 2025 Ryan Large

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "./alarmData.h"
#include "../Console/write.h"
#include <vector>
#include <iostream>

AlarmData::AlarmData(
  const std::vector < Alarm::DaysOfWeek>& daysOfWeek,
  const std::string& alarmTime,
  const bool& on,
  const std::string& meridiem,
  const AlarmData::Vibrate& vibrate
):
daysOfWeek(daysOfWeek),
alarmTime(alarmTime),
on(on),
meridiem(meridiem),
vibrate(vibrate) {}

void AlarmData::changeTime(const std::string& newTime) {}
void AlarmData::toggleOnOff() {}
void AlarmData::toggleMeridiem() {}

void AlarmData::print() {
  using namespace Write;

  // Print alarm with colors
  if (this->on) {
    std::cout << c(Colors::BLUE) << this->alarmTime c(Colors::ENDCOLOR) << " " << this->meridiem << "\n";
    // Print days of week where alarm is active
  } else {
    std::cout << c(Colors::RED) << this->alarmTime c(Colors::ENDCOLOR) << " " << this->meridiem << "\n";
    // Print days of week where alarm is not active
  }

  for ([int& key, std::string& day]: Alarm::daysOfWeek) {
    bool isOnToday = false;

    for (int& weekday: this->daysOfWeek) {
      if (weekday == key) {
        isOnToday = true;
      }
    }

    std::cout << isOnToday ? c(Colors::BLUE): c(Colors::RED) << day <<
    c(Colors::ENDCOLOR) << " ";
  }

  // Flush
  std::cout << "\n";
}