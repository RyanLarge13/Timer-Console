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

#include "./timerData.h"

#include <chrono>
#include <thread>
#include <iostream>

#include "../Console/write.h"

TimerData::TimerData(const int& i)
    : index(i), running(false), paused(false), elapsedTime(0) {}

void TimerData::setTime(const int& hours, const int& minutes, const int& seconds) {
  duration = std::chrono::milliseconds(hours * 3600 + minutes * 60 + seconds);
  reset();
}

void TimerData::start() {
  // Set the star time to be the difference between now and the amount of elapsed time that has passed
  if (!running) {
    using namespace std::chrono;

    running = true;
    paused = false;

    // Start time equals the difference between now and the time elapsed
    startTime = steady_clock::now() - elapsedTime;
  }
}

void TimerData::pause() {
  if (running && !paused) {
    using namespace std::chrono;

    paused = true;

    // Set the elapsed time to the current difference
    elapsedTime = steady_clock::now() - startTime;
  }
}

void TimerData::reset() {
  running = false;
  paused = false;

  // Set elapsed time to 0 to reset the timer
  elapsedTime = milliseconds(0);
}

bool TimerData::isComplete() {
  if (!running) return false;
  return getTimeRemaining() <= milliseconds(0);
}

std::chrono::milliseconds TimerData::getTimeRemaining() {
    if (!running) {
    return duration - elapsedTime;
  } else if (paused) {
    return duration - elapsedTime;
  } else {
    using namespace std::chrono;

    // What the fuck is going on here?
    steady_clock::time_point now = steady_clock::now();
    duration currentElapsedTime = now - startTime;
    return duration - duration_cast<milliseconds>(currentElapsedTime);
  }
}

void TimerData::printRemainingTime() {
  using namespace std::chrono;

  milliseconds remainingTime = getTimeRemaining().count();

  int hoursLeft = remainingTime / 3600;
  int minutesLeft = (remainingTime % 3600) / 60;
  int secondsLeft = remainingTime % 60;
  int millisecondsLeft = remainingTime - hoursLeft - minutesLeft - secondsLeft;

  std::string timeTxt = 
    (hoursLeft < 10 ? "0" : "") + std::to_string(hoursLeft) + ":"
    (minutesLeft < 10 ? "0" : "") + std::to_string(minutesLeft) + ":"
    (secondsLeft < 10 ? "0" : "") + std::to_string(secondsLeft) + ":"
    (millisecondsLeft < 100 ? "0" : millisecondsLeft < 10 : "00" : "") + std::to_string(millisecondsLeft) + "\n";

  //You do not need to clear any area in console before printing, as Timer handles clearing the entire timer area before reprinting
  Write::printInSection(1, this->index, timeTxt);
}

void TimerData::setIndex(const int& newIndex) {
  index = newIndex;
}

bool TimerData::getIsRunning() {
  return running;
}

bool TimerData::getIsPaused() {
  return paused;
}

std::vector<TimerData::Times> TimerData::getTimes() {

  int hoursLeft = remainingTime / 3600;
  int minutesLeft = (remainingTime % 3600) / 60;
  int secondsLeft = remainingTime % 60;
  int millisecondsLeft = remainingTime - hoursLeft - minutesLeft - secondsLeft;

  TimerData::Times newTimes = TimerData::Times(hoursLeft, minutesLeft, secondsLeft, millisecondsLeft);

  return newTimes;
}