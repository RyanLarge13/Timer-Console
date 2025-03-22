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

int takeInput() {
  int selection;

  std::cout << "Selection: ";
  std::cin >> selection;

  if (selection < 1 || selection > 4) {
    // Print correction
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
void handleTimer() {
  Timer timer;
  reset();
  takeInput();
}
// Functionality Methods - - - - - - - - -

void branchApp(const int& selection) {
  // Flip through the various cases comparing selection to local ENUM
  switch (selection) {
    case AppFunction::ALARM:
    {
      // Handle alarm
      reset();
    }
    break;
    case AppFunction::STOPWATCH:
    {
      // Handle stopwatch
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
  // Print menu and provide options
  printMenu();

  // Query selection
  int selection = takeInput();

  // Take selection and branch off to handle each functionality
  branchApp(selection);

  return 0;
}