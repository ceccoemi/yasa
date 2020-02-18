#pragma once

#include <sqlite3.h>
#include <string>

#include "DbHandler.h"

class SqliteHandler : public DbHandler {
 public:
  explicit SqliteHandler(const std::string& dbName);

  SqliteHandler();

  ~SqliteHandler();

  QueryResult query(const std::string& sqlQuery);

 private:
  sqlite3* db;

  void openDb(const char* dbName);
};
