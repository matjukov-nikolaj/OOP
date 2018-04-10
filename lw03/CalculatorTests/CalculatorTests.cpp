#include "stdafx.h"
//#include "../Car/Car/CCar.h"

struct CarFixture
{
	int car;
};


BOOST_FIXTURE_TEST_SUITE(lol, CarFixture)
BOOST_AUTO_TEST_CASE(kek)
{
	BOOST_CHECK(1 == 1);
}

BOOST_AUTO_TEST_SUITE_END()
