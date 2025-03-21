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
#include "../Console/write.h"

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

void TimerData::print(const int& yStart) {
  // First clear the section of the screen for new time update
  // A single timer should be on a single line
  // Write::clearSection(1, this->index + yStart, Write::myTerminalSize.width, yStart + 1);

  // Sorry Not sure if I should even be reprinting this yet given the times are currently static and not
  // running there is no need to call an update on the displayed text so commenting out above section for now

  std::string timeString = 
  std::to_string(this->index) + ". " + 
  std::to_string(this->hours) + ":" + 
  std::to_string(this->minutes) + ":" + 
  std::to_string(this->seconds) + ":" + 
  std::to_string(this->milliseconds) + "\n";

  std::cout << timeString;
}

void TimerData::printUpdate(const int& yStart) {
  using namespace std::chrono;

  // First clear section where previous time was
  Write::clearSection(1, this->index + yStart, Write::myTerminalSize.width, yStart + 1);

  steady_clock::time_point now = steady_clock::now();

  steady_clock::duration timeElapsed = steady_clock::time_point(this->totalTimeInMs) - now;

  auto h = duration_cast < std::chrono::hours > (timeElapsed);
  auto m = duration_cast < std::chrono::minutes > (timeElapsed - h);
  auto s = duration_cast < std::chrono::seconds > (timeElapsed - h - m);
  auto mill = duration_cast < std::chrono::milliseconds > (timeElapsed - h - m - s);

  std::string timeString = 
  std::to_string(this->index) + ". " + 
  std::to_string(h.count()) + ":" + 
  std::to_string(m.count()) + ":" + 
  std::to_string(s.count()) + ":" + 
  std::to_string(mill.count()) + "\n";

  // Reprint new updated time in the same place
  Write::printInSection(1, this->index + yStart, timeString);
}