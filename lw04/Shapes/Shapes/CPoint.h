#pragma once
class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	std::string ToString() const;
	double GetDistanceToPoint(const CPoint & point) const;
	double GetXCoord() const;
	double GetYCoord() const;
	void SetXCoord(double x);
	void SetYCoord(double y);
	~CPoint();
private:
	double m_x;
	double m_y;
};
