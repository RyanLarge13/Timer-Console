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

#include "./alarm.h"
#include "../Config/files.h"
#include "../Consle/write.h"

Alarm::Alarm() {
  loadAlarms();
}

void Alarm::loadAlarms() {
  alarms = Files::getAlarms();

  printAlarms();
}

void Alarm::printAlarms() {
  Write::clearAllConsole();

  for (int i = 0; i < Alarm::daysOfTheWeek; i++) {
    // Print day of the week and all of the alarms associated
    std::cout << daysOfTheWeek[i] << "\n";

    for (AlarmData* alarm : alarms[i]) {
      alarm->print();
    }
  }
}