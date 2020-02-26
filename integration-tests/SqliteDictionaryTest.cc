#include <QueryResult.h>
#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <SqliteHandler.h>
#include <gtest/gtest.h>

class SqliteDictionaryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    handler = new SqliteHandler();
    dictionary = SqliteDictionary<SqliteHandler>(handler);
  }

  virtual void TearDown() { delete handler; }

  SqliteDictionary<SqliteHandler> dictionary;

 private:
  SqliteHandler* handler;
};

TEST_F(SqliteDictionaryTest, sizeOfEmptyDictionary) {
  ASSERT_EQ(dictionary.size(), 0);
}

TEST_F(SqliteDictionaryTest, sizeOfADictionaryWithOneWord) {
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
}

TEST_F(SqliteDictionaryTest, sizeOfASqliteDictionaryTwoWords) {
  ASSERT_EQ(dictionary.size(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.size(), 1);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
}

TEST_F(SqliteDictionaryTest, positivesCount) {
  ASSERT_EQ(dictionary.positivesCount(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 3);
}

TEST_F(SqliteDictionaryTest, positivesCountUniques) {
  ASSERT_EQ(dictionary.positivesCountUniques(), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCountUniques(), 1);
  dictionary.add("split", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCountUniques(), 2);
}

TEST_F(SqliteDictionaryTest, negativesCount) {
  ASSERT_EQ(dictionary.negativesCount(), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 3);
}

TEST_F(SqliteDictionaryTest, negativesCountUniques) {
  ASSERT_EQ(dictionary.negativesCountUniques(), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCountUniques(), 1);
  dictionary.add("split", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCountUniques(), 2);
}

TEST_F(SqliteDictionaryTest, positivesCountOfAWord) {
  ASSERT_EQ(dictionary.positivesCount("banana"), 0);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 1);
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount("banana"), 3);
  ASSERT_EQ(dictionary.positivesCount("apple"), 0);
}

TEST_F(SqliteDictionaryTest, negativesCountOfAWord) {
  ASSERT_EQ(dictionary.negativesCount("banana"), 0);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 1);
  dictionary.add("banana", Sentiment::negative);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount("banana"), 3);
  ASSERT_EQ(dictionary.negativesCount("apple"), 0);
}

TEST_F(SqliteDictionaryTest, resetDictionary) {
  dictionary.add("banana", Sentiment::positive);
  dictionary.add("banana", Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 2);
  dictionary.reset();
  ASSERT_EQ(dictionary.size(), 0);
}
