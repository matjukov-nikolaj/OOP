#include "stdafx.h"
#include "CComplex.h"

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_imaginary(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_imaginary;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(m_imaginary, 2) + pow(m_real, 2));
}

double CComplex::GetArgument() const
{
	if ((fabs(m_real) < DBL_EPSILON) && (fabs(m_imaginary) < DBL_EPSILON))
	{
		throw std::domain_error("The argument is not defined.");
	}
	return atan2(m_imaginary, m_real);
}

CComplex const operator+(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());
}

CComplex const operator-(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() - complex2.Re(), complex1.Im() - complex2.Im());
}

CComplex const operator*(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im(),
		complex1.Im() * complex2.Re() + complex1.Re() * complex2.Im());
}

CComplex const operator/(const CComplex& complex1, const CComplex& complex2)
{
	double denominator = (pow(complex2.Re(), 2) + pow(complex2.Im(), 2));
	return CComplex(
		((complex1.Re() * complex2.Re() + complex1.Im() * complex2.Im()) / denominator)
		, ((complex1.Im() * complex2.Re() - complex1.Re() * complex2.Im()) / denominator)
	);
}

CComplex const CComplex::operator+() const
{
	return *this;
}

CComplex const CComplex::operator-() const
{
	return CComplex(-m_real, -m_imaginary);
}

CComplex& CComplex::operator+=(const CComplex& complex)
{
	m_imaginary += complex.m_imaginary;
	m_real += complex.m_real;
	return *this;
}

CComplex& CComplex::operator-=(const CComplex& complex)
{
	m_imaginary -= complex.m_imaginary;
	m_real -= complex.m_real;
	return *this;
}

CComplex& CComplex::operator*=(const CComplex& complex)
{
	return *this = *this * complex;
}

CComplex& CComplex::operator/=(const CComplex& complex)
{
	return *this = *this / complex;
}

//bool CComplex::operator==(const CComplex& complex) const
//{
//	return fabs(complex.m_imaginary - m_imaginary) < DBL_EPSILON
//		&& fabs(complex.m_real - m_real) < DBL_EPSILON;
//}

bool operator==(double real, const CComplex& complex)
{
	return CComplex(real) == complex;
}

//bool CComplex::operator!=(const CComplex& complex) const
//{
//	return !(complex == *this);
//}

bool operator!=(double real, const CComplex& complex)
{
	return !(CComplex(real) == complex);
}

std::istream& operator>>(std::istream& input, CComplex& complex)
{
	double real = 0;
	double imaginary = 0;
	if ((input >> real) && (input >> imaginary) && (input.get() == 'i'))
	{
		complex = CComplex(real, imaginary);
	}
	return input;
}

std::ostream& operator<<(std::ostream& output, const CComplex& complex)
{
	output << complex.Re();
	double imaginary = complex.Im();
	if ((fabs(imaginary) > DBL_EPSILON))
	{
		output << "+";
	}
	output << imaginary << "i";
	return output;
}
