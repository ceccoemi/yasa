#pragma once

#include <map>
#include <string>
#include <vector>

class SqliteYasa {
 public:
  explicit SqliteYasa(const std::string& dbName);

  // TODO(ceccoemi): find a better data structure (map is not cache friendly)
  using QueryResult = std::map<std::string, std::vector<std::string>>;

  QueryResult query(const std::string& sqlQuery);

 private:
  std::string dbName;
};
