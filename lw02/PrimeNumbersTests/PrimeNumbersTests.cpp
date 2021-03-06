#include "stdafx.h"
#include "..\PrimeNumbers\PrimeNumbers\PrimeNumbersGenerator.h"

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

BOOST_AUTO_TEST_CASE(when_upper_bound_is_20_returns_vector_with_2_3_5_7_11_13_17_19)
{
	auto set = GeneratePrimeNumbersSet(20);
	std::set<int> result = { 2, 3, 5, 7, 11, 13, 17, 19};
	BOOST_CHECK(set == result);
}

BOOST_AUTO_TEST_CASE(when_upper_bound_is_100_millions_returns_vector_with_5761455_elements)
{
	auto set = GeneratePrimeNumbersSet(100000000);
	BOOST_CHECK(set.size() == 5761455);
}

BOOST_AUTO_TEST_SUITE_END()
