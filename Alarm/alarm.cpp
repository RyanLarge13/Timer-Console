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
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../Config/files.h"
#include "../Consle/write.h"
#include "../Consle/read.h"

Alarm::Alarm() {
  loadAlarms();
}

void Alarm::loadAlarms() {
  alarms = Files::getAlarms();

  printOptions();
  printAlarms();
}

void Alarm::printAlarms() {
  for (AlarmData alarm : alarms) {
    alarm.print();
  }
}

void Alarm::printOptions() {
  Write::clearAllConsole();

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
    read(STDIN_FILENO, &answer, 1);
    Read::setCanonicalMode(false);

    handleOption(answer);
}

void Alarm::handleOption(const int& answer) {
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

void Timer::handleAddAlarm() {
  Write::clearAllConsole();

  bool gettingTime = true;
  bool gettingMeridiem = false;
  bool gettingDays = false;

  int hour = -1;
  int minute = -1;
  bool newMeridiem = -1;

  std::vector<int> daysSelected;

  while (gettingTime) {

  }

  while (gettingMeridiem) {

  }

  while (gettingDays) {
    
  }
}