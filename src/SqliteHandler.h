#pragma once

#include <sqlite3.h>
#include <map>
#include <string>
#include <vector>

class SqliteHandler {
 public:
  explicit SqliteHandler(const std::string& dbName);

  SqliteHandler();

  ~SqliteHandler();

  using QueryResult = std::map<std::string, std::vector<std::string>>;

  QueryResult query(const std::string& sqlQuery);

 private:
  sqlite3* db;

  void openDb(const char* dbName);
};
