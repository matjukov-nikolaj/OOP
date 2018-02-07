#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string RaplaceAllOccurences(string currStr, const string &searchStr, const string &replaceStr)
{
	string::size_type position = currStr.find(searchStr, 0);
	while (position != string::npos)
	{
		currStr.replace(position, searchStr.size(), replaceStr);
		position = currStr.find(searchStr, position + replaceStr.size());
	}
	return currStr;
}

void ReplaceInFile(ifstream &fIn, ofstream &fOut, const string &searchStr, const string &replaceStr)
{
	string currString;
	while (getline(fIn, currString)) {
		currString = RaplaceAllOccurences(currString, searchStr, replaceStr);
		if (!(fOut << currString << endl))
			cout << "Failed to write data on disk" << endl;
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
	if (searchString.size() == 0)
		fileOut << fileIn.rdbuf();
	else
      ReplaceInFile(fileIn, fileOut, searchString, replaceString);
	fileIn.close();
	fileOut.close();
	return 0;
}
