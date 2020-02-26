#include <Dictionary.h>
#include <Sentiment.h>
#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>

#include <string>

class MockDictionary : public Dictionary {
 public:
  MOCK_METHOD2(add, void(const std::string& word, Sentiment sentiment));

  MOCK_METHOD0(size, int());

  MOCK_METHOD0(reset, void());

  MOCK_METHOD0(positivesCount, int());

  MOCK_METHOD0(positivesCountUniques, int());

  MOCK_METHOD1(positivesCount, int(const std::string& word));

  MOCK_METHOD0(negativesCount, int());

  MOCK_METHOD0(negativesCountUniques, int());

  MOCK_METHOD1(negativesCount, int(const std::string& word));
};
