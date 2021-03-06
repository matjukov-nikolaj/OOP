#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

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
} // namespace NumericCellType

namespace CharCellType
{
constexpr char EMPTY = ' ';
constexpr char WALL = '#';
constexpr char START = 'A';
constexpr char FINISH = 'B';
constexpr char WAY = '.';
} // namespace CharCellType

enum class ErrorCode
{
	None,
	UnknownCell,
	InvalidPointsCount,
	NoPath,
	IncorrectLabyrinthSize,
	InputFileNotOpened,
	OutputFileNotOpened,
	FailedToSaveData
};

struct Point
{
	int x;
	int y;
};

struct Size
{
	size_t width;
	size_t height;
};

struct Displacement
{
	short horizontal;
	short vertical;
};

const Displacement DIRECTIONS[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

struct Labyrinth
{
	LabyrinthVec field;
	Size size;
	Point start;
	Point finish;
};

struct LabyrinthStats
{
	int numberOfStartPoints = 0;
	int numberOfFinalPoints = 0;
	ErrorCode errorCode = ErrorCode::None;
};

void SetBordersOfLabyrinth(Labyrinth& labyrinth)
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

bool IsEqualPoints(const Point& pointOne, const Point& pointTwo)
{
	return (pointOne.x == pointTwo.x && pointOne.y == pointTwo.y);
}

bool IsEqualCellValue(int valueOne, int valueTwo)
{
	return (valueOne == valueTwo);
}

bool IsIncorrectLabyrinthSize(const Size& size)
{
	return size.width > MAX_SIZE || size.height > MAX_SIZE;
}

void ReadRow(Labyrinth& labyrinth, const string& str, LabyrinthStats& stats, int row)
{
	for (int column = 1; column <= str.size(); column++)
	{

		if (GetValueOfCell(str[column - 1]) == NumericCellType::UNKNOWN)
		{
			stats.errorCode = ErrorCode::UnknownCell;
			return;
		}

		labyrinth.field[row][column] = GetValueOfCell(str[column - 1]);
		if (str[column - 1] == CharCellType::START)
		{
			labyrinth.start = { column, row };
			stats.numberOfStartPoints++;
		}

		if (str[column - 1] == CharCellType::FINISH)
		{
			labyrinth.finish = { column, row };
			stats.numberOfFinalPoints++;
		}
	}
}

Labyrinth ReadLabyrinth(ifstream& input, ErrorCode& errorCode)
{
	Labyrinth labyrinth = InitLabyrinth();
	string currLine;
	LabyrinthStats stats;
	int row = 1;

	while (getline(input, currLine) && row < MAX_SIZE_WITH_BORDERS)
	{
		labyrinth.size.width = (currLine.size() > labyrinth.size.width) ? currLine.size() : labyrinth.size.width;
		if (IsIncorrectLabyrinthSize(labyrinth.size))
		{
			errorCode = ErrorCode::IncorrectLabyrinthSize;
			return labyrinth;
		}

		ReadRow(labyrinth, currLine, stats, row);
		if (stats.errorCode != ErrorCode::None)
		{
			errorCode = stats.errorCode;
			return labyrinth;
		}
		row++;
		labyrinth.size.height = row;
	}

	if (stats.numberOfStartPoints != VALID_NUMBER_OF_POINTS || stats.numberOfFinalPoints != VALID_NUMBER_OF_POINTS)
	{
		errorCode = ErrorCode::InvalidPointsCount;
		return labyrinth;
	}
	return labyrinth;
}

void PrintValueOfCell(ofstream& output, const Labyrinth& labyrinth, Point& point)
{
	char ch = ' ';
	int cellValue = labyrinth.field[point.y][point.x];

	if (IsEqualPoints(point, labyrinth.finish))
	{
		ch = CharCellType::FINISH;
	}
	else if (IsEqualPoints(point, labyrinth.start))
	{
		ch = CharCellType::START;
	}
	else if (IsEqualCellValue(cellValue, NumericCellType::WALL))
	{
		ch = CharCellType::WALL;
	}
	else if (IsEqualCellValue(cellValue, NumericCellType::WAY))
	{
		ch = CharCellType::WAY;
	}
	else
	{
		ch = CharCellType::EMPTY;
	}
	output << ch;
}

void PrintLabyrinth(const Labyrinth& labyrinth, ofstream& output)
{
	for (int row = 1; row < labyrinth.size.height; row++)
	{
		for (int col = 1; col <= labyrinth.size.width; col++)
		{
			Point point = { col, row };
			PrintValueOfCell(output, labyrinth, point);
		}
		output << endl;
	}
}

void PropagateWaveOnNeighborCells(Labyrinth& labyrinth, queue<Point>& queue, const Point& pos)
{
	for (auto& offset : DIRECTIONS)
	{
		Point posWithOffset = { pos.x + offset.horizontal, pos.y + offset.vertical };
		int cellValue = labyrinth.field[posWithOffset.y][posWithOffset.x];
		
		if (cellValue == NumericCellType::EMPTY)
		{
			cellValue = labyrinth.field[pos.y][pos.x] + 1;
			queue.push(posWithOffset);
			labyrinth.field[posWithOffset.y][posWithOffset.x] = cellValue;
		}
	}
}

void StartWaveAlgorithm(Labyrinth& labyrinth)
{
	queue<Point> queue;
	queue.push(labyrinth.start);
	Point pos = { 0, 0 };

	while (queue.size() > 0 && !IsEqualPoints(pos, labyrinth.finish))
	{
		pos = queue.front();
		queue.pop();
		PropagateWaveOnNeighborCells(labyrinth, queue, pos);
	}
}

bool IsNextCellForWay(const Labyrinth& labyrinth, const Point& pos, const Point& posWithOffset)
{
	return labyrinth.field[posWithOffset.y][posWithOffset.x] == labyrinth.field[pos.y][pos.x] - 1;
}

Point FindNextPathCell(Labyrinth& labyrinth, const Point& pos)
{
	Point nextPos = { 0, 0 };
	for (auto& offset : DIRECTIONS)
	{
		Point posWithOffset = { pos.x + offset.horizontal, pos.y + offset.vertical };
		if (IsNextCellForWay(labyrinth, pos, posWithOffset))
		{
			nextPos = { pos.x + offset.horizontal, pos.y + offset.vertical };
			labyrinth.field[pos.y][pos.x] = NumericCellType::WAY;
			break;
		}
	}
	return nextPos;
}

void SearchTheWay(Labyrinth& labyrinth, ErrorCode& errorCode)
{
	errorCode = ErrorCode::None;
	StartWaveAlgorithm(labyrinth);
	Point pos = labyrinth.finish;

	if (labyrinth.field[pos.y][pos.x] == NumericCellType::EMPTY)
	{
		errorCode = ErrorCode::NoPath;
		return;
	}

	while (!IsEqualPoints(pos, labyrinth.start))
	{
		pos = FindNextPathCell(labyrinth, pos);
	}
}

string GetErrorMessage(ErrorCode errorCode)
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
	case ErrorCode::InputFileNotOpened:
		return "The input file has not open for reading!";
		break;
	case ErrorCode::OutputFileNotOpened:
		return "The output file has not open for reading!";
		break;
	case ErrorCode::FailedToSaveData:
		return "Failed to save data on disk!";
		break;
	}
	return "";
}

