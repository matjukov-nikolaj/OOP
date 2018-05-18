#pragma once
class CComplex
{
public:
	// инициализация комплексного числа значениями действительной и мнимой частей
	CComplex(double real = 0, double image = 0);
	// возвращает действительную часть комплексного числа
	double Re() const;
	// возвращает мнимую часть комплексного числа
	double Im() const;
	// возвращает модуль комплексного числа
	double GetMagnitude() const;
	// возвращает аргумент комплексного числа
	double GetArgument() const;
	// возвращает комплексное число в обычном виде
	
	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);
	CComplex& operator*=(const CComplex& complex);
	CComplex& operator/=(const CComplex& complex);

private:
	double m_real;
	double m_imaginary;
};

CComplex const operator+(const CComplex& complex1, const CComplex& complex2);
CComplex const operator-(const CComplex& complex1, const CComplex& complex2);
CComplex const operator*(const CComplex& complex1, const CComplex& complex2);
CComplex const operator/(const CComplex& complex1, const CComplex& complex2);
bool operator==(const CComplex& complex1, const CComplex& complex2);
bool operator!=(const CComplex& complex1, const CComplex& complex2);
std::istream& operator>>(std::istream& input, CComplex& complex);
std::ostream& operator<<(std::ostream& output, const CComplex& complex);
