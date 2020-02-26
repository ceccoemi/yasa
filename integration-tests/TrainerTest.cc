#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <SqliteHandler.h>
#include <Trainer.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

class TrainerTest : public ::testing::Test {
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

TEST_F(TrainerTest, trainWithNoWords) {
  Trainer trainer(&dictionary);
  std::vector<std::string> words{};
  trainer.train(words, Sentiment::positive);
  trainer.train(words, Sentiment::negative);
  ASSERT_EQ(dictionary.size(), 0);
}

TEST_F(TrainerTest, trainWithThreePositivesWords) {
  std::vector<std::string> words{"very", "good", "review"};
  Trainer trainer(&dictionary);
  trainer.train(words, Sentiment::positive);
  ASSERT_EQ(dictionary.positivesCount(), 3);
  for (auto& word : words) {
    ASSERT_EQ(dictionary.positivesCount(word), 1);
  }
}

TEST_F(TrainerTest, trainWithThreeNegativesWords) {
  std::vector<std::string> words{"very", "bad", "review"};
  Trainer trainer(&dictionary);
  trainer.train(words, Sentiment::negative);
  ASSERT_EQ(dictionary.negativesCount(), 3);
  for (auto& word : words) {
    ASSERT_EQ(dictionary.negativesCount(word), 1);
  }
}
