#include <DbHandler.h>
#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>
#include <string>

class MockDbHandler : public DbHandler {
 public:
  MOCK_METHOD1(query, DbHandler::QueryResult(const std::string& query));
};
