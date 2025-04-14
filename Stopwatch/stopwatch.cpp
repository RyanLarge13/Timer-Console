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

#include "./stopwatch.h"
#include "../Config/files.h"
#include "../Console/write.h"
#include "../Console/read.h"
#include "../Timer/timerData.h"
#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

std::atomic < bool > running(true);

Stopwatch::Stopwatch() {
  // Set startTime to now
  startTime = std::chrono::system_clock::now();

  loadStopWatch();
}

void Stopwatch::loadStopWatch() {
  StopWatchData storedWatch = Files::getStopWatch();

  stopwatch = storedWatch;

  if (!stopwatch.paused) {
    std::chrono::system_clock::time_point timeAtLastSave = std::chrono::system_clock::time_point(std::chrono::milliseconds(stopwatch.lastTime));

    std::chrono::duration timeElapsed = timeAtLastSave - startTime;
    stopwatch.updateElapsedTime(timeElapsed);
  }

  std::thread displayWatch(&Stopwatch::printTime, this);
  std::thread promptUser(&Stopwatch::printOptions, this);

  displayWatch.join();
  promptUser.join();
}

void Stopwatch::printTime() {

  while (running && stopwatch.paused) {
    startTime = std::chrono::system_clock::now();
  }

  while (running && !stopwatch.paused) {
    using namespace std::chrono;

    stopwatch.print();

    // Find the time elapsed and update this->elapsedTime
    system_clock::time_point now = system_clock::now();
    duration timeElapsed = now - this->startTime;
    stopwatch.updateElapsedTime(timeElapsed);

    // Update startTime to the latest for next round
    this->startTime = now;

    std::this_thread::sleep_for(milliseconds(100));
  }
}

void Stopwatch::printOptions() {
  std::string options = stopwatch.paused ? "1. Resume, ": "1. Stop,";
  
  std::string optionsStr = options + "2. Reset, 3. Quit" + "\n" + "Option: ";
  
  
  Write::clearSection(3, 1, Write::myTerminalSize.width, 1);
  Write::printInSection(3, 1, options);

  while (running) {
    int option;
    std::cin >> option;

    switch (option) {
      case 1: {
        if (stopwatch.paused) {
          handleResume();
        } else {
          handleStop();
        }
      }
      break;
      case 2: {
        handleReset();
      }
      break;
      case 3: {
        handleQuit();
      }
      break;
      default: {
        std::cout << "Please input a valid option" << "\n" << "Option: ";
      }
      break;
    }
  }
}

void Stopwatch::handleReset() {
  // Reset elapsed time back to 00:00:00::000 and pause the timer
  TimerData::Times resetStopwatch = TimerData::Times(0, 0, 0, 0);
  stopwatch.elapsedTime = resetStopwatch;

  stopwatch.paused = true;
}

void Stopwatch::handleStop() {
  stopwatch.paused = true;
}

void Stopwatch::handleResume() {
  stopwatch.paused = false;
}

void Stopwatch::handleQuit() {
  using namespace std::chrono;

  running = false;

  system_clock::time_point now = system_clock::now();
  duration timeElapsed = now - this->startTime;
  stopwatch.updateElapsedTime(timeElapsed);


  milliseconds millis = duration_cast < milliseconds > (system_clock::now().time_since_epoch()).count();
  stopwatch.lastTime = millis;

  // Files::saveStopwatch(stopwatch);
}