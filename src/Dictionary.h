#pragma once

#include <string>

#include "Sentiment.h"
#include "SqliteYasa.h"

class Dictionary {
public:
	static Dictionary* getInstance();

	void addWord(std::string word, Sentiment sentiment);

	int size();

	void reset();

	int positivesCount();

	int positivesCount(std::string word);

	int negativesCount();

	int negativesCount(std::string word);

private:
	Dictionary();

	static Dictionary *instance;
	SqliteYasa db;
};
