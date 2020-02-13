#include "ArgumentParser.h"

#include "version.h"

ArgumentParser::ArgumentParser(int argc, const char *argv[])
    : numArgs{argc}, mainBehaviour{displayMessage} {
  argValues = std::vector<std::string>(argv, argv + argc);
}

const std::string ArgumentParser::globalUsageMessage = "Usage Message.";
const std::string ArgumentParser::trainUsageMessage = "Train Usage Message.";
const std::string ArgumentParser::classifyUsageMessage =
    "Classify Usage Message.";

void ArgumentParser::handleTrainArguments() {
  constexpr int oneOptionLength = 4;
  constexpr int twoOptionsLength = 6;
  constexpr int firstOptionIdx = 2;
  constexpr int firstArgIdx = 3;
  constexpr int secondOptionIdx = 4;
  constexpr int secondArgIdx = 5;

  if (numArgs == oneOptionLength) {
    if (argValues[firstOptionIdx] == "-p" ||
        argValues[firstOptionIdx] == "--positives") {
      positivesDir = argValues[firstArgIdx];
      mainBehaviour = MainBehaviour::train;
    } else if (argValues[firstOptionIdx] == "-n" ||
               argValues[firstOptionIdx] == "--negatives") {
      negativesDir = argValues[firstArgIdx];
      mainBehaviour = MainBehaviour::train;
    }
  } else if (numArgs == twoOptionsLength) {
    if (((argValues[firstOptionIdx] == "-p") ||
         (argValues[firstOptionIdx] == "--positives")) &&
        ((argValues[secondOptionIdx] == "-n") ||
         (argValues[secondOptionIdx] == "--negatives"))) {
      positivesDir = argValues[firstArgIdx];
      negativesDir = argValues[secondArgIdx];
      mainBehaviour = MainBehaviour::train;
    } else if (((argValues[firstOptionIdx] == "-n") ||
                (argValues[firstOptionIdx] == "--negatives")) &&
               ((argValues[secondOptionIdx] == "-p") ||
                (argValues[secondOptionIdx] == "--positives"))) {
      negativesDir = argValues[firstArgIdx];
      positivesDir = argValues[secondArgIdx];
      mainBehaviour = MainBehaviour::train;
    }
  }
}

void ArgumentParser::handleClassifyArgument() {
  if ((numArgs > 3) && ((argValues[2] == "-f") || (argValues[2] == "--file"))) {
    fileToClassify = argValues[3];
    mainBehaviour = MainBehaviour::classify;
  }
}

void ArgumentParser::handleFirstArgument() {
  if ((argValues[1] == "-v") || (argValues[1] == "--version")) {
    message = "yasa version " + std::string(VERSION);
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
  if (numArgs < 2) {
    message = globalUsageMessage;
  } else {
    handleFirstArgument();
  }
}

std::string ArgumentParser::main() {
  switch (mainBehaviour) {
    case MainBehaviour::train:
      return "Training.";
    case MainBehaviour::classify:
      return "Result: fake";
    default:
      return message;
  }
}
