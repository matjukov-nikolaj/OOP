#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string RaplaceInString(string &currStr, const string &searchStr, const string &replaceStr)
{
	if (searchStr.size() == 0)
	{
		return currStr;
	}
	size_t findPos = 0;
	findPos = currStr.find(searchStr, 0);
	string newStr;
	size_t currPos = 0;
	if (currPos != string::npos)
	{
		while (currPos != currStr.size())
		{
			if (currPos != findPos)
			{
				newStr += currStr[currPos];
				++currPos;
			}
			else
			{
				newStr += replaceStr;
				currPos += searchStr.size();
				findPos = currStr.find(searchStr, currPos);
			}
		}
	}
	else
	{
		newStr += currStr;
	}
	return newStr;
}

void ReplaceInFile(ifstream &fIn, ofstream &fOut, const string &searchStr, const string &replaceStr)
{
	string currString;
	while (getline(fIn, currString)) {
		currString = RaplaceInString(currString, searchStr, replaceStr);
		if (!(fOut << currString << endl))
		{
			cout << "Failed to write data on disk" << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: replace.exe <input file> <output file> <search string> <replace string>" << endl;
		return 1;
	}
	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "File " << argv[1] << " has not opened for reading.";
		return 1;
	}
	ofstream fileOut(argv[2]);
	if (!fileOut.is_open())
	{
		cout << "File " << argv[2] << " has not opened for writing.";
		return 1;
	}
	const string searchString = argv[3];
	const string replaceString = argv[4];
	ReplaceInFile(fileIn, fileOut, searchString, replaceString);
	fileIn.close();
	fileOut.close();
	return 0;
}
