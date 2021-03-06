#include "stdafx.h"
#include "..\replace\replace\Replace.h"

BOOST_AUTO_TEST_SUITE(replace_tests)

BOOST_AUTO_TEST_CASE(replace_number_to_word)
{
	std::string result = FindAndReplace("12312312345   12312312345    12312312345", "1231234", "replace");
	BOOST_CHECK_EQUAL("123replace5   123replace5    123replace5", result);
}

BOOST_AUTO_TEST_CASE(replace_of_the_ma_by_the_mama)
{
	std::string result = FindAndReplace("mamamamamamamamamama", "ma", "mama");
	BOOST_CHECK_EQUAL("mamamamamamamamamamamamamamamamamamamama", result);
}

BOOST_AUTO_TEST_CASE(replace_of_the_brother_by_the_sister)
{
	std::string result = FindAndReplace("brother  brother", "brother", "sister");
	BOOST_CHECK_EQUAL("sister  sister", result);
}

BOOST_AUTO_TEST_CASE(replace_a_to_bb)
{
	std::string result = FindAndReplace("aaaaaaaaaaaaaaaaaaaa", "a", "bb");
	BOOST_CHECK_EQUAL("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", result);
}

BOOST_AUTO_TEST_CASE(try_to_replace_in_empty_string)
{
	std::string result = FindAndReplace("", "a", "bb");
	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(try_to_find_empty_string_return_unchangeable_string)
{
	std::string result = FindAndReplace("aaa", "", "bb");
	BOOST_CHECK_EQUAL("aaa", result);
}

BOOST_AUTO_TEST_SUITE_END()
