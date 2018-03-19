#include "stdafx.h"
#include "..\task1\task1\VectorProcessor.h"


using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// ‘ункци€ ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

// —оздает пустой вектор из пустого вектора
BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	ErrorCode errorCode = ErrorCode::None;
	vector<double> emptyVector;
	ProcessVector(emptyVector, errorCode);
	BOOST_CHECK(emptyVector.empty());
	BOOST_CHECK(errorCode == ErrorCode::VectorIsEmpty);
}

// не измен€ет содержимое вектора, содержит одинаковые значени€
BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_the_same_values)
{
	ErrorCode errorCode = ErrorCode::None;
	vector<double> numbers = { 1, 1, 1, 1, 1 };
	auto copy(numbers); // аналог vector<double> copy(numbers);
	ProcessVector(numbers, errorCode);
	BOOST_CHECK(numbers == copy);
}

//≈сли минимальный элемент равен нулю, то происходит деление на 0

BOOST_AUTO_TEST_CASE(when_min_element_is_equal_zero_and_error_code_contains_the_value_dividing_by_zero)
{
	ErrorCode errorCode = ErrorCode::None;
	vector<double> numbers = { 0, 1, 2, 3, 4 };
	ProcessVector(numbers, errorCode);
	BOOST_CHECK(errorCode == ErrorCode::DivisionByZero);
}

BOOST_AUTO_TEST_CASE(check_function_when_not_empty_vector_and_the_min_element_is_not_zero)
{
	ErrorCode errorCode = ErrorCode::None;
	vector<double> numbers = { 1, 1, 2, 3, 4 };
	ProcessVector(numbers, errorCode);
	BOOST_CHECK(VectorsAreEqual(numbers,
		{ 4, 4, 8, 12, 16 }
	));
}

BOOST_AUTO_TEST_SUITE_END();
