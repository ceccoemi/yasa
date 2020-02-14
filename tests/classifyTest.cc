#include <Dictionary.h>
#include <classify.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <train.h>

#include <string>

class ClassifyTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    dictionary = Dictionary::getInstance();
    train("./resources/neg", "./resources/pos");
  };

  virtual void TearDown() { dictionary->reset(); }
  Dictionary *dictionary;
};

TEST(classifyTest, classifyEmptyTest) {
  std::string actual = classify("./resources/fileWithoutWords.txt");
  std::string expected = "The given file does not contain words.";
  ASSERT_EQ(actual, expected);
}

TEST_F(ClassifyTest, classifyPositiveTest) {
  std::string actual = classify("./resources/positiveFileToClassify.txt");
  std::string expected = "positive";
  ASSERT_EQ(actual, expected);
}

TEST_F(ClassifyTest, classifyNegativeTest) {
  std::string actual = classify("./resources/negativeFileToClassify.txt");
  std::string expected = "negative";
  ASSERT_EQ(actual, expected);
}
