#pragma once
class CComplex
{
public:
	// ������������� ������������ ����� ���������� �������������� � ������ ������
	CComplex(double real = 0, double image = 0);
	// ���������� �������������� ����� ������������ �����
	double Re() const;
	// ���������� ������ ����� ������������ �����
	double Im() const;
	// ���������� ������ ������������ �����
	double GetMagnitude() const;
	// ���������� �������� ������������ �����
	double GetArgument() const;
	// ���������� ����������� ����� � ������� ����
	
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
