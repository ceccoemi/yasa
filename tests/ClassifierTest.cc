#include <Classifier.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "MockDictionary.h"

using ::testing::_;

TEST(classifyTest, classifyEmptyTest) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, positivesCount(_)).Times(0);
  EXPECT_CALL(dictionary, negativesCount(_)).Times(0);
  Classifier classifier(&dictionary);
  classifier.classify("./resources/fileWithoutWords.txt");
}

TEST(ClassifyTest, classifyPositiveTest) {
  MockDictionary dictionary;
  int numWordsInFile = 5;
  EXPECT_CALL(dictionary, positivesCount(_)).Times(numWordsInFile);
  EXPECT_CALL(dictionary, negativesCount(_)).Times(numWordsInFile);
  Classifier classifier(&dictionary);
  classifier.classify("./resources/positiveFileToClassify.txt");
}

TEST(ClassifyTest, classifyNegativeTest) {
  MockDictionary dictionary;
  int numWordsInFile = 11;
  EXPECT_CALL(dictionary, positivesCount(_)).Times(numWordsInFile);
  EXPECT_CALL(dictionary, negativesCount(_)).Times(numWordsInFile);
  Classifier classifier(&dictionary);
  classifier.classify("./resources/negativeFileToClassify.txt");
}
