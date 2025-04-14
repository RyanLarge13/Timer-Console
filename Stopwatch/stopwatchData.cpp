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

#include <chrono>
#include <string>
#include "./stopwatchData.h"
#include "../Console/write.h"

StopWatchData::StopWatchData(
  const TimerData::Times& elapsedTime,
  const bool& paused,
  const std::chrono::milliseconds& lastTime
):
elapsedTime(elapsedTime),
paused(paused),
lastTime(lastTime) {}

std::string StopWatchData::getStopwatchTimeString() {
  TimerData::Times t = this->elapsedTime;

  std::string timeString =
  std::to_string(t.hours) + ":" +
  std::to_string(t.minutes) + ":" +
  std::to_string(t.seconds) + ":" +
  std::to_string(t.milliseconds) + "\n";

  return timeString;
}

void StopWatchData::print() {
  Write::clearSection(1, 1, Write::myTerminalSize.width, 1);
  std::string nowTime = getStopwatchTimeString();
  Write::printInSection(1, 1, nowTime);
}

void StopWatchData::updateElapsedTime(const std::chrono::duration& t) {
  using namespace std::chrono;

  int h = t.hours.count();
  int m = t.minutes.count();
  int s = t.seconds.count();
  int mill = t.milliseconds.count();

  TimerData::Times newTime = TimerData::Times(h, m, s, mill);

  this->elapsedTime = newTime;
}