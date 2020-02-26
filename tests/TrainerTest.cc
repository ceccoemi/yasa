#include <Sentiment.h>
#include <Trainer.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "MockDictionary.h"

using ::testing::_;

TEST(trainerTest, trainWithNoWords) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, add(_, _)).Times(0);

  Trainer trainer(&dictionary);
  std::vector<std::string> words{};
  trainer.train(words, Sentiment::positive);
  trainer.train(words, Sentiment::negative);
}

TEST(trainerTest, trainWithThreePositivesWords) {
  MockDictionary dictionary;
  std::vector<std::string> words{"very", "good", "review"};
  EXPECT_CALL(dictionary, add("very", Sentiment::positive)).Times(1);
  EXPECT_CALL(dictionary, add("good", Sentiment::positive)).Times(1);
  EXPECT_CALL(dictionary, add("review", Sentiment::positive)).Times(1);

  Trainer trainer(&dictionary);
  trainer.train(words, Sentiment::positive);
}

TEST(trainerTest, trainWithThreeNegativesWords) {
  MockDictionary dictionary;
  std::vector<std::string> words{"very", "bad", "review"};
  EXPECT_CALL(dictionary, add("very", Sentiment::negative)).Times(1);
  EXPECT_CALL(dictionary, add("bad", Sentiment::negative)).Times(1);
  EXPECT_CALL(dictionary, add("review", Sentiment::negative)).Times(1);

  Trainer trainer(&dictionary);
  trainer.train(words, Sentiment::negative);
}
