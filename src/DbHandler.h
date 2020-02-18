#pragma once

#include <map>
#include <string>
#include <vector>

class DbHandler {
 public:
  virtual ~DbHandler() {}  // LCOV_EXCL_LINE

  using QueryResult = std::map<std::string, std::vector<std::string>>;

  virtual QueryResult query(const std::string& query) = 0;
};
