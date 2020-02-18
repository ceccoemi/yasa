#pragma once

#include <string>
#include <vector>

#include "Dictionary.h"
#include "Sentiment.h"

class Trainer {
 public:
  Trainer(Dictionary* dictionary);

  void train(const std::vector<std::string>& words, Sentiment sentiment);

 private:
  Dictionary* dictionary;
};
