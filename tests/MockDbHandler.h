#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>
#include <string>

#include <DbHandler.h>

class MockDbHandler : public DbHandler {
 public:
  MOCK_METHOD1(query, DbHandler::QueryResult(const std::string& query));
};
