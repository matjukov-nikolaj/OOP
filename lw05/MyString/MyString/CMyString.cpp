#include "stdafx.h"
#include "CMyString.h"

CMyString::CMyString(const char* pString)
	:CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_pChars = std::make_unique<char[]>(length + 1);
	memcpy(m_pChars.get(), pString, length + 1);
	m_length = length;
	m_pChars[length] = '\0';
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
	:CMyString(stlString.c_str(), stlString.length())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	const char zeroLengthString[] = "";
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
	if (m_pChars)
	{
		m_pChars.reset();
	}
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

CMyString const CMyString::operator+(const CMyString& string) const
{
	auto tmp = std::make_unique<char[]>(m_length + string.m_length + 1);
	memcpy(tmp.get(), m_pChars.get(), m_length);
	memcpy(tmp.get() + m_length, string.m_pChars.get(), string.m_length + 1);
	tmp[m_length + string.m_length] = '\0';

	return CMyString(tmp.get(), m_length + string.m_length);
}

CMyString const operator+(const std::string& string1, const CMyString& string2)
{
	return CMyString(string1) + string2;
}

CMyString const operator+(const char* string1, const CMyString& string2)
{
	return CMyString(string1) + string2;
}

CMyString const CMyString::operator+=(const CMyString& string)
{
	return *this = *this + string;
}

bool CMyString::operator==(const CMyString& string) const
{
	if (m_length != string.m_length)
	{
		return false;
	}

	return memcmp(m_pChars.get(), string.m_pChars.get(), m_length) == 0;
}

bool CMyString::operator!=(const CMyString& string) const
{
	return !(*this == string);
}

char const& CMyString::operator[](size_t index) const
{
	if ((index >= m_length) || (index < 0))
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	if ((index >= m_length) || (index < 0))
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

bool CMyString::operator<(const CMyString& string) const
{
	if (m_length == string.m_length)
	{
		return (memcmp(m_pChars.get(), string.m_pChars.get(), m_length) < 0);
	}
	return (m_length < string.m_length);
}

bool CMyString::operator>=(const CMyString& string) const
{
	return !(*this < string);
}

bool CMyString::operator>(const CMyString& string) const
{
	if (m_length == string.m_length)
	{
		return (memcmp(m_pChars.get(), string.m_pChars.get(), m_length) > 0);
	}
	return (m_length > string.m_length);
}

bool CMyString::operator<=(const CMyString& string) const
{
	return !(*this > string);
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
	strm << string.GetStringData();

	return strm;
}
