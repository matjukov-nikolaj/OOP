#include "stdafx.h"
#include "CCar.h"
#include "ССarController.h"


int main()
{
	CCar car;
	CCarController carController;
	while (!std::cin.eof())
	{
		std::cout << "> ";
		carController.HandleCommand();
	}
	return 0;
}
