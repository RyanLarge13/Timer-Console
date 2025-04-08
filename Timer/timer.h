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

#ifndef TIMER_H
#define TIMER_H

#include <atomic>
#include <chrono>
#include <iostream>
#include <vector>

#include "./timerData.h"

/**
* @brief Timer class handles all high level timer tasks and management including adding, removing, providing interface for updating and defining crucial data for timer functionality
*/
class Timer {
 public:
  Timer();

  /**
* @brief timeData stores all the timers in memory for the user to manipulate as a vector of TimerData structures. @see TimerData
  */
  std::vector<TimerData> timeData;

  /**
* @brief running is a special atomic bool created for managing the multi threaded nature of this class. Allowing both the printing in real time of the timers to the console and prompting the user for input
  */
  std::atomic<bool> running;

  /**
  * @brief loadTimers calls upon Files. @see Files to pull any stored timers from the users configuration and loads them into memory as timeData. @see timeData
  */
  void loadTimers();

  /**
  * @brief printTimers loops through timeData to grab each TimerData instance and calls their corresponding print method. @see TimerData
  */
  void printTimers();


  /// Thread methods ---------------------------
  /**
  * @brief listenForInput opens a thread which prompts the user for input and prints options for the user to select from to the console
  */
  void listenForInput();

  /**
  * @brief handleCases is a switch case method that handles mapping the users input to the correct class method
  * @param answer: single character input indicating what option method will be called based on users input
  */
  void handleCases(const char& answer);

  /**
  * @brief getUserTimer prompts the user to input the hours minutes and seconds they would like to set on the timer
  and returns these values as a TimerData::Times struct. @see TimerData::Times
  */
  TimerData::Times getUserTimer();


  /// Option methods --------------------------
  /**
  * @brief handleQuit quits the timer instance class by ending input clearing the console and stopping the printing of users timer. Also saves in memory timers as JSON to the users timer configuration file
  */
  void handleQuit();

  /**
  * @brief deleteAll removes all timers from memory
  */
  void handleDeleteAll();

  /**
  * @brief handleResetAllTimers handles resetting all timers to 00:00:00 in memory
  */
  void handleResetAllTimers();

  /**
  * @brief handleAddTimer prompts the user to create a timer and add it to timeData vector
  */
  void handleAddtimer();

  /**
  * @brief handleRemoveTimer removes a timer from timeData vector after prompting the user for the index of the timer they would like to remove
  */
  void handleRemoveTimer();

 protected:
 private:
};

#endif