#include <iostream>
#include <string>
#include <vector>

#include "ArgumentParser.h"

int main(int argc, const char *argv[]) {
  ArgumentParser argumentParser(
      argc, std::vector<std::string>(argv, argv + argc),
      [](auto x, auto y) { return "Training ... Done"; },
      [](auto x) { return "Classifying .. Done"; });
  std::cout << argumentParser.main() << '\n';
  return 0;
}
