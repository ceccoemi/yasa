#pragma once

#include <string>
#include <vector>

class ArgumentParser {
 public:
  ArgumentParser(int argc, const char *argv[]);
  static const std::string globalUsageMessage;
  static const std::string trainUsageMessage;
  static const std::string classifyUsageMessage;
  void parseArgs();
  std::string main();

 private:
  int numArgs;
  std::vector<std::string> argValues;
  std::string message;
  std::string positivesDir;
  std::string negativesDir;
  std::string fileToClassify;
  enum MainBehaviour { train, classify, displayMessage };
  MainBehaviour mainBehaviour;

  void handleFirstArgument();
  void handleTrainArguments();
  void handleClassifyArgument();
};
