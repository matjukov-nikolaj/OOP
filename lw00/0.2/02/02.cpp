#include "stdafx.h"
#include <iostream>
using namespace std;

enum StrintToIntErrors { SUCCESS, OVERFILL, UNDERFILL, INCONVERTIBLE };

int sumDigit(int number)
{
	int sum = 0;
	while (number != 0)
	{
		sum += number % 10;
		number /= 10;
	}
	return sum;
}

int getLastNumber(int maxNum)
{
	int number = maxNum;
	bool findLastSuitNumber = false;
	int sumDigitOfNumber;
	while (!findLastSuitNumber)
	{
		sumDigitOfNumber = sumDigit(number);
		if (number % sumDigitOfNumber == 0)
		{
			findLastSuitNumber = true;
		} else {
			number--;
		}
	}
	return number;
}

StrintToIntErrors strintToInt(int &maxNumber, const char *str)
{
	char *pLastChar;
	long  number;
	errno = 0;
	number = strtol(str, &pLastChar, 10);
	if ((errno == ERANGE && number == LONG_MAX) || number > INT_MAX) {
		cout << "The number is more than MAX_INT" << endl;
		return OVERFILL;
	}
	if ((errno == ERANGE && number == LONG_MIN) || number < INT_MIN) {
		cout << "The number is less than MIN_INT" << endl;
		return UNDERFILL;
	}
	if (*str == '\0' || *pLastChar != '\0') {
		cout << "Argument is not a number." << endl;
		return INCONVERTIBLE;
	}
	maxNumber = number;
	return SUCCESS;
}

int main(int argc, char* argv[])
{
	int i;
	int sumDigitOfNumber;
	int lastSuitableNumber;
	if (argc != 2)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: 02.exe <number>" << endl;
		return 1;
	}
	int maxNumber;
	StrintToIntErrors maxNumberIsGood = strintToInt(maxNumber, argv[1]);
	if (maxNumberIsGood != SUCCESS)
		return 1;
	if (maxNumber <= 0)
	{
		cout << "The argument is less or is equal than 0." << endl;
		return 1;
	}
	lastSuitableNumber = getLastNumber(maxNumber);
	for (i = 1; i <= maxNumber; ++i)
	{
		sumDigitOfNumber = sumDigit(i);
		if (i % sumDigitOfNumber == 0)
		{
			cout << i;
			if (i != lastSuitableNumber)
			{
				cout << ", ";
			}
		}
	}
	cout << "\n";
	return 0;
}
