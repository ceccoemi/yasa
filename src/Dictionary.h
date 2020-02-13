#pragma once

#include <string>

#include "Sentiment.h"
#include "SqliteYasa.h"

class Dictionary {
 public:
  static Dictionary* getInstance();

  void addWord(const std::string& word, Sentiment sentiment);

  int size();

  void reset();

  int positivesCount();

  int positivesCount(const std::string& word);

  int negativesCount();

  int negativesCount(const std::string& word);

 private:
  Dictionary();

  static Dictionary* instance;
  SqliteYasa db;
};
