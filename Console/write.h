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

#ifndef WRITE_H
#define WRITE_H

#include <iostream>

class Write {
public:

struct TerminalSize {
    int height;
    int width;
};

enum Colors {
    YELLOW = 0;
    RED = 1;
    BLUE = 2;
    BLACK = 3;
    PURPLE = 4;
    CYAN = 5;
    WHITE = 6;
    ENDCOLOR = 7;
};

static TerminalSize myTerminalSize;

Write();

static std::string c(const Colors& color);

static void clearSection(int x, int y, int width, int height);
static void printInSection(int x, int y, std::string text);
static void clearAllConsole();

protected:
private:
};

#endif