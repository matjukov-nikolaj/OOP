#include "stdafx.h"
#include "ConvertType.h"
#include "Config.h"

const std::string DoubleToString(double value)
{
	std::stringstream strm;
	strm << std::setprecision(NUMBER_DIGIT_AFTER_DECIMAL) << value;
	std::string str;
	strm >> str;
	return str;
}