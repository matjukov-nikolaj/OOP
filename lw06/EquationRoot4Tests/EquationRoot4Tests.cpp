#include "stdafx.h"
#include "../EquationRoot4/EquationRoot4/EquationRoot4.h"

namespace std
{
std::ostream& operator<<(std::ostream& strm, const std::vector<double>& result)
{
	for (size_t i = 0; i < result.size(); ++i)
	{
		strm << result[i];
	}
	return strm;
}
} // namespace std

BOOST_AUTO_TEST_SUITE(Solve4_function_tests)

	BOOST_AUTO_TEST_CASE(throws_an_exception_when_first_equals_to_zero)
	{
		BOOST_CHECK_THROW(Solve4(0, 1, 1, 1, 1), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(throws_an_exception_when_equation_has_no_valid_roots)
	{
		BOOST_CHECK_THROW(Solve4(7, 0, 0, 0, 9), std::domain_error);
	}

	BOOST_AUTO_TEST_CASE(get_coorect_result_when_first_argument_is_one_and_other_arguments_is_zero)
	{
		std::vector<double> result = Solve4(1, 0, 0, 0, 0);
		std::vector<double> expectedResult = { 0 };
		BOOST_CHECK_EQUAL(result, expectedResult);
	}

	BOOST_AUTO_TEST_CASE(get_two_correct_real_roots)
	{
		std::vector<double> result = Solve4(1, 1, 0, 0, 0);
		std::vector<double> expectedResult = { 0, -1 };
		BOOST_CHECK_EQUAL(result, expectedResult);
	}

	BOOST_AUTO_TEST_CASE(get_three_correct_real_roots)
	{
		std::vector<double> result = Solve4(1, 0, -1, 0, 0);
		std::vector<double> expectedResult = { 0, 1, -1 };
		BOOST_CHECK_EQUAL(result, expectedResult);
	}

	BOOST_AUTO_TEST_CASE(get_two_correct_real_roots_when_equation_have_two_real_solutions)
	{
		std::vector<double> result = Solve4(1, -7, -1, 4, -9);
		std::vector<double> expectedResult = { 7.08675, -1.23359 };
		BOOST_CHECK_CLOSE(result[0], expectedResult[0], 0.01);
		BOOST_CHECK_CLOSE(result[1], expectedResult[1], 0.01);
	}

	BOOST_AUTO_TEST_CASE(can_be_printed_root_in_output)
	{
		std::vector<double> result = Solve4(1, -1, -1, 1, -1);
		std::vector<double> expectedResult = { 1.51288, -1.17872 };
		BOOST_CHECK_CLOSE(result[0], expectedResult[0], 0.01);
		BOOST_CHECK_CLOSE(result[1], expectedResult[1], 0.01);
		std::ostringstream strm;
		PrintRoots(result, strm);
		std::string resultString = strm.str();
		std::string expectedString = "Equation roots : 1.51288 -1.17872 \n";
		BOOST_CHECK_EQUAL(resultString, expectedString);
	}

	BOOST_AUTO_TEST_CASE(get_three_real_root)
	{
		std::vector<double> result = Solve4(2, 3, 1, 0, 0);
		std::vector<double> expectedResult = { 0, -0.5, -1 };
		BOOST_CHECK_EQUAL(result, expectedResult);
	}

	BOOST_AUTO_TEST_CASE(get_two_correct_real_root_when_d2_is_equal_zero)
	{
		std::vector<double> result = Solve4(1, -1, 0, 0, 0);
		std::vector<double> expectedResult = { 1, 0 };
		BOOST_CHECK_EQUAL(result, expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()
