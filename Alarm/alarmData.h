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

#ifndef ALARM_DATA_H
#define ALARM_DATA_H

#include "./alarm.h"
#include <vector>
#include <map>

/**
* @brief AlarmData class handles the implementation of the actual alarm that is stored or in memory to be manipulated and used
*/
class AlarmData {
  public:

  /**
  * @brief Vibrate struct provides more customization over how the device will react to an alarm being triggered
  * @param on: Boolean describing if the alarm should or should not vibrate when triggered
  * @note The application will automatically set on to false if the device does not support vibration
  * @param intensity: Double to describe how intense the vibration should be
  */
  struct Vibrate {
    bool on;
    double intensity;

    Vibrate(const bool& on, const double& intensity): on(on),
    intensity(intensity) {}
  };

  /**
  * @brief AlarmTime struct enables an integer pair for defining the time the alarm should be set for by hour and minute
  * @param hour: Int defining the hour the alarm should go off 1 - 12
  * @param minute: Int defining the minutes the alarm should trigger 0 - 59
  */
  struct AlarmTime {
    int hour;
    int minute;

    AlarmTime(const int& h, cont int& m): hour(h),
    minute(m) {}
  }

  /**
  * @brief AlarmData constructor takes in all necessary data to build a functional alarm to be stored and used in the app
  * @param daysOfWeek: Vector of integers correlating to the days of the week an alarm will be triggered on
  * @param alarmTime: @see AlarmTime struct. Gives the hour and minute the alarm should be triggered
  * @param on: Boolean indicating if the alarm is active or not
  * @param meridiem: String indicating if the alarm is for AM or PM. Used only when creating an alarm and when showing the user
  * @param vibrate: @see Vibrate struct. Indicating the type of vibration pattern should be applied to the device when the alarm triggers
  * @param message: String optional. Provided to the user when the alarm triggers
  */
  AlarmData(
    const std::vector < Alarm::DaysOfWeek>& daysOfWeek,
    const AlarmTime& alarmTime,
    const bool& on,
    const std::string& meridiem,
    const Vibrate& vibrate
    const std::string& message
  );

  /**
  * @brief change the time of the alarm by creating a new AlarmTime struct after prompting. This method also updates AlarmData.meridiem
  * @param newTome: @see AlarmTime which provides the hour and minute the alarm should trigger
  */
  void changeTime(const AlarmTime& newTime);

  /**
  * @brief toggleOnOff turns the alarm on state to the opposite of what it current is set as
  * @return Boolean
  */
  bool toggleOnOff();
  
  /**
   * @brief toggleMeridiem will ch age the string value to AM if currently PM and PM if currently AM. This method also updates the hour in the instances alarmTime struct @see AlarmData.alarmTime
   */
  void toggleMeridiem();
  
  /**
   * @brief Print specializes in printing the alarm in a user friendly way to the console along with the shortened day of the week strings associated with @see Alarm::DaysOfWeek. 
   */
  void print();

  protected:
  private:
};

#endif