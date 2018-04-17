#include "stdafx.h"
#include "CRectangle.h"
#include "Config.h"

CRectangle::CRectangle(const CPoint & leftTop,
	double width, double height, 
	const std::string & outlineColor, 
	const std::string & fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, CSolidShape::CSolidShape("Rectangle", outlineColor, fillColor)
{
	if (width <= 0)
	{
		throw std::exception("The width can not be less than or equal to zero");
	}
	if (height <= 0)
	{
		throw std::exception("The height can not be less than or equal to zero");
	}
}

CRectangle::~CRectangle()
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return COEFFICENT_TWO * (m_width + m_height);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightTop() const
{
	return { m_leftTop.GetXCoord() + m_width, m_leftTop.GetYCoord() };
}

CPoint CRectangle::GetLeftBottom() const
{
	return { m_leftTop.GetXCoord(), m_leftTop.GetYCoord() + m_height };
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTop.GetXCoord() + m_width, m_leftTop.GetYCoord() + m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AppendProperties(std::ostream & strm) const
{
	strm << "\tleft top = " << GetLeftTop().ToString() << "\n"
		<< "\tleft bottom = " << GetLeftBottom().ToString() << "\n"
		<< "\tright top = " << GetRightTop().ToString() << "\n"
		<< "\tright bottom = " << GetRightBottom().ToString() << "\n"
		<< "\twidth = " << GetWidth() << "\n"
		<< "\theight = " << GetHeight() << "\n";
}