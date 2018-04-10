#include "stdafx.h"
#include "HtmlEncode.h"

const std::unordered_map<std::string, std::string> HTML_ENTITIES = {
	{ ">", "&gt;" },
	{ "&", "&amp;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ "\"", "&quot;" }
};

std::string DecodeHtmlEntityInString(const std::string& str, const std::string& searchStr, const std::string& replacementStr)
{
	if (searchStr.empty())
	{
		return str;
	}
	std::string result;
	size_t pos = 0;
	while (pos < str.size())
	{
		size_t foundPos = str.find(searchStr, pos);
		result.append(str, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementStr);
			pos = foundPos + searchStr.size();
		}
		else
		{
			break;
		}
	}
	return result;
}

std::string HtmlEncode(const std::string& html)
{
	std::string result = html;
	for (auto& htmlEntity : HTML_ENTITIES)
	{
		result = DecodeHtmlEntityInString(result, htmlEntity.first, htmlEntity.second);
	}
	return result;
}
