#include "stdafx.h"
#include "CMyString.h"

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (length != 0)
	{
		m_pChars = std::make_unique<char[]>(length + 1);
		memcpy(m_pChars.get(), pString, length + 1);
		m_length = length;
		m_pChars[length] = '\0';
	}
}

CMyString::CMyString(const CMyString& other)
{
	if (other.m_length > 0)
	{
		size_t size = other.m_length;
		m_pChars = std::make_unique<char[]>(size + 1);
		memcpy(m_pChars.get(), other.m_pChars.get(), size + 1);
		m_length = size;
	}
}

CMyString::CMyString(CMyString&& other)
	: m_pChars(std::move(other.m_pChars))
	, m_length(other.m_length)
{
	other.m_length = 0;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	static const char zeroLengthString[] = "";
	return m_pChars ? m_pChars.get() : zeroLengthString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("Out of range");
	}
	if (start == m_length)
	{
		return "";
	}
	size_t strLength = m_length < length - start ? m_length - start : length - start;
	return CMyString(GetStringData() + start, strLength);
}

void CMyString::Clear()
{
	m_pChars.reset();
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& rhs)
{
	if (std::addressof(rhs) != this)
	{
		CMyString tmpCopy(rhs);
		std::swap(m_pChars, tmpCopy.m_pChars);
		std::swap(m_length, tmpCopy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		std::swap(m_pChars, other.m_pChars);
		std::swap(m_length, other.m_length);
		other.Clear();
	}

	return *this;
}

CMyString CMyString::operator+=(const CMyString& string)
{
	return *this = *this + string;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

CMyString::CMyString(std::unique_ptr<char[]>&& pChars, size_t length)
	: m_pChars(std::move(pChars))
	, m_length(length)
{
}

CMyString operator+(const CMyString& string1, const CMyString& string2)
{
	std::unique_ptr<char[]> tmp = std::make_unique<char[]>(string1.m_length + string2.m_length + 1);
	try
	{
		memcpy(tmp.get(), string1.m_pChars.get(), string1.m_length);
		memcpy(tmp.get() + string1.m_length, string2.m_pChars.get(), string2.m_length + 1);
		tmp[string1.m_length + string2.m_length] = '\0';

		return CMyString(std::move(tmp), string1.m_length + string2.m_length);
	}
	catch (std::exception const&)
	{
		tmp.reset();
		throw;
	}
}

bool operator==(const CMyString& string1, const CMyString& string2)
{
	if (string1.m_length != string2.m_length)
	{
		return false;
	}
	return memcmp(string1.GetStringData(), string2.GetStringData(), string1.m_length) == 0;
}

bool operator!=(const CMyString& string1, const CMyString& string2)
{
	return !(string1 == string2);
}

bool operator<(const CMyString& string1, const CMyString& string2)
{
	int cmp = memcmp(string1.GetStringData(), string2.GetStringData(), std::min(string1.m_length, string2.m_length));
	return cmp == 0 ? string1.m_length < string2.m_length : cmp < 0;
}

bool operator>=(const CMyString& string1, const CMyString& string2)
{
	return !(string1 < string2);
}

bool operator>(const CMyString& string1, const CMyString& string2)
{
	int cmp = memcmp(string1.GetStringData(), string2.GetStringData(), std::min(string1.m_length, string2.m_length));
	return cmp == 0 ? string1.m_length > string2.m_length : cmp > 0;
}

bool operator<=(const CMyString& string1, const CMyString& string2)
{
	return !(string1 > string2);
}

std::istream& operator>>(std::istream& strm, CMyString& string)
{
	std::string str;
	strm >> str;
	string = str;

	return strm;
}

std::ostream& operator<<(std::ostream& strm, const CMyString& string)
{
	for (size_t i = 0; i < string.GetLength(); ++i)
	{
		strm << string[i];
	}
	return strm;
}
