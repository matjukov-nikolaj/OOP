#include "stdafx.h"
#include "../MyList/MyList/CMyList.h"

struct list_with_empty_string
{
	CMyList<std::string> stringList;
	std::string data = "data";
};

template <typename T>
bool IsEqualLists(const CMyList<T>& list, std::vector<T>& elements)
{
	BOOST_CHECK_EQUAL(list.GetSize(), elements.size());
	size_t index = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, elements[index]);
		index++;
	}
	return true;
}

template <typename T>
std::vector<T> GetVectorOfElementsFromTheList(CMyList<T>& list)
{
	std::vector<std::string> elements;
	for (auto elem : list)
	{
		elements.push_back(elem);
	}
	return elements;
}

template <typename T>
std::ostream& operator<<(std::ostream& strm, const CMyList<std::string>::CMyIterator<T> item)
{
	strm << *item << " ";
	return strm;
}

BOOST_FIXTURE_TEST_SUITE(my_list, list_with_empty_string)

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
			BOOST_CHECK_EQUAL(stringList.GetSize(), size + 1);
			BOOST_CHECK_EQUAL(stringList.GetBackElement(), data);
		}

		BOOST_AUTO_TEST_CASE(can_push_front_element)
		{
			size_t size = stringList.GetSize();
			stringList.PushFront(data);
			BOOST_CHECK_EQUAL(stringList.GetSize(), size + 1);
			BOOST_CHECK_EQUAL(stringList.GetFrontElement(), data);
		}

		BOOST_AUTO_TEST_CASE(if_list_is_empty_end_iterator_return_begin)
		{
			BOOST_CHECK_EQUAL(stringList.begin(), stringList.end());
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct not_empty_list : list_with_empty_string
	{
		not_empty_list()
		{
			stringList.PushBack(data);
			stringList.PushBack(data);
			stringList.PushBack(data);
			stringList.PushBack(data);
			stringList.PushBack(data);
		}
		size_t size = 5;
	};

	BOOST_FIXTURE_TEST_SUITE(when_in_the_list_there_are_elements, not_empty_list)

		BOOST_AUTO_TEST_CASE(list_can_be_cleared)
		{
			BOOST_CHECK_EQUAL(stringList.GetSize(), size);
			BOOST_CHECK(!stringList.IsEmpty());
			stringList.Clear();
			BOOST_CHECK(stringList.IsEmpty());
			BOOST_CHECK_EQUAL(stringList.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(can_get_back_element)
		{
			std::string line = stringList.GetBackElement();
			BOOST_CHECK_EQUAL(line, data);
		}

		BOOST_AUTO_TEST_CASE(can_get_front_element)
		{
			std::string line = stringList.GetFrontElement();
			BOOST_CHECK_EQUAL(line, data);
		}

		BOOST_AUTO_TEST_CASE(have_iterator_at_begin_and_end)
		{
			BOOST_CHECK_EQUAL(addressof(*stringList.end()), nullptr);
			BOOST_CHECK_EQUAL(addressof(*stringList.begin()), addressof(stringList.GetFrontElement()));
		}

		BOOST_AUTO_TEST_CASE(have_const_iterator_at_begin_and_end)
		{
			BOOST_CHECK_EQUAL(addressof(*stringList.cend()), nullptr);
			BOOST_CHECK_EQUAL(addressof(*stringList.cbegin()), addressof(stringList.GetFrontElement()));
		}

		BOOST_AUTO_TEST_CASE(can_make_copy)
		{
			CMyList<std::string> copiedList(stringList);
			BOOST_CHECK_EQUAL(stringList.GetSize(), copiedList.GetSize());
			BOOST_CHECK_EQUAL(stringList.GetBackElement(), copiedList.GetBackElement());
			BOOST_CHECK_EQUAL(stringList.GetFrontElement(), copiedList.GetFrontElement());

			std::vector<std::string> list = GetVectorOfElementsFromTheList(stringList);
			BOOST_CHECK(IsEqualLists(stringList, list));
		}

		BOOST_AUTO_TEST_CASE(there_is_a_copying_assignment_operator)
		{
			const CMyList<std::string> lol(stringList);
			CMyList<std::string> copiedList;
			copiedList = stringList;
			BOOST_CHECK_EQUAL(stringList.GetSize(), copiedList.GetSize());
			BOOST_CHECK_EQUAL(stringList.GetBackElement(), copiedList.GetBackElement());
			BOOST_CHECK_EQUAL(stringList.GetFrontElement(), copiedList.GetFrontElement());

			std::vector<std::string> list = GetVectorOfElementsFromTheList(copiedList);
			BOOST_CHECK(IsEqualLists(stringList, list));
		}
		
		BOOST_AUTO_TEST_CASE(can_make_const_copy)
		{
			const CMyList<std::string> copiedList(stringList);
			BOOST_CHECK_EQUAL(stringList.GetBackElement(), copiedList.GetBackElement());
			BOOST_CHECK_EQUAL(stringList.GetFrontElement(), copiedList.GetFrontElement());

			std::vector<std::string> list = GetVectorOfElementsFromTheList(stringList);
			BOOST_CHECK(IsEqualLists(stringList, list));
		}

		BOOST_AUTO_TEST_CASE(can_insert_an_element_into_the_position_set_by_an_iterator)
		{
			std::vector<std::string> oldList = GetVectorOfElementsFromTheList(stringList);
			size_t oldSize = stringList.GetSize();
			std::string newListElement = "123";
			stringList.Insert(stringList.begin(), newListElement);
			oldList.insert(oldList.begin(), newListElement);
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize + 1);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			stringList.Insert(stringList.end(), newListElement);
			oldList.insert(oldList.end(), newListElement);
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize + 2);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			auto it = ++stringList.begin();
			stringList.Insert(it, newListElement);
			oldList.insert(++oldList.begin(), newListElement);
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize + 3);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			it = --stringList.begin();
			stringList.Insert(it, newListElement);
			oldList.insert(--oldList.end(), newListElement);
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize + 4);
			BOOST_CHECK(IsEqualLists(stringList, oldList));
		}

		BOOST_AUTO_TEST_CASE(can_erase_an_element_from_the_position_set_by_an_iterator)
		{
			std::vector<std::string> oldList = GetVectorOfElementsFromTheList(stringList);
			size_t oldSize = stringList.GetSize();
			stringList.Erase(stringList.begin());
			oldList.erase(oldList.begin());
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize - 1);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			stringList.Erase(++stringList.begin());
			oldList.erase(++oldList.begin());
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize - 2);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			stringList.Clear();
			stringList.PushFront(data);
			oldList = GetVectorOfElementsFromTheList(stringList);
			oldSize = stringList.GetSize();
			stringList.Erase(stringList.begin());
			oldList.erase(oldList.begin());
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize - 1);
			BOOST_CHECK(IsEqualLists(stringList, oldList));

			stringList.PushFront(data);
			stringList.PushFront(data);
			oldList = GetVectorOfElementsFromTheList(stringList);
			oldSize = stringList.GetSize();
			stringList.Erase(++(stringList.begin()));
			oldList.erase(--oldList.end());
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize - 1);
			BOOST_CHECK(IsEqualLists(stringList, oldList));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct string_list_with_different_elements : list_with_empty_string
	{
		string_list_with_different_elements()
		{
			stringList.PushBack("1");
			stringList.PushBack("2");
			stringList.PushBack("3");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(check_reverse_iterators, string_list_with_different_elements)

		BOOST_AUTO_TEST_CASE(can_insert_an_element_into_the_position_set_by_an_reverse_iterator)
		{
			std::vector<std::string> oldList = GetVectorOfElementsFromTheList(stringList);
			size_t oldSize = stringList.GetSize();
			stringList.Insert(stringList.rbegin(), data);
			oldList.insert(--oldList.end(), data);
			BOOST_CHECK_EQUAL(stringList.GetSize(), oldSize + 1);
			BOOST_CHECK(IsEqualLists(stringList, oldList));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(check_iterators_for_empty_list, list_with_empty_string)

		BOOST_AUTO_TEST_CASE(when_the_list_is_empty_begin_and_end_r_equal)
		{
			BOOST_CHECK_EQUAL(stringList.begin(), stringList.end());
			const CMyList<std::string> emptyList;
			BOOST_CHECK_EQUAL(emptyList.cbegin(), emptyList.cend());
			BOOST_CHECK_EQUAL(stringList.rbegin(), stringList.rend());
			BOOST_CHECK_EQUAL(emptyList.crbegin(), emptyList.crend());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()