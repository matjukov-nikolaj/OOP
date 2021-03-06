// ObsceneWordsFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObsceneWordsFilter.h"

bool ReadObsceneWordsFromFile(std::istream &input, std::set<std::string> &obsceneWords)
{
	std::string obsceneWord = "";
	while (input >> obsceneWord)
	{
		obsceneWords.insert(obsceneWords.end(), obsceneWord);
	}
	return true;
}

std::string RemoveObsceneWords(std::string &str)
{
	char ch = ' ';
	for (size_t i = 0; i < str.size(); ++i)
	{
		ch = str[i];
		if (std::isalpha(ch))
		{
			std::cout << ch << std::endl;
		}
	}
	return "";
}
