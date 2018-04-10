#include "stdafx.h"
#include "..\WordOccurrence\WordOccurence\WordOccurrence.h"
using WordsOccurrence = std::map<std::string, int>;


BOOST_AUTO_TEST_SUITE(calculation_frequency_words_occurrence)

BOOST_AUTO_TEST_CASE(calculate_of_one_word)
{
	WordsOccurrence result = CalculationFrequencyWordsOccurrence("a");
	WordsOccurrence exprectedResult = {
		{"a", 1}
	};
	BOOST_CHECK(exprectedResult == result);
}

BOOST_AUTO_TEST_CASE(calculate_five_words_a)
{
	WordsOccurrence result = CalculationFrequencyWordsOccurrence("a a a a a");
	WordsOccurrence exprectedResult = {
		{ "a", 5 }
	};
	BOOST_CHECK(exprectedResult == result);
}

BOOST_AUTO_TEST_CASE(try_to_calculate_words_occurrence_in_empty_string)
{
	WordsOccurrence result = CalculationFrequencyWordsOccurrence("");
	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(calculate_occurrence_words_in_different_register)
{
	WordsOccurrence result = CalculationFrequencyWordsOccurrence("Hello HeLLo hello");
	WordsOccurrence exprectedResult = {
		{ "hello", 3 }
	};
	BOOST_CHECK(exprectedResult == result);
}

BOOST_AUTO_TEST_CASE(calculate_five_words_a_and_six_words_b)
{
	WordsOccurrence result = CalculationFrequencyWordsOccurrence("a b a b a b a a b b b");
	WordsOccurrence exprectedResult = {
		{ "a", 5 },
		{ "b", 6 }
	};
	BOOST_CHECK(exprectedResult == result);
}

BOOST_AUTO_TEST_SUITE_END()