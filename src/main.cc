#include <iostream>
#include <string>
#include <vector>

#include "ArgumentParser.h"

int main(int argc, const char *argv[]) {
  ArgumentParser argumentParser(argc,
                                std::vector<std::string>(argv, argv + argc));
  std::cout << argumentParser.main() << '\n';
  return 0;
}
