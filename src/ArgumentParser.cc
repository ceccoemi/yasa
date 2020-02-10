#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, const char *argv[]) :
		numArgs { argc } {
	for (int i = 0; i < numArgs; ++i) {
		argValues.push_back(argv[i]);
	}
}

std::vector<std::string> ArgumentParser::getArgValues() {
	return argValues;
}
std::string ArgumentParser::getMessage() {
	return message;
}

std::string ArgumentParser::getPositivesDir() {
	return positivesDir;
}

std::string ArgumentParser::getNegativesDir() {
	return negativesDir;
}

std::string ArgumentParser::getFileToClassify() {
	return fileToClassify;
}

std::string ArgumentParser::getGlobalUsageMessage() {
	std::string globalUsageMessage { "Usage Message." };
	return globalUsageMessage;
}

std::string ArgumentParser::getTrainUsageMessage() {
	std::string trainUsageMessage { "Train Usage Message." };
	return trainUsageMessage;
}

std::string ArgumentParser::getClassifyUsageMessage() {
	std::string classifyUsageMessage { "Classify Usage Message." };
	return classifyUsageMessage;
}

std::string ArgumentParser::getPositivesDirMessage() {
	std::string positivesDirMessage { "PositivesDir Message." };
	return positivesDirMessage;
}

std::string ArgumentParser::getNegativesDirMessage() {
	std::string negativesDirMessage { "NegativesDir Message." };
	return negativesDirMessage;
}

std::string ArgumentParser::getFileToClassifyMessage() {
	std::string fileToClassifyMessage { "FileToClassify Message." };
	return fileToClassifyMessage;
}

void ArgumentParser::handleTrainArguments() {
	for (int i = 2; i < numArgs; ++i) {
		if ((argValues[i] == "-h") || (argValues[i] == "--help")) {
			message = getTrainUsageMessage();
		} else if ((argValues[i] == "-p") || (argValues[i] == "--positives")) {
			message = getPositivesDirMessage();
			if ((i + 1 < numArgs) && positivesDir.empty()){
				positivesDir = argValues[++i];
			} else {
				message = getTrainUsageMessage();
			}
		} else if ((argValues[i] == "-n") || (argValues[i] == "--negatives")) {
			message = getNegativesDirMessage();
			if ((i + 1 < numArgs) && negativesDir.empty()) {
				negativesDir = argValues[++i];
			} else {
				message = getTrainUsageMessage();
			}
		}
	}
}

void ArgumentParser::handleClassifyArgument() {
	if (numArgs > 2) {
		if ((argValues[2] == "-f") || (argValues[2] == "--file")) {
			message = getFileToClassifyMessage();
			if (numArgs > 3) {
				fileToClassify = argValues[3];
			} else {
				message = getClassifyUsageMessage();
			}
		}
	}
}

void ArgumentParser::handleFirstArgument() {
	if ((argValues[1] == "-h") || argValues[1] == "--help") {
		message = getGlobalUsageMessage();
	} else if (argValues[1] == "train") {
		message = getTrainUsageMessage();
		handleTrainArguments();
	} else if (argValues[1] == "classify") {
		message = getClassifyUsageMessage();
		handleClassifyArgument();
	} else {
		message = getGlobalUsageMessage();
	}
}

int ArgumentParser::parseArgs() {
	bool exit = 0;
	if (numArgs < 2) {
		message = getGlobalUsageMessage();
	} else {
		handleFirstArgument();
	}
	return exit;
}
