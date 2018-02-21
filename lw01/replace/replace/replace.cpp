#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string ReplaceInString(const string &str, const string &searchStr, const string &replaceStr)
{
	if (searchStr.size() == 0)
	{
		return str;
	}
	size_t findPos = 0;
	findPos = str.find(searchStr, 0);
	string newStr;
	size_t currPos = 0;
	if (currPos != string::npos)
	{
		while (currPos != str.size())
		{
			if (currPos != findPos)
			{
				newStr += str[currPos];
				++currPos;
			}
			else
			{
				newStr += replaceStr;
				currPos += searchStr.size();
				findPos = str.find(searchStr, currPos);
			}
		}
	}
	else
	{
		newStr += str;
	}
	return newStr;
}

bool ReplaceInFile(ifstream &fIn, ofstream &fOut, const string &searchStr, const string &replaceStr)
{
	string currString;
	while (getline(fIn, currString))
	{
		if (currString.size() != 0)
		{
			currString = ReplaceInString(currString, searchStr, replaceStr);
			if (!(fOut << currString << endl))
			{
				return false;
			}
		}
		else
		{
			if (!(fOut << currString << endl))
			{
				return false;
			}
		}
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
	if (!ReplaceInFile(fileIn, fileOut, searchString, replaceString))
	{
		cout << "Failed to write data on disk." << endl;
		return 1;
	}
	return 0;
}
