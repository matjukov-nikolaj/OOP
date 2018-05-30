#pragma once

class CMyString
{
public:
	// конструктор по умолчанию

	CMyString() = default;

	// конструктор, инициализирующий строку данными строки

	// с завершающим нулевым символом

	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из

	// символьного массива заданной длины

	CMyString(const char* pString, size_t length);

	// конструктор копирования

	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)

	// реализуется совместно с перемещающим оператором присваивания

	CMyString(CMyString&& other);

	// конструктор, инициализирующий строку данными из

	// строки стандартной библиотеки C++

	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки

	~CMyString() = default;

	// возвращает длину строки (без учета завершающего нулевого символа)

	size_t GetLength() const;

	// возвращает указатель на массив символов строки.

	// В конце массива обязательно должен быть завершающий нулевой символ

	// даже если строка пустая

	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)

	void Clear();

	//операторы
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
