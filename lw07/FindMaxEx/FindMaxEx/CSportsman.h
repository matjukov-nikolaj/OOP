#pragma once
class CSportsman
{
public:
	CSportsman() = default;
	CSportsman(std::string const& name, double height, double weight);
	std::string GetName() const;
	double GetWeight() const;
	double GetHeight() const;
	void PrintSportsmanInfo(const CSportsman & sportsman);
private:
	std::string m_name;
	double m_height;
	double m_weight;
};


class CBadSportsman
{
public:
	CBadSportsman(std::string const & name = "Kek", double height = 1, double weight = 1, bool throwExc = false);
	friend bool operator==(const CBadSportsman& lhs, const CBadSportsman& rhs);
	friend bool operator<(const CBadSportsman& lhs, const CBadSportsman& rhs);
	CBadSportsman& operator=(const CBadSportsman& param);
	std::string m_name;
	double m_height;
	double m_weight;
	bool m_throwExc = false;
};

