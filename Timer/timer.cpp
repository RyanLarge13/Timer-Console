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
#include "../Console/write.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>

std::vector < TimerData > timeData = {};
std::atomic < bool > running(true);

// To save TimerData last time use duration_cast <millis> since last epoch

Timer::Timer() {
  system("clear");

  // Display all timers options and listen for input in the console
  std::thread listen(&Timer::listenForInput, this);
  std::thread timerLoader(&Timer::loadTimers, this);

  listen.join();
  timerLoader.join();
}

void Timer::loadTimers() {
  Files timerFileHandler;

  timeData = timerFileHandler.getTimers();

  while(running) {
    printTimers();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void Timer::printTimers() {
  // Clear the section below the Timer options already printed
  Write::clearSection(1, 8, Write::myTerminalSize.width, Write::myTerminalSize.height - 8);

  for (TimerData& t: timeData) {
    if (!t.isOn) {
      t.print(8);
    } else {
      t.printUpdate(8);
    }
  }
}

void Timer::listenForInput() {
  std::string optionTxt =
  "'a': Add Timer\n"
  "'r': Remove Timer\n"
  "'d': Delete All Timers\n"
  "'o': Reset All Timers\n"
  "'q': Exit Timer\n"
  "\n Option: ";

  Write::clearSection(1, 1, Write::myTerminalSize.width, 6);
  Write::printInSection(1, 1, optionTxt);

  std::string answer;

  std::cin >> answer;
  std::cout << answer << "\n";

  if (answer.length() == 1) {
    handleCases(answer[0]);
  } else {
    std::cout << "Please input a valid option" << "\n";
    listenForInput();
  }
}

void Timer::handleCases(const char& answer) {
  switch (answer) {
    case 'q': {
      running = false;
      return;
    }
    break;
    case 'o': {
      handleResetAllTimers();
    }
    break;
    case 'd': {
      handleDeleteAll();
    }
    break;
    default: {
      std::cout << "Please input a valid option" << "\n";
      listenForInput();
    }
    break;
  }
}

// Option methods
void Timer::handleDeleteAll() {
  timeData = {};
  running = false;

  Write::clearAllConsole();

  listenForInput();
}

void Timer::handleResetAllTimers() {
  for (TimerData& t: timeData) {
    t.reset();
    t.stop();
  }
}