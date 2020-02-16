#include <SqliteDictionary.h>
#include <gtest/gtest.h>
#include <train.h>

TEST(trainTest, trainWithNoDirectories) {
  train("", "");
  SqliteDictionary *dictionary = SqliteDictionary::getInstance();
  ASSERT_EQ(dictionary->size(), 0);
}

TEST(trainTest, trainWithOnlyNegativesDir) {
  train("./resources/neg/", "");
  SqliteDictionary *dictionary = SqliteDictionary::getInstance();
  ASSERT_GT(dictionary->negativesCount(), 0);
  ASSERT_EQ(dictionary->positivesCount(), 0);
  dictionary->reset();
}

TEST(trainTest, trainWithOnlyPositivesDir) {
  train("", "./resources/pos");
  SqliteDictionary *dictionary = SqliteDictionary::getInstance();
  ASSERT_EQ(dictionary->negativesCount(), 0);
  ASSERT_GT(dictionary->positivesCount(), 0);
  dictionary->reset();
}
