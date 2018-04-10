#include "stdafx.h"
#include "Replace.h"

std::string FindAndReplace(const std::string& subject, const std::string& search, const std::string& replace)
{
	if (search.empty())
	{
		return subject;
	}
	std::string result;
	size_t pos = 0;
	while (pos < subject.size())
	{
		size_t foundPos = subject.find(search, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replace);
			pos = foundPos + search.size();
		}
		else
		{
			break;
		}
	}
	return result;
}
