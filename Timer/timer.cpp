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

#include "./timer.h"
#include "./timerData.h"
#include "../Config/files.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

std::vector < TimerData > timeData = {};
bool looping = false;

// To save TimerData last time use duration_cast <millis> since last epoch

Timer::Timer() {
  system("clear");
  loadTimers();
  // Display all timers to the console
}

void Timer::loadTimers() {
  Files timerFileHandler;

  timeData = timerFileHandler.getTimers();

  if (timeData.size() < 1) {
    printTimerOptions();
    return;
  }

  looping = true;

  while(looping) {
    printTimers();
    printTimerOptions();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "\033[2J\033[1;1H";
  }
}

void Timer::printTimers() {
  for (TimerData& t: timeData) {
    if (!t.isOn) {
      t.print();
    } else {
      t.printUpdate();
    }
  }
}

void Timer::printTimerOptions() {
  std::cout << "'a': Add Timer" << "\n";
  std::cout << "'rm': Remove Timer" << "\n";
  std::cout << "'d': Delete All Timers" << "\n";
  std::cout << "'o': Reset All Timers" << "\n";
  std::cout << "'q': Exit Timer" << "\n";
}