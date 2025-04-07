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
  void saveTimers(const std::vector<TimerData>& times);

  // Alarm Methods
  /**
* @brief getAlarms takes in no parameters. This method is made to fetch alarms from a configuration file
which is either existing or being created by the application and returns them to the caller of the method or an empty vector
* @return A vector of AlarmData structures. @see AlarmData
*/
  std::vector<AlarmData> getAlarms();

  protected:
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

  nlohmann::json deserializeJson(std::ifstream& inFile);

  void saveJsonToFile(const std::string& fileName, json j);

  private:
};

#endif