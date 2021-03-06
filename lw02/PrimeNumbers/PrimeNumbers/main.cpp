// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumbersGenerator.h"

const int MAX_BOUND = 100000000;
const int MIN_BOUND = 2;

bool IsCorrectUpperBound(int upperBound)
{
	return (upperBound >= MIN_BOUND && upperBound <= MAX_BOUND);
}

void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers)
{
	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<int>(output, " "));
	output << "\n";
}

int _tmain(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Incorrect number of parameters." << std::endl;
		std::cout << "Write so: main.exe <number>" << std::endl;
		return 1;
	}
	int upperBound = std::atoi(argv[1]);
	if (!IsCorrectUpperBound(upperBound))
	{
		std::cout << "Incorrect upper bound." << std::endl;
		return 1;
	}
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(std::cout, primeNumbers);
	return 0;
}
