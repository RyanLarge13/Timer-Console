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

/**
* @brief For better readability and development process using json is declared here at the top of the implementation file
*/
using json = nlohmann::json;

Files::Files() {}

// Read alarms from file, create AlarmData instances from json returned from file and return AlarmData instances in a vector
std::vector<AlarmData> Files::getAlarms() {
  std::string basePath = Files::getAppDataPath();
  std::filesystem::create_directories(basePath);

  std::ifstream alarmFile(basePath + "alarm.json");

  /**
  * @brief alarmFileData return type
    {
      "error": boolean // did the read fail or not  
      "alarms": [ // array of AlarmData types @see AlarmData
        {
          "dow": int[],
          "time": {
            "hour": int,
            "minute": int
          },
          "on": boolean,
          "meridiem": "string",
          "vibrate": {
            "on": boolean,
            "intensity": double
          }
        },
        ...
      ]
    }
  */
  json alarmFileData = deserializeJson(alarmFile);

  if (alarmFileData["error"] == true) {
    return {};
  }

  if (!alarmFileData.contains("alarms")) {
    return {};
  }

  int index = 0;

  std::vector<AlarmData> alarms;

  // For each field in alarms create the alarm in memory and add it to the alarms vector the function plans to return

  /*
    TODO:
      1. Verify all this data and or return valid options if it does not exist before creating AlarmData object
  */
  for (AlarmData alarm: alarmFileData["alarms"]) {
    
    std::vector<Alarm::DaysOfWeek> daysOfWeek = alarm["dow"];

    std::string alarmTimeHours = alarm["time"]["hour"];
    std::string alarmTimeMinutes = alarm["time"]["minute"];

    bool on = alarm["on"];
    std::string meridiem = alarm["meridiem"];
    
    bool vibrateOn = alarm["vibrate"]["on"];
    double intensity = alarm["vibrate"]["intensity"];

    AlarmData::Vibrate vibrate(vibrateOn, intensity);

    // Build the alarm with data pulled from file
    AlarmData existingAlarm = AlarmData(daysOfWeek, AlarmData::AlarmTime(alarmTimeHours, alarmTimeMinutes), on, meridiem, vibrate);

    // Loop through days of week to make sure that map contains the alarm and week day
    alarms.push_back(existingAlarm);
    
    index++;
  }
}

// Timer methods ----------------------------------------------------------------------------------
// Read timers as json from the timer config file stored on the users computer and create Timer objects to return to the caller of the method
std::vector < TimerData > Files::getTimers() {
  std::string basePath = Files::getAppDataPath();
  std::filesystem::create_directories(basePath);

  std::ifstream timerFile(basePath + "timer.json");

  json timerFileData = deserializeJson(timerFile);

  /**
  * @brief timerFileData json data structure
  {
    "error": boolean,
    "timers": [ // array of TimerData data. @see TimerData
      {
        "hours": int,
        "minutes": int,
        "seconds": int,
        "running": boolean,
        "paused": boolean
      },
      ...
    ]
  }
  */

  std::vector < TimerData > times = {};

  if (timerFileData["error"] == true) {
    return {};
  }

  if (!timerFileData.contains("timers")) {
    return {};
  }

  int index = 0;

  for (const json& timer: timerFileData["timers"]) {
    TimerData newtimer = TimerData(
      index,
      timer["hours"].get < int > () || 0,
      timer["minutes"].get < int > () || 0,
      timer["seconds"].get < int > () || 0,
    );
    
    bool isRunning = timer["running"].get < bool > () || false;
    bool isPaused = timer["paused"].get < bool > () || true;

    if (isRunning && !isPaused) {
      newTimer.start();
    }

    times.push_back(newtimer);

    index++;
  }

  return times;
};

void Files::saveTimers(const std::vector<TimerData>& timers) {
    // Loop over timers to save correct data
    json timerConfig;

    timerConfig["error"] = false;
    std::vector<json> timersToSave = {};

    for (TimerData timer : timers) {
      json time;

      TimerData::Times timerTimes = timer.getTimes();
      time["running"] =  timer.getIsRunning();
      time["paused"] = timer.getIsPaused();
      time["hours"] = timerTimes.hours;
      time["minutes"] = timerTimes.minutes;
      time["seconds"] = timerTimes.seconds;

      // Push the new timer to the timers json vector
      timersToSave.push_back(time);
    } 

    // Save the vector as the json timers in config
    timerConfig["timers"] = timersToSave;

    saveJsonToFile("timer.json", timerConfig);
}
// Timer methods ----------------------------------------------------------------------------------


// Store json of any shape into json nlohmann::json type and return it to the caller of the method
// Catch errors of many sorts returning j with j["error"] set to true
json Files::deserializeJson(std::ifstream& inFile) {
  json j;

  if (!inFile.is_open()) {
    j["error"] = true;
    return j;
  }

  try {
    inFile >> j;
    inFile.close();
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

// Save any json type to specified file
void Files::saveJsonToFile(const std::string& fileName, json j) {
    std::string basePath = Files::getAppDataPath();
    std::filesystem::create_directories(basePath);

    std::ofstream file(basePath + fileName);

    if (!file.is_open()) {
      return;
    }

    file << j;

    file.close();
}