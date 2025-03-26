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

#ifndef TIMER_DATA_H
#define TIMER_DATA_H

#include <chrono>

class TimerData {
 public:
  bool index;

  struct Times {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

    Times(const int&  h, const int& m, const int& s, const int& mill) : hours(h), minutes(m), seconds(s), milliseconds(mill) {};
  };

  TimerData(const int& i);

  void setTime(const int& hours, const int& minutes, const int& seconds);
  void start();
  void pause();
  void reset();
  bool isComplete();
  std::chrono::milliseconds getTimeRemaining();
  void printRemainingTime();
  void setIndex(const int& newIndex);
  bool getIsPaused();
  bool getIsRunning();
  std::vector<Times> getTimes();

 protected:

 private:
 std::chrono::milliseconds duration;
 std::chrono::steady_clock::time_point startTime;
 std::chrono::steady_clock::duration elapsedTime;
 bool running;
 bool paused;
};

#endif