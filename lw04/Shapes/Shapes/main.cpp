// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CTraingle.h"


int _tmain()
{
	try
	{
		//CTraingle traingle({ 0, 0 }, { 1, 1 }, {2, 0}, "lol", "kek");
		//double lol = traingle.GetArea(); // проверить формулу
		//std::cout << lol << "\n";
		////double lol = traingle.GetPerimeter();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

