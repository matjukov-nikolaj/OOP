#pragma once
class CUtilites
{
public:
	CUtilites();
	~CUtilites();
	static const std::string DoubleToString(double value);
	static const uint32_t StringToUInt(const std::string & str);
};

