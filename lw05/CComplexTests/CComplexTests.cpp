#include "stdafx.h"
#include "../CComplex/CComplex/CComplex.h"

struct ComplexFixture
{
	const double real = 1.0;
	const double imaginary = 1.0;
	CComplex complex;
	ComplexFixture()
		:complex(real, imaginary)
	{
	}
};

BOOST_AUTO_TEST_SUITE(Complex)
	BOOST_AUTO_TEST_CASE(can_create_complex_number)
	{
		const double real = 1.0;
		const double imaginary = 1.0;
		CComplex complex(real, imaginary);
		BOOST_CHECK(complex.Re() == real);
		BOOST_CHECK(complex.Im() == imaginary);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Complex, ComplexFixture)

	BOOST_AUTO_TEST_CASE(can_get_real_part)
	{
		BOOST_CHECK_EQUAL(complex.Re(), 1.0);
	}

	BOOST_AUTO_TEST_CASE(can_get_imaginary_part)
	{
		BOOST_CHECK_EQUAL(complex.Im(), 1.0);
	}

	BOOST_AUTO_TEST_CASE(can_get_magnitude)
	{
		double magnitude = sqrt(pow(imaginary, 2) + pow(real, 2));
		BOOST_CHECK_EQUAL(complex.GetMagnitude(), magnitude);
	}

	BOOST_AUTO_TEST_CASE(can_get_argument_when_real_part_is_more_than_zero)
	{
		double expectedArgument = atan2(imaginary, real);
		BOOST_CHECK_EQUAL(complex.GetArgument(), expectedArgument);
	}

	BOOST_AUTO_TEST_CASE(can_get_argument_when_real_part_is_less_than_zero_and_imaginary_is_more_than_zero)
	{
		double real = -1.0;
		CComplex complexNumber(real, imaginary);
		double expectedArgument = atan2(imaginary, real);
		BOOST_CHECK_EQUAL(complexNumber.GetArgument(), expectedArgument);
	}

	BOOST_AUTO_TEST_CASE(can_get_argument_when_real_part_is_less_than_zero_and_imaginary_is_lass_than_zero)
	{
		double real = -1.0;
		double imaginary = -1.0;
		CComplex complexNumber(real, imaginary);
		double expectedArgument = atan2(imaginary, real);
		BOOST_CHECK_EQUAL(complexNumber.GetArgument(), expectedArgument);
	}

	BOOST_AUTO_TEST_CASE(has_binary_plus_operator)
	{
		CComplex complexResult = complex + CComplex(real, imaginary);
		BOOST_CHECK_EQUAL(complexResult, CComplex(2.0, 2.0));
	}

	BOOST_AUTO_TEST_CASE(can_be_added_complex_number_and_real_number)
	{
		double real = 1.0;
		CComplex complexResult = real + complex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(2.0, 1.0));
	}

	BOOST_AUTO_TEST_CASE(has_binary_minus_operator)
	{
		CComplex complexResult = CComplex(2.0, 2.0) - complex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(real, imaginary));
	}

	BOOST_AUTO_TEST_CASE(can_be_substracted_complex_number_and_real_number)
	{
		double real = 1.0;
		CComplex complexResult = real - complex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(0.0, -1.0));
	}

	BOOST_AUTO_TEST_CASE(has_unnary_minus_operator)
	{
		BOOST_CHECK_EQUAL(-complex, CComplex(-real, -imaginary));
	}

BOOST_AUTO_TEST_SUITE_END()

struct OtherComplexValue : ComplexFixture
{
	double real = 2.0;
	double imaginary = 4.0;
	CComplex otherComplex;
	OtherComplexValue()
		:otherComplex(real, imaginary)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(other_complex_value, OtherComplexValue)

