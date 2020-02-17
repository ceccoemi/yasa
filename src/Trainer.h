#pragma once

#include <string>

#include "Sentiment.h"

class Dictionary;

class Trainer {
 public:
  Trainer(Dictionary* dictionary);

  void train(const std::string& negativesDir, const std::string& positivesDir);

 private:
  Dictionary* dictionary;

  void updateDictionary(const std::string& dir, Sentiment sentiment);
};
