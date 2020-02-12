#pragma once

#include <map>
#include <string>
#include <vector>

class SqliteYasa {
 public:
  SqliteYasa(std::string dbName);

  std::string getDbPath();

  // TODO find a better data structure (map is not cache friendly)
  typedef std::map<std::string, std::vector<std::string>> QueryResult;

  QueryResult query(std::string sqlQuery);

 private:
  std::string dbName;
};
