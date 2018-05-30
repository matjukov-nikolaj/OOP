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




// BadSportsman
CBadSportsman::CBadSportsman(std::string const & name, double height, double weight, bool throwExc)
	:m_name(name)
	, m_height(height)
	, m_weight(weight)
	, m_throwExc(throwExc)
{
}

CBadSportsman & CBadSportsman::operator=(const CBadSportsman & param)
{
	throw std::runtime_error("error");
}

bool operator==(const CBadSportsman & lhs, const CBadSportsman & rhs)
{
	return lhs.m_height == rhs.m_height
		&& lhs.m_name == rhs.m_name
		&& lhs.m_weight == rhs.m_weight;
}

bool operator<(const CBadSportsman & lhs, const CBadSportsman & rhs)
{
	if (lhs.m_throwExc || rhs.m_throwExc)
	{
		throw std::runtime_error("Error");
	}

	return lhs.m_height < rhs.m_height;
}
