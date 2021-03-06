// WordOccurence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordOccurrence.h"


int _tmain()
{
	std::string currLine;
	std::map<std::string, int> wordsOccurrence;
	while (std::getline(std::cin, currLine))
	{
		wordsOccurrence = CalculationFrequencyWordsOccurrence(currLine);
		if (!wordsOccurrence.empty())
		{
			PrintFrequencyWordsOccurrence(std::cout, wordsOccurrence);
		}
		else
		{
			std::cout << "\n";
		}
	}
	return 0;
}
