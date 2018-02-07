#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool replaceInFile(ifstream &fIn, ofstream &fOut, const string &searchStr, const string &replaceStr, int & isReplaced)
{
	string currString;
	while (getline(fIn, currString)) {
		int positionOfSearchStr = currString.find(searchStr, 0);
		if (positionOfSearchStr != string::npos) {
			currString.replace(positionOfSearchStr, searchStr.size(), replaceStr);
			if (!(fOut << currString << endl))
				isReplaced = -1;
			else
				isReplaced = 1;
		} else
			if (!(fOut << currString << endl))
				isReplaced = -1;
	}
	if ((isReplaced != 1) & (isReplaced == -1))
		isReplaced = 0;
	return isReplaced;
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
	int isReplaced;
	if (searchString.size() == 0)
	{
		fileOut << fileIn.rdbuf();
		isReplaced = 0;
	}
	else
	    isReplaced = replaceInFile(fileIn, fileOut, searchString, replaceString, isReplaced);
	if (isReplaced == -1) {
		cout << "During file recording there was a mistake Error." << endl;
		return 1;
	}
	else if (isReplaced == 1)
		cout << "Replace has happened successfully!" << endl;
	else if (isReplaced == 0)
		cout << "There is no such subline in the file, the file was copied." << endl;
	fileIn.close();
	fileOut.close();
	return 0;
}
