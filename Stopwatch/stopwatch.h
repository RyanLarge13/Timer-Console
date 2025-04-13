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

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "./stopwatchData.h"
#include <iostream>
#include <chrono>

/**
* @brief Stopwatch class defines the application interface into handling all users stopwatches, retrieving and updating them in memory and in storage
*/
class Stopwatch {
  public:

  /**
  * @brief member variable holding in memory the active timer and its associated data.
  * @see StopWatchData
  */
  StopWatchData stopwatch;

  /**
  * @brief startTime will represent the time that was captured upon opening the instance of stopwatch using system_clock
  */
  std::chrono::system_clock::time_point startTime;

  /**
  * @brief Constructor calls immediately loadStopwatch upon initialization
  * @see loadStopWatch
  */
  Stopwatch();


  protected:
  private:

  /**
  * @brief loadStopwatch method calls upon Files to read json and find if there was a previous stopwatch set from a previous session, if there is it loads it into memory as stopWatch.
  * @see stopWatch
  */
  void loadStopWatch();

  /**
  * @brief printTime prints the current elapsed time of the stopwatch to the console
  */
  void printTime();

  /**
  * @brief printOptions prints options the user can take on the stopwatch eg. pause, reset and prompts the user for input on the options listed
  */
  void printOptions();

  /// Handle option methods from user selection
  void handleReset();
  void handleStop();
  void handleResume();
  void handleQuit();

};

#endif