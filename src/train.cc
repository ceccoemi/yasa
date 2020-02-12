#include "train.h"

#include <experimental/filesystem>
#include <iostream>
#include <vector>

#include "Dictionary.h"
#include "fileProcessing.h"

namespace fs = std::experimental::filesystem;

namespace {

void updateDictionary(std::string dir, Sentiment sentiment) {
  if (dir.size() > 0) {
    Dictionary* dictionary = Dictionary::getInstance();
    for (const auto& entry : fs::directory_iterator(dir)) {
      std::string filePath = entry.path();
      std::string text = extractText(filePath);
      std::vector<std::string> words = extractWords(text);
      for (const auto word : words) {
        dictionary->addWord(word, sentiment);
      }
    }
  }
}

}  // namespace

void train(std::string negativesDir, std::string positivesDir) {
  updateDictionary(negativesDir, Sentiment::negative);
  updateDictionary(positivesDir, Sentiment::positive);
}
