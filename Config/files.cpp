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

#include "../includes/json.hpp"
#include "../Timer/timer.h"
#include "./files.h"
#include <fstream>

using json = nlohmann::json;

Files::Files() {}

std::vector < Timer::TimerData > Files::getTimers() {
  std::string basePath = Files::getAppDataPath();
  std::filesystem::create_directories(basePath);

  std::ifstream timerFile(basePath + "timer.json");

  json timerFileData = deserializeJson(timerFile);

  std::vector < Timer::TimerData > times;

  if (timerFileData["error"] == true) {
    return {};
  }

  if (!timerFileData.contains("timers")) {
    return {};
  }

  for (const std::string& timer: timerFileData["timers"]) {

    Timer::TimerData data = Timer::TimerData(
      std::chrono::steady_clock::to_time_t(timer.time),
      timer.on
    );

    times.push_back(data);
  }

  return times;
};

void Files::getAlarms() {};
void Files::getStopwatch() {};

void Files::setTimers() {};
void Files::setAlarms() {};
void Files::setStopwatch() {};

json deserializeJson(const std::ifstream& inFile) {
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
  } catch (const json::type_error& e) {
    std::cerr << "Type error: " << e.what() << std::endl;
  } catch (const json::out_of_range& e) {
    std::cerr << "Out of range error: " << e.what() << std::endl;
  }

};