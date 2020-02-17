#pragma once

#include <string>

class Dictionary;

class Classifier {
 public:
  Classifier(Dictionary* dictionary);
  std::string classify(const std::string& filename);

 private:
  Dictionary* dictionary;
};
