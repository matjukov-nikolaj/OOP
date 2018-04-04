#pragma once
#include "CCar.h"

class CCarController : public CCar
{
public:
	CCarController(std::istream& input = std::cin, std::ostream& output = std::cout);
	bool HandleCommand();

private:
	void Info();
	bool EngineOn();
	bool EngineOff();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool TryGetNumber(std::istream & arg, int& number);

private:
	std::istream& m_input;
	std::ostream& m_output;
	const std::map<std::string, std::function<bool()>> m_engineHandler;
	const std::map<std::string, std::function<void()>> m_infoHandler;
	const std::map<std::string, std::function<bool(int number)>> m_handleSpeedAndGear;
};
