#pragma once

#include <string>

class FileReader {
 public:
  virtual ~FileReader() {}

  virtual std::string read() = 0;
};
