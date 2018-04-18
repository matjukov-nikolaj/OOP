#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
#include "ICanvas.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint & center, double radius,
		const std::string & outlineColor,
		const std::string & fillColor);
	~CCircle();
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas & canvas) const override;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_radius;
	CPoint m_center;
};

