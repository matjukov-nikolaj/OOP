#include "stdafx.h"
#include "HtmlDecode.h"

const std::unordered_map<std::string, std::string> HTML_ENTITIES = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

std::string DecodeHtmlEntityInString(const std::string &str, const std::string &searchStr, const std::string &replacementStr)
{
	if (searchStr.empty())
	{
		return str;
	}
	std::string result;
	size_t pos = 0;
	for (size_t foundPos = 0; foundPos != std::string::npos; pos = foundPos + searchStr.size())
	{
		foundPos = str.find(searchStr, pos);
		if (foundPos != std::string::npos)
		{
			result.append(str, pos, foundPos - pos);
			result.append(replacementStr);
		}
		else
		{
			break;
		}
	}
	result.append(str.substr(pos));
	return result;
}

std::string HtmlDecode(const std::string &html)
{
	std::string result = html;
	for (auto & htmlEntity : HTML_ENTITIES)
	{
		result = DecodeHtmlEntityInString(result, htmlEntity.first, htmlEntity.second);
	}
	return result;
}
