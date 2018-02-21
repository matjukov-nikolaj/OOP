#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

bool IsValidValue(int number)
{
	bool isValidValue = true;
	const int MAX_VALUE = 255;
	const int MIN_VALUE = 0;
	if ((number < MIN_VALUE) || (number > MAX_VALUE))
	{
		cout << "The entrance argument doesn't enter range from 0 to 255." << endl;
		isValidValue = false;
	}
	return isValidValue;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

unsigned char FlipBits(unsigned char number)
{
	unsigned char result = 0;
	for (int i = 0; i < 8; i++)
	{
		result = result << 1;
		result |= number & 1;
		number = number >> 1;
	}
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: flipbyte.exe <number>" << endl;
		return 1;
	}
	bool err;
	int number = StringToInt(argv[1], err);
	if (err)
	{
		cout << "Entrance argument is not a number." << endl;
		return 1;
	}
	if (!IsValidValue(number))
	{
		return 1;
	}
	unsigned char byteValue = static_cast<unsigned char>(number);
	int newNumber = FlipBits(byteValue);
	cout << newNumber << endl;
    return 0;
}
