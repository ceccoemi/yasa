#include "Dictionary.h"

#include <vector>

Dictionary* Dictionary::instance = nullptr;

Dictionary::Dictionary() : db("yasa.db") {
  db.query("CREATE TABLE IF NOT EXISTS positives(word VARCHAR(30));");
  db.query("CREATE TABLE IF NOT EXISTS negatives(word VARCHAR(30));");
}

Dictionary* Dictionary::getInstance() {
  if (instance == nullptr) {
    instance = new Dictionary();
  }
  return instance;
}

void Dictionary::addWord(std::string word, Sentiment sentiment) {
  std::string table =
      sentiment == Sentiment::positive ? "positives" : "negatives";
  db.query("INSERT INTO " + table + "(word) VALUES('" + word + "');");
}

int Dictionary::size() { return positivesCount() + negativesCount(); }

void Dictionary::reset() {
  db.query(
      "DELETE FROM positives;"
      "DELETE FROM negatives;"
      "VACUUM;");
}

int Dictionary::positivesCount() {
  SqliteYasa::QueryResult queryResult =
      db.query("SELECT COUNT(*) AS positives_count FROM positives;");
  return std::stoi(queryResult["positives_count"].front());
}

int Dictionary::positivesCount(std::string word) {
  SqliteYasa::QueryResult queryResult = db.query(
      "SELECT COUNT(*) AS positives_count FROM positives "
      "WHERE word = '" +
      word + "';");
  return std::stoi(queryResult["positives_count"].front());
}

int Dictionary::negativesCount() {
  SqliteYasa::QueryResult queryResult =
      db.query("SELECT COUNT(*) AS negatives_count FROM negatives;");
  return std::stoi(queryResult["negatives_count"].front());
}

int Dictionary::negativesCount(std::string word) {
  SqliteYasa::QueryResult queryResult = db.query(
      "SELECT COUNT(*) AS negatives_count FROM negatives "
      "WHERE word = '" +
      word + "';");
  return std::stoi(queryResult["negatives_count"].front());
}
