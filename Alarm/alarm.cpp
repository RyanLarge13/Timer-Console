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

#include "./alarm.h"
#include "./alarmData.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "../Config/files.h"
#include "../Console/write.h"
#include "../Console/read.h"

std::atomic < bool > running(true);

Alarm::Alarm() {
  // Immediately load alarms from config file and place them in memory
  loadAlarms();
}

void Alarm::loadAlarms() {
  alarms = Files::getAlarms();

  // Print and prompt for input right away
  printAlarms();
  printOptions();
}


void Alarm::printAlarms() {
  for (AlarmData alarm: alarms) {
    alarm.print();
  }
}


void Alarm::printOptions() {
  int answer;

  std::cout <<
  "1. Add Alarm" << "\n" <<
  "2. Remove Alarm" << "\n" <<
  "3. Update Alarm Time" << "\n" <<
  "4. Update Alarm Days"<< "\n" <<
  "5. Toggle on/off" << "\n" <<
  "6. Remove All Alarms" << "\n" <<
  "7. Main Menu" << "\n" << "\n";

  Read::setCanonicalMode(true);
  read(STDIN_FILENO, &answer, 4);
  Read::setCanonicalMode(false);

  handleOption(answer);
}


void Alarm::handleOption(const int& answer) {
  Write::clearAllConsole();

  // Switch statement to handle large amount of options
  switch (answer) {
    case 1: {
      handleAddAlarm();
    }
    break;
    case 2: {
      handleRemoveAlarm();
    }
    break;
    case 3: {
      handleUpdateAlarmTime();
    }
    break;
    case 4: {
      handleUpdateAlarmDay();
    }
    break;
    case 5: {
      handleToggleOnOffAlarm();
    }
    break;
    case 6: {
      handleRemoveAllAlarms();
    }
    break;
    case 7: {
      handleQuit();
    }
    break;
    default: {
      std::cout << "Please provide a valid option. 1 - 7" << "\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));

      printOptions();
      printAlarms();
    }
    break;
  }
}


void Alarm::setAlarmTime(AlarmData& alarmToUpdate) {
  // Prompt user, for minutes and hours. Then set those values as the alarm instance alarm.alarmTime from params
  std::cout << "What would you like your new time to be? \nHour: ";

  int newHour;
  int newMinute;

  if (alarmToUpdate.alarmTime.hour == -1) {
    Read::setCanonicalMode(true);
    read(STDIN_FILENO, &newHour, 1);

    if (newHour > 12 || newHour < 1) {
      std::cout << "Please select a valid hour 0 - 12" << "\n";
      return setAlarmTime(alarmToUpdate);
    }

    alarmToUpdate.alarmTime.hour = newHour;
  }

  if (alarmToUpdate.alarmTime.minute == -1) {
    std::cout << "Minute: ";
    read(STDIN_FILENO, &newMinute, 1);

    if (newMinute > 59) {
      std::cout << "Please select a valid time. Minutes 0 - 59" << "\n";
      return setAlarmTime(alarmToUpdate);
    }

    alarmToUpdate.alarmTime.minute = newMinute;
  }

  Read::setCanonicalMode(false);
}



void Alarm::setAlarmMeridiem(AlarmData& alarmToUpdate) {
  // Prompt and set meridiem of alarm
  Write::clearAllConsole();

  std::string newMeridiem;

  std::cout << "AM or PM? ";
  std::cin >> newMeridiem;

  if (newMeridiem != "AM" && newMeridiem != "PM") {
    return setAlarmMeridiem(alarmToUpdate);
  }

  if (newMeridiem == "PM") {
    alarmToUpdate.alarmTime.hour += 12;
  }

  alarmToUpdate.meridiem = newMeridiem;
}



bool Alarm::includes(const int& dayCode, const std::vector < int>& daysSelected) {
  // Specifically checks for days existing within the days vector of an alarm being created
  bool isPresent = false;

  for (int i = 0; i < daysSelected.size(); i++) {
    if (daysSelected[i] == dayCode) {
      isPresent = true;
    }
  }

  return isPresent;
}



