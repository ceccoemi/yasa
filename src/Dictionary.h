#pragma once

#include <string>

#include "Sentiment.h"

class Dictionary {
 public:
  virtual ~Dictionary() {}

  virtual void add(const std::string& word, Sentiment sentiment) = 0;

  virtual int size() = 0;

  virtual void reset() = 0;

  virtual int positivesCount() = 0;

  virtual int positivesCountUniques() = 0;

  virtual int positivesCount(const std::string& word) = 0;

  virtual int negativesCount() = 0;

  virtual int negativesCountUniques() = 0;

  virtual int negativesCount(const std::string& word) = 0;
};
