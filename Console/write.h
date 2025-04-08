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

/**
* @brief Write class creates an abstraction for controlling how the terminal will print to the screen
*/
class Write {
public:

/**
* @brief Terminal size structure defines a simple interface for defining a width and a height integer
*/
struct TerminalSize {
    int height;
    int width;

    /**
    * @brief Constructor takes in width and height and initializes struct
    * @param width: Int indicating the width of the terminal
    * @param height: Int indicating the height of the terminal
    * @note Must use built in api to get the width of terminal before creating this struct
    */
    TerminalSize(const int& width, const int& height) : width(width), height(height) {}
};

/**
* @brief Colors integer enum creates an easy interface for defining colors to use in the console when printing
*/
enum Colors {
    YELLOW = 0, 
    RED = 1, 
    BLUE =2,
    BLACK = 3, 
    PURPLE =4,
    CYAN = 5, 
    WHITE = 6, 
    ENDCOLOR = 7
};

/**
* @brief myTerminalSize is a public variable to use throughout the application to easily query the terminal dimensions the user is currently working with
*/
static TerminalSize myTerminalSize;

Write();

/**
* @brief c method returns a color associated with enum @see Colors
* @param color: ENUM color @see Colors
*/
static std::string c(const Colors& color);

/**
* @brief clearSection erases specified section of the terminal by replacing them with empty strings
* @param x: Integer indicating where to start the cursor in column
* @param y: Integer indicating where to start the cursor in row
* @param width: Integer indicating the amount of columns the cursor should travel to erase
* @param height: Integer indicating the amount of rows the cursor should travel to erase
*/
static void clearSection(int x, int y, int width, int height);

/**
* @brief printInSection takes a section of the terminal and prints the specified string in the section
* @param x: Integer indicating where to start the cursor in column
* @param y: Integer indicating where to start the cursor in row
* @param text: String that should be printed
*/
static void printInSection(int x, int y, std::string text);

/**
* @brief clearAllConsole method clears the entire console erasing all characters on the console screen
*/
static void clearAllConsole();

protected:
private:
};

#endif