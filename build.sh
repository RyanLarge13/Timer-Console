#!bin bash

## Simple bash script to help build or run the code

buildWithClang() {
clang++ -o timerOut main.cpp Config/files.cpp Timer/timer.cpp Alarm/alarm.cpp Alarm/alarmData.cpp Timer/timerData.cpp Console/write.cpp Console/read.cpp Stopwatch/stopwatch.cpp Stopwatch/stopwatchData.cpp -Iincludes/nlohman -IConfig -ITimer -IConsole -IAlarm -IStopwatch
} 

if command -v clang >/dev/null 2>&1; then
    buildWithClang
else
    echo "Clang is not installed, install it here https://clang.llvm.org/get_started.html)%5BInstall"
fi