#include "Classifier.h"

#include <stdexcept>
#include <vector>

#include "preprocessing.h"

Classifier::Classifier(Dictionary* dictionary) : dictionary(dictionary) {}

Sentiment Classifier::classify(const std::vector<std::string>& words) {
  int counter = 0;
  for (auto& word : words) {
    counter += dictionary->positivesCount(word);
    counter -= dictionary->negativesCount(word);
  }
  return counter > 0 ? Sentiment::positive : Sentiment::negative;
}
