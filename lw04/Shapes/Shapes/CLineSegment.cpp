#include "stdafx.h"
#include "CLineSegment.h"
#include "Config.h"


CLineSegment::CLineSegment(const CPoint & start, const CPoint & end, const std::string & color)
	: m_start(start)
	, m_end(end)
	, CShape("Line segment", color)
{
}

double CLineSegment::GetArea() const
{
	return ABSOLUTE_ZERO;
}

double CLineSegment::GetPerimeter() const
{
	return m_start.GetDistanceToPoint(m_end);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}

void CLineSegment::AppendProperties(std::ostream & strm) const
{
	strm << "\tstart = " << GetStartPoint().ToString() << "\n"
		<< "\tend = " << GetEndPoint().ToString() << "\n";
}

CLineSegment::~CLineSegment()
{
}
