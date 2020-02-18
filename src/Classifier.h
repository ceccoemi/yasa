#pragma once

#include <string>

#include "Dictionary.h"
#include "Sentiment.h"

class Classifier {
 public:
  Classifier(Dictionary* dictionary);

  Sentiment classify(const std::string& filename);

 private:
  Dictionary* dictionary;
};
