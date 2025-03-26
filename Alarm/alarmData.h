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

#ifndef ALARM_DATA_H
#define ALARM_DATA_H

#include "./alarm.h"
#include <vector>

class AlarmData {
  public:

  struct Vibrate {
    bool on;
    double intensity;

    Vibrate(const bool& on, const double& intensity): on(on), intensity(intensity) {}
  };

  AlarmData(
    const std::vector < Alarm::DaysOfWeek>& daysOfWeek, 
    const std::string& alarmTime, 
    const bool& on, 
    const std::string meridiem, const bool& vibrate
  );

void AlarmData::changeTime(const std::string& newTime);
void AlarmData::toggleOnOff();
void AlarmData::toggleMeridiem();

  protected:
  private:
};

#endif