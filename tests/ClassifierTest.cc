#include <Classifier.h>
#include <Sentiment.h>
#include <gmock/gmock-actions.h>
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "MockDictionary.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

TEST(ClassifyTest, classifyWithNoWordsReturnNegative) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, positivesCountUniques()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(dictionary, negativesCountUniques()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(dictionary, positivesCount(_)).Times(0);
  EXPECT_CALL(dictionary, negativesCount(_)).Times(0);

  Classifier classifier(&dictionary);
  std::vector<std::string> words{};
  classifier.classify(words);
}

TEST(ClassifyTest, classifyPositive) {
  MockDictionary dictionary;
  std::vector<std::string> words{"very", "good", "review"};
  EXPECT_CALL(dictionary, positivesCountUniques()).Times(1).WillOnce(Return(3));
  EXPECT_CALL(dictionary, negativesCountUniques()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(dictionary, positivesCount("very")).Times(1).WillOnce(Return(1));
  EXPECT_CALL(dictionary, positivesCount("good")).Times(1).WillOnce(Return(1));
  EXPECT_CALL(dictionary, positivesCount("review"))
      .Times(1)
      .WillOnce(Return(1));
  EXPECT_CALL(dictionary, negativesCount(_)).Times(3).WillRepeatedly(Return(0));

  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify(words), Sentiment::positive);
}

TEST(ClassifyTest, classifyNegative) {
  MockDictionary dictionary;
  std::vector<std::string> words{"very", "bad", "review"};
  EXPECT_CALL(dictionary, positivesCountUniques()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(dictionary, negativesCountUniques()).Times(1).WillOnce(Return(3));
  EXPECT_CALL(dictionary, negativesCount("very")).Times(1).WillOnce(Return(1));
  EXPECT_CALL(dictionary, negativesCount("bad")).Times(1).WillOnce(Return(1));
  EXPECT_CALL(dictionary, negativesCount("review"))
      .Times(1)
      .WillOnce(Return(1));
  EXPECT_CALL(dictionary, positivesCount(_)).Times(3).WillRepeatedly(Return(0));

  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify(words), Sentiment::negative);
}
