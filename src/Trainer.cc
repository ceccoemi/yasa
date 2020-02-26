#include "Trainer.h"

Trainer::Trainer(Dictionary* dictionary) : dictionary(dictionary) {}

void Trainer::train(const std::vector<std::string>& words,
                    Sentiment sentiment) {
  for (const auto& word : words) {
    dictionary->add(word, sentiment);
  }
}
