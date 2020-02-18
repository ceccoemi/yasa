#include "TextFileReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

TextFileReader::TextFileReader(const std::string& fileName)
    : filePath(fileName) {
  if (!fs::exists(filePath)) {
    throw std::runtime_error(filePath.u8string() + " does not exist");
  }
  if (!fs::is_regular_file(filePath)) {
    throw std::runtime_error(filePath.u8string() + " is not a regular file");
  }
}

std::string TextFileReader::read() {
  std::ifstream ifs(filePath);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}
