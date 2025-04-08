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

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

#include "./write.h"

// Define the static terminal size, initializing it to 0 height and 0 width
Write::TerminalSize Write::myTerminalSize = {
  0,
  0
};

Write::Write() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  // Create a static global terminal size variable to help avoid (but not prevent)
  // clearing the terminal screen with unexpected behavior
  myTerminalSize = Write::TerminalSize({
    w.ws_row, w.ws_col
  });
}

void Write::clearSection(int x, int y, int width, int height) {
  for (int i = 0; i < height; ++i) {
    // Clear while moving cursor
    std::cout << "\033[" << y + i << ";" << x << "H";
    for (int j = 0; j < width; ++j) {

      // Clear the section with empty strings
      std::cout << " ";
    }
  }
  std::cout.flush();
}

void Write::printInSection(int x, int y, std::string text) {
  // Print the text starting at x y positions
  std::cout << "\033[" << y << ";" << x << "H" << text;
  std::cout.flush();
}

std::string Write::c(const Write::Colors& color) {
  using namespace std;

  // Map the color enum to the actual console color to print

  switch (color) {
    case 0:
    return "\033[31m";
    break;
    case 1:
    return "\033[32m";
    break;
    case 2:
    return "\033[33m";
    break;
    case 3:
    return "\033[34m";
    break;
    case 4:
    return "\033[35m";
    break;
    case 5:
    return "\033[36m";
    break;
    case 6:
    return "\033[37m";
    break;
    case 7:
    return "\033[0m";
    break;
    default: {
      // Throw error for development
      throw std::invalid_argument("Out of range. Please return a valid enum integer between 0 and 7");
    }
    break;
  }

}

void Write::clearAllConsole() {

  // Using ASCII to clear console. Quicker and more efficient
  std::cout << "\033[2J\033[1;1H";
};