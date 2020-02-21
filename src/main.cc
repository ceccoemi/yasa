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
    int counter = 0;
    for (const auto& entry : fs::directory_iterator(negDir)) {
      TextFileReader reader(entry.path());
      std::string text(reader.read());
      std::vector<std::string> words = extractWords(text);
      trainer.train(words, Sentiment::negative);
      ++counter;
      if (counter % 10 == 0) {
        std::cout << "Processed " << counter << " neg files\n";
      }
    }
  }
  if (!posDir.empty()) {
    SqliteHandler handler("yasa.db");
    SqliteDictionary<SqliteHandler> dictionary(&handler);
    Trainer trainer(&dictionary);
    int counter = 0;
    for (const auto& entry : fs::directory_iterator(posDir)) {
      TextFileReader reader(entry.path());
      std::string text(reader.read());
      std::vector<std::string> words = extractWords(text);
      trainer.train(words, Sentiment::positive);
      ++counter;
      if (counter % 10 == 0) {
        std::cout << "Processed " << counter << " pos files\n";
      }
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
  return sentiment == Sentiment::positive ? "Positive" : "Negative";
};

int main(int argc, const char* argv[]) {
  std::cout << fs::current_path() << '\n';
  ArgumentParser argumentParser(argc,
                                std::vector<std::string>(argv, argv + argc),
                                trainFunc, classifyFunc);
  std::cout << argumentParser.main() << '\n';
  return 0;
}
