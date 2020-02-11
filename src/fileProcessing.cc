#include "fileProcessing.h"

#include <stddef.h>
#include <cctype>

std::vector<std::string> tokenize(std::string text) {
	std::vector<std::string> words;
	size_t first = 0;
	while (first < text.size()) {
		size_t last = first + 1;
		if (!ispunct(text[first])) {
			while (last < text.size() && isalnum(text[last])) {
				++last;
			}
		}
		words.push_back(text.substr(first, last - first));
		while (last < text.size() && isspace(text[last])) {
			++last;
		}
		first = last;
	}
	return words;

}
