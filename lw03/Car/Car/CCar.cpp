#include "stdafx.h"
#include "CCar.h"

bool CCar::IsTurnedOn()
{
	return m_engineIsTurnedOn;
}

bool CCar::TurnOnEngine()
{
	if (!m_engineIsTurnedOn)
	{
		m_engineIsTurnedOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_engineIsTurnedOn)
	{
		if (m_speed == 0 && m_gear == 0)
		{
			m_engineIsTurnedOn = false;
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
	const std::pair<int, int>& limits = SPEED_LIMITS[gear + 1];
	if (speed < limits.first || limits.second < speed)
	{
		return false;
	}
	return true;
}

bool CCar::SetGear(int gear)
{
	if (!m_engineIsTurnedOn && gear != static_cast<int>(Gear::Neutral))
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
	if (speed < 0)
	{
		return false;
	}

	if (!m_engineIsTurnedOn && speed != 0)
	{
		return false;
	}

	if (m_gear == 0 && std::abs(speed) > std::abs(m_speed))
	{
		return false;
	}

	if (m_gear == static_cast<int>(Gear::Reverse) || m_speed < 0)
	{
		speed = 0 - speed;
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
	return std::abs(m_speed);
}

CCar::MovementDirection CCar::GetMovementDirection() const
{
	if (m_speed < 0)
	{
		return MovementDirection::Back;
	}

	if (m_speed == 0)
	{
		return MovementDirection::Standing;
	}
	return MovementDirection::Forward;
}
