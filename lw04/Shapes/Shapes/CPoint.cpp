#include "stdafx.h"
#include "CPoint.h"
#include "CUtilites.h"
#include "Config.h"

CPoint::CPoint()
{
}

CPoint::CPoint(double x, double y)
	:m_x(x)
	,m_y(y)
{
}

std::string CPoint::ToString() const
{
	return "(" + CUtilites::DoubleToString(m_x) + ", " + CUtilites::DoubleToString(m_y) + ")";
}

double CPoint::GetDistanceToPoint(const CPoint &point) const
{
	return sqrt(pow((point.m_x - m_x), SECOND_DEGREE) + pow((point.m_y - m_y), SECOND_DEGREE));
}

double CPoint::GetXCoord() const
{
	return m_x;
}

double CPoint::GetYCoord() const
{
	return m_y;
}

void CPoint::SetXCoord(double x)
{
	m_x = x;
}

void CPoint::SetYCoord(double y)
{
	m_y = y;
}

CPoint::~CPoint()
{
}
