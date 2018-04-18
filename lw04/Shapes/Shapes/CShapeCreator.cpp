#include "stdafx.h"
#include "CShapeCreator.h"
#include "Config.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
using namespace std::placeholders;

CShapeCreator::CShapeCreator(std::istream& input)
	: m_actionMap({
		{ "line", bind(&CShapeCreator::CreateLine, this, _1) },
		{ "circle", bind(&CShapeCreator::CreateCircle, this, _1) },
		{ "rectangle", bind(&CShapeCreator::CreateRectangle, this, _1) },
		{ "triangle", bind(&CShapeCreator::CreateTriangle, this, _1) } })
	, m_input(input)
{
}

CShapeCreator::~CShapeCreator()
{
}

std::shared_ptr<IShape> CShapeCreator::HandleCommand() const
{
	std::string command;
	if (!std::getline(m_input, command))
	{
		return {};
	}
	std::transform(command.begin(), command.end(), command.begin(), tolower);
	std::istringstream strm(command);
	std::string figure;
	strm >> figure;

	auto it = m_actionMap.find(figure);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	throw std::exception("Unknown command");
}

std::shared_ptr<IShape> CShapeCreator::CreateLine(std::istringstream & strm) const
{
	CPoint start = GetPointFromInput(strm);
	CPoint end = GetPointFromInput(strm);
	std::string color;
	strm >> color;
	AddOpacityToColor(color);
	if (!IsValidColor(color))
	{
		throw std::invalid_argument("Invalid color");
	}
	AddOpacityToColor(color);
	return std::make_shared<CLineSegment>(start, end, color);
}

std::shared_ptr<IShape> CShapeCreator::CreateTriangle(std::istringstream & strm) const
{
	CPoint v1 = GetPointFromInput(strm);
	CPoint v2 = GetPointFromInput(strm);
	CPoint v3 = GetPointFromInput(strm);
	std::string outlineColor;
	std::string fillColor;
	strm >> outlineColor >> fillColor;
	if (!IsValidColor(outlineColor) || !IsValidColor(fillColor))
	{
		throw std::invalid_argument("Invalid color");
	}
	AddOpacityToColor(outlineColor);
	AddOpacityToColor(fillColor);
	return std::make_shared<CTriangle>(v1, v2, v3, outlineColor, fillColor);
}

std::shared_ptr<IShape> CShapeCreator::CreateRectangle(std::istringstream & strm) const
{
	CPoint leftTop = GetPointFromInput(strm);
	double width;
	double height;
	strm >> width >> height;
	std::string outlineColor;
	std::string fillColor;
	strm >> outlineColor >> fillColor;
	if (!IsValidColor(outlineColor) || !IsValidColor(fillColor))
	{
		throw std::invalid_argument("Invalid color");
	}
	AddOpacityToColor(outlineColor);
	AddOpacityToColor(fillColor);
	return std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}


std::shared_ptr<IShape> CShapeCreator::CreateCircle(std::istringstream & strm) const
{
	CPoint center = GetPointFromInput(strm);
	double radius;
	strm >> radius;
	std::string outlineColor;
	std::string fillColor;
	strm >> outlineColor >> fillColor;
	if (!IsValidColor(outlineColor) || !IsValidColor(fillColor))
	{
		throw std::invalid_argument("Invalid color");
	}
	AddOpacityToColor(outlineColor);
	AddOpacityToColor(fillColor);
	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

void CShapeCreator::AddOpacityToColor(std::string & color) const
{
	if (color.size() == VALID_COLOR_SIZE)
	{
		color += FULL_OPACITY;
	}
}

bool CShapeCreator::IsHexColor(const std::string &color)
{
	char ch = ' ';
	for (size_t i = 0; i < color.size(); ++i)
	{
		ch = color[i];
		if (!(ch >= '0' && ch <= '9') && !(ch >= 'a' && ch <= 'f'))
		{
			return false;
		}
	}
	return true;
}

CPoint CShapeCreator::GetPointFromInput(std::istringstream & strm)
{
	double x;
	double y;
	strm >> x >> y;
	CPoint point(x, y);
	return point;
}

bool CShapeCreator::IsValidColor(const std::string & color)
{
	return (((color.size() == VALID_COLOR_SIZE) 
		|| (color.size() == VALID_COLOR_SIZE_WITH_OPACITY)) 
		&& IsHexColor(color));
}
