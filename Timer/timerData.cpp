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
#include <chrono>
#include "./timerData.h"

TimerData::TimerData(const int& i, const int& h, const int& m, const int& s, const int&
  mill, const bool& isOn, const std::chrono::milliseconds& lt):
index(i),
hours(h),
minutes(m),
seconds(s),
milliseconds(mill),
isOn(isOn),
lastTime(lt) {
  using namespace std;

  chrono::milliseconds tpOfLastTime = chrono::duration_cast < chrono::milliseconds > (chrono::milliseconds(lastTime));

  lastTime = tpOfLastTime;

  totalStoredTime = chrono::duration_cast < chrono::milliseconds > (
    chrono::hours(hours) +
    chrono::minutes(minutes) +
    chrono::seconds(seconds) +
    chrono::milliseconds(milliseconds)
  );

  totalTimeInMs = this->totalStoredTime + this->lastTime;
}

void TimerData::print() {
  std::cout << this->index << ". " << this->hours << ":" << this->minutes << ":"
  << this->seconds << ":" << this->milliseconds << "\n";
}

void TimerData::printUpdate() {
  using namespace std::chrono;

  steady_clock::time_point now = steady_clock::now();

  duration timeElapsed = this->totalTimeInMs - now;

  auto h = duration_cast < hours > (timeElapsed);
  auto m = duration_cast < minutes > (timeElapsed - hours);
  auto s = duration_cast < seconds > (timeElapsed - hours - minutes);
  auto mill = duration_cast < milliseconds > (timeElapsed - hours - minutes - seconds);

  std::cout << this->index << ". " << h.count() << ":" << m.count() << ":" << s.count() << ":" << mill.count() << "\n";
}