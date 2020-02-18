#pragma once

#include <string>

#include "Dictionary.h"
#include "Sentiment.h"
#include "SqliteHandler.h"

template <class Handler>  // template needed for mocking purposes
class SqliteDictionary : public Dictionary {
 public:
  SqliteDictionary(Handler* db) : db(db) {
    db->query("CREATE TABLE IF NOT EXISTS positives(word VARCHAR(30));");
    db->query("CREATE TABLE IF NOT EXISTS negatives(word VARCHAR(30));");
  }

  void add(const std::string& word, Sentiment sentiment) {
    std::string table =
        sentiment == Sentiment::positive ? "positives" : "negatives";
    db->query("INSERT INTO " + table + "(word) VALUES('" + word + "');");
  }

  int size() { return positivesCount() + negativesCount(); }

  void reset() {
    db->query(
        "DELETE FROM positives;"
        "DELETE FROM negatives;"
        "VACUUM;");
  }

  int positivesCount() {
    SqliteHandler::QueryResult result =
        db->query("SELECT COUNT(*) FROM positives;");
    return std::stoi(result["COUNT(*)"].front());
  }

  int positivesCount(const std::string& word) {
    SqliteHandler::QueryResult result = db->query(
        "SELECT COUNT(*) FROM positives WHERE word = '" + word + "';");
    return std::stoi(result["COUNT(*)"].front());
  }

  int negativesCount() {
    SqliteHandler::QueryResult result =
        db->query("SELECT COUNT(*) FROM negatives;");
    return std::stoi(result["COUNT(*)"].front());
  }

  int negativesCount(const std::string& word) {
    SqliteHandler::QueryResult result = db->query(
        "SELECT COUNT(*) FROM negatives WHERE word = '" + word + "';");
    return std::stoi(result["COUNT(*)"].front());
  }

 private:
  Handler* db;
};
