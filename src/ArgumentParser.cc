#include "ArgumentParser.h"

#include <iostream>

ArgumentParser::ArgumentParser(int argc, const char *argv[]) :
		numArgs { argc }, mainBehaviour { displayMessage } {
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

MainBehaviour ArgumentParser::getMainBehaviour() {
	return mainBehaviour;
}

std::string ArgumentParser::globalUsageMessage = "Usage Message.";
std::string ArgumentParser::trainUsageMessage = "Train Usage Message.";
std::string ArgumentParser::classifyUsageMessage = "Classify Usage Message.";

void ArgumentParser::handleTrainArguments() {
	if ((numArgs > 2)
			&& ((argValues[2] == "-h") || (argValues[2] == "--help"))) {
		;
	} else if (numArgs == 4) {
		if (argValues[2] == "-p" || argValues[2] == "--positives") {
			positivesDir = argValues[3];
			mainBehaviour = MainBehaviour::trainPositives;
		} else if (argValues[2] == "-n" || argValues[2] == "--negatives") {
			negativesDir = argValues[3];
			mainBehaviour = MainBehaviour::trainNegatives;
		}
	} else if (numArgs == 6) {
		if (((argValues[2] == "-p") || (argValues[2] == "--positives"))
				&& ((argValues[4] == "-n") || (argValues[4] == "--negatives"))) {
			positivesDir = argValues[3];
			negativesDir = argValues[5];
			mainBehaviour = MainBehaviour::trainPositivesAndNegatives;
		} else if (((argValues[2] == "-n") || (argValues[2] == "--negatives"))
				&& ((argValues[4] == "-p") || (argValues[4] == "--positives"))) {
			negativesDir = argValues[3];
			positivesDir = argValues[5];
			mainBehaviour = MainBehaviour::trainPositivesAndNegatives;
		}
	}
}

void ArgumentParser::handleClassifyArgument() {
	if (numArgs > 2) {
		if ((argValues[2] == "-h") || (argValues[2] == "--help")) {
			;
		} else if ((argValues[2] == "-f") || (argValues[2] == "--file")) {
			if (numArgs > 3) {
				fileToClassify = argValues[3];
				mainBehaviour = MainBehaviour::classify;
			}
		}
	}
}

void ArgumentParser::handleFirstArgument() {
	if ((argValues[1] == "-h") || argValues[1] == "--help") {
		message = globalUsageMessage;
	} else if (argValues[1] == "train") {
		message = trainUsageMessage;
		handleTrainArguments();
	} else if (argValues[1] == "classify") {
		message = classifyUsageMessage;
		handleClassifyArgument();
	} else {
		message = globalUsageMessage;
	}
}

void ArgumentParser::parseArgs() {
	mainBehaviour = MainBehaviour::displayMessage;
	if (numArgs < 2) {
		message = globalUsageMessage;
	} else {
		handleFirstArgument();
	}
}

std::string ArgumentParser::main() {
	switch (mainBehaviour) {
	case trainPositives:
		return "Training done on given positive examples.";
	case trainNegatives:
		return "Training done on given negative examples.";
	case trainPositivesAndNegatives:
		return "Training done on given positive and negative examples.";
	case classify:
		return "Result: fake";
	default:
		std::cout << getMessage();
		return getMessage();
	}
}
