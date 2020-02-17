#include "Trainer.h"

#include <experimental/filesystem>
#include <vector>

#include "Dictionary.h"
#include "fileProcessing.h"

namespace fs = std::experimental::filesystem;

Trainer::Trainer(Dictionary* dictionary) : dictionary(dictionary) {}

void Trainer::train(const std::string& negativesDir,
                    const std::string& positivesDir) {
  updateDictionary(negativesDir, Sentiment::negative);
  updateDictionary(positivesDir, Sentiment::positive);
}

void Trainer::updateDictionary(const std::string& dir, Sentiment sentiment) {
  if (!dir.empty()) {
    for (const auto& entry : fs::directory_iterator(dir)) {
      std::string filePath = entry.path();
      std::string text = extractText(filePath);
      std::vector<std::string> words = extractWords(text);
      for (const auto& word : words) {
        dictionary->add(word, sentiment);
      }
    }
  }
}
