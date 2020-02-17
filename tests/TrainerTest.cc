#include <Sentiment.h>
#include <Trainer.h>
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "MockDictionary.h"

using ::testing::_;
using ::testing::AtLeast;

TEST(trainerTest, trainWithNoDirectories) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, add(_, _)).Times(0);
  Trainer trainer(&dictionary);
  trainer.train("", "");
}

TEST(trainerTest, trainWithOnlyNegativesDir) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, add(_, Sentiment::negative)).Times(AtLeast(1));
  Trainer trainer(&dictionary);
  trainer.train("./resources/neg/", "");
}

TEST(trainerTest, trainWithOnlyPositivesDir) {
  MockDictionary dictionary;
  EXPECT_CALL(dictionary, add(_, Sentiment::positive)).Times(AtLeast(1));
  Trainer trainer(&dictionary);
  trainer.train("", "./resources/pos/");
}
