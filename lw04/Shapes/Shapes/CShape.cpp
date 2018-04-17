#include "stdafx.h"
#include "CShape.h"


CShape::CShape(const std::string &type, const std::string &color)
	:m_type(type)
	,m_color(color)
{
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl << std::setprecision(10)
		<< "\tarea = " << GetArea() << std::endl
		<< "\tperimeter = " << GetPerimeter() << std::endl
		<< "\tcolor = " << GetOutlineColor() << std::endl;
	AppendProperties(strm);
	return strm.str();
}

std::string CShape::GetOutlineColor() const
{
	return m_color;
}

CShape::~CShape()
{
}
