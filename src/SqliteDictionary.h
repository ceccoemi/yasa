#pragma once

#include <string>

#include "DbHandler.h"
#include "Dictionary.h"
#include "Sentiment.h"

class SqliteDictionary : public Dictionary {
 public:
  ~SqliteDictionary(){};

  SqliteDictionary(DbHandler* dbHandler);

  void add(const std::string& word, Sentiment sentiment);

  int size();

  void reset();

  int positivesCount();

  int positivesCount(const std::string& word);

  int negativesCount();

  int negativesCount(const std::string& word);

 private:
  DbHandler* db;
};
