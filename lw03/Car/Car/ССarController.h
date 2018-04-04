#pragma once
#include "CCar.h"

class ÑÑarController : public CCar
{
public:
	ÑÑarController(std::istream& input = std::cin, std::ostream& output = std::cout);
	bool HandleCommand();

private:
	std::istream& m_input;
	std::ostream& m_output;
	void Info();
	bool EngineOn();
	bool EngineOff();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	const std::map<std::string, std::function<bool()>> m_engineHandler;
	const std::map<std::string, std::function<void()>> m_infoHandler;
	const std::map<std::string, std::function<bool(int number)>> m_handleSpeedAndGear;
	bool TryGetNumber(std::istream & arg, int& number);
};

const std::map<CCar::MovementDirection, std::string> MOVEMENT_DIRECTION = {
	{ CCar::MovementDirection::Back, "back" },
	{ CCar::MovementDirection::Forward, "forward" },
	{ CCar::MovementDirection::Standing, "standing" }
};
