#pragma once

#include <string>
#include <vector>

#include "Sentiment.h"

class Dictionary;

class Classifier {
 public:
  Classifier(Dictionary* dictionary);

  Sentiment classify(const std::vector<std::string>& words);

 private:
  Dictionary* dictionary;
};
