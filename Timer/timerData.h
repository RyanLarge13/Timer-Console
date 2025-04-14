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

/**
* @brief TimerData class is the structure of what the actual timer imementatiom will be for each timer a user creates. Initializes all data when created
*/
class TimerData {
  public:
  bool index;

  /**
  * @brief Times struct organizes parts of a timer body including the hour, minutes, seconds and milliseconds. All parts are initialized at creation time
  */
  struct Times {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

    Times(const int& h, const int& m, const int& s, const int& mill): hours(h),
    minutes(m),
    seconds(s),
    milliseconds(mill) {}
  };

  /**
  * TimerData constructor takes in single para
  * @param i: Provided by the length of the timerData vector in Timer class for easy selection when prompting user for input
  * @see Timer
  */
  TimerData(const int& i);

  /**
  * @brief setTime method sets the initial time on creation when called from Timer class.
  * @see Timer
  */
  void setTime(const int& hours, const int& minutes, const int& seconds);

  /**
  * @brief start method updates paused and running member methods to start counting time and updates the startTime
  * @see paused
  * @see running
  * @see startTime
  */
  void start();

  /**
  * @brief pause stops the timer and calculates the elapsed time to update it
  * @see elapsedTime
  */
  void pause();

  /**
  * @brief reset method updates paused and running g member variables and sets the elapsedTime to 0
  * @see paused
  * @see running
  * @see elapsedTime
  */
  void reset();

  /**
  * @brief isComplete method returns a true or false depending on if getTimeRemaining returns a value less than 0. To stop the timer and set off an alarm
  * @see getTimeRemaining
  */
  bool isComplete();
  std::chrono::milliseconds getTimeRemaining();

  /**
  * @brief printRemainingTime method prints the timer to the console in a user friendly way and in the correctly place in the console
  */
  void printRemainingTime();

  /**
  * @brief setIndex method changes the index of the timer depending on if the user moves the timer within the list of timers in memory aka TimerData vector setIndex
  * @see timerData
  * @param newIndex: Integer defining what index of TimerData vector the timer should change to
  */
  void setIndex(const int& newIndex);

  /**
  * @brief getIsPaused tells the caller of the method if the timer is counting down
  */
  bool getIsPaused();

  /**
  * @brief getIsRunning tells the caller of the method if the timer is counting down
  */
  bool getIsRunning();

  /**
  * @brief getTimes method returns the time of the timer as a Times structure
  * @see Times
  */
  std::vector < Times > getTimes();

  protected:

  private:
  std::chrono::milliseconds duration;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::duration elapsedTime;
  bool running;
  bool paused;
};

#endif