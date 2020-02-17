#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

class SqliteDictionaryTest : public ::testing::Test {
 protected:
  virtual void SetUp() { dictionary = SqliteDictionary::getInstance(); }

  virtual void TearDown() { dictionary->reset(); }

  SqliteDictionary *dictionary;
};

TEST_F(SqliteDictionaryTest, testSingleton) {
  SqliteDictionary *d1 = SqliteDictionary::getInstance();
  SqliteDictionary *d2 = SqliteDictionary::getInstance();
  ASSERT_EQ(d1, d2);
}

TEST_F(SqliteDictionaryTest, sizeOfEmptySqliteDictionary) {
  ASSERT_EQ(dictionary->size(), 0);
}

TEST_F(SqliteDictionaryTest, sizeOfASqliteDictionaryWithOneWord) {
  ASSERT_EQ(dictionary->size(), 0);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->size(), 1);
}

TEST_F(SqliteDictionaryTest, sizeOfASqliteDictionaryTwoWords) {
  ASSERT_EQ(dictionary->size(), 0);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->size(), 1);
  dictionary->add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary->size(), 2);
}

TEST_F(SqliteDictionaryTest, positivesCount) {
  ASSERT_EQ(dictionary->positivesCount(), 0);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->positivesCount(), 1);
  dictionary->add("banana", Sentiment::positive);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->positivesCount(), 3);
}

TEST_F(SqliteDictionaryTest, negativesCount) {
  ASSERT_EQ(dictionary->negativesCount(), 0);
  dictionary->add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary->negativesCount(), 1);
  dictionary->add("banana", Sentiment::negative);
  dictionary->add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary->negativesCount(), 3);
}

TEST_F(SqliteDictionaryTest, positivesCountOfAWord) {
  ASSERT_EQ(dictionary->positivesCount("banana"), 0);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->positivesCount("banana"), 1);
  dictionary->add("banana", Sentiment::positive);
  dictionary->add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary->positivesCount("banana"), 3);
  ASSERT_EQ(dictionary->positivesCount("apple"), 0);
}

TEST_F(SqliteDictionaryTest, negativesCountOfAWord) {
  ASSERT_EQ(dictionary->negativesCount("banana"), 0);
  dictionary->add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary->negativesCount("banana"), 1);
  dictionary->add("banana", Sentiment::negative);
  dictionary->add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary->negativesCount("banana"), 3);
  ASSERT_EQ(dictionary->negativesCount("apple"), 0);
}
