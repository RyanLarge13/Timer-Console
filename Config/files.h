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


class Files {
  public:
  Files();

  // Timer Methods
  std::vector < TimerData > getTimers();
  void saveTimers(const std::vector<TimerData>& times);

  // Alarm Methods
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