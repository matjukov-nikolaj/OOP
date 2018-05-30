#pragma once
#include "stdafx.h"

template < typename T, typename Less>
bool FindMax(
	const std::vector<T>& arr,
	T& maxValue,
	Less&& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto largest = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*largest, *it))
		{
			largest = it;
		}
	}
	
	maxValue = *largest;
	return true;
}
