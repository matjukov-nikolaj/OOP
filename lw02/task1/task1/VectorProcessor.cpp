#include "stdafx.h"
#include "VectorProcessor.h"
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>
#include <functional>
#include <iterator>
#include <iomanip>

static const double ABSOLUTE_NULL = 1E-12;

void ReadVector(std::istream &input, std::vector<double> &vec)
{
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(vec));
}

void PrintVector(std::ostream &output, std::vector<double> vec)
{
	output << std::fixed << std::setprecision(3);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(output, " "));
	std::cout << std::endl;
}

void ProcessVector(std::vector<double> &vec, ErrorCode &errorCode)
{
	errorCode = ErrorCode::None;
	if (vec.empty())
	{
		errorCode = ErrorCode::VectorIsEmpty;
		return;
	}
	const double minElement = *min_element(vec.begin(), vec.end());
	const double maxElement = *max_element(vec.begin(), vec.end());
	if (abs(minElement) < ABSOLUTE_NULL)
	{
		errorCode = ErrorCode::DivisionByZero;
		return;
	}
	std::transform(vec.begin(), vec.end(), vec.begin(), [=](double number) { return number *= maxElement / minElement; });
}