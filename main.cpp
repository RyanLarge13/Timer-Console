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

#include <iostream>
#include "./Timer/timer.h"
#include "./Alarm/alarm.h"

/**
* @brief predefined functions
* @params selection is queried from the user to choose which functionality they want. Alarm, timer, stopwatch...
* @see branchApp()
*/
void branchApp(const int& selection);

enum AppFunction {
  ALARM = 1,
  STOPWATCH = 2,
  TIMER = 3,
  QUIT = 4
};

void printMenu() {
  std::cout << "1. Alarm" << "\n";
  std::cout << "2. Stopwatch" << "\n";
  std::cout << "3. Timer" << "\n";
  std::cout << "4. Quit" << "\n";
}


/**
* @brief Instruct user to select a valid functionality via integer to map to local ENUM @see AppFunction eg: alarm, timer, stopwatch
*/
int takeInput() {
  int selection;

  std::cout << "Selection: ";
  std::cin >> selection;

  if (selection < 1 || selection > 4) {
    system("clear");
    std::cout << "Please select 1 through 3" << "\n" << "\n";
    printMenu();
    return takeInput();
  }

  return selection;
}

void reset() {
  system("clear");
  printMenu();
}

// Functionality Methods - - - - - - - - -
void handleAlarm() {
  Alarm alarm;
}

void handleTimer() {
  Timer timer;
}
// Functionality Methods - - - - - - - - -

/**
* @brief Take user selection and branch it to create the correct class instance
*/
void branchApp(const int& selection) {
  switch (selection) {
    case AppFunction::ALARM:
    {
      handleAlarm();
    }
    break;
    case AppFunction::STOPWATCH:
    {
      reset();
    }
    break;
    case AppFunction::TIMER:
    {
      handleTimer();
    }
    break;
    case AppFunction::QUIT:
    {
      system("clear");
      return;
    }
    break;
    default: {
      reset();
    }
  }
}

int main() {
  printMenu();

  int selection = takeInput();
  branchApp(selection);

  return 0;
}