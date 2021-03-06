#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const short MATRIX_SIZE = 3;
typedef double Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
typedef double Matrix2x2[MATRIX_SIZE - 1][MATRIX_SIZE - 1];

struct WrappedMatrix3x3 {
	Matrix3x3 items;
};

struct WrappedMatrix2x2 {
	Matrix2x2 items;
};

bool ReadMatrix(ifstream &fIn, WrappedMatrix3x3 &matrix)
{
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		for (short j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(fIn >> matrix.items[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

double GetDeterminantOfMatrix(const WrappedMatrix3x3 &matrix)
{
	double determinant = 0;
	determinant += matrix.items[0][0] * matrix.items[1][1] * matrix.items[2][2];
	determinant += matrix.items[0][1] * matrix.items[1][2] * matrix.items[2][0];
	determinant += matrix.items[0][2] * matrix.items[1][0] * matrix.items[2][1];
	determinant -= matrix.items[0][2] * matrix.items[1][1] * matrix.items[2][0];
	determinant -= matrix.items[0][0] * matrix.items[1][2] * matrix.items[2][1];
	determinant -= matrix.items[0][1] * matrix.items[1][0] * matrix.items[2][2];
	return determinant;
}

double GetMinor(const WrappedMatrix3x3 &matrix, const short row, const short col)
{
	WrappedMatrix2x2 Matrix2x2;
	short Matrix2x2Row = 0;
	short Matrix2x2Col = 0;
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		Matrix2x2Col = 0;
		if (i != row)
		{
			for (short j = 0; j < MATRIX_SIZE; j++)
			{
				if (j != col)
				{
					Matrix2x2.items[Matrix2x2Row][Matrix2x2Col] = matrix.items[i][j];
					Matrix2x2Col++;
				}
			}
			Matrix2x2Row++;
		}
	}

	double determinant = Matrix2x2.items[0][0] * Matrix2x2.items[1][1] - Matrix2x2.items[0][1] * Matrix2x2.items[1][0];
	return determinant;
}

WrappedMatrix3x3 GetMatrixOfMinors(const WrappedMatrix3x3 &matrix)
{
	WrappedMatrix3x3 matrixOfMinors;
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		for (short j = 0; j < MATRIX_SIZE; j++)
		{
			matrixOfMinors.items[i][j] = GetMinor(matrix, i, j);
		}
	}
	return matrixOfMinors;
}

WrappedMatrix3x3 GetMatrixOfAlgebraicAdditions(WrappedMatrix3x3 matrix)
{
	matrix.items[0][1] = -matrix.items[0][1];
	matrix.items[1][0] = -matrix.items[1][0];
	matrix.items[1][2] = -matrix.items[1][2];
	matrix.items[2][1] = -matrix.items[2][1];
	return matrix;
}

WrappedMatrix3x3 GetTransposedMatrix(WrappedMatrix3x3 matrix)
{
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		for (short j = 0; j < MATRIX_SIZE && j < i; j++)
		{
			swap(matrix.items[i][j], matrix.items[j][i]);
		}
	}
	return matrix;
}

void MultiplyMatrixByNumber(WrappedMatrix3x3 &matrix, const double multiplier)
{
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		for (short j = 0; j < MATRIX_SIZE; j++)
		{
			matrix.items[i][j] *= multiplier;
		}
	}
}

WrappedMatrix3x3 GetInvertMatrix(const WrappedMatrix3x3 &matrix, bool &isSingularMatrix)
{
	double determinant = GetDeterminantOfMatrix(matrix);
	if (abs(determinant) < 1E-12)
	{
		isSingularMatrix = true;
		return matrix;
	}
	WrappedMatrix3x3 matrixOfMinors = GetMatrixOfMinors(matrix);
	WrappedMatrix3x3 matrixOfAlgebraicAdditions = GetMatrixOfAlgebraicAdditions(matrixOfMinors);
	WrappedMatrix3x3 transposedMatrix = GetTransposedMatrix(matrixOfAlgebraicAdditions);
	MultiplyMatrixByNumber(transposedMatrix, 1 / determinant);
	return transposedMatrix;
}


void PrintMatrix(WrappedMatrix3x3 &matrix)
{
	cout << fixed << setprecision(3);
	for (short i = 0; i < MATRIX_SIZE; i++)
	{
		for (short j = 0; j < MATRIX_SIZE; j++)
		{
			cout << matrix.items[i][j] << " ";
		}
		cout << endl;
	}
}

bool ReadMatrixFromFile(const string &inputFileName, WrappedMatrix3x3 &matrix)
{
	ifstream fileIn(inputFileName);
	if (!fileIn.is_open())
	{
		cout << "File " << inputFileName << " has not opened for reading." << endl;;
		return false;
	}
	
	if (!ReadMatrix(fileIn, matrix))
	{
		cout << "Error of reading a matrix from the file." << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: invert.exe <input file>" << endl;
		return 1;
	}
	WrappedMatrix3x3 matrix;
	if (!ReadMatrixFromFile(argv[1], matrix))
	{
		return 1;
	}

	bool isSingularMatrix = false;
	WrappedMatrix3x3 invertedMatrix = GetInvertMatrix(matrix, isSingularMatrix);
	if (isSingularMatrix)
	{
		cout << "it is impossible to invert a matrix because the determinant is equal to 0" << endl;
		return 1;
	}

	PrintMatrix(invertedMatrix);
    return 0;
}
