#include "stdafx.h"
#include "VectorProcessor.h"
#include <string>

std::string GetErrorMessage(const ErrorCode &errorCode)
{
	switch (errorCode)
	{
	case ErrorCode::VectorIsEmpty:
		return "Vector is empty";
		break;
	case ErrorCode::DivisionByZero:
		return "Division by zero";
		break;
	}
	return "";
}

int _tmain(int argc, char *argv[])
{
	std::vector<double> vec;
	ErrorCode errorCode = ErrorCode::None;
	ReadVector(std::cin, vec);
	ProcessVector(vec, errorCode);
	if (errorCode != ErrorCode::None)
	{
		std::cout << GetErrorMessage(errorCode) << std::endl;
		return 1;
	}
	sort(vec.begin(), vec.end());
	PrintVector(std::cout, vec);
	return 0;
}
