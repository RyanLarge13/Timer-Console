@mainpage Timer Console

# Timer Console

**Timer Console** is a lightweight C++ terminal application designed for Unix-based systems.
It provides robust timekeeping functionality with support for:

- **Timer**: Set countdowns that notify you when time is up.
- **Alarm**: Schedule alerts for specific system times.
- **Stopwatch**: Track elapsed time with start/stop/lap capabilities.

  ***

## Architecture

Timer Console is built with modularity in mind, with each core feature separated into its own class:

- `Timer`: Handles countdown logic and time formatting.
- `Alarm`: Schedules alarms based on user-defined system times.
- `Stopwatch`: Tracks elapsed time and supports lap features.

These classes are designed for clarity, testability, and future extensibility.

---

## Features

- Terminal-based interface
- Clean and modular C++ codebase
- Cross-feature state management
- Uses only standard C++ libraries (no third-party dependencies)
- Easily extensible for additional functionality

---

## How to Use

First make sure clang is installed. If you are on Mac it comes pre installed

[Install Clang](https://clang.llvm.org/get_started.html)

1. Open a terminal
2. cd into directory

```
$ cd Timer-Console/
```

3. Check permissions

```
$ chmod 777 build.sh
```

4. Run build script using bash

```
$ ./build.sh
```

---

## Supported Platforms

- Unix-based systems (Linux, macOS, BSD, etc.)

---

## Author

Developed by Ryan Large
