#include <chrono>
#include <iostream>
#include <thread>

void print(const int& diff) {
  auto hours = std::chrono::duration_cast < std::chrono::hours > (diff);
  auto minutes = std::chrono::duration_cast < std::chrono::minutes > (diff -
    hours);
  auto seconds = std::chrono::duration_cast < std::chrono::seconds > (diff -
    hours - minutes);
  auto milliseconds = std::chrono::duration_cast < std::chrono::milliseconds > (diff -
    hours - minutes - seconds);

  std::cout << hours.count() << ":" << minutes.count() << ":" <<
  seconds.count() << ":" <<
  milliseconds.count() << ":";
}

void startLoop(const std::chrono::steady_clock::time_point& start, const
  std::chrono::steady_clock::time_point& end) {
  auto diff = start - end;
  print(diff);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  system("clear");
  auto newEnd = std::chrono::steady_clock::now();
  startLoop(start, newEnd);
}

int main() {
  auto start = std::chrono::steady_clock::now();

  auto end = std::chrono::steady_clock::now();

  startLoop(start, end);
  return 0;
}