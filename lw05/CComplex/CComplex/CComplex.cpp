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
	double argument = 1.0 / atan2(m_imaginary, m_real);
	if (m_real < DBL_EPSILON && m_imaginary > DBL_EPSILON)
	{
		return M_PI + argument;
	}
	if (m_real < DBL_EPSILON && m_imaginary < DBL_EPSILON)
	{
		return -M_PI + argument;
	}
	return argument;
}

CComplex const CComplex::operator+(const CComplex& complex) const
{
	return CComplex(m_real + complex.m_real, m_imaginary + complex.m_imaginary);
}

CComplex const operator+(double real, const CComplex& complex)
{
	return CComplex(real) + complex;
}

CComplex const CComplex::operator-(const CComplex& complex) const
{
	return CComplex(m_real - complex.m_real, m_imaginary - complex.m_imaginary);
}

CComplex const operator-(double real, const CComplex& complex)
{
	return CComplex(real) - complex;
}

CComplex const CComplex::operator*(const CComplex& complex) const
{
	return CComplex(m_real * complex.m_real - m_imaginary * complex.m_imaginary,
		m_imaginary * complex.m_real + m_real * complex.m_imaginary);
}

CComplex const operator*(double real, const CComplex& complex)
{
	return CComplex(real) * complex;
}

CComplex const CComplex::operator/(const CComplex& complex) const
{
	double denominator = (pow(complex.m_real, 2) + pow(complex.m_imaginary, 2));
	return CComplex(
		((m_real * complex.m_real + m_imaginary * complex.m_imaginary) / denominator)
		, ((m_imaginary * complex.m_real - m_real * complex.m_imaginary) / denominator)
	);
}

CComplex const operator/(double real, const CComplex& complex)
{
	return CComplex(real) / complex;
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

bool CComplex::operator==(const CComplex& complex) const
{
	return fabs(complex.m_imaginary - m_imaginary) < DBL_EPSILON 
			&& fabs(complex.m_real - m_real) < DBL_EPSILON;
}

bool operator==(double real, const CComplex& complex)
{
	return CComplex(real) == complex;
}

bool CComplex::operator!=(const CComplex& complex) const
{
	return !(complex == *this);
}

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
