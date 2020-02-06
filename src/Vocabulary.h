#pragma once

#include <string>

#include "Sentiment.h"

namespace yasa {

class Vocabulary {
public:
	Vocabulary();

	void addWord(std::string word, yasa::Sentiment sentiment);

	int getPositiveCount(std::string word);

	int getNegativeCount(std::string word);
};

}  // namespace yasa
