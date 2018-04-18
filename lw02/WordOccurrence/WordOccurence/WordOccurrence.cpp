#include "stdafx.h"
#include "WordOccurrence.h"
#include "regex"

std::string RemoveConstraintCharactersFromWord(const std::string& str)
{
	static const std::string specialSymbols = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~";
	std::string result = "";
	char ch = ' ';

	for (size_t i = 0; i < str.size(); ++i)
	{
		ch = str[i];
		if (specialSymbols.find(ch) == std::string::npos)
		{
			result += ch;
		}
	}

	return result;
}

std::map<std::string, int> CalculationFrequencyWordsOccurrence(const std::string& str)
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
		word = RemoveConstraintCharactersFromWord(word);
		if (!word.empty())
		{
			wordsOccurrence[word]++;
		}
	}

	return wordsOccurrence;
}

void PrintFrequencyWordsOccurrence(std::ostream& output, const std::map<std::string, int> &wordsOccurrence)
{
	for (auto word: wordsOccurrence)
	{
		output << word.first << " : " << word.second << "\n";
	}
}
