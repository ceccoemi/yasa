#include "Classifier.h"

#include <stdexcept>
#include <vector>

#include "fileProcessing.h"

Classifier::Classifier(Dictionary* dictionary) : dictionary(dictionary) {}

Sentiment Classifier::classify(const std::string& filename) {
  std::string text = extractText(filename);
  std::vector<std::string> words = extractWords(text);
  if (words.empty()) {
    throw std::runtime_error("The given file does not contain words.");
  }
  int counter = 0;
  for (auto& word : words) {
    counter += dictionary->positivesCount(word);
    counter -= dictionary->negativesCount(word);
  }
  return counter > 0 ? Sentiment::positive : Sentiment::negative;
}
