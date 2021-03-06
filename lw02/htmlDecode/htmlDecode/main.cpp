// htmlDecode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HtmlDecode.h"

void DecodeHtmlEntities(std::istream& input, std::ostream& output)
{
	std::string html;
	while (std::getline(input, html))
	{
		output << HtmlDecode(html) << std::endl;
	}
}

int _tmain()
{
	DecodeHtmlEntities(std::cin, std::cout);
	return 0;
}
