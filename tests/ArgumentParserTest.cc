#include <ArgumentParser.h>
#include <gtest/gtest.h>
#include <MainBehaviour.h>
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

TEST(ArgumentParserTest, checkGlobalUsageMessage) {
	std::string expected = ArgumentParser::globalUsageMessage;
	std::string actual { "Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkTrainUsageMessage) {
	std::string expected = ArgumentParser::trainUsageMessage;
	std::string actual { "Train Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkClassifyUsageMessage) {
	std::string expected = ArgumentParser::classifyUsageMessage;
	std::string actual { "Classify Usage Message." };
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithNoArgs) {
	int numArgs { 1 };
	const char *argValues[numArgs] = { "./yasa" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.globalUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, showUsageWithFirstArgumentWrong) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "hola" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.globalUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsHelp) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "--help" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.globalUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsTrain) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "train" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.trainUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentWhenItIsClassify) {
	int numArgs { 2 };
	const char *argValues[numArgs] = { "./yasa", "classify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.classifyUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkPositivesArgumentAfterTrain) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.trainUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkNegativesArgumentAfterTrain) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.trainUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, checkFirstArgumentAfterClassify) {
	int numArgs { 3 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-f" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected = argumentParser.classifyUsageMessage;
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
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::trainPositives;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
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
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::trainNegatives;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
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
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::trainPositivesAndNegatives;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
}

TEST(ArgumentParserTest, getNegativesDirAndPositivesDir) {
	int numArgs { 6 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n", "aNegativesDir",
			"-p", "aPositivesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actualPos = argumentParser.getPositivesDir();
	std::string expectedPos { "aPositivesDir" };
	ASSERT_EQ(actualPos, expectedPos);
	std::string actualNeg = argumentParser.getNegativesDir();
	std::string expectedNeg { "aNegativesDir" };
	ASSERT_EQ(actualNeg, expectedNeg);
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::trainPositivesAndNegatives;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
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
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::classify;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
}

TEST(ArgumentParserTest, checkClassifyHelp) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-h",
			"aFileToClassify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.getMessage();
	std::string expected { "Classify Usage Message." };
	ASSERT_EQ(actual, expected);
	MainBehaviour actualBehaviour = argumentParser.getMainBehaviour();
	MainBehaviour expectedBehaviour = MainBehaviour::displayMessage;
	ASSERT_EQ(actualBehaviour, expectedBehaviour);
}

TEST(ArgumentParserTest, mainDisplayMessage) {
	int numArgs { 1 };
	const char *argValues[numArgs] = { "./yasa" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.main();
	std::string expected = ArgumentParser::globalUsageMessage;
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainPositives) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "positivesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.main();
	std::string expected = "Training done on given positive examples.";
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainNegatives) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "train", "-n", "negativesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.main();
	std::string expected = "Training done on given negative examples.";
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainTrainPositivesAndNegatives) {
	int numArgs { 6 };
	const char *argValues[numArgs] = { "./yasa", "train", "-p", "aPositivesDir",
			"-n", "aNegativesDir" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.main();
	std::string expected =
			"Training done on given positive and negative examples.";
	ASSERT_EQ(actual, expected);
}

TEST(ArgumentParserTest, mainClassify) {
	int numArgs { 4 };
	const char *argValues[numArgs] = { "./yasa", "classify", "-f",
			"fileToClassify" };
	ArgumentParser argumentParser(numArgs, argValues);
	argumentParser.parseArgs();
	std::string actual = argumentParser.main();
	std::string expected = "Result: fake";
	ASSERT_EQ(actual, expected);
}
