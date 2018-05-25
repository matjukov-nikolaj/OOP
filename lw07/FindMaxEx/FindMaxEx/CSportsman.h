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

