// MyList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyList.h"
#include <iostream>

int _tmain()
{
	CMyList<std::string> list;
	list.PushFront("lol");
	//std::cout << list.GetElement(1) << "\n";
	return 0;
}

