#include "stdafx.h"
#include "..\HTMLEncode\HTMLEncode\HtmlEncode.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(html_encode_tests)

BOOST_AUTO_TEST_CASE(encode_quot)
{
	std::string quot = "\"";
	std::string result = HtmlEncode(quot);
	BOOST_CHECK_EQUAL("&quot;", result);
}

BOOST_AUTO_TEST_CASE(encode_apos)
{
	std::string quot = "'";
	std::string result = HtmlEncode(quot);
	BOOST_CHECK_EQUAL("&apos;", result);
}

BOOST_AUTO_TEST_CASE(encode_lt)
{
	std::string quot = "<";
	std::string result = HtmlEncode(quot);
	BOOST_CHECK_EQUAL("&lt;", result);
}

BOOST_AUTO_TEST_CASE(encode_gt)
{
	std::string quot = ">";
	std::string result = HtmlEncode(quot);
	BOOST_CHECK_EQUAL("&gt;", result);
}

BOOST_AUTO_TEST_CASE(encode_amp)
{
	std::string quot = "&";
	std::string result = HtmlEncode(quot);
	BOOST_CHECK_EQUAL("&amp;", result);
}

BOOST_AUTO_TEST_CASE(when_string_empty_returns_empty_string)
{
	std::string emptyString;
	std::string result = HtmlEncode(emptyString);
	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(when_string_has_not_html_codes_returns_origin_string)
{
	std::string html = "This line does not contain the html entities";
	std::string result = HtmlEncode(html);
	BOOST_CHECK_EQUAL(result, "This line does not contain the html entities");
}

BOOST_AUTO_TEST_CASE(when_string_has_html_codes_returns_encoded_string)
{
	std::string html = "Cat <says> \"Meow\". M&M's";
	std::string result = HtmlEncode(html);
	BOOST_CHECK("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s" == result);
}

BOOST_AUTO_TEST_CASE(when_encode_ampersand_symbol_and_lt_return_amp_and_lt)
{
	std::string result = HtmlEncode("&<");
	BOOST_CHECK_EQUAL("&amp;&lt;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_all_html_entities)
{
	std::string result = HtmlEncode("<>'\"&");
	BOOST_CHECK_EQUAL("&lt;&gt;&apos;&quot;&amp;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_all_html_entities_in_other_order)
{
	std::string result = HtmlEncode("&\"'<>");
	BOOST_CHECK_EQUAL("&amp;&quot;&apos;&lt;&gt;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_ampersand_series)
{
	std::string result = HtmlEncode("&&&&");
	BOOST_CHECK_EQUAL("&amp;&amp;&amp;&amp;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_lt_series)
{
	std::string result = HtmlEncode("<<<<");
	BOOST_CHECK_EQUAL("&lt;&lt;&lt;&lt;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_gt_series)
{
	std::string result = HtmlEncode(">>>>");
	BOOST_CHECK_EQUAL("&gt;&gt;&gt;&gt;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_quot_series)
{
	std::string result = HtmlEncode("\"\"\"\"");
	BOOST_CHECK_EQUAL("&quot;&quot;&quot;&quot;", result);
}

BOOST_AUTO_TEST_CASE(when_encode_apos_series)
{
	std::string result = HtmlEncode("''''");
	BOOST_CHECK_EQUAL("&apos;&apos;&apos;&apos;", result);
}

BOOST_AUTO_TEST_SUITE_END()
