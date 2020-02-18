#include <gtest/gtest.h>
#include <preprocessing.h>
#include <string>
#include <vector>

TEST(PreprocessingTest, emptyTest) {
  std::vector<std::string> actual = extractWords("");
  std::vector<std::string> expected{};
  ASSERT_EQ(actual, expected);
}

TEST(PreprocessingTest, oneLetterText) {
  std::vector<std::string> actual = extractWords("O");
  std::vector<std::string> expected{"O"};
  ASSERT_EQ(actual, expected);
}

TEST(PreprocessingTest, extractWordsWithSpaces) {
  std::vector<std::string> actual =
      extractWords("  yasa is   the\nbest\r\nsoftware\tin\vthe\fworld   ");
  std::vector<std::string> expected = {"yasa", "best", "software", "world"};
  ASSERT_EQ(actual, expected);
}

TEST(PreprocessingTest, extractWordsWithPunctuation) {
  std::vector<std::string> actual =
      extractWords("  yasa. is,the!best:software;;in the' world?   ");
  std::vector<std::string> expected = {"yasa", "best", "software", "world"};
  ASSERT_EQ(actual, expected);
}
