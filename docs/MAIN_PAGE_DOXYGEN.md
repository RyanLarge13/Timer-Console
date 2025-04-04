 @mainpage Timer Console
 
 # Timer Console
 
  **Timer Console** is a lightweight C++ terminal application designed for Unix-based systems.
  It provides robust timekeeping functionality with support for:
 
 - **Timers**: Set countdowns that notify you when time is up.
 - **Alarms**: Schedule alerts for specific system times.
 - **Stopwatch**: Track elapsed time with start/stop/lap capabilities.
 
  ---
 
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
 
  Compile the application with your preferred C++ compiler:
 
  ```bash
  g++ -std=c++17 -o timer_console main.cpp
  ./timer_console
  ```
 
  Follow the in-terminal prompts to create timers, set alarms, or use the stopwatch.
 
  ---
 
  ## Supported Platforms
 
  - Unix-based systems (Linux, macOS, BSD, etc.)
 
  ---
 
  ## Author
 
  Developed by Ryan Large