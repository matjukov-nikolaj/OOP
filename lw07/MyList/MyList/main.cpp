// MyList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyList.h"


int main()
{
	CMyList<std::string> list;
	list.PushFront("lol");
	list.PushFront("kek");
	list.Erase((++list.begin()));
	return 0;
}

