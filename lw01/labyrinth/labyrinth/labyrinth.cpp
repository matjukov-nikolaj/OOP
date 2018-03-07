#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
using LabyrinthVec = vector<vector<int>>;

const size_t MAX_SIZE = 100;
const size_t MAX_SIZE_WITH_BORDERS = 102;
const short VALID_NUMBER_OF_POINTS = 1;

namespace NumericCellType
{
	constexpr short BORDER = -2;
	constexpr short EMPTY = 0;
	constexpr short WALL = -1;
	constexpr short START = 1;
	constexpr short UNKNOWN = -3;
	constexpr short WAY = -4;
}

namespace CharCellType
{
	constexpr char EMPTY = ' ';
	constexpr char WALL = '#';
	constexpr char START = 'A';
	constexpr char FINISH = 'B';
	constexpr char WAY = '.';
}

enum class ErrorCode
{
	None, 
	UnknownCell,
	InvalidPointsCount,
	NoPath,
	IncorrectLabyrinthSize
};

struct Point
{
	size_t x;
	size_t y;
};

struct Size
{
	size_t width;
	size_t height;
};

struct Direction
{
	short left;
	short top;
};

const Direction DIRECTIONS[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

struct Labyrinth
{
	LabyrinthVec field;
	Size size;
	Point start;
	Point finish;
};

void SetBordersOfLabyrinth(Labyrinth &labyrinth)
{
	for (size_t i = 0; i < MAX_SIZE_WITH_BORDERS; i++)
	{
		labyrinth.field[i][0] = NumericCellType::BORDER;
		labyrinth.field[i][MAX_SIZE_WITH_BORDERS - 1] = NumericCellType::BORDER;
		labyrinth.field[0][i] = NumericCellType::BORDER;
		labyrinth.field[MAX_SIZE_WITH_BORDERS - 1][i] = NumericCellType::BORDER;
	}
}

Labyrinth InitLabyrinth()
{
	Labyrinth labyrinth;
	labyrinth.field = LabyrinthVec(MAX_SIZE_WITH_BORDERS, vector<int>(MAX_SIZE_WITH_BORDERS, 0));
	SetBordersOfLabyrinth(labyrinth);
	labyrinth.start = { 0, 0 };
	labyrinth.finish = { 0, 0 };
	labyrinth.size = { 0, 0 };
	return labyrinth;
}

short GetValueOfCell(char ch)
{
	switch (ch)
	{
	case CharCellType::WALL:
		return NumericCellType::WALL;
		break;
	case CharCellType::EMPTY:
		return NumericCellType::EMPTY;
		break;
	case CharCellType::FINISH:
		return NumericCellType::EMPTY;
		break;
	case CharCellType::START:
		return NumericCellType::START;
		break;
	default:
		return NumericCellType::UNKNOWN;
		break;
	}
}

bool IsEqualPoints(const Point &pointOne, const Point &pointTwo)
{
	return (pointOne.x == pointTwo.x && pointOne.y == pointTwo.y);
}

bool IsIncorrectLabyrinthSize(const Size &size)
{
	return size.width > MAX_SIZE || size.height > MAX_SIZE;
}

Labyrinth ReadLabyrinth(ifstream &input, ErrorCode &errorCode)
{
	Labyrinth labyrinth = InitLabyrinth();
	string currLine;
	short numberOfStartPoints = 0;
	short numberOfFinalPoints = 0;
	size_t row = 1;
	while (getline(input, currLine) && row < MAX_SIZE_WITH_BORDERS)
	{
		labyrinth.size.width = (currLine.size() > labyrinth.size.width) ? currLine.size() : labyrinth.size.width;
		if (IsIncorrectLabyrinthSize(labyrinth.size))
		{
			errorCode = ErrorCode::IncorrectLabyrinthSize;
			return labyrinth;
		}
		for (size_t column = 1; column <= currLine.size(); column++)
		{
			if (GetValueOfCell(currLine[column - 1]) == NumericCellType::UNKNOWN)
			{
				errorCode = ErrorCode::UnknownCell;
				return labyrinth;
			}
			labyrinth.field[row][column] = GetValueOfCell(currLine[column - 1]);
			if (currLine[column - 1] == CharCellType::START)
			{
				labyrinth.start = { column, row };
				numberOfStartPoints++;
			}
			if (currLine[column - 1] == CharCellType::FINISH)
			{
				labyrinth.finish = { column, row };
				numberOfFinalPoints++;
			}
		}
		row++;
		labyrinth.size.height = row;
	}
	if (numberOfStartPoints != VALID_NUMBER_OF_POINTS ||
		numberOfFinalPoints != VALID_NUMBER_OF_POINTS)
	{
		errorCode = ErrorCode::InvalidPointsCount;
		return labyrinth;
	}
	return labyrinth;
}

void PrintLabyrinthInFile(ofstream & output, const Labyrinth & labyrinth)
{
	for (size_t row = 1; row < labyrinth.size.height; row++)
	{
		for (size_t col = 1; col <= labyrinth.size.width; col++)
		{
			if (col == labyrinth.finish.x && row == labyrinth.finish.y)
			{
				output << CharCellType::FINISH;
			}
			else if (col == labyrinth.start.x && row == labyrinth.start.y)
			{
				output << CharCellType::START;
			}
			else if (labyrinth.field[row][col] == NumericCellType::WALL)
			{
				output << CharCellType::WALL;
			}
			else if (labyrinth.field[row][col] == NumericCellType::WAY)
			{
				output << CharCellType::WAY;
			}
			else
			{
				output << CharCellType::EMPTY;
			}
		}
		output << endl;
	}
}

void ChangeValueOfCell(Labyrinth &labyrinth, queue <Point> &queue, const Point &pos, int deltaX, int deltaY)
{
	Point posWithOffset = { pos.x + deltaX, pos.y + deltaY };
	int cellValue = labyrinth.field[posWithOffset.y][posWithOffset.x];
	if (cellValue != NumericCellType::WALL && cellValue == NumericCellType::EMPTY)
	{
		cellValue = labyrinth.field[pos.y][pos.x] + 1;
		queue.push(posWithOffset);
	}
	labyrinth.field[posWithOffset.y][posWithOffset.x] = cellValue;
}

void StartWaveAlgorithm(Labyrinth &labyrinth)
{
	queue <Point> queue;
	queue.push(labyrinth.start);
	Point pos = { 0, 0 };
	while (queue.size() > 0 && !IsEqualPoints(pos, labyrinth.finish))
	{
		pos = queue.front();
		queue.pop();
		for (auto & offset : DIRECTIONS)
		{
			ChangeValueOfCell(labyrinth, queue, pos, offset.left, offset.top);
		}
	}
}

bool IsVisitedCell(const Labyrinth &labyrinth, const Point & pos, int deltaX, int deltaY)
{
	return labyrinth.field[pos.y + deltaY][pos.x + deltaX] == labyrinth.field[pos.y][pos.x] - 1;
}

Point FindNextPosition(Labyrinth & labyrinth, const Point &pos)
{
	Point nextPos = { 0, 0 };
	for (auto & offset : DIRECTIONS)
	{
		if (IsVisitedCell(labyrinth, pos, offset.left, offset.top))
		{
			nextPos = { pos.x + offset.left, pos.y + offset.top };
			labyrinth.field[pos.y][pos.x] = NumericCellType::WAY;
			break;
		}
	}
	return nextPos;
}

ErrorCode SearchTheWay(Labyrinth &labyrinth)
{
	StartWaveAlgorithm(labyrinth);
	Point pos = labyrinth.finish;
	if (labyrinth.field[pos.y][pos.x] == NumericCellType::EMPTY)
	{
		return ErrorCode::NoPath;
	}
	while (!IsEqualPoints(pos, labyrinth.start))
	{
		pos = FindNextPosition(labyrinth, pos);
	}
	return ErrorCode::None;
}

string GetErrorMessage(const ErrorCode &errorCode)
{
	switch (errorCode)
	{
	case ErrorCode::UnknownCell:
		return "Unrecognized symbol!";
		break;
	case ErrorCode::InvalidPointsCount:
		return "Invalid number of points!";
		break;
	case ErrorCode::NoPath:
		return "There is no path from point A to point B!";
		break;
	case ErrorCode::IncorrectLabyrinthSize:
		return "The size of the labyrinth exceeds the maximum size of the field!";
		break;
	}
	return "";
}

bool FindAWayInLabyrinth(ifstream &fileIn, ofstream &fileOut)
{
	ErrorCode errorCode = ErrorCode::None;
	Labyrinth labyrinth = ReadLabyrinth(fileIn, errorCode);
	if (errorCode != ErrorCode::None)
	{
		fileOut << GetErrorMessage(errorCode) << endl;
		return false;
	}
	errorCode = SearchTheWay(labyrinth);
	if (errorCode != ErrorCode::None)
	{
		fileOut << GetErrorMessage(errorCode) << endl;
		return false;
	}
	PrintLabyrinthInFile(fileOut, labyrinth);
	return true;
}

bool FindPathOnLabyrinth(const std::string &inputFileName, const std::string &outputFileName)
{
	ifstream fileIn(inputFileName);
	if (!fileIn.is_open())
	{
		cout << "File " << inputFileName << " has not opened for reading.";
		return false;
	}
	ofstream fileOut(outputFileName);
	if (!fileOut.is_open())
	{
		cout << "File " << outputFileName << " has not opened for writing.";
		return false;
	}
	bool success = FindAWayInLabyrinth(fileIn, fileOut);
	if (!success)
	{
		return false;
	}
	if (!fileOut.flush())
	{
		std::cout << "Failed to save data on disk.\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: labyrinth.exe <input file> <output file>" << endl;
		return 1;
	}
	bool success = FindPathOnLabyrinth(std::string(argv[1]), std::string(argv[2]));
	if (!success)
	{
		return 1;
	}
    return 0;
}
