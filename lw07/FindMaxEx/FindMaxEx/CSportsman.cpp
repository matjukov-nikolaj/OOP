#include "stdafx.h"
#include "CSportsman.h"


CSportsman::CSportsman(std::string const & name, double height, double weight)
	: m_name(name)
	, m_height(height)
	, m_weight(weight)
{
}

std::string CSportsman::GetName() const
{
	return m_name;
}

double CSportsman::GetWeight() const
{
	return m_weight;
}

double CSportsman::GetHeight() const
{
	return m_height;
}

void CSportsman::PrintSportsmanInfo(const CSportsman & sportsman)
{
	std::cout << sportsman.GetName() << " " << sportsman.GetWeight() << " " << sportsman.GetHeight() << "\n";
}
