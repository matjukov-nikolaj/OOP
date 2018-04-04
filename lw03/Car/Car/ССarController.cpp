#include "stdafx.h"
#include "ÑÑarController.h"

CCarController::CCarController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_engineHandler({
		  { "EngineOn", [&]() { return EngineOn(); } },
		  { "EngineOff", [&]() { return EngineOff(); } },
	  })
	, m_infoHandler({
		  { "Info", [&]() { Info(); } },
	  })
	, m_handleSpeedAndGear({
		  { "SetSpeed", [&](int number) { return SetSpeed(number); } },
		  { "SetGear", [&](int number) { return SetGear(number); } },
	  })
{
}

static const std::map<CCar::MovementDirection, std::string> MOVEMENT_DIRECTION = {
	{ CCar::MovementDirection::Back, "back" },
	{ CCar::MovementDirection::Forward, "forward" },
	{ CCar::MovementDirection::Standing, "standing" }
};

void CCarController::Info()
{
	m_output << "  Engine     :   " << (CCar::IsTurnedOn() ? "On" : "Off") << "\n"
			 << "  Gear       :   " << (CCar::GetGear()) << "\n"
			 << "  Speed      :   " << (CCar::GetSpeed()) << "\n"
			 << "  Direction  :   " << (MOVEMENT_DIRECTION.at(CCar::GetMovementDirection())) << "\n";
}

bool CCarController::EngineOn()
{
	if (CCar::TurnOnEngine())
	{
		m_output << "  Engine     :   On"
				 << "\n";
		return true;
	}
	m_output << "  Failed to on engine."
			 << "\n";
	return false;
}

bool CCarController::EngineOff()
{
	if (CCar::TurnOffEngine())
	{
		m_output << "  Engine     :   Off"
				 << "\n";
		return true;
	}
	m_output << "  Failed to off engine."
			 << "\n";
	return false;
}

bool CCarController::SetGear(int gear)
{
	if (CCar::SetGear(gear))
	{
		m_output << "  Gear       :   " << gear << "\n";
		return true;
	}
	m_output << "  Failed to set gear."
			 << "\n";
	return false;
}

bool CCarController::SetSpeed(int speed)
{
	if (CCar::SetSpeed(speed))
	{
		m_output << "  Speed      :   " << speed << "\n";
		return true;
	}
	m_output << "  Failed to set speed."
			 << "\n";
	return false;
}

bool CCarController::HandleCommand()
{
	std::string command;
	std::getline(m_input, command);
	std::istringstream line(command);
	std::string action;
	line >> action;

	auto itEngine = m_engineHandler.find(action);
	if (itEngine != m_engineHandler.end())
	{
		return itEngine->second();
	}

	auto itInfo = m_infoHandler.find(action);
	if (itInfo != m_infoHandler.end())
	{
		itInfo->second();
		return true;
	}

	auto itSpeedAndGear = m_handleSpeedAndGear.find(action);
	if (itSpeedAndGear != m_handleSpeedAndGear.end())
	{
		int number;
		if (TryGetNumber(line, number))
		{
			return itSpeedAndGear->second(number);
		}
		else
		{
			m_output << "  No entered number." << "\n";
			return false;
		}
	}
	m_output << "  Unknown command"
			 << "\n";
	return false;
}

bool CCarController::TryGetNumber(std::istream& arg, int& number)
{
	std::string argString;
	arg >> argString;
	if (argString.empty())
	{
		return false;
	}
	number = std::stoi(argString);
	return true;
}
