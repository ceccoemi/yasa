#include <iostream>
#include <string>

#include "ArgumentParser.h"

int main(int argc, const char *argv[]) {
  ArgumentParser argumentParser(argc, argv);
  argumentParser.parseArgs();
  std::cout << argumentParser.main() << std::endl;

  return 0;
}
