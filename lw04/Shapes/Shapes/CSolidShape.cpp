#include "stdafx.h"
#include "CSolidShape.h"


CSolidShape::CSolidShape(const std::string & type, const std::string & outlineColor, const std::string & fillColor)
	: CShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

std::string CSolidShape::ToString() const
{
	return CShape::ToString();
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::AppendProperties(std::ostream & strm) const
{
	strm << "\tfill color = #" << m_fillColor << std::endl;
}

CSolidShape::~CSolidShape()
{
}
