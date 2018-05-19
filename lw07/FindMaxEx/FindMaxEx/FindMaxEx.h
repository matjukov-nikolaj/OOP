#pragma once
#include "stdafx.h"

template < typename T, typename Less>
bool FindMax(
	std::vector<T> const& arr,
	T& maxValue,
	Less const& less = std::less<T>)
{
	auto largest = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*largest, *it))
		{
			largest = it;
		}
	}
	if (largest != arr.end())
	{
		maxValue = *largest;
		return true;
	}
	return false;
}
