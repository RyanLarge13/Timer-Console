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

#include "./read.h"

#include <termios.h>
#include <unistd.h>
#include <iostream>

Read::Read() {}

// Change the input mode to either only accept a single character and continue or accept input from user as usual to create a better user experience, one that feels more automatic and simple
void Read::setCanonicalMode(const bool& on) {
  struct termios settings;

  // Get current terminal attributes
  tcgetattr(STDIN_FILENO, &settings);

  if (on) {
    settings.c_lflag &= ~(ICANON | ECHO);
  } else {
    settings.c_lflag |= (ICANON | ECHO);
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}