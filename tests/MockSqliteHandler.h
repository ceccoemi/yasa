#include <QueryResult.h>
#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>

#include <string>

class MockSqliteHandler {
 public:
  MOCK_METHOD1(query, QueryResult(const std::string& query));
};
