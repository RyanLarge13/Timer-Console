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

#include <chrono>
#include <iostream>
#include <thread>

void print(const std::vector < std::chrono::steady_clock::duration>& diffs) {

  std::cout << "\033[2J\033[1;1H";
  for (const std::chrono::steady_clock::duration& dir: diffs) {
    auto hours = std::chrono::duration_cast < std::chrono::hours > (dir);
    auto minutes = std::chrono::duration_cast < std::chrono::minutes > (dir -
      hours);
    auto seconds = std::chrono::duration_cast < std::chrono::seconds > (dir -
      hours - minutes);
    auto milliseconds = std::chrono::duration_cast < std::chrono::milliseconds >
    (dir -
      hours - minutes - seconds);

    std::cout << hours.count() << ":" << minutes.count() << ":" <<
    seconds.count() << ":" <<
    milliseconds.count() << "\n";
  }
}

void startLoop(const std::vector < std::chrono::steady_clock::time_point>& starts, const
  std::chrono::steady_clock::time_point& end) {

  std::vector < std::chrono::steady_clock::duration > diffs = {};

  for (int i = 0; i < starts.size(); i++) {
    auto diff = end - starts[i];
    diffs.push_back(diff);
  }

  print(diffs);

  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  auto newEnd = std::chrono::steady_clock::now();
  startLoop(starts, newEnd);
}

int main() {
  // auto start = std::chrono::steady_clock::now();

  std::vector < std::chrono::steady_clock::time_point > startTimes = {
    std::chrono::steady_clock::now(),
    std::chrono::steady_clock::now() - std::chrono::seconds(5),
    std::chrono::steady_clock::now() - std::chrono::seconds(15),
    std::chrono::steady_clock::now() - std::chrono::seconds(10),
    std::chrono::steady_clock::now() - std::chrono::seconds(11),
    std::chrono::steady_clock::now() - std::chrono::seconds(19),
    std::chrono::steady_clock::now() - std::chrono::seconds(600),
    std::chrono::steady_clock::now() - std::chrono::seconds(34),
    std::chrono::steady_clock::now() - std::chrono::seconds(900),
    std::chrono::steady_clock::now() - std::chrono::seconds(423),
  };

  auto end = std::chrono::steady_clock::now();

  startLoop(startTimes, end);
  return 0;
}