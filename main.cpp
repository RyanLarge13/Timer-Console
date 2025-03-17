#include <iostream>

int main() {
  int selection;
  // Print menu and provide options
  std::cout << "1. Alarm" << "\n";
  std::cout << "2. Stopwatch" << "\n";
  std::cout << "3. Timer" << "\n";
  std::cout << "4. Quit" << "\n";

  std::cout << "Selection: ";
  std::cin >> selection;

  if (selection < 1 || selection > 4) {
    // Print correction
    system("clear");
    std::cout << "Please select 1 through 3" << "\n";
  }
  return 0;
}