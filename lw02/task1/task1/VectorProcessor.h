#pragma once

enum class ErrorCode
{
	VectorIsEmpty,
	DivisionByZero,
	None
};

void ProcessVector(std::vector<double> &vec, ErrorCode &errorCode);
void ReadVector(std::istream &input, std::vector<double> &vec);
void PrintVector(std::ostream &output, std::vector<double> vec);
