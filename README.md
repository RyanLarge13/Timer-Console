# Timer Console

Handle time with this console based time management application. Set multiple
timers, alrams and start the stopwatch!

C++ for fast, safe and reliable code. Garunteed to work in any Unix based
system and is also compatable on windows systems using powershell.

This is a bare bones project. You are welcome to configure a cmake file or just
simply compile with GCC or clang

## Compiling With Clang

First make sure clang is installed. If you are on Mac it comes pre installed

(https://clang.llvm.org/get_started.html)[Install Clang]

### Compile

```
~$ clang++ -o timerOut main.cpp Config/files.cpp Timer/timer.cpp Alarm/alarm.h
Timer/timerData.cpp Console/write.cpp Console/read.cpp
-Iincludes/nlohman -IConfig -ITimer -IConsole -IAlarm
```

## How to use

Check out the docs for developers if you are interested in learning how to use this code or develop further with this project 

[Docs](https://legendary-narwhal-a2300f.netlify.app/)
