#pragma once

#include <experimental/filesystem>

#include "FileReader.h"

namespace fs = std::experimental::filesystem;

class TextFileReader : public FileReader {
 public:
  TextFileReader(const std::string& fileName);

  std::string read();

 private:
  fs::path filePath;
};
