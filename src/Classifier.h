#pragma once

#include <string>
#include <vector>

#include "Dictionary.h"
#include "Sentiment.h"

class Classifier {
 public:
  Classifier(Dictionary* dictionary);

  Sentiment classify(const std::vector<std::string>& words);

 private:
  Dictionary* dictionary;
};
