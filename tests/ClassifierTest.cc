#include <Classifier.h>
#include <Sentiment.h>
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include <stdexcept>

#include "../src/Sentiment.h"
#include "MockDictionary.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

TEST(classifyTest, classifyEmptyTest) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, positivesCount(_)).Times(0);
  EXPECT_CALL(dictionary, negativesCount(_)).Times(0);
  Classifier classifier(&dictionary);
  ASSERT_THROW(classifier.classify("./resources/fileWithoutWords.txt"),
               std::runtime_error);
}

TEST(ClassifyTest, classifyPositiveTest) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, positivesCount(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(2));
  EXPECT_CALL(dictionary, negativesCount(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(1));
  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify("./resources/positiveFileToClassify.txt"),
            Sentiment::positive);
}

TEST(ClassifyTest, classifyNegativeTest) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, positivesCount(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(1));
  EXPECT_CALL(dictionary, negativesCount(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(2));
  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify("./resources/negativeFileToClassify.txt"),
            Sentiment::negative);
}
