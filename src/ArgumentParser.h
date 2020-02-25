#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

class ArgumentParser {
 public:
  static const std::string globalUsageMessage;
  static const std::string trainUsageMessage;
  static const std::string classifyUsageMessage;

  ArgumentParser(
      int argc, std::vector<std::string> argValues,
      std::function<std::string(const std::string& negDir,
                                const std::string& posDir)>
          trainFunc,
      std::function<std::string(const std::string& fileName)> classifyFunc);

  std::pair<int, std::string> main();

 private:
  int numArgs;
  std::vector<std::string> argValues;
  std::function<std::string(const std::string& negDir,
                            const std::string& posDir)>
      trainFunc;
  std::function<std::string(const std::string& fileName)> classifyFunc;
  std::string message;
  std::string positivesDir;
  std::string negativesDir;
  std::string fileToClassify;

  void parseArgs();
  void handleFirstArgument();
  void handleTrainArguments();
  void handleClassifyArgument();

  enum MainBehaviour { train, classify, displayVersion, displayMessage };
  MainBehaviour mainBehaviour;
};
