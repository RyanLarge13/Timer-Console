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

#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include "../Alarm/alarm.h"
#include "../Timer/timer.h"
#include "../Timer/timerData.h"
#include "../Stopwatch/stopwatchData.h"
#include "../includes/nlohmann/json.hpp"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

/**
* @brief Files class introduces an abstraction of the filesystem api, and json parsing. This class handles reading and writing to JSON configuration files for the persistent data (Alarms, Timers, Stopwatches) within the application.
*/
class Files {
  public:
  /**
  * @brief Files constructor takes in no parameters and executes no initializing logic
  */
  Files();

  // Timer Methods
  /**
  * @brief getTimers takes in no parameters. This method is made to fetch timers stored from a configuration file
  which is either existing or being created by the application and returns them to the caller of the method or an empty vector
  * @return A vector of TimerData structures. @see TimerData
  */
  std::vector < TimerData > getTimers();
  void saveTimers(const std::vector < TimerData>& times);

  // Alarm Methods
  /**
  * @brief getAlarms takes in no parameters. This method is made to fetch alarms from a configuration file
  which is either existing or being created by the application and returns them to the caller of the method or an empty vector
  * @return A vector of AlarmData structures. @see AlarmData
  */
  std::vector < AlarmData > getAlarms();

  // Stopwatch methods

  /**
  * @brief getStopWatch method reads or creates JSON config file for stopwatch data and returns the data as StopWatchData to the caller of the method
  * @see StopWatchData
  */
  StopWatchData getStopWatch();

  protected:
  /**
  * @brief getAppDataPath returns the string that represents the file path which locates the configuration directory in storage for the application
  * @note This directory will be created if there is none in first search
  */
  std::string getAppDataPath() {
    #ifdef _WIN32
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
      return std::string(path) + "\\timer-console\\";
    }
    #else
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
      homeDir = "";
    }
    return std::string(homeDir) + "/.timer-console/";
    #endif
    return "";
  }

  /**
  * @brief deserializeJson returns a valid JSON object
  * @note json being returned can take any shape or form and must be checked by the caller
  * @param inFile: String reprisenting the path to the file which should be read from on the user's system
  */
  nlohmann::json deserializeJson(std::ifstream& inFile);

  /**
  * @brief saveJsonToFile does as it says. It takes any json shape and saves it to a file found or created at the location provided in params
  * @param fileName: string representing the path to the file in question 
  * @param j: a valid json object taking any shape to be saved to the file
  */
  void saveJsonToFile(const std::string& fileName, nlohmann::json j);

  private:
};

#endif