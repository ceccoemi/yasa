#include "ArgumentParser.h"

#include <algorithm>

#include "version.h"

ArgumentParser::ArgumentParser(int argc, std::vector<std::string> argValues)
    : numArgs{argc},
      argValues(std::move(argValues)),
      mainBehaviour{displayMessage} {}

const std::string ArgumentParser::globalUsageMessage{
    "\nUsage: yasa <command> <option(s)> <source>\n\nCommand line tool to "
    "perform sentiment analysis written in C++ with Docker\n\nOptions:\n\t-h, "
    "--help\t\t\tShow this help message\n\t-v, --version\t\t\tPrint version "
    "information and quit\nCommands:\n\ttrain\t\t\t\tTrain on given"
    "positives|negatives examples\n\tclassify\t\t\tClassify a given file\n"};
const std::string ArgumentParser::trainUsageMessage{
    "\nUsage: yasa train <option(s)> <source>\n\nTrain on given "
    "positives|negatives examples\n\nOptions:\n\t-h, --help\t\t\tShow this "
    "help message\nOptions:\n\t-p, --positives\t\t\tDirectory with positives "
    "examples\n\t-n, --negatives\t\t\tDirectory with negatives examples"};
const std::string ArgumentParser::classifyUsageMessage{
    "\nUsage: yasa classify <option> <source>\n\nClassify a given "
    "file\n\nOptions:\n\t-h, --help\t\t\tShow this help "
    "message\nOptions:\n\t-f, --file\t\t\tFile to classify"};

void ArgumentParser::handleTrainArguments() {
  if (numArgs == 4) {
    if ((argValues[2] == "-p") || (argValues[2] == "--positives")) {
      positivesDir = argValues[3];
      mainBehaviour = MainBehaviour::train;
    } else if ((argValues[2] == "-n") || (argValues[2] == "--negatives")) {
      negativesDir = argValues[3];
      mainBehaviour = MainBehaviour::train;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  } else if (numArgs == 6) {
    if (((argValues[2] == "-p") || (argValues[2] == "--positives")) &&
        ((argValues[4] == "-n") || (argValues[4] == "--negatives"))) {
      positivesDir = argValues[3];
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      negativesDir = argValues[5];
      mainBehaviour = MainBehaviour::train;
    } else if (((argValues[2] == "-n") || (argValues[2] == "--negatives")) &&
               ((argValues[4] == "-p") || (argValues[4] == "--positives"))) {
      negativesDir = argValues[3];
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      positivesDir = argValues[5];
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
  parseArgs();
  switch (mainBehaviour) {
    case MainBehaviour::train:
      return "Training.";
    case MainBehaviour::classify:
      return "Result: fake.";
    default:
      return message;
  }
}
