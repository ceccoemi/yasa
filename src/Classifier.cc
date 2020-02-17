#include "Classifier.h"

#include <vector>

#include "Dictionary.h"
#include "fileProcessing.h"

Classifier::Classifier(Dictionary* dictionary) : dictionary(dictionary) {}

std::string Classifier::classify(const std::string& filename) {
  std::string text = extractText(filename);
  std::vector<std::string> words = extractWords(text);
  if (words.empty()) {
    return "The given file does not contain words.";
  }
  int counter = 0;
  for (auto& it : words) {
    counter += dictionary->positivesCount(it);
    counter -= dictionary->negativesCount(it);
  }
  return counter > 0 ? "positive" : "negative";
}
