#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint & leftTop,
		double width, double height,
		const std::string & outlineColor,
		const std::string & fillColor);
	~CRectangle();
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightTop() const;
	CPoint GetLeftBottom() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_width = 0;
	double m_height = 0;
	CPoint m_leftTop;
};