void Alarm::setAlarmDays(AlarmData& alarmToUpdate) {
  bool gettingDays = true;
  std::vector < int > daysSelected = {};

  while (gettingDays) {
    Write::clearAllConsole();
    int index = 1;

    // Print days selected with color
    for (const auto& [code, day]: Alarm::DaysOfWeek) {
      if (includes(code, daysSelected)) {
        std::cout << index << Write::c(Write::Colors::YELLOW) << day <<
        Write::c(Write::Colors::ENDCOLOR) << " ";
      } else {
        std::cout << index << day << " ";
      }
      index++;
    }

    std::cout << "\n" << "\n";
    std::cout << "0 to finish, 9 to quit" << "\n";
    std::cout << "Select days by number:";

    int answer;
    Read::setCanonicalMode(true);
    read(STDIN_FILENO, &answer, 1);
    Read::setCanonicalMode(false);

    if (answer == 9) {
      gettingDays = false;
    }

    daysSelected.push_back(answer);
  }

  alarmToUpdate.daysOfWeek = daysSelected;
}



void Alarm::handleUpdateAlarmTime() {
  AlarmData selectedAlarm = getAlarm();

  if (!selectedAlarm) {
    std::cout << "Please select an alarm that exists" << "\n";

    handleUpdateAlarmTime();
    return;
  }

  setAlarmTime(selectedAlarm);
  setAlarmMeridiem(selectedAlarm);

  std::cout << "Your alarm is now updated to go off at " << selectedAlarm.printTime() << "\n";
}



void Alarm::handleRemoveAlarm() {
  int alarmIndex;

  std::cout << "Which alarm would you like to remove? ";

  Read::setCanonicalMode(true);
  read(STDIN_FILENO, &alarmIndex, 1);
  Read::setCanonicalMode(false);

  if (alarmIndex > alarms.size() || alarmIndex < 1) {
    std::cout << "That was an invalid option. Please try again" << "\n";

    // Recursively call if failed for new prompt
    return handleRemoveAlarm();
  }

  alarms.erase(alarms.begin() + alarmIndex - 1);
}



void Alarm::handleAddAlarm() {
  int daysSelectedDefault = 1;

  // Build a default alarm that will be updated throughout the user input process
  AlarmData newAlarm = AlarmData(daysSelectedDefault, AlarmData::AlarmTime(1, 0), true, "AM", AlarmData::Vibrate(true, 1.0));

  setAlarmTime(newAlarm);
  setAlarmMeridiem(newAlarm);
  setAlarmDays(newAlarm);

  alarms.push_back(newAlarm);
}



void Alarm::handleToggleOnOffAlarm() {
  AlarmData selectedAlarm = getAlarm();

  // if (!selectedAlarm) {
  //   std::cout << "Please make a valid selection on an existing alarm" << "\n";

  //   // Recursively call upon to re-prompt the user
  //   return handleToggleOnOffAlarm();
  // }

  selectedAlarm.toggleOnOff();
}



AlarmData Alarm::getAlarm() {
  // Select provided alarms from alarms vector by indexing and user input
  int selectedAlarmIndex;

  std::cout << "which alarm would you like to change the time on?" << "\n";

  Read::setCanonicalMode(true);
  read(STDIN_FILENO, &selectedAlarmIndex, 1);
  Read::setCanonicalMode(false);

  if (selectedAlarmIndex > alarms.size() || selectedAlarmIndex < 1) {
    std::cout << "Please select an alarm that exists" << "\n";

    // Recursively prompt user for selecting a valid alarm index
    return getAlarm();
  }

  AlarmData selectedAlarm = alarms[selectedAlarmIndex - 1];

  return selectedAlarm;
}



void Alarm::handleRemoveAllAlarms() {
  // Clear the alarms in memory
  alarms = {};

  /*
  TODO
    1. Remove all alarms from storage
  */
}



void Alarm::handleQuit() {
  return;
}