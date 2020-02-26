#include "Classifier.h"

#include <iostream>

Classifier::Classifier(Dictionary* dictionary) : dictionary(dictionary) {}

Sentiment Classifier::classify(const std::vector<std::string>& words) {
  auto numPos = static_cast<double>(dictionary->positivesCountUniques() + 1);
  auto numNeg = static_cast<double>(dictionary->negativesCountUniques() + 1);
  double tot = numPos + numNeg;
  double counter = 0;
  for (auto& word : words) {
    counter +=
        static_cast<double>(dictionary->positivesCount(word)) * (tot / numPos);
    counter -=
        static_cast<double>(dictionary->negativesCount(word)) * (tot / numNeg);
  }
  return counter > 0 ? Sentiment::positive : Sentiment::negative;
}
