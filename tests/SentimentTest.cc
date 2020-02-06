#include <gtest/gtest.h>
#include <Sentiment.h>

TEST(sentimentTest, positiveTest) {
	yasa::Sentiment pos = yasa::Sentiment::positive;
	ASSERT_EQ(pos, 1);
}

TEST(sentimentTest, negativeTest) {
	yasa::Sentiment neg = yasa::Sentiment::negative;
	ASSERT_EQ(neg, 0);
}
