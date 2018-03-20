#include "stdafx.h"
#include "PrimeNumbersGenerator.h"

std::set<int> GetPrimeNumbers(const std::vector<bool> & vec)
{
	std::set<int> numbers;
	for (auto i = 2; i < vec.size(); ++i)
	{
		if (vec[i])
		{
			numbers.insert(numbers.end(), static_cast<int>(i));
		}
	}
	return numbers;
}

void StartEratosthenesSieve(std::vector<bool> &numbers)
{
	int step = 1;
	for (size_t i = 2; i*i < numbers.size(); ++i)
	{
		if (numbers[i])
		{
			for (size_t j = i * i; j < numbers.size(); j += i * step)
			{
				numbers[j] = false;
			}
		}
		step = 2;
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> numbers(upperBound + 1, true);
	StartEratosthenesSieve(numbers);
	std::set<int> primeNumbers = GetPrimeNumbers(numbers);
	return primeNumbers;
}
