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

TEST(ArgumentParserTest, )
