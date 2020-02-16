#include "SqliteDictionary.h"

#include <experimental/filesystem>
#include <vector>

namespace fs = std::experimental::filesystem;

SqliteDictionary* SqliteDictionary::instance = nullptr;

SqliteDictionary* SqliteDictionary::getInstance() {
  if (instance == nullptr) {
    instance = new SqliteDictionary();
  }
  return instance;
}

void SqliteDictionary::add(const std::string& word, Sentiment sentiment) {
  std::string table =
      sentiment == Sentiment::positive ? "positives" : "negatives";
  db.query("INSERT INTO " + table + "(word) VALUES('" + word + "');");
}

int SqliteDictionary::size() { return positivesCount() + negativesCount(); }

void SqliteDictionary::reset() {
  db.query(
      "DELETE FROM positives;"
      "DELETE FROM negatives;"
      "VACUUM;");
}

int SqliteDictionary::positivesCount() {
  SqliteHandle::QueryResult queryResult =
      db.query("SELECT COUNT(*) AS positives_count FROM positives;");
  return std::stoi(queryResult["positives_count"].front());
}

int SqliteDictionary::positivesCount(const std::string& word) {
  SqliteHandle::QueryResult queryResult = db.query(
      "SELECT COUNT(*) AS positives_count FROM positives "
      "WHERE word = '" +
      word + "';");
  return std::stoi(queryResult["positives_count"].front());
}

int SqliteDictionary::negativesCount() {
  SqliteHandle::QueryResult queryResult =
      db.query("SELECT COUNT(*) AS negatives_count FROM negatives;");
  return std::stoi(queryResult["negatives_count"].front());
}

int SqliteDictionary::negativesCount(const std::string& word) {
  SqliteHandle::QueryResult queryResult = db.query(
      "SELECT COUNT(*) AS negatives_count FROM negatives "
      "WHERE word = '" +
      word + "';");
  return std::stoi(queryResult["negatives_count"].front());
}

SqliteDictionary::SqliteDictionary() : db("yasa.db") {
  db.query("CREATE TABLE IF NOT EXISTS positives(word VARCHAR(30));");
  db.query("CREATE TABLE IF NOT EXISTS negatives(word VARCHAR(30));");
}
