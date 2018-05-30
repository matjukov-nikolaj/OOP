#include "stdafx.h"
#include "../MyString/MyString/CMyString.h"

BOOST_AUTO_TEST_SUITE(my_string)

	BOOST_AUTO_TEST_CASE(can_create_string_with_default_constructor)
	{
		CMyString str;
		BOOST_CHECK_EQUAL(str.GetLength(), 0);
		BOOST_CHECK_EQUAL(str, "");
	}

	BOOST_AUTO_TEST_CASE(can_create_string_from_array_of_chars)
	{
		CMyString str("123");
		BOOST_CHECK_EQUAL(str.GetLength(), 3);
		BOOST_CHECK_EQUAL(str, "123");
	}

	BOOST_AUTO_TEST_CASE(can_create_string_from_array_of_chars_with_length_indication)
	{
		CMyString str("123", 3);
		BOOST_CHECK_EQUAL(str.GetLength(), 3);
		BOOST_CHECK_EQUAL(str, "123");
	}

	BOOST_AUTO_TEST_CASE(can_create_string_from_stl_string)
	{
		std::string line = "123";
		CMyString str(line);
		BOOST_CHECK_EQUAL(str.GetLength(), line.size());
		BOOST_CHECK_EQUAL(str, "123");
	}

	BOOST_AUTO_TEST_CASE(can_move_a_string)
	{
		CMyString str("123");
		CMyString movedStr(std::move(str));
		BOOST_CHECK_EQUAL(movedStr, "123");
		BOOST_CHECK_EQUAL(str, "");
	}

	BOOST_AUTO_TEST_CASE(check_Get_strign_data_if_m_pChars_is_empty)
	{
		CMyString str("123");
		str.Clear();
		const char zeroLengthString[] = "";
		const char* value = str.GetStringData();
		BOOST_CHECK_EQUAL(value, zeroLengthString);
	}

	struct my_string_fixture
	{
		CMyString str;
		my_string_fixture()
			: str("123")
		{
		}
	};

	BOOST_FIXTURE_TEST_SUITE(string_fixture, my_string_fixture)

		BOOST_AUTO_TEST_CASE(has_data)
		{
			BOOST_CHECK_EQUAL(CMyString(str.GetStringData(), 3), "123");
		}

		BOOST_AUTO_TEST_CASE(can_create_substring)
		{
			BOOST_CHECK_EQUAL(str.SubString(0, 3), "123");
			BOOST_CHECK_EQUAL(str.SubString(1, 2), "2");
			BOOST_CHECK_EQUAL(str.SubString(3), "");
		}

		BOOST_AUTO_TEST_CASE(cant_create_substring_when_start_greater_than_length)
		{
			BOOST_CHECK_THROW(str.SubString(3 + 1), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(has_copy_operator)
		{
			CMyString line;
			line = str;
			BOOST_CHECK_EQUAL(line, str);
		}

		BOOST_AUTO_TEST_CASE(has_moving_operator)
		{
			CMyString line = std::move(str);
			BOOST_CHECK_EQUAL(line, "123");
			BOOST_CHECK_EQUAL("", str);
			BOOST_CHECK(str.GetLength() == 0);
		}

		BOOST_AUTO_TEST_CASE(has_plus_operator)
		{
			CMyString line("123");
			str = str + line;
			BOOST_CHECK_EQUAL(str, "123123");

			str = line + str;
			BOOST_CHECK_EQUAL(str, "123123123");

			str = "0" + str;
			BOOST_CHECK_EQUAL(str, "0123123123");

			const std::string string= "123";
			str = string + str;
			BOOST_CHECK_EQUAL(str, "1230123123123");

		}

		BOOST_AUTO_TEST_CASE(can_add_with_the_plus_equals_operator)
		{
			str += str;
			BOOST_CHECK_EQUAL(str, "123123");


			CMyString x("1");
			CMyString y("2");
			CMyString z("3");
			BOOST_CHECK_EQUAL(((x += y) += z), "123");
		}

		BOOST_AUTO_TEST_CASE(can_compare_string_to_equality)
		{
			CMyString line(str);
			BOOST_CHECK(str == line);
			BOOST_CHECK(!(str != line));

			line = "1234";
			BOOST_CHECK(!(str == line));
		}

		BOOST_AUTO_TEST_CASE(can_compare_string_to_inequality)
		{
			CMyString line("1234");
			BOOST_CHECK(str != line);
			BOOST_CHECK(!(str == line));
		}

		BOOST_AUTO_TEST_CASE(have_access_to_the_item_by_index)
		{
			BOOST_CHECK_EQUAL(str[0], '1');
		}

		BOOST_AUTO_TEST_CASE(throw_out_of_range_if_you_try_to_get_a_non_existent_index)
		{
			BOOST_CHECK_THROW(str[-1], std::out_of_range);
			BOOST_CHECK_THROW(str[4], std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(can_get_const_element_by_the_index_access)
		{
			const CMyString line(str);
			const auto ch = line[0];
			BOOST_CHECK_EQUAL(ch, '1');
			BOOST_CHECK_THROW(line[-1], std::out_of_range);
			BOOST_CHECK_THROW(line[4], std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(has_less_operator)
		{
			CMyString line("1234");
			BOOST_CHECK(str < line);
			BOOST_CHECK(!(str > line));

			line = "321";
			BOOST_CHECK(str < line);

			CMyString aligator("aligator");
			CMyString zebra("zebra");

			BOOST_CHECK(aligator < zebra);
		}

		BOOST_AUTO_TEST_CASE(has_less_equal_operator)
		{
			CMyString line("1234");
			BOOST_CHECK(str <= line);
			BOOST_CHECK(!(str >= line));
		}

		BOOST_AUTO_TEST_CASE(has_greater_operator)
		{
			CMyString line("12");
			BOOST_CHECK(!(line > str));
			BOOST_CHECK(str > line);

			line = "122";
			BOOST_CHECK(str > line);
		}

		BOOST_AUTO_TEST_CASE(has_greater_equal_operator)
		{
			CMyString line("12");
			BOOST_CHECK(!(line >= str));
			BOOST_CHECK(str >= line);
		}

		BOOST_AUTO_TEST_CASE(can_be_input_from_stream)
		{
			std::istringstream strm("123");
			BOOST_CHECK(strm >> str);
			BOOST_CHECK_EQUAL(str, "123");
		}

		BOOST_AUTO_TEST_CASE(can_be_output_to_stream)
		{
			std::stringstream strm;
			CMyString line("123\0321");
			strm << line;
			CMyString string(strm.str());
			BOOST_CHECK_EQUAL(line, string);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
