#include "stdafx.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int i = 100;
	if (i == 100)
	{
		while (i != 0)
		{
			std::cout << i;
			i -= 2;
			if (i != 0)
			{
				std::cout << ", ";
			}
		}
	}
	std::cout << "\n";
	return 0;
}
