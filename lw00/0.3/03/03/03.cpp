#include "stdafx.h"
#include <iostream>
using namespace std;

enum StrintToIntErrors { SUCCESS, OVERFILL, UNDERFILL, INCONVERTIBLE };

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
	int number = 0;
	i = 1;
	int quantityNumbersInLine = 0;
	int currNum = 1;
	int prevNum = -1;
	while (number <= maxNumber)
	{   
		number = currNum + prevNum;
		prevNum = currNum;
		currNum = number;
		if (number > maxNumber) break;
		cout << number;
		quantityNumbersInLine++;
		if ((quantityNumbersInLine != 5) & (number + prevNum <= maxNumber)) cout << ", ";
		if (quantityNumbersInLine == 5)
		{
			quantityNumbersInLine = 0;
			cout << endl;
		}
	}
	cout << std::endl;
	return 0;
}
