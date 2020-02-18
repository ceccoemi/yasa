#pragma once

#include <sqlite3.h>
#include <string>

#include "DbHandler.h"

class SqliteHandle : public DbHandler {
 public:
  explicit SqliteHandle(const std::string& dbName);

  SqliteHandle();

  ~SqliteHandle();

  QueryResult query(const std::string& sqlQuery);

 private:
  sqlite3* db;

  void openDb(const char* dbName);
};
