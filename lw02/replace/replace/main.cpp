// replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Replace.h"


int _tmain(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Incorrect number of parameters." << std::endl;
		std::cout << "Write so: replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}
	std::string currLine = "";
	while (std::getline(std::cin, currLine))
	{
		std::cout << FindAndReplace(currLine, argv[1], argv[2]) << std::endl;
	}
	return 0;
}

