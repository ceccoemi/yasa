#include "../src/fileProcessing.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(fileProcessingTest, emptyTest) {
  std::vector<std::string> actual = extractWords("");
  std::vector<std::string> expected{};
  ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, oneLetterText) {
  std::vector<std::string> actual = extractWords("O");
  std::vector<std::string> expected{"O"};
  ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, extractWordsWithSpaces) {
  std::vector<std::string> actual =
      extractWords("  yasa is   the\nbest\r\nsoftware\tin\vthe\fworld   ");
  std::vector<std::string> expected = {"yasa", "best", "software", "world"};
  ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, extractWordsWithPunctuation) {
  std::vector<std::string> actual =
      extractWords("  yasa. is,the!best:software;;in the' world?   ");
  std::vector<std::string> expected = {"yasa", "best", "software", "world"};
  ASSERT_EQ(actual, expected);
}

TEST(fileProcessingTest, extractTextFromFile) {
  std::string actual = extractText("./resources/test.txt");
  std::string expected = "THIS IS A LINE\nTHIS IS ANOTHER LINE";
  ASSERT_EQ(actual, expected);
}
