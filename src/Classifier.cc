#include "Classifier.h"

#include "Dictionary.h"

Classifier::Classifier(Dictionary* dictionary) : dictionary(dictionary) {}

Sentiment Classifier::classify(const std::vector<std::string>& words) {
  double numPos = dictionary->positivesCountUniques() + 1.0;
  double numNeg = dictionary->negativesCountUniques() + 1.0;
  double tot = numPos + numNeg;
  double counter = 0;
  for (auto& word : words) {
    counter += (tot / numPos) * dictionary->positivesCount(word);
    counter -= (tot / numNeg) * dictionary->negativesCount(word);
  }
  return counter > 0 ? Sentiment::positive : Sentiment::negative;
}
