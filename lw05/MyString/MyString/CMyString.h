#pragma once

class CMyString
{
public:
	// ����������� �� ���������

	CMyString() = default;

	// �����������, ���������������� ������ ������� ������

	// � ����������� ������� ��������

	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� ��

	// ����������� ������� �������� �����

	CMyString(const char* pString, size_t length);

	// ����������� �����������

	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)

	// ����������� ��������� � ������������ ���������� ������������

	CMyString(CMyString&& other);

	// �����������, ���������������� ������ ������� ��

	// ������ ����������� ���������� C++

	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������

	~CMyString() = default;

	// ���������� ����� ������ (��� ����� ������������ �������� �������)

	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.

	// � ����� ������� ����������� ������ ���� ����������� ������� ������

	// ���� ���� ������ ������

	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)

	void Clear();

	//���������
	CMyString& operator=(const CMyString& rhs);

	CMyString& operator=(CMyString&& other);

	CMyString operator+=(const CMyString & string);

	const char& operator[](size_t index) const;

	char& operator[](size_t index);

	friend CMyString operator+(CMyString const & str1, CMyString const & str2);

	friend bool operator==(const CMyString& string1, const CMyString& string2);

	friend bool operator!=(const CMyString& string1, const CMyString& string2);

	friend bool operator<(const CMyString& string1, const CMyString& string2);

	friend bool operator>=(const CMyString& string1, const CMyString& string2);

	friend bool operator>(const CMyString& string1, const CMyString& string2);

	friend bool operator<=(const CMyString& string1, const CMyString& string2);

private:
	CMyString(std::unique_ptr<char[]>&& pChars, size_t length);
	
private:
	std::unique_ptr<char[]> m_pChars = nullptr;

	size_t m_length = 0;
};

CMyString operator+(const CMyString& string1, const CMyString& string2);
std::istream& operator>>(std::istream& stream, CMyString& string);
std::ostream& operator<<(std::ostream& stream, const CMyString& string);
