// htmlDecode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HtmlEncode.h"

void EncodeHtmlEntities(std::istream& input, std::ostream& output)
{
	std::string html;
	while (std::getline(input, html))
	{
		output << HtmlEncode(html) << std::endl;
	}
}

int _tmain()
{
	EncodeHtmlEntities(std::cin, std::cout);
	return 0;
}
