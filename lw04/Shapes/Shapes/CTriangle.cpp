#include "stdafx.h"
#include "CTriangle.h"
#include "Config.h"
#include "CUtilites.h"


CTriangle::CTriangle(const CPoint & v1, const CPoint & v2, const CPoint & v3,
	const std::string & outlineColor, const std::string & fillColor)
	: CSolidShape("Triangle", outlineColor, fillColor)
{
	if (abs(v1.GetXCoord() * (v2.GetYCoord() - v3.GetYCoord()) + v1.GetYCoord() * (v2.GetXCoord() - v3.GetXCoord())
		+ (v2.GetXCoord() * v3.GetYCoord()) - (v2.GetYCoord() * v3.GetXCoord())) < ABSOLUTE_ZERO)
	{
		throw std::invalid_argument("Incorrect points, you can not create a triangle");
	}
	m_firstVertex = v1;
	m_secondVertex = v2;
	m_thirdVertex = v3;
}

CTriangle::~CTriangle()
{
}

double CTriangle::GetPerimeter() const
{
	return (m_firstVertex.GetDistanceToPoint(m_secondVertex)
		+ m_secondVertex.GetDistanceToPoint(m_thirdVertex)
		+ m_thirdVertex.GetDistanceToPoint(m_firstVertex));
}

double CTriangle::GetArea() const
{
	return abs(HALF_DIGIT_ONE * 
		(m_firstVertex.GetXCoord() * (m_secondVertex.GetYCoord() - m_thirdVertex.GetYCoord())
		+ m_secondVertex.GetXCoord() * (m_thirdVertex.GetYCoord() - m_firstVertex.GetYCoord())
		+ m_thirdVertex.GetXCoord() * (m_firstVertex.GetYCoord() - m_secondVertex.GetYCoord())));
}

CPoint CTriangle::GetVertexFirst() const
{
	return m_firstVertex;
}

CPoint CTriangle::GetVertexSecond() const
{
	return m_secondVertex;
}

CPoint CTriangle::GetVertexThird() const
{
	return m_thirdVertex;
}

void CTriangle::Draw(ICanvas & canvas) const
{
	std::vector<CPoint> points = {
		GetVertexFirst(),
		GetVertexSecond(),
		GetVertexThird()
	};

	canvas.FillPolygon(points, CUtilites::StringToUInt(GetFillColor()));

	uint32_t outlineColor = CUtilites::StringToUInt(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[0], points[2], outlineColor);
}

void CTriangle::AppendProperties(std::ostream & strm) const
{
	strm << "\tfirst vertex = " << GetVertexFirst().ToString() << "\n"
		<< "\tsecond vertex = " << GetVertexSecond().ToString() << "\n"
		<< "\tthird vertex = " << GetVertexThird().ToString() << "\n";
}

bool CTriangle::OrientingAreaOfTriangleIsEqualZero(const CPoint & v1, const CPoint & v2, const CPoint & v3) const
{
	return (abs(v1.GetXCoord() * (v2.GetYCoord() - v3.GetYCoord())
		+ v1.GetYCoord() * (v2.GetXCoord() - v3.GetXCoord())
		+ (v2.GetXCoord() * v3.GetYCoord())
		- (v2.GetYCoord() * v3.GetXCoord())) < ABSOLUTE_ZERO);
}