bool ReadLabyrinthFromFile(const string& inputfileName, Labyrinth& labyrinth, ErrorCode& errorCode)
{
	ifstream fileIn(inputfileName);
	if (!fileIn.is_open())
	{
		errorCode = ErrorCode::InputFileNotOpened;
		return false;
	}

	labyrinth = ReadLabyrinth(fileIn, errorCode);
	if (errorCode != ErrorCode::None)
	{
		return false;
	}
	return true;
}

bool PrintLabyrinthInFile(const string& outputFileName, Labyrinth& labyrinth, ErrorCode& errorCode)
{
	ofstream fileOut(outputFileName);
	if (!fileOut.is_open())
	{
		errorCode = ErrorCode::OutputFileNotOpened;
		return false;
	}

	PrintLabyrinth(labyrinth, fileOut);
	if (!fileOut.flush())
	{
		errorCode = ErrorCode::FailedToSaveData;
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

	Labyrinth labyrinth;
	ErrorCode errorCode = ErrorCode::None;

	if (!ReadLabyrinthFromFile(argv[1], labyrinth, errorCode))
	{
		cout << GetErrorMessage(errorCode) << endl;
		return 1;
	}

	SearchTheWay(labyrinth, errorCode);

	if (errorCode != ErrorCode::None)
	{
		cout << GetErrorMessage(errorCode) << endl;
		return 1;
	}

	if (!PrintLabyrinthInFile(argv[2], labyrinth, errorCode))
	{
		cout << GetErrorMessage(errorCode) << endl;
		return 1;
	}

	return 0;
}
