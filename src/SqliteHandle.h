#pragma once

#include <sqlite3.h>
#include <map>
#include <string>
#include <vector>

class SqliteHandle {
 public:
  explicit SqliteHandle(const std::string& dbName);

  ~SqliteHandle();

  // TODO(ceccoemi): find a better data structure (map is not cache friendly)
  using QueryResult = std::map<std::string, std::vector<std::string>>;

  QueryResult query(const std::string& sqlQuery);

 private:
  sqlite3* db;
};
