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

#include <termios.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "../Config/files.h"
#include "../Console/read.h"
#include "../Console/write.h"
#include "./timerData.h"

std::vector < TimerData > timeData = {};
std::atomic < bool > running(true);

// To save TimerData last time use duration_cast <millis> since last epoch

Timer::Timer() {
  Write::clearAllConsole();

  // Display all timers options and listen for input in the console
  std::thread listen(&Timer::listenForInput, this);
  std::thread timerLoader(&Timer::loadTimers, this);

  listen.join();
  timerLoader.join();
}

void Timer::loadTimers() {
  Files timerFileHandler;

  timeData = timerFileHandler.getTimers();

  while (running.load()) {
    printTimers();
    // Give time between new prints so the program doesn't overwhelm itself
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void Timer::printTimers() {
  // Clear the section below the Timer options already printed
  Write::clearSection(1, 8, Write::myTerminalSize.width, Write::myTerminalSize.height - 8);

  for (TimerData& t: timeData) {
    t.printRemainingTime();
  }
}

void Timer::listenForInput() {
  std::string optionTxt =
  "'a': Add Timer\n"
  "'r': Remove Timer\n"
  "'d': Delete All Timers\n"
  "'o': Reset All Timers\n"
  "'q': Exit Timer\n"
  "\nOption: ";

  Write::clearSection(1, 1, Write::myTerminalSize.width, 6);
  Write::printInSection(1, 1, optionTxt);

  Read::setCanonicalMode(true);

  char answer;

  // Errors found in Termux. Code not working properly with atomic variable. --------------------------------
  // Termux printing 0 instead of 1/true when printing running.load()

  while (running.load()) {
    // Build a separate loop to keep the input thread alive attached to this
    // function call instance. If I recall this function elsewhere without
    // properly managing the current input thread we run into loop issues
    // and stack overflow problems

    // eg. For instance, calling listenForInput inside of any other option method
    // (handleDeleteAll, handleAddTimer, etc...) to handle the character input again

    read(STDIN_FILENO, &answer, 1);
    handleCases(answer);

    if (!running) {
      break;
    }
  }

  Read::setCanonicalMode(false);
}

void Timer::handleCases(const char& answer) {
  switch (answer) {
    case 'q': {
      handleQuit();
    } break;
    case 'o': {
      handleResetAllTimers();
    } break;
    case 'd': {
      handleDeleteAll();
    } break;
    case 'a': {
      handleAddtimer();
    } break;
    case 'r': {
      handleRemoveTimer();
    } break;
    default: {
      std::cout << "Please input a valid option" << "\n";
    } break;
  }
}

// Option methods
void Timer::handleQuit() {
  // Save to file and quit
  Files::saveTimers(timeData);

  // This ends timer session completely
  running = false;
}

void Timer::handleDeleteAll() {
  timeData = {};
  // Delete all timers from files

  Write::clearAllConsole();
}

void Timer::handleResetAllTimers() {
  for (TimerData& t: timeData) {
    t.pause();
    t.reset();
  }
}

void Timer::handleAddtimer() {
  Writer::clearAllConsole();

  if (timeData.size() > 8) {
    // Return early. Only allow the user to have 9 timers at once
    std::cout << Write::c(Write::Colors::RED) << "You can only have 9 timers" << Write::c(Write::Colors::ENDCOLOR) << "\n";
    return;
  }

  int newIndex = timeData.size() | 1;

  TimerData::Times newTimerTimes = getUserTimer();

  TimerData newTimer(newIndex);
  newTimer.setTime(newTimerTimes.hours, newTimerTimes.minutes, newtimerTimes.seconds);

  timeData.push_back(newTimer);
}

void Timer::handleRemoveTimer() {
  // Query for input by index to remove specific timer
  Write::clearAllConsole();

  for (TimerData& time: timeData) {
    std::cout << time.index << ". " << time.printRemainingTime() << "\n";
  }

  std::cout << "Which timer do you want to remove? ";

  Read::setCanonicalMode(true);

  int timerIndex;
  read(STDIN_FILENO, &timerIndex, 1);

  Read::setCanonicalMode(false);

  timeData.erase(timeData.begin() + timerIndex);
}

TimerData::Times Timer::getUserTimer() {
  int hours = -1;
  int minutes = -1;
  int seconds = -1;

  bool isQuerying = true;

  std::cout <<
  hours == -1 ? "00": hours < 10 ? "0": "" << hours << ":" <<
  minutes == -1 ? "00": minutes < 10 ? "0": "" << minutes << ":" <<
  seconds == -1 ? "00": seconds < 10 ? "0": "" << seconds << ":000" << "\n";

  while (isQuerying) {
    if (hours == -1) {
      std::cout << "Hours: ";
      std::cin >> hours;
    }

    if (minutes == -1) {
      std::cout << "Minutes: ";
      std::cin >> minutes;
    }

    if (seconds == -1) {
      std::cout << "Seconds: ";
      std::cin >> seconds;
    }
  }

  TimerData::Times returnTimes = TimerData::Times(
    hours == -1 ? 0: hours,
    minutes == -1 ? 0: minutes,
    seconds == -1 ? 0: seconds
  );

  Write::clearAllConsole();

  return returnTimes;
}