	BOOST_AUTO_TEST_CASE(has_operator_of_miltiplication)
	{
		CComplex complexResult = CComplex(2.0, 2.0) * otherComplex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(-4.0, 12.0));
	}

	BOOST_AUTO_TEST_CASE(has_operator_of_miltiplication_on_real_number)
	{
		double number = 4.0;
		CComplex complexResult = otherComplex * number;
		BOOST_CHECK_EQUAL(complexResult, CComplex(8.0, 16.0));
		complexResult = number * otherComplex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(8.0, 16.0));
	}

	BOOST_AUTO_TEST_CASE(has_operator_of_division)
	{
		CComplex complexResult = otherComplex / CComplex(2.0, 2.0);
		BOOST_CHECK_EQUAL(complexResult, CComplex(1.5, 0.5));
	}

	BOOST_AUTO_TEST_CASE(has_operator_of_division_real_number_on_complex_number)
	{
		double number = 4.0;
		CComplex complexResult = number / otherComplex;
		BOOST_CHECK_EQUAL(complexResult, CComplex(0.4, -0.8));
	}

	BOOST_AUTO_TEST_CASE(has_operator_of_division_complex_number_on_real_number)
	{
		double number = 4.0;
		CComplex complexResult = otherComplex / number;
		BOOST_CHECK_EQUAL(complexResult, CComplex(0.5, 1));
	}

	BOOST_AUTO_TEST_CASE(has_unnary_plus_operator)
	{
		BOOST_CHECK_EQUAL(+otherComplex, otherComplex);
	}

	BOOST_AUTO_TEST_CASE(has_unnary_minus_operator)
	{
		BOOST_CHECK_EQUAL(-otherComplex, CComplex(-real, -imaginary));
	}

	BOOST_AUTO_TEST_CASE(can_be_added_with_operator_plus_equally)
	{
		complex += otherComplex;
		BOOST_CHECK_EQUAL(complex, CComplex(3.0, 5.0));
	}

	BOOST_AUTO_TEST_CASE(can_be_substracted_with_operator_minus_equally)
	{
		otherComplex -= complex;
		BOOST_CHECK_EQUAL(otherComplex, CComplex(1.0, 3.0));
	}

	BOOST_AUTO_TEST_CASE(can_be_multiplied_with_operator_multiply_equally)
	{
		otherComplex *= complex;
		BOOST_CHECK_EQUAL(otherComplex, CComplex(-2.0, 6.0));
	}

	BOOST_AUTO_TEST_CASE(can_be_divided_with_operator_division_equally)
	{
		otherComplex /= complex;
		BOOST_CHECK_EQUAL(otherComplex, CComplex(3.0, 1.0));
	}

	BOOST_AUTO_TEST_CASE(can_be_cheked_for_equality)
	{
		CComplex equalComplex(real, imaginary);
		BOOST_CHECK(otherComplex == equalComplex);
		BOOST_CHECK(!(otherComplex == complex));
	}

	BOOST_AUTO_TEST_CASE(can_be_cheked_for_equality_with_real_number)
	{
		double number = 1.0;
		BOOST_CHECK(number == CComplex(number));
		BOOST_CHECK(!(number == complex));
	}

	BOOST_AUTO_TEST_CASE(can_be_cheked_for_inquality)
	{
		CComplex equalComplex(real, imaginary);
		BOOST_CHECK(otherComplex != complex);
		BOOST_CHECK(!(otherComplex != equalComplex));
	}

	BOOST_AUTO_TEST_CASE(can_be_cheked_for_inequality_with_real_number)
	{
		double number = 1.0;
		BOOST_CHECK(number != complex);
		BOOST_CHECK(!(number != CComplex(number)));
	}

BOOST_AUTO_TEST_SUITE_END()

struct EmptyComplex : ComplexFixture
{
	std::string complexString = "1+1i";
	CComplex emptyComplex;
};

BOOST_FIXTURE_TEST_SUITE(empty_complex_value, EmptyComplex)

	BOOST_AUTO_TEST_CASE(can_be_read_complex_number_from_input)
	{
		std::istringstream input(complexString);
		input >> emptyComplex;
		BOOST_CHECK_EQUAL(emptyComplex, complex);
	}

	BOOST_AUTO_TEST_CASE(can_be_write_complex_number_on_output)
	{
		std::ostringstream output;
		output << complex;
		BOOST_CHECK_EQUAL(output.str(), complexString);
	}

	BOOST_AUTO_TEST_CASE(attempt_to_receive_an_argument_from_empty_complex_number)
	{
		BOOST_CHECK_THROW(emptyComplex.GetArgument(), std::domain_error);
	}

BOOST_AUTO_TEST_SUITE_END()