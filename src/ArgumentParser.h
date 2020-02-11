#pragma once

#include <string>
#include <vector>

#include "MainBehaviour.h"

class ArgumentParser {
public:
	ArgumentParser(int argc, const char *argv[]);
	std::vector<std::string> getArgValues();
	std::string getMessage();
	std::string getPositivesDir();
	std::string getNegativesDir();
	std::string getFileToClassify();
	MainBehaviour getMainBehaviour();
	static std::string globalUsageMessage;
	static std::string trainUsageMessage;
	static std::string classifyUsageMessage;
	void parseArgs();
	std::string main();
private:
	int numArgs;
	std::vector<std::string> argValues;
	std::string message;
	std::string positivesDir;
	std::string negativesDir;
	std::string fileToClassify;
	MainBehaviour mainBehaviour;

	void handleFirstArgument();
	void handleTrainArguments();
	void handleClassifyArgument();
};
