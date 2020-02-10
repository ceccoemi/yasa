#include <ArgumentParser.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(ArgumentParserTest, ArgumentParserConstructor) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "-p", "aDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	std::vector<std::string> actual = argumentParser.getArgValues();
	std::vector<std::string> expected { "./yasa", "-p", "aDir" };
	for (int i = 0; i < numArgs; ++i) {
		ASSERT_EQ(actual[i], expected[i]);
	}
}

TEST(ArgumentParserTest, parseArgsExit) {
	int numArgs { 1 };
	const char *argValues[numArgs] = { "./yasa" };
	ArgumentParser argumentParser(numArgs, argValues);
	int actual = argumentParser.parseArgs();
	int expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkGlobalUsageMessage) {
	int numArgs { 1 };
	const char *argValues[numArgs] = { "./yasa" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string expected = argumentParser.getGlobalUsageMessage();
	std::string actual { "Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkTrainUsageMessage) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "train" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string expected = argumentParser.getTrainUsageMessage();
	std::string actual { "Train Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkClassifyUsageMessage) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "classify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string expected = argumentParser.getClassifyUsageMessage();
	std::string actual { "Classify Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkPositivesDirMessage) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "aDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string expected = argumentParser.getPositivesDirMessage();
	std::string actual { "PositivesDir Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkNegativesDirMessage) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n", "aDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string expected = argumentParser.getNegativesDirMessage();
	std::string actual { "NegativesDir Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithNoArgs) {
	int numArgs { 1 };
	const char *argValues[numArgs] = { "./yasa" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getGlobalUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithFirstArgumentWrong) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "hola" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getGlobalUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsHelp) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "--help" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getGlobalUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsTrain) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "train" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getTrainUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsClassify) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "classify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getClassifyUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkPositivesArgumentAfterTrain) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getTrainUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkNegativesArgumentAfterTrain) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getTrainUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentAfterClassify) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-f" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getClassifyUsageMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getPositivesDirMessage) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "aDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getPositivesDirMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getNegativesDirMessage) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n", "aDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.getNegativesDirMessage();
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getPositivesDir) {
	int numArgs { 4 };
	const char *argValues[numArgs] =
			{ "./yasa", "train", "-p", "aPositivesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getPositivesDir();
	std::string expected { "aPositivesDir" };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getNegativesDir) {
	int numArgs { 4 };
	const char *argValues[numArgs] =
			{ "./yasa", "train", "-n", "aNegativesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getNegativesDir();
	std::string expected { "aNegativesDir" };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getPositivesDirAndNegativesDir) {
	int numArgs { 6 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "aPositivesDir",
			"-n", "aNegativesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actualPos = argumentParser.getPositivesDir();
	std::string expectedPos { "aPositivesDir" };
	ASSERT_EQ(actualPos, expectedPos);
	std::string actualNeg = argumentParser.getNegativesDir();
	std::string expectedNeg { "aNegativesDir" };
	ASSERT_EQ(actualNeg, expectedNeg);
}

TEST(ArgumentParserTest, getPositivesDirAndPositivesDir) {
	int numArgs { 6 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "aPositivesDir",
			"-p", "anotherPositivesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actualPos1 = argumentParser.getPositivesDir();
	std::string expectedPos1 { "aPositivesDir" };
	ASSERT_EQ(actualPos1, expectedPos1);
	std::string actualPos2 = argumentParser.getPositivesDir();
	std::string expectedPos2 { "aPositivesDir" };
	ASSERT_EQ(actualPos2, expectedPos2);
}

TEST(ArgumentParserTest, getNegativesDirAndNegativesDir) {
	int numArgs { 6 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n", "aNegativesDir",
			"-n", "anotherNegativesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actualNeg1 = argumentParser.getNegativesDir();
	std::string expectedNeg1 { "aNegativesDir" };
	ASSERT_EQ(actualNeg1, expectedNeg1);
	std::string actualNeg2 = argumentParser.getNegativesDir();
	std::string expectedNeg2 { "aNegativesDir" };
	ASSERT_EQ(actualNeg2, expectedNeg2);
}

TEST(ArgumentParserTest, getFileToClassify) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-f",
			"aFileToClassify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getFileToClassify();
	std::string expected { "aFileToClassify" };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, getFileToClassifyMessage) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-f",
			"aFileToClassify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected { "FileToClassify Message." };
	ASSERT_EQ(actual, expected);
}
