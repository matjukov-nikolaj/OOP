#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
using LabyrinthVec = vector<vector<int>>;

const size_t MAX_SIZE = 100;
const short BORDER = -2;
const short EMPTY = 0;
const short WALL = -1;
const short BEGIN = -3;
const short END = -4;
const short UNKNOWN = -5;

struct Point
{
	size_t x;
	size_t y;
};

struct Labyrinth
{
	LabyrinthVec field;
	Point size;
	Point begin;
	Point end;
};

Labyrinth InitLabyrinth()
{
	Labyrinth labytinth;
	labytinth.field = LabyrinthVec(MAX_SIZE, vector<int>(MAX_SIZE, 0));
	labytinth.begin = { 0, 0 };
	labytinth.end = { 0, 0 };
	labytinth.size = { 0, 0 };
	return labytinth;
}

short GetValueOfCell(char ch)
{
	switch (ch)
	{
	case '#':
		return WALL;
		break;
	case ' ':
		return EMPTY;
		break;
	case 'B':
		return END;
		break;
	case 'A':
		return BEGIN;
		break;
	default:
		return UNKNOWN;
		break;
	}
}

Labyrinth ReadLabyrinth(ifstream &fIn, bool &err)
{
	Labyrinth labyrinth = InitLabyrinth();
	string currLine;
	size_t row = 0;
	while (getline(fIn, currLine) && row < MAX_SIZE)
	{
		if (currLine.size() > labyrinth.size.x)
		{
			labyrinth.size.x = currLine.size();
		}
		for (size_t col = 0; col < currLine.size(); col++)
		{
			if (GetValueOfCell(currLine[col]) == UNKNOWN)
			{
				err = true;
				return labyrinth;
			}
			labyrinth.field[row][col] = GetValueOfCell(currLine[col]);
			if (GetValueOfCell(currLine[col]) == BEGIN)
			{
				labyrinth.begin = { col, row };
			}
			if (GetValueOfCell(currLine[col]) == END)
			{
				labyrinth.end = { col, row };
			}
		}
		row++;
	}
	labyrinth.size.y = row;
	return labyrinth;
}

void PrintLabyrinthInFile(ofstream & fOut, const Labyrinth & labyrinth)
{
	for (size_t row = 0; row < labyrinth.size.y; row++)
	{
		for (size_t col = 0; col < labyrinth.size.x; col++)
		{
			if ((labyrinth.field[row][col] >= 0) && (labyrinth.field[row][col] < 10))
			{
				cout << "  " << labyrinth.field[row][col];
			}
			else if (labyrinth.field[row][col] >= 10)
			{
				cout << " " << labyrinth.field[row][col];
			}
			else
			{
				cout << " "  <<labyrinth.field[row][col];
			}
			if (col == labyrinth.begin.x && row == labyrinth.begin.y)
			{
				fOut << 'A';
			}
			else if (col == labyrinth.end.x && row == labyrinth.end.y)
			{
				fOut << 'B';
			}
			else if (labyrinth.field[row][col] == -1)
			{
				fOut << '#';
			}
			else
			{
				fOut << ' ';
			}
		}
		cout << endl;
		fOut << endl;
	}
}

void PrintLabyrinthInCons(const Labyrinth & labyrinth)
{
	for (size_t row = 0; row < labyrinth.size.y; row++)
	{
		for (size_t col = 0; col < labyrinth.size.x; col++)
		{
			if ((labyrinth.field[row][col] >= 0) && (labyrinth.field[row][col] < 10))
			{
				cout << "  " << labyrinth.field[row][col];
			}
			else if (labyrinth.field[row][col] >= 10)
			{
				cout << " " << labyrinth.field[row][col];
			}
			else
			{
				cout << " " << labyrinth.field[row][col];
			}
		}
		cout << endl;
	}
}

void VisitCell(Labyrinth &labyrinth, queue <Point> &q, Point currPos, const int dX, const int dY)
{
	if ((labyrinth.field[currPos.x + dX][currPos.y + dY] == 0))
	{
		int level;
		level = labyrinth.field[currPos.x][currPos.y];
		if (level == -3)
		{
			level = 1;
		}
		level++;
		labyrinth.field[currPos.x + dX][currPos.y + dY] = level;
		currPos.x += dX;
		currPos.y += dY;
		q.push(currPos);
	}
}

void SearchOfAWay(Labyrinth &labyrinth)
{
	queue <Point> q;
	q.push(labyrinth.begin);
	Point currPos = { 0, 0 };
	while ((q.size() > 0) && (currPos.x != labyrinth.end.x) && (currPos.y != labyrinth.end.y))
	{
		Point currPos = q.front();
		q.pop();
		VisitCell(labyrinth, q, currPos, 1, 0);
		//PrintLabyrinthInCons(labyrinth);
		VisitCell(labyrinth, q, currPos, -1, 0);
		//PrintLabyrinthInCons(labyrinth);
		VisitCell(labyrinth, q, currPos, 0, 1);
		//PrintLabyrinthInCons(labyrinth);
		VisitCell(labyrinth, q, currPos, 0, -1);
		//PrintLabyrinthInCons(labyrinth);
		//cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: replace.exe <input file> <output file>" << endl;
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
	bool err = false;
	Labyrinth labyrinth = ReadLabyrinth(fileIn, err);
	SearchOfAWay(labyrinth);
	PrintLabyrinthInFile(fileOut, labyrinth);
    return 0;
}

