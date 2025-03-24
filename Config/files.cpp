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

#include "./files.h"

#include <fstream>

#include "../Alarm/alarm.h"
#include "../Timer/timer.h"
#include "../Timer/timerData.h"
#include "../includes/nlohmann/json.hpp"

using json = nlohmann::json;

Files::Files() {}

std::vector < AlarmData > Files::getAlarms() {
  std::string basePath = Files::getAppDataPath();
  std::filesystem::create_directories(basePath);

  std::ifstream alarmFile(basePath + "alarm.json");

  json alarmFileData = deserializeJson(alarmFile);

  if (alarmFileData["error"] == true) {
    return {};
  }

  if (!alarmFileData.contains("alarms")) {
    return {};
  }

  int index = 0;

  for (Alarm::AlarmData alarm: alarmFileData["alarms"]) {
    Alarm::AlarmData existingAlarm = Alarm::AlarmData();
    
    alarms.push_back(existingAlarm);
    
    index++;
  }
}

std::vector < TimerData > Files::getTimers() {
  /*
  Timer JSON type
  {
    "error": boolean,
    timers: [
      {
        "on": boolean,
        "start": std::time_t,
        "hours": int,
        "minutes" int,
        "seconds": int,
        "milliseconds": int,
        "lastTime": int??
      },
      ...
    ]
  }
*/

  std::string basePath = Files::getAppDataPath();
  std::filesystem::create_directories(basePath);

  std::ifstream timerFile(basePath + "timer.json");

  json timerFileData = deserializeJson(timerFile);

  std::vector < TimerData > times = {};

  if (timerFileData["error"] == true) {
    return {};
  }

  if (!timerFileData.contains("timers")) {
    return {};
  }

  int index = 0;

  for (const json& timer: timerFileData["timers"]) {
    TimerData data = TimerData(
      index,
      timer["hours"].get < int > (),
      timer["minutes"].get < int > (),
      timer["seconds"].get < int > (),
      timer["milliseconds"].get < int > (),
      timer["isOn"].get < bool > (),
      std::chrono::milliseconds(timer["lastTime"].get < int > ())
    );

    times.push_back(data);

    index++;
  }

  return times;
};

json Files::deserializeJson(std::ifstream& inFile) {
  json j;

  if (!inFile.is_open()) {
    j["error"] = true;
    return j;
  }

  try {
    inFile >> j;
    j["error"] = false;
    return j;
  } catch (const json::parse_error& e) {
    std::cerr << "Parse error: " << e.what() << std::endl;
    return j;
  } catch (const json::type_error& e) {
    std::cerr << "Type error: " << e.what() << std::endl;
    return j;
  } catch (const json::out_of_range& e) {
    std::cerr << "Out of range error: " << e.what() << std::endl;
    return j;
  }

  return j;
};