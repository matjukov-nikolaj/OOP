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

const uint32_t StringToUInt(const std::string & str)
{
	uint32_t x;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> x;
	return x;
}
