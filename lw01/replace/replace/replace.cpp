#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string ReplaceInString(const string &str, const string &searchStr, const string &replacementStr)
{
	if ((searchStr.empty()) || (str.empty()))
	{
		return str;
	}
	string newStr;
	size_t currPos = 0;
	for (size_t findPos = 0; findPos != string::npos; currPos = findPos + searchStr.size())
	{
		findPos = str.find(searchStr, currPos);
		if (findPos != string::npos)
		{
		    newStr.append(str, currPos, findPos - currPos);
		    newStr.append(replacementStr);
		}
		else
		{
			break;
		}
	}
	newStr.append(str.substr(currPos));
	return newStr;
}

bool ReplaceAllOccurencesInFile(ifstream &fIn, ofstream &fOut, const string &searchStr, const string &replacementStr)
{
	string currLine;
	while (getline(fIn, currLine))
	{
		if (!(fOut << ReplaceInString(currLine, searchStr, replacementStr) << endl))
		{
			return false;
		}
	}
	return true;
}

bool ReplaceInFile(char * argv[])
{
	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "File " << argv[1] << " has not opened for reading.";
		return false;
	}

	ofstream fileOut(argv[2]);
	if (!fileOut.is_open())
	{
		cout << "File " << argv[2] << " has not opened for writing.";
		return false;
	}

	const string searchString = argv[3];
	const string replacementString = argv[4];

	if (!ReplaceAllOccurencesInFile(fileIn, fileOut, searchString, replacementString))
	{
		cout << "Failed to write data on disk." << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: replace.exe <input file> <output file> <search string> <replace string>" << endl;
		return 1;
	}
	bool success = ReplaceInFile(argv);
	if (!success)
	{
		return 1;
	}
	return 0;
}
