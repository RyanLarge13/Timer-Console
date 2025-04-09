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

#ifndef STOPWATCHDATA_H
#define STOPWATCHDATA_H

#include "../Timer/timerData.h"
#include <atomic>

class StopWatchData {
    public:

    /**
    * @brief StopWAtchData constructor takes in all data necessary for a stopwatch in this app and initializes member variables
    * @param elapsedTime: Times data showing how much time has passed on the stop watch
    * @param paused: Boolean indicating if the timer is running or has been running
    * @param lastTime Times data there for if the stopwatch was not put on pause when the application was exited or the class instance destroyed the application has a way of telling how much time has elapsed
    * @see Times
    */
    StopWatchData(
        const Times& elapsedTime, 
        const bool& paused, 
        const Times& lastTime
    );

    ~StopWatchData();

    /**
    * @brief elapsedTime is a Times data structure showing how much time has passed on the stop watch which includes hours, minutes, seconds and milliseconds
    * @see Times
    */
    Times elapsedTime;

    /**
    * @brief Indicating if the stopwatch should be running and printing or not
    */
    bool paused;

    /**
    * @brief lastTime is a Times data structure showing how much time has passed on the stop watch if it was left running and saved to a file which includes hours, minutes, seconds and milliseconds
    * @see Times
    */
    Times lastTime;


    // Class methods -----------------------------------
    /**
    * @brief print method handles printing the Times data in a friendly way to the terminal
    */
    void print();

    /**
    * @brief updateTimes updates the Times structure for the class instance
    */
    void updateTimes();


    protected:
    private:
};

#endif