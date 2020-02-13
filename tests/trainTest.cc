#include "../src/train.h"

#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "../src/Dictionary.h"

TEST(trainTest, trainWithNoDirectories) {
  train("", "");
  Dictionary *dictionary = Dictionary::getInstance();
  ASSERT_EQ(dictionary->size(), 0);
}

TEST(trainTest, trainWithOnlyNegativesDir) {
  train("./resources/neg/", "");
  Dictionary *dictionary = Dictionary::getInstance();
  ASSERT_GT(dictionary->negativesCount(), 0);
  ASSERT_EQ(dictionary->positivesCount(), 0);
  dictionary->reset();
}

TEST(trainTest, trainWithOnlyPositivesDir) {
  train("", "./resources/pos");
  Dictionary *dictionary = Dictionary::getInstance();
  ASSERT_EQ(dictionary->negativesCount(), 0);
  ASSERT_GT(dictionary->positivesCount(), 0);
  dictionary->reset();
}
