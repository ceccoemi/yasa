#include <ArgumentParser.h>
#include <gtest/gtest.h>
#include <version.h>

#include <string>

TEST(ArgumentParserTest, checkGlobalUsageMessage) {
  std::string expected = ArgumentParser::globalUsageMessage;
  std::string actual{"Usage Message."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkTrainUsageMessage) {
  std::string expected = ArgumentParser::trainUsageMessage;
  std::string actual{"Train Usage Message."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkClassifyUsageMessage) {
  std::string expected = ArgumentParser::classifyUsageMessage;
  std::string actual{"Classify Usage Message."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithNoArgs) {
  int numArgs{1};
  const char *argValues[numArgs] = {"./yasa"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithFirstArgumentWrong) {
  int numArgs{2};
  const char *argValues[numArgs] = {"./yasa", "hola"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsHelp) {
  int numArgs{2};
  const char *argValues[numArgs] = {"./yasa", "--help"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.globalUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsTrain) {
  int numArgs{2};
  const char *argValues[numArgs] = {"./yasa", "train"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsClassify) {
  int numArgs{2};
  const char *argValues[numArgs] = {"./yasa", "classify"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkPositivesArgumentAfterTrain) {
  int numArgs{3};
  const char *argValues[numArgs] = {"./yasa", "train", "-p"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkNegativesArgumentAfterTrain) {
  int numArgs{3};
  const char *argValues[numArgs] = {"./yasa", "train", "-n"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.trainUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentAfterClassify) {
  int numArgs{3};
  const char *argValues[numArgs] = {"./yasa", "classify", "-f"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = argumentParser.classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainPositives) {
  int numArgs{4};
  const char *argValues[numArgs] = {"./yasa", "train", "-p", "aPositivesDir"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected{"Training."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainNegatives) {
  int numArgs{4};
  const char *argValues[numArgs] = {"./yasa", "train", "-n", "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected{"Training."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainPositivesAndNegatives) {
  int numArgs{6};
  const char *argValues[numArgs] = {"./yasa",        "train", "-p",
                                    "aPositivesDir", "-n",    "aNegativesDir"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected{"Training."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainNegativesAndPositives) {
  int numArgs{6};
  const char *argValues[numArgs] = {"./yasa",        "train", "-n",
                                    "aNegativesDir", "-p",    "aPositivesDir"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected{"Training."};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainClassify) {
  int numArgs{4};
  const char *argValues[numArgs] = {"./yasa", "classify", "-f",
                                    "aFileToClassify"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected{"Result: fake"};
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkClassifyHelp) {
  int numArgs{4};
  const char *argValues[numArgs] = {"./yasa", "classify", "-h",
                                    "aFileToClassify"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = ArgumentParser::classifyUsageMessage;
  ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkVersion) {
  int numArgs{2};
  const char *argValues[numArgs] = {"./yasa", "-v"};
  ArgumentParser argumentParser(numArgs, argValues);
  argumentParser.parseArgs();
  std::string actual = argumentParser.main();
  std::string expected = "yasa version " + std::string(VERSION);
  ASSERT_EQ(actual, expected);
}
