#include "stdafx.h"
#include "../StringStack/StringStack/CStringStack.h"

struct StringStackFixture
{
	std::string line = "123";
	CStringStack stringStack;
};

BOOST_FIXTURE_TEST_SUITE(string_stack_test, StringStackFixture)

	BOOST_AUTO_TEST_CASE(can_push_string_to_stack)
	{
		stringStack.Push(line);
		BOOST_CHECK_EQUAL(stringStack.GetTopValue(), line);
	}

	BOOST_AUTO_TEST_CASE(can_check_string_stack_for_empty)
	{
		BOOST_CHECK(stringStack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(check_string_for_empty_if_stack_is_not_empty)
	{
		stringStack.Push(line);
		BOOST_CHECK(!stringStack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_pop_element_if_stack_is_not_empty)
	{
		BOOST_CHECK_THROW(stringStack.GetTopValue(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(cant_get_top_element_when_stack_is_empty)
	{
		BOOST_CHECK(stringStack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(if_stack_is_empty_throw_logic_error)
	{
		BOOST_CHECK(stringStack.IsEmpty());
		BOOST_CHECK_THROW(stringStack.Pop(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(can_clear_stack)
	{
		for (int i = 0; i < 10; ++i)
		{
			stringStack.Push(line);
		}
		BOOST_CHECK(!stringStack.IsEmpty());
		stringStack.Clear();
		BOOST_CHECK(stringStack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(check_stack_for_many_push)
	{
		for (size_t i = 0; i < 10000; i++)
		{
			stringStack.Push(line);
		}
		BOOST_CHECK(!stringStack.IsEmpty());
		stringStack.Clear();
		BOOST_CHECK(stringStack.IsEmpty());
	}

BOOST_AUTO_TEST_SUITE_END()
