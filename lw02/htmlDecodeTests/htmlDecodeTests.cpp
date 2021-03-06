#include "stdafx.h"
#include "..\htmlDecode\htmlDecode\HtmlDecode.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(HtmlDecode_tests)

BOOST_AUTO_TEST_CASE(when_decode_quot_return_double_quotation_mark)
{
	std::string quot = "&quot;";
	std::string result = HtmlDecode(quot);
	BOOST_CHECK("\"" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_apos_return_apostrophe)
{
	std::string apos = "&apos;";
	std::string result = HtmlDecode(apos);
	BOOST_CHECK("\'" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_lt_return_less_symbol)
{
	std::string lt = "&lt;";
	std::string result = HtmlDecode(lt);
	BOOST_CHECK("<" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_gt_return_greater_symbol)
{
	std::string gt = "&gt;";
	std::string result = HtmlDecode(gt);
	BOOST_CHECK(">" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_amp_return_ampersand_symbol)
{
	std::string amp = "&amp;";
	std::string result = HtmlDecode(amp);
	BOOST_CHECK("&" == result);
}

BOOST_AUTO_TEST_CASE(when_string_empty_returns_empty_string)
{
	std::string emptyString;
	std::string result = HtmlDecode(emptyString);
	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(when_string_has_not_html_codes_returns_origin_string)
{
	std::string html = "This line does not contain the html entities";

	std::string result = HtmlDecode(html);
	BOOST_CHECK(result == "This line does not contain the html entities");
}

BOOST_AUTO_TEST_CASE(when_string_has_html_codes_returns_decoded_string)
{
	std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string result = HtmlDecode(html);
	BOOST_CHECK(result == "Cat <says> \"Meow\". M&M's");
}

BOOST_AUTO_TEST_CASE(when_decode_amp_and_lt_return_ampersand_symbol_and_lt)
{
	std::string result = HtmlDecode("&amp;lt;");
	BOOST_CHECK("&lt;" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_apos_series)
{
	std::string apos = "&apos;&apos;&apos;&apos;&apos;&apos;&apos;";
	std::string result = HtmlDecode(apos);
	BOOST_CHECK("'''''''" == result);
}

BOOST_AUTO_TEST_CASE(when_decode_amp_series)
{
	std::string apos = "&amp;&amp;&amp;&amp;&amp;&amp;&amp;";
	std::string result = HtmlDecode(apos);
	BOOST_CHECK("&&&&&&&" == result);
}

BOOST_AUTO_TEST_SUITE_END()
