#!bin bash

## Simple bash script to help build or run the code

include_path="includes/nlohmann"
json_file_path="$include_path/json.hpp"
json_url="https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp"

checkJson() {

  if [ ! -d "$include_path" ]; then
    mkdir -p "$include_path"
  fi

  if [ ! -f "$json_file_path" ]; then
    # Install json.hpp into project
    touch "$json_file_path"

    echo "installing json.hpp from nlohmann json"
    echo "https://github.com/nlohmann/json"

    curl -f "$json_url" -o "$json_file_path"

    if [ $? -eq 0 ]; then
      echo "Successfully installed necessary deps"
    else
      echo "Could not install json.hpp. This file is necessary to build the application. Please check out the url above"
    fi

  fi
}

buildWithClang() {
  # Check is nlohmann json is included with the project
  checkJson

  clang++ -o timerOut main.cpp Config/files.cpp Timer/timer.cpp Alarm/alarm.cpp Alarm/alarmData.cpp Timer/timerData.cpp Console/write.cpp Console/read.cpp Stopwatch/stopwatch.cpp Stopwatch/stopwatchData.cpp -Iincludes/nlohman -IConfig -ITimer -IConsole -IAlarm -IStopwatch
}

if command -v clang >/dev/null 2>&1; then
  buildWithClang
else
  echo "Clang is not installed, install it here https://clang.llvm.org/get_started.html)%5BInstall"
fi
