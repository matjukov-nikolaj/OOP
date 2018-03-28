#include "stdafx.h"
#include "CCar.h"

static const std::vector<std::pair<int, int>> SPEED_LIMITS = {
	{ 0, 20 },
	{ INT_MIN, INT_MAX },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 }
};

bool CCar::IsTurnedOn()
{
	return m_engine_is_turned_on;
}

bool CCar::TurnOnEngine()
{
	if (!m_engine_is_turned_on)
	{
		m_engine_is_turned_on = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_engine_is_turned_on)
	{
		if (m_speed == 0 && m_gear == 0)
		{
			m_engine_is_turned_on = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CCar::SpeedIsRangeOfGear(int speed, int gear)
{
	const std::pair<int, int> & limits = SPEED_LIMITS[gear + 1];
	if (speed < limits.first || limits.second < speed)
	{
		return false;
	}
	return true;
}

bool CCar::SetGear(int gear)
{
	if (!m_engine_is_turned_on && gear != static_cast<int>(Gear::Neutral))
	{
		return false;
	}

	if (gear == static_cast<int>(Gear::Reverse) && m_speed != 0)
	{
		return false;
	}

	if (gear < static_cast<int>(Gear::Reverse) || gear > static_cast<int>(Gear::Fifth))
	{
		return false;
	}

	if (!SpeedIsRangeOfGear(m_speed, gear))
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_engine_is_turned_on && speed != 0)
	{
		return false;
	}

	if (m_gear == 0 && speed > m_speed)
	{
		return false;
	}

	if (!SpeedIsRangeOfGear(speed, m_gear))
	{
		return false;
	}

	m_speed = speed;
	return true;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

CCar::MovementDirection CCar::GetMovementDirection() const
{
	if (m_speed > 0 && m_gear == static_cast<int>(static_cast<int>(Gear::Neutral)))
	{
		return MovementDirection::Back;
	}

	if (m_speed == 0)
	{
		return MovementDirection::Standing;
	}
	return MovementDirection::Forward;
}
