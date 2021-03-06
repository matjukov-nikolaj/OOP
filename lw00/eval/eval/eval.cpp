#include "stdafx.h"
#include <iostream>
using namespace std;

enum StrintToDoubleErrors { SUCCESS, OVERFILL, UNDERFILL, INCONVERTIBLE };
const char ADDITION = '+';
const char DIFFERENCE = '-';
const char MULTIP = '*';
const char DIVISION = '/';
const double DOUBLE_MAX = numeric_limits<double>::max();
const double DOUBLE_MIN = numeric_limits<double>::min();
const double FLOAT_MAX = numeric_limits<float>::max();
const double FLOAT_MIN = numeric_limits<float>::min();


StrintToDoubleErrors strintToDouble(float &num, const char *str)
{
	char *pLastChar;
	double  number;
	errno = 0;
	number = strtod(str, &pLastChar);
	if (*str == '\0' || *pLastChar != '\0') {
		cout << "Argument is not a number." << endl;
		return INCONVERTIBLE;
	}
	if (number != 0) {
		if ((errno == ERANGE && number == DOUBLE_MAX) || (number > FLOAT_MAX)) {
			cout << "The number is more than FLOAT_MAX" << endl;
			return OVERFILL;
		}
		if ((errno == ERANGE && number == DOUBLE_MIN) || (number < FLOAT_MIN)) {
			cout << "The number is less than FLOAT_MIN" << endl;
			return UNDERFILL;
		}
	}
	num = number;
	return SUCCESS;
}

float calculateTwoOperands(char sign, float numOne, float numTwo)
{
	switch (sign)
	{
	case ADDITION:
		numOne += numTwo;
		break;
	case DIFFERENCE:
		numOne -= numTwo;
		break;
	case MULTIP:
		numOne *= numTwo;
		break;
	case DIVISION:
		numOne /= numTwo;
		break;
	}
	return numOne;
}

int main(int argc, char* argv[])
{
	if (argc <= 4)
	{
		cout << "The program calculates the sum, a difference, multiplication, division of the arguments of a command line." << endl;
		cout << "Write so: eval.exe 1 + 3 - ... * 4 / 3 + ... " << endl;
		return 0;
	}
	float numberOne = 0;
	float numberTwo = 0;
	float result = 0;
	int i = 1;
	bool calculation = true;
	char sign = ' ';
	StrintToDoubleErrors numberOneIsGood = strintToDouble(numberOne, argv[i]);
	if (numberOneIsGood != SUCCESS) return 1;
	while (calculation)
	{
		i++;
		if ((argv[i][0] != DIVISION) & (argv[i][0] != DIFFERENCE) & (argv[i][0] != MULTIP) & (argv[i][0] != ADDITION))
		{
			cout << "Argument is not a arithmetic number." << endl;
			return 1;
		} else sign = argv[i][0];
		i++;
		StrintToDoubleErrors numberTwoIsGood = strintToDouble(numberTwo, argv[i]);
		if (numberTwoIsGood != SUCCESS) return 1;
		if ((numberTwo == 0) & (sign == DIVISION)) {
			cout << "it is impossible to divide into zero." << endl;
			return 1;
		}
		result = calculateTwoOperands(sign, numberOne, numberTwo);
		if (i == (argc - 1)) calculation = false;
		numberOne = result;
	}
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(3);
	cout << result << endl;
	return 0;
}
