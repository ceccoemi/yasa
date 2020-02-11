#include "../src/fileProcessing.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(fileProcessingTest, emptyTest) {
	std::vector<std::string> actual = tokenize("");
	std::vector<std::string> expected { };
	ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, oneLetterText) {
	std::vector<std::string> actual = tokenize("O");
	std::vector<std::string> expected { "O" };
	ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, tokenizeWithSpaces) {
	std::vector<std::string> actual = tokenize(
			"yasa is   the\nbest\r\nsoftware\tin\vthe\fworld");
	std::vector<std::string> expected = { "yasa", "is", "the", "best",
			"software", "in", "the", "world" };
	ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, tokenizeWithPunctuation) {
	std::vector<std::string> actual = tokenize(
			"yasa. is,the!best:software;;in the' world?");
	std::vector<std::string> expected = { "yasa", ".", "is", ",", "the", "!",
			"best", ":", "software", ";", ";", "in", "the", "'", "world", "?" };
	ASSERT_EQ(actual, expected);
}

