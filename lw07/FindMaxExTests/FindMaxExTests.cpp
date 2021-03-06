#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx/CSportsman.h"
#include "../FindMaxEx/FindMaxEx/FindMaxEx.h"

BOOST_AUTO_TEST_SUITE(find_max_function)

	BOOST_AUTO_TEST_CASE(try_to_get_max_in_empty_vector_return_false)
	{
		std::vector<CSportsman> emptyVector;
		CSportsman element;
		BOOST_CHECK(!FindMax(emptyVector, element, [](const auto& man1, const auto& man2) {
			return man1.GetHeight() < man1.GetHeight();
		}));
	}

	BOOST_AUTO_TEST_CASE(get_max_when_vector_is_not_empty_return_true)
	{
		std::vector<CSportsman> sportsmans = {
			CSportsman("Vasya", 60, 170),
			CSportsman("Petya", 63, 173),
			CSportsman("Igor", 65, 175),
		};

		CSportsman man;
		BOOST_CHECK(FindMax(sportsmans, man, [](const auto& man1, const auto& man2) {
			return man1.GetHeight() < man1.GetHeight();
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct ElementsInt
{
	int value1;
	int value2;
	std::string stringId;
};

BOOST_FIXTURE_TEST_SUITE(get_max_in_int_array, ElementsInt)

	BOOST_AUTO_TEST_CASE(get_max_when_vector_consist_integer_numbers)
	{
		std::vector<ElementsInt> elements = {
			{ 1, 2, "1" },
			{ 3, 4, "2" },
			{ 5, 6, "3" }
		};

		ElementsInt element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value1 < second.value1;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "3");
	}

	BOOST_AUTO_TEST_CASE(get_max_when_vector_consist_equals_integer_numbers)
	{
		std::vector<ElementsInt> elements = {
			{ 1, 1, "1" },
			{ 1, 1, "2" },
			{ 1, 1, "3" }
		};

		ElementsInt element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value1 < second.value1;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "1");
	}

	BOOST_AUTO_TEST_CASE(get_min_when_vector_consist_equals_integer_numbers)
	{
		std::vector<ElementsInt> elements = {
			{ 1, 1, "1" },
			{ 1, 1, "2" },
			{ 1, 1, "3" }
		};

		ElementsInt element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value1 > second.value1;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "1");
	}

BOOST_AUTO_TEST_SUITE_END()

struct ElementsDouble
{
	double value1;
	double value2;
	std::string stringId;
};

BOOST_FIXTURE_TEST_SUITE(get_max_in_double_array, ElementsDouble)

	BOOST_AUTO_TEST_CASE(get_max_when_vector_consist_double_numbers)
	{
		std::vector<ElementsDouble> elements = {
			{ 5.123, 2.321, "1" },
			{ 3.4321, 4.4312, "2" },
			{ 1.242314, 6.431, "3" },
		};

		ElementsDouble element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value2 < second.value2;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "3");
	}

	BOOST_AUTO_TEST_CASE(get_max_when_vector_consist__equals_double_numbers)
	{
		std::vector<ElementsDouble> elements = {
			{ 1.0, 1.0, "1" },
			{ 1.0, 1.0, "2" },
			{ 1.0, 1.0, "3" },
		};

		ElementsDouble element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value2 < second.value2;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "1");
	}

	BOOST_AUTO_TEST_CASE(get_min_when_vector_consist__equals_double_numbers)
	{
		std::vector<ElementsDouble> elements = {
			{ 1.0, 1.0, "1" },
			{ 1.0, 1.0, "2" },
			{ 1.0, 1.0, "3" },
		};

		ElementsDouble element;
		BOOST_CHECK(FindMax(elements, element, [](const auto& first, const auto& second) {
			return first.value2 > second.value2;
		}));

		BOOST_CHECK_EQUAL(element.stringId, "1");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(check_commit_or_rollback)

	BOOST_AUTO_TEST_CASE(use_CBadSportsman)
	{
		std::vector<CBadSportsman> badSportsmans{
			{ "Vasya", 160, 50 },
			{ "Petya", 161, 51 },
			{ "Sanya", 162, 35 },
			{ "Jeka", 163, 45 },
			{ "Lol", 164, 21 }
		};

		CBadSportsman max;
		badSportsmans[1].m_throwExc = true;
		try
		{
			FindMax(badSportsmans, max, [](const CBadSportsman& first, const CBadSportsman& second) {
				return first.m_weight < second.m_weight;
			});
		}
		catch (...)
		{
			BOOST_CHECK(max == CBadSportsman());
		}
	}

BOOST_AUTO_TEST_SUITE_END()
