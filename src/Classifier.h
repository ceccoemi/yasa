#pragma once

#include <string>

#include "Sentiment.h"

class Dictionary;

class Classifier {
 public:
  Classifier(Dictionary* dictionary);
  Sentiment classify(const std::string& filename);

 private:
  Dictionary* dictionary;
};
