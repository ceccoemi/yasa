#include <gtest/gtest.h>
#include <Vocabulary.h>

TEST(vocabularyTest, addWord) {
	yasa::Vocabulary vocabulary;
	vocabulary.addWord("banana", yasa::Sentiment::positive);
	int actual = vocabulary.getPositiveCount("banana");
	ASSERT_EQ(actual, 1);
}
