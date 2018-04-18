#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
#include "ICanvas.h"

class CTraingle : public CSolidShape
{
public:
	CTraingle(const CPoint & v1, const CPoint &v2, const CPoint& v3,
		const std::string & outlineColor, const std::string & fillColor);
	~CTraingle();
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetVertexFirst() const;
	CPoint GetVertexSecond() const;
	CPoint GetVertexThird() const;
	void Draw(ICanvas & canvas) const override;
protected:
	void AppendProperties(std::ostream & strm) const;
private:
	CPoint m_firstVertex;
	CPoint m_secondVertex;
	CPoint m_thirdVertex;
};

