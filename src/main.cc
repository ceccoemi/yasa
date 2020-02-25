#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "ArgumentParser.h"
#include "Classifier.h"
#include "SqliteDictionary.h"
#include "SqliteHandler.h"
#include "TextFileReader.h"
#include "Trainer.h"
#include "preprocessing.h"

namespace fs = std::experimental::filesystem;

auto trainFunc = [](auto negDir, auto posDir) {
  if (!negDir.empty()) {
    SqliteHandler handler("yasa.db");
    SqliteDictionary<SqliteHandler> dictionary(&handler);
    Trainer trainer(&dictionary);
    for (const auto &entry : fs::directory_iterator(negDir)) {
      TextFileReader reader(entry.path());
      std::string text(reader.read());
      std::vector<std::string> words = extractWords(text);
      trainer.train(words, Sentiment::negative);
    }
  }
  if (!posDir.empty()) {
    SqliteHandler handler("yasa.db");
    SqliteDictionary<SqliteHandler> dictionary(&handler);
    Trainer trainer(&dictionary);
    for (const auto &entry : fs::directory_iterator(posDir)) {
      TextFileReader reader(entry.path());
      std::string text(reader.read());
      std::vector<std::string> words = extractWords(text);
      trainer.train(words, Sentiment::positive);
    }
  }
  return "Training done.";
};

auto classifyFunc = [](auto fileName) {
  SqliteHandler handler("yasa.db");
  SqliteDictionary<SqliteHandler> dictionary(&handler);
  Classifier classifier(&dictionary);
  TextFileReader reader(fileName);
  std::string text(reader.read());
  std::vector<std::string> words = extractWords(text);
  Sentiment sentiment = classifier.classify(words);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  return sentiment == Sentiment::positive ? "Positive" : "Negative";
};

int main(int argc, const char *argv[]) {
  ArgumentParser argumentParser(argc,
                                std::vector<std::string>(argv, argv + argc),
                                trainFunc, classifyFunc);
  auto out = argumentParser.main();
  std::cout << out.second << '\n';
  return out.first;
}
