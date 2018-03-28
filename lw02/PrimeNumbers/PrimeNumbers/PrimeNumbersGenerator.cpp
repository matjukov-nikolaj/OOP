#include "stdafx.h"
#include "PrimeNumbersGenerator.h"

static const int MAX_BOUND = 100000000;
static const int MIN_BOUND = 2;

bool IsCorrectUpperBound(int upperBound)
{
	return (upperBound >= MIN_BOUND && upperBound <= MAX_BOUND);
}

std::set<int> GetPrimeNumbers(const std::vector<bool>& vec)
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

void StartEratosthenesSieve(std::vector<bool>& sieve)
{
	int step = 1;
	for (int i = 2; i * i < sieve.size(); ++i)
	{
		if (sieve[i])
		{
			for (int j = i * i; j < sieve.size(); j += i * step)
			{
				sieve[j] = false;
			}
		}
		step = 2;
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> sieve(upperBound + 1, true);
	StartEratosthenesSieve(sieve);
	std::set<int> primeNumbers = GetPrimeNumbers(sieve);
	return primeNumbers;
}
