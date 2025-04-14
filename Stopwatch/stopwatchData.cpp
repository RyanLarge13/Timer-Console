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
#include <iomanip>
#include <sstream>

StopWatchData::StopWatchData(
  TimerData::Times elapsedTime,
  bool paused,
  std::chrono::milliseconds lastTime
):
elapsedTime(elapsedTime),
paused(paused),
lastTime(lastTime) {}


std::string StopWatchData::getStopwatchTimeString() {
  TimerData::Times t = this->elapsedTime;

  std::ostringstream ss;
  ss << std::setfill('0')
     << std::setw(2) << t.hours << ":"
     << std::setw(2) << t.minutes << ":"
     << std::setw(2) << t.seconds << ":"
     << std::setw(3) << t.milliseconds;

  return ss.str();
}


void StopWatchData::print() {
  Write::clearSection(1, 1, Write::myTerminalSize.width, 1);
  std::string nowTime = getStopwatchTimeString();
  Write::printInSection(1, 1, nowTime);
}

void StopWatchData::updateElapsedTime(const std::chrono::duration<double>& t) {
  using namespace std::chrono;

  int ms = duration_cast<milliseconds>(t);
  int h = duration_cast<hours>(ms);
  int m = duration_cast<minutes>(ms - h);
  int s = duration_cast<seconds>(ms - h - m);
  int mill = duration_cast<milliseconds>(ms - h - m - s);

  TimerData::Times newTime = TimerData::Times(h.count(), m.count(), s.count(), mill.count());

  this->elapsedTime = newTime;
}