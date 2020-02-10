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
	static std::string getFileToClassifyMessage();
	void handleFirstArgument();
	void handleTrainArguments();
	void handleClassifyArgument();
	int parseArgs();
private:
	int numArgs;
	std::vector<std::string> argValues;
	std::string message;
	std::string positivesDir;
	std::string negativesDir;
	std::string fileToClassify;
};
