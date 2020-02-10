#pragma once

#include <string>
#include <vector>

class ArgumentParser {
public:
	ArgumentParser(int argc, const char *argv[]);
	std::vector<std::string> getArgValues();
	std::string getMessage();
	std::string getPositivesDir();
	std::string getNegativesDir();
	std::string getFileToClassify();
	static std::string getGlobalUsageMessage();
	static std::string getTrainUsageMessage();
	static std::string getClassifyUsageMessage();
	static std::string getPositivesDirMessage();
	static std::string getNegativesDirMessage();
	int parseArgs();
	void handleFirstArgument();
	void handleTrainArguments();
private:
	int numArgs;
	std::vector<std::string> argValues;
	std::string message;
	std::string positivesDir;
	std::string negativesDir;
	std::string fileToClassify;
};
