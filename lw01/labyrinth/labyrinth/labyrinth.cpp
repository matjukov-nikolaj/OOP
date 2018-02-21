#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
using LabyrinthVec = vector<vector<int>>;

const size_t MAX_SIZE = 102;
const short BORDER = -2;
const short EMPTY = 0;
const short WALL = -1;

struct Point
{
	size_t x;
	size_t y;
};

Point start = { 0, 0 };
Point finish = { 0, 0 };

void ReadInput(ifstream &fIn, LabyrinthVec & Labyrinth)
{
	string currString;
	size_t row = 0;
	while (getline(fIn, currString) && row < MAX_SIZE - 1)
	{
		for (size_t col = 0; col < currString.size(); col++)
		{

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
	LabyrinthVec Labyrinth(MAX_SIZE, vector<int>(MAX_SIZE, 0));
	ReadInput(fileIn, Labyrinth);
		
	//LakeVec lake(lakeSize, vector<int>(lakeSize, 0)
    return 0;
}

