#include <Sentiment.h>
#include <gtest/gtest.h>

TEST(SentimentTest, positiveDifferentFromNegative) {
  ASSERT_NE(Sentiment::positive, Sentiment::negative);
}

TEST(SentimentTest, positiveEqualsToPositive) {
  ASSERT_EQ(Sentiment::positive, Sentiment::positive);
}

TEST(SentimentTest, positiveEqualsToNegative) {
  ASSERT_EQ(Sentiment::negative, Sentiment::negative);
}
