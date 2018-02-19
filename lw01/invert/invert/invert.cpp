#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
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
	

    return 0;
}

