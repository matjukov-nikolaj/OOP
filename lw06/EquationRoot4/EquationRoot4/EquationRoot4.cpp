#include "stdafx.h"
#include "EquationRoot4.h"

double GetCoefficientP(double a, double c, double b)
{
	return (8 * a * c - 3 * pow(b, 2)) / (8 * pow(a, 2));
}

double GetCoefficientQ(double a, double b, double c, double d)
{
	double numerator = (8 * pow(a, 2) * d + pow(b, 3) - 4 * a * b * c);
	double denominator = (8 * pow(a, 3));
	return numerator / denominator;
}

double GetCoefficientR(double a, double b, double c, double d, double e)
{
	double numerator = (16 * a * pow(b, 2) * c - 64 * pow(a, 2) * b * d - 3 * pow(b, 4) + 256 * pow(a, 3) * e);
	double denominator = (256 * pow(a, 4));
	return numerator / denominator;
}

bool IsZero(double value)
{
	return abs(value) < DBL_EPSILON;
}

bool IsMoreZero(double value)
{
	return (value) > DBL_EPSILON;
}

bool IsLessZero(double value)
{
	return (value) < DBL_EPSILON;
}

std::vector<double> Solve3(double a1, double a2, double a3)
{
	std::vector<double> result;
	double Q = (3 * a2 - pow(a1, 2)) / 9;
	double R = (9 * a2 * a1 - 27 * a3 - 2 * pow(a1, 3)) / 54;
	double D = pow(Q, 3) + pow(R, 2);
	double S = cbrt(R + sqrt(D));
	double T = cbrt(R - sqrt(D));

	if (IsZero(D) && IsZero(R))
	{
		result.push_back(-a1 / 3);
	}

	if (IsZero(D) && !IsZero(R))
	{
		result.push_back(2 * cbrt(R) - a1/3);
		result.push_back(-cbrt(R) - a1/3);
	}

	if (IsMoreZero(D))
	{
		result.push_back(((-a1 / 3) + (S + T)));
	}

	if (IsLessZero(D))
	{
		double O = (acos(R / sqrt(pow(-Q, 3)))) / 3.0;
		result.push_back(2 * sqrt(-Q)*cos(O) - (a1 / 3));
		result.push_back(2 * sqrt(-Q)*cos(O + 2 * M_PI / 3) - (a1 / 3));
		result.push_back(2 * sqrt(-Q)*cos(O - 2 * M_PI / 3) - (a1 / 3));
	}

	return result;
}

double GetPositiveRoot(const std::vector<double> & realRoots)
{
	double z0 = DBL_EPSILON;
	for (size_t i = 0; i < realRoots.size(); ++i)
	{
		if (realRoots[i] > 0)
		{
			z0 = realRoots[i];
			break;
		}
	}
	return z0;
}

std::vector<double> GetSolve4RootsWhenQUnequalZero(double p, double q, double r)
{
	std::vector<double> result;
	double a1 = p;
	double a2 = (p*p - 4 * r) / 4;
	double a3 = -q * q / 8;
	std::vector<double> realRootsSolve3 = Solve3(a1, a2, a3);
	double z0 = GetPositiveRoot(realRootsSolve3);
	
	double d1 = 2 * z0 - 4 * ((p / 2) + z0 + (q / (2 * sqrt(2 * z0))));
	if (IsMoreZero(d1))
	{
		result.push_back((sqrt(2 * z0) + sqrt(d1)) / 2);
		result.push_back((sqrt(2 * z0) - sqrt(d1)) / 2);
	}
	if (IsZero(d1))
	{
		result.push_back(sqrt(2 * z0) / 2);
	}
	
	double d2 = 2 * z0 - 4 * ((p / 2) + z0 - (q / (2 * sqrt(2 * z0))));
	if (IsMoreZero(d2))
	{
		result.push_back((-sqrt(2 * z0) + sqrt(d2)) / 2);
		result.push_back((-sqrt(2 * z0) - sqrt(d2)) / 2);
	}
	if (IsZero(d2))
	{
		result.push_back(-sqrt(2 * z0) / 2);
	}

	return result;
}


double GetDescriminantOfQuadraticEquation(double a, double b, double c)
{
	return pow(b, 2) - 4 * a * c;
}

void Solve2WhenDescriminantNotLessThenZero(std::vector<double> &result, double D)
{
	if (D > 0)
	{
		result.push_back(sqrt(D/2));
		result.push_back(-sqrt(D/2));
	}
	else if (D == 0)
	{
		result.push_back(0);
	}
}

std::vector<double> GetSolve4RootsWhenQEqualZero(double p, double r)
{
	double descriminant = GetDescriminantOfQuadraticEquation(1.0, p, r);
	std::vector<double> result;
	if (descriminant >= 0)
	{
		Solve2WhenDescriminantNotLessThenZero(result, (-p - sqrt(descriminant)));
		Solve2WhenDescriminantNotLessThenZero(result, (-p + sqrt(descriminant)));
	}
	return result;
}

std::vector<double> GetSolve4Roots(double p, double q, double r)
{
	if (IsZero(q))
	{
		return GetSolve4RootsWhenQEqualZero(p, r);
	}
	else
	{
		return GetSolve4RootsWhenQUnequalZero(p, q, r);
	}
}

std::vector<double> GetXRoots(const std::vector<double> &depressedRoots, double a, double b)
{
	std::vector<double> result;
	for (size_t i = 0; i < depressedRoots.size(); ++i)
	{
		double element = (depressedRoots[i] - b / (4 * a));
		if (std::find(result.begin(), result.end(), element) == result.end())
		{
			result.push_back(element);
		}
	}
	return result;
}

std::vector<double> Solve4(double a, double b, double c, double d, double e)
{
	if (IsZero(a))
	{
		throw std::invalid_argument("The first coefficient can't be equal to zero");
	}

	double p = GetCoefficientP(a, c, b);
	double q = GetCoefficientQ(a, b, c, d);
	double r = GetCoefficientR(a, b, c, d, e);
	std::vector<double> yRoots = GetSolve4Roots(p, q, r);
	std::vector<double> roots = GetXRoots(yRoots, a, b);

	if (roots.empty())
	{
		throw std::domain_error("There are no real roots.");
	}
	return roots;
}

void PrintRoots(std::vector<double> const& roots, std::ostream &output)
{
	if (!roots.empty())
	{
		output << "Equation : ";
		for (size_t i = 0; i < roots.size(); i++)
		{
			output << roots[i] << " ";
		}
		output << "\n";
	}
}
