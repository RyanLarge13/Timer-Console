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

// Initialize all AlarmData variables upon creation
AlarmData::AlarmData(
  const std::vector < Alarm::DaysOfWeek>& daysOfWeek,
  const AlarmData::AlarmTime& alarmTime,
  const bool& on,
  const std::string& meridiem,
  const AlarmData::Vibrate& vibrate,
  const std::string& message
):
daysOfWeek(daysOfWeek),
alarmTime(alarmTime),
on(on),
meridiem(meridiem),
vibrate(vibrate),
message(message) {}

void AlarmData::changeTime(const AlarmData::AlarmTime& newTime) {
  this->alarmTime = newTime;
}

void AlarmData::toggleOnOff() {
  this->on = !this->on;
}

// Plus or minus hours, for program purpose only. Not display purpose
void AlarmData::toggleMeridiem() {
  if (this->meridiem == "AM") {
    this->meridiem = "PM";
    this->alarmTime.hour += 12;
  } else {
    this->meridiem = "AM";
    this->alarmTime.hour -= 12;
  }
}

void AlarmData::print() {
  using namespace Write;

  // Print alarm with colors
  if (this->on) {
    // Print days of week where alarm is active
    std::cout << c(Colors::BLUE) << this->alarmTime.hour << c(Colors::ENDCOLOR) << " " << this->meridiem << "\n";
  } else {
    // Print days of week where alarm is not active
    std::cout << c(Colors::RED) << this->alarmTime.hour << c(Colors::ENDCOLOR) << " " << this->meridiem << "\n";
  }

  for (const auto& [key, day]: Alarm::daysOfWeek) {
    bool isOnToday = false;

    for (int& weekday: this->daysOfWeek) {
      if (weekday == key) {
        isOnToday = true;
      }
    }

    // If the alarm is on today print the day string with a blue color
    std::cout << (isOnToday ? c(Colors::BLUE) : c(Colors::RED)) << day <<
    c(Colors::ENDCOLOR) << " ";
  }

  // Flush
  std::cout << "\n";
}