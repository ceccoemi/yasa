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

int main(int argc, const char* argv[]) {
  ArgumentParser argumentParser(
      argc, std::vector<std::string>(argv, argv + argc),
      [](auto negDir, auto posDir) {
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
        counter = 0;
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
        return "Training done.";
      },
      [](auto fileName) {
        SqliteHandler handler("yasa.db");
        SqliteDictionary<SqliteHandler> dictionary(&handler);
        Classifier classifier(&dictionary);
        TextFileReader reader(fileName);
        std::string text(reader.read());
        std::vector<std::string> words = extractWords(text);
        Sentiment sentiment = classifier.classify(words);
        return sentiment == Sentiment::positive ? "Positive" : "Negative";
      });
  std::cout << argumentParser.main() << '\n';
  return 0;
}
