#include "stdafx.h"
#include "ObsceneWordsFilter.h"

int _tmain(int argc, char* argv[])
{
	std::setlocale(LC_CTYPE, "Russian");
	//if (argc != 2)
	//{
	//	std::cout << "Incorrect number of parameters." << std::endl;
	//	std::cout << "Write so: replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
	//	return 1;
	//}

	//std::ifstream fileWithObsceneWords(argv[1]);
	//if (!fileWithObsceneWords.is_open())
	//{
	//	std::cout << "File " << argv[1] << " has not opened for reading." << "\n";
	//	return 1;
	//}

	std::set<std::string> obsceneWords;
	//if (ReadObsceneWordsFromFile(fileWithObsceneWords, obsceneWords))
	//{
		std::string currLine;
		while (std::getline(std::cin, currLine))
		{
			std::string result = RemoveObsceneWords(currLine);
		}
	//}

	return 0;
}
