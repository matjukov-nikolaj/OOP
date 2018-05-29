#include "stdafx.h"
#include "../MyList/MyList/CMyList.h"

struct ListWithEmptyString
{
	CMyList<std::string> stringList;
	std::string data = "data";
};

BOOST_FIXTURE_TEST_SUITE(my_list, ListWithEmptyString)

	BOOST_AUTO_TEST_SUITE(when_list_created)

		BOOST_AUTO_TEST_CASE(string_list_is_empty)
		{
			BOOST_CHECK(stringList.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(can_get_size)
		{
			BOOST_CHECK_EQUAL(stringList.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(can_push_back_element)
		{
			size_t size = stringList.GetSize();
			stringList.PushBack(data);
			//BOOST_CHECK_EQUAL(stringList.GetSize(), size + 1);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
