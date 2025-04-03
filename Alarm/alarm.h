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
#include "./alarmData.h"

/**
 * @brief Alarm.class handles all high level alarm tasks and managment including adding, removing, providing interface for updating and defining crucial data for alarm functionality
 */
class Alarm {
  public:

  enum DaysOfWeek = {
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6,
    SUNDAY = 7
  };

  std::map < int code,
  std::string day > daysOfTheWeek = {
    1: "Mo",
    2: "Tu",
    3: "We",
    4: "Th",
    5: "Fr",
    6: "Sa",
    7: "Su"
  };

  std::vector < AlarmData > alarms;

  Alarm();

  bool includes(const int& dayCode, const std::vector < int>& daysSelected);
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
  void setAlarmMeridiem(AlarmData& alarmToUpdate);
  void setAlarmTime(AlarmData& alarmToUpdate);
  void setAlarmDays(AlarmData& alarmToUpdate);

  protected:
  private:
  
  AlarmData getAlarm();
}

#endif