#include "../src/Dictionary.h"

#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

#include "../src/Sentiment.h"

class DictionaryTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dictionary = Dictionary::getInstance();
	}

	virtual void TearDown() {
		dictionary->reset();
	}

	Dictionary *dictionary;
};

TEST_F(DictionaryTest, testSingleton) {
	Dictionary *d1 = Dictionary::getInstance();
	Dictionary *d2 = Dictionary::getInstance();
	ASSERT_EQ(d1, d2);
}

TEST_F(DictionaryTest, sizeOfEmptyDictionary) {
	ASSERT_EQ(dictionary->size(), 0);
}

TEST_F(DictionaryTest, sizeOfADictionaryWithOneWord) {
	ASSERT_EQ(dictionary->size(), 0);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->size(), 1);
}

TEST_F(DictionaryTest, sizeOfADictionaryTwoWords) {
	ASSERT_EQ(dictionary->size(), 0);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->size(), 1);
	dictionary->addWord("banana", Sentiment::negative);
	ASSERT_EQ(dictionary->size(), 2);
}

TEST_F(DictionaryTest, positivesCount) {
	ASSERT_EQ(dictionary->positivesCount(), 0);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->positivesCount(), 1);
	dictionary->addWord("banana", Sentiment::positive);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->positivesCount(), 3);
}

TEST_F(DictionaryTest, negativesCount) {
	ASSERT_EQ(dictionary->negativesCount(), 0);
	dictionary->addWord("banana", Sentiment::negative);
	ASSERT_EQ(dictionary->negativesCount(), 1);
	dictionary->addWord("banana", Sentiment::negative);
	dictionary->addWord("banana", Sentiment::negative);
	ASSERT_EQ(dictionary->negativesCount(), 3);
}

TEST_F(DictionaryTest, positivesCountOfAWord) {
	ASSERT_EQ(dictionary->positivesCount("banana"), 0);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->positivesCount("banana"), 1);
	dictionary->addWord("banana", Sentiment::positive);
	dictionary->addWord("banana", Sentiment::positive);
	ASSERT_EQ(dictionary->positivesCount("banana"), 3);
}

TEST_F(DictionaryTest, negativesCountOfAWord) {
	ASSERT_EQ(dictionary->negativesCount("banana"), 0);
	dictionary->addWord("banana", Sentiment::negative);
	ASSERT_EQ(dictionary->negativesCount("banana"), 1);
	dictionary->addWord("banana", Sentiment::negative);
	dictionary->addWord("banana", Sentiment::negative);
	ASSERT_EQ(dictionary->negativesCount("banana"), 3);
}
