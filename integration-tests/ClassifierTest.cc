#include <Classifier.h>
#include <Sentiment.h>
#include <SqliteDictionary.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(ClassifyTest, classifyWithNoWordsReturnNegative) {
  SqliteHandler handler;
  SqliteDictionary<SqliteHandler> dictionary(&handler);
  Classifier classifier(&dictionary);
  std::vector<std::string> words{};
  ASSERT_EQ(classifier.classify(words), Sentiment::negative);
}

TEST(ClassifyTest, classifyPositive) {
  SqliteHandler handler;
  SqliteDictionary<SqliteHandler> dictionary(&handler);
  std::vector<std::string> words{"very", "good", "review"};
  for (auto& word : words) {
    dictionary.add(word, Sentiment::positive);
  }
  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify(words), Sentiment::positive);
}

TEST(ClassifyTest, classifyNegative) {
  SqliteHandler handler;
  SqliteDictionary<SqliteHandler> dictionary(&handler);
  std::vector<std::string> words{"very", "bad", "review"};
  for (auto& word : words) {
    dictionary.add(word, Sentiment::negative);
  }
  Classifier classifier(&dictionary);
  ASSERT_EQ(classifier.classify(words), Sentiment::negative);
}
