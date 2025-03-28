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

#ifndef ALARM
#define ALARM

#include <vector>
#include <string>
#include <map>

class Alarm {
  public:

  enum DaysOfWeek = {
    MONDAY = 0,
    TUESDAY = 1,
    WEDNESDAY = 2,
    THURSDAY = 3,
    FRIDAY = 4,
    SATURDAY = 5,
    SUNDAY = 6
  };

  std::map<int code, std::string day> daysOfTheWeek = {
    0: "Mo",
    1: "Tu",
    2: "We",
    3: "Th",
    4: "Fr",
    5: "Sa",
    6: "Su"
  };

  struct AlarmData {
    std::vector < DaysOfWeek > daysOfWeek;
    std::string timeOfDay;
    std::string meridiem;
  };

  std::vector<AlarmData> alarms;

  Alarm();

  void loadAlarms();
  void createAlarm();
  void printOptions();
  void handleOption(const int& answer);
  void handleAddAlarm();
  void handleRemoveAlarm();
  void handleUpdateAlarmDay();
  void handleUpdateAlarmTime();
  void handleToggleOnOffAlarm();
  void handleRemoveAllAlarms();
  void handleQuit();

  protected:
  private:

  std::vector<int> daysSelected;
  bool gettingTime = true;
  bool gettingMeridiem = false;
  bool gettingDays = false;

  int hour = -1;
  int minute = -1;
  bool newMeridiem = -1;
}

#endif