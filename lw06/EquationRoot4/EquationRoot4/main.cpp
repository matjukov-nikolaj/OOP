// EquationRoot4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EquationRoot4.h"

int _tmain()
{
	try
	{
		std::cout << "Enter coefficients of the equation of the 4th degree" << "\n"
			<< "ax^4 + bx^3 + cx^2 + dx + e = 0" << "\n";
		double value;
		std::vector<double> values;
		while (!std::cin.eof())
		{
			std::cout << "> ";
			while (std::cin >> value)
			{
				values.push_back(value);
			}
			std::vector<double> roots = Solve4(values[0], values[1], values[2], values[3], values[4]);
			PrintRoots(roots, std::cout);
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

