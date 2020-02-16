#include "classify.h"

#include <vector>

#include "SqliteDictionary.h"
#include "fileProcessing.h"

std::string classify(const std::string& filename) {
  std::string text = extractText(filename);
  std::vector<std::string> words = extractWords(text);
  if (words.empty()) {
    return "The given file does not contain words.";
  }
  SqliteDictionary* dictionary = SqliteDictionary::getInstance();
  int counter = 0;
  for (auto& it : words) {
    counter += dictionary->positivesCount(it);
    counter -= dictionary->negativesCount(it);
  }
  return counter > 0 ? "positive" : "negative";
}
