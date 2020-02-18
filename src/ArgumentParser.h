#pragma once

#include <string>
#include <vector>

class ArgumentParser {
 public:
  ArgumentParser(int argc, std::vector<std::string> argValues);
  static const std::string globalUsageMessage;
  static const std::string trainUsageMessage;
  static const std::string classifyUsageMessage;
  std::string main();

 private:
  int numArgs;
  std::vector<std::string> argValues;
  std::string message;
  std::string positivesDir;
  std::string negativesDir;
  std::string fileToClassify;

  void parseArgs();
  void handleFirstArgument();
  void handleTrainArguments();
  void handleClassifyArgument();

  enum MainBehaviour { train, classify, displayMessage };
  MainBehaviour mainBehaviour;
};
