#include <ArgumentParser.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <version.h>

#include <functional>
#include <string>
#include <vector>

class ArgumentParserTest : public ::testing::Test {
 protected:
  std::function<std::string(const std::string& negDir,
                            const std::string& posDir)>
      trainFunc = [](auto x, auto y) { return "neg: " + x + " pos: " + y; };
  std::function<std::string(const std::string& fileName)> classifyFunc =
      [](auto x) { return "classify " + x; };
};

TEST_F(ArgumentParserTest, showUsageWithNoArgs) {
  int numArgs{1};
  std::vector<std::string> argValues{"./yasa"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, showUsageWithFirstArgumentWrong) {
  int numArgs{2};
  std::vector<std::string> argValues{"./yasa", "hola"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkFirstArgumentWhenItIsHelp) {
  int numArgs{2};
  std::vector<std::string> argValues{"./yasa", "--help"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkFirstArgumentWhenItIsTrain) {
  int numArgs{2};
  std::vector<std::string> argValues{"./yasa", "train"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkFirstArgumentWhenItIsClassify) {
  int numArgs{2};
  std::vector<std::string> argValues{"./yasa", "classify"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkPositivesArgumentAfterTrain) {
  int numArgs{3};
  std::vector<std::string> argValues{"./yasa", "train", "-p"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkPositivesArgumentAfterTrainExt) {
  int numArgs{3};
  std::vector<std::string> argValues{"./yasa", "train", "--positives"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkNegativesArgumentAfterTrainExt) {
  int numArgs{3};
  std::vector<std::string> argValues{"./yasa", "train", "--negatives"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkFirstArgumentAfterClassify) {
  int numArgs{3};
  std::vector<std::string> argValues{"./yasa", "classify", "-f"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainPositives) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "train", "-p", "aPositivesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg:  pos: aPositivesDir"};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainPositivesExtended) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "train", "--positives",
                                     "aPositivesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg:  pos: aPositivesDir"};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainNegatives) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "train", "-n", "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg: aNegativesDir pos: "};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainNegativesExtended) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "train", "--negatives",
                                     "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg: aNegativesDir pos: "};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainPositivesAndNegatives) {
  int numArgs{6};
  std::vector<std::string> argValues{"./yasa",        "train", "-p",
                                     "aPositivesDir", "-n",    "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg: aNegativesDir pos: aPositivesDir"};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainPositivesAndNegativesExtended) {
  int numArgs{6};
  std::vector<std::string> argValues{"./yasa",      "train",
                                     "--positives", "aPositivesDir",
                                     "--negatives", "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg: aNegativesDir pos: aPositivesDir"};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, mainTrainNegativesAndPositives) {
  int numArgs{6};
  std::vector<std::string> argValues{"./yasa",        "train", "-n",
                                     "aNegativesDir", "-p",    "aPositivesDir"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected{"neg: aNegativesDir pos: aPositivesDir"};
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkClassify) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "classify", "-f",
                                     "aFileToClassify"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = "classify aFileToClassify";
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkClassifyHelp) {
  int numArgs{4};
  std::vector<std::string> argValues{"./yasa", "classify", "-h",
                                     "aFileToClassify"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = ArgumentParser::classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST_F(ArgumentParserTest, checkVersion) {
  int numArgs{2};
  std::vector<std::string> argValues{"./yasa", "-v"};
  ArgumentParser argumentParser(numArgs, argValues, trainFunc, classifyFunc);
  std::string actual = argumentParser.main().second;
  std::string expected = "yasa version " + std::string(VERSION);
  ASSERT_EQ(actual, expected);
}
