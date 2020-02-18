#pragma once

#include "QueryResult.h"

#include <sqlite3.h>

class SqliteHandler {
 public:
  explicit SqliteHandler(const std::string& dbName);

  SqliteHandler();

  ~SqliteHandler();

  QueryResult query(const std::string& sqlQuery);

 private:
  sqlite3* db;

  void openDb(const char* dbName);
};
