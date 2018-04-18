#include "stdafx.h"
#include "CTraingle.h"
#include "Config.h"
#include "ConvertType.h"


CTraingle::CTraingle(const CPoint & v1, const CPoint & v2, const CPoint & v3,
	const std::string & outlineColor, const std::string & fillColor)
	: CSolidShape("Triangle", outlineColor, fillColor)
{
	if (abs(v1.GetXCoord() * (v2.GetYCoord() - v3.GetYCoord()) + v1.GetYCoord() * (v2.GetXCoord() - v3.GetXCoord())
		+ (v2.GetXCoord() * v3.GetYCoord()) - (v2.GetYCoord() * v3.GetXCoord())) < ABSOLUTE_ZERO)
	{
		throw std::exception("Incorrect points, you can not create a triangle");
	}
	m_firstVertex = v1;
	m_secondVertex = v2;
	m_thirdVertex = v3;
}

CTraingle::~CTraingle()
{
}

double CTraingle::GetPerimeter() const
{
	return (m_firstVertex.GetDistanceToPoint(m_secondVertex)
		+ m_secondVertex.GetDistanceToPoint(m_thirdVertex)
		+ m_thirdVertex.GetDistanceToPoint(m_firstVertex));
}

double CTraingle::GetArea() const
{
	return abs(HALF_DIGIT_ONE * 
		(m_firstVertex.GetXCoord() * (m_secondVertex.GetYCoord() - m_thirdVertex.GetYCoord())
		+ m_secondVertex.GetXCoord() * (m_thirdVertex.GetYCoord() - m_firstVertex.GetYCoord())
		+ m_thirdVertex.GetXCoord() * (m_firstVertex.GetYCoord() - m_secondVertex.GetYCoord())));
}

CPoint CTraingle::GetVertexFirst() const
{
	return m_firstVertex;
}

CPoint CTraingle::GetVertexSecond() const
{
	return m_secondVertex;
}

CPoint CTraingle::GetVertexThird() const
{
	return m_thirdVertex;
}

void CTraingle::Draw(ICanvas & canvas) const
{
	std::vector<CPoint> points = {
		GetVertexFirst(),
		GetVertexSecond(),
		GetVertexThird()
	};

	canvas.FillPolygon(points, StringToUInt(GetFillColor()));

	uint32_t outlineColor = StringToUInt(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[0], points[2], outlineColor);
}

void CTraingle::AppendProperties(std::ostream & strm) const
{
	strm << "\tfirst vertex = " << GetVertexFirst().ToString() << "\n"
		<< "\tsecond vertex = " << GetVertexSecond().ToString() << "\n"
		<< "\tthird vertex = " << GetVertexThird().ToString() << "\n";
}
