#include "stdafx.h"
#include "CUtilites.h"
#include "Config.h"

const std::string CUtilites::DoubleToString(double value)
{
	std::stringstream strm;
	strm << std::setprecision(NUMBER_DIGIT_AFTER_DECIMAL) << value;
	std::string str;
	strm >> str;
	return str;
}

const uint32_t CUtilites::StringToUInt(const std::string & str)
{
	uint32_t x;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> x;
	return x;
}
