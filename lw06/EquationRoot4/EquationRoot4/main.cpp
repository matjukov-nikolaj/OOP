// EquationRoot4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EquationRoot4.h"

int _tmain()
{
	double a, b, c, d, e;
	std::cout << "Enter coefficients of the equation of the 4th degree" << "\n"
		<< "ax^4 + bx^3 + cx^2 + dx + e = 0" << "\n";
	std::cout << "\n";
	while (std::cout << "> " &&(std::cin >> a) && (std::cin >> b)
		&& (std::cin >> c) && (std::cin >> d) && (std::cin >> e))
	{
		try
		{
			PrintRoots(Solve4(a, b, c, d, e), std::cout);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << "\n";
		}
	}
	return 0;
}

