#include "stdafx.h"
#include "WordOccurrence.h"

std::map<std::string, int> CalculationFrequencyWordsOccurrence(const std::string &str)
{
	std::map<std::string, int> wordsOccurrence;
	if (str.empty())
	{
		return wordsOccurrence;

	}

	std::string word;
	std::istringstream strm(str);

	while (strm >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), tolower);
		wordsOccurrence[word]++;
	}

	return wordsOccurrence;
}

void PrintFrequencyWordsOccurrence(std::ostream& output, std::map<std::string, int> wordsOccurrence)
{
	std::map<std::string, int>::iterator it;
	for (it = wordsOccurrence.begin(); it != wordsOccurrence.end(); ++it)
	{
		output << it->first << " : " << it->second << "\n";
	}
}
