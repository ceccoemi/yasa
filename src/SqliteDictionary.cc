#include "SqliteDictionary.h"

#include <vector>

#include "DbHandler.h"

SqliteDictionary::SqliteDictionary(DbHandler* dbHandler) : db(dbHandler) {
  db->query("CREATE TABLE IF NOT EXISTS positives(word VARCHAR(30));");
  db->query("CREATE TABLE IF NOT EXISTS negatives(word VARCHAR(30));");
}

void SqliteDictionary::add(const std::string& word, Sentiment sentiment) {
  std::string table =
      sentiment == Sentiment::positive ? "positives" : "negatives";
  db->query("INSERT INTO " + table + "(word) VALUES('" + word + "');");
}

int SqliteDictionary::size() { return positivesCount() + negativesCount(); }

void SqliteDictionary::reset() {
  db->query(
      "DELETE FROM positives;"
      "DELETE FROM negatives;"
      "VACUUM;");
}

int SqliteDictionary::positivesCount() {
  DbHandler::QueryResult result = db->query("SELECT COUNT(*) FROM positives;");
  return std::stoi(result["COUNT(*)"].front());
}

int SqliteDictionary::positivesCount(const std::string& word) {
  DbHandler::QueryResult result =
      db->query("SELECT COUNT(*) FROM positives WHERE word = '" + word + "';");
  return std::stoi(result["COUNT(*)"].front());
}

int SqliteDictionary::negativesCount() {
  DbHandler::QueryResult result = db->query("SELECT COUNT(*) FROM negatives;");
  return std::stoi(result["COUNT(*)"].front());
}

int SqliteDictionary::negativesCount(const std::string& word) {
  DbHandler::QueryResult result =
      db->query("SELECT COUNT(*) FROM negatives WHERE word = '" + word + "';");
  return std::stoi(result["COUNT(*)"].front());
}